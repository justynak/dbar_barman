#include "bill_edition_window.h"
#include "ui_bill_edition_window.h"
#include <QtSql>
#include <QDate>
#include "tables_window.h"

#define COL_PRODUCT     0
#define COL_ADD_ONE     1
#define COL_REMOVE_ONE  3
#define COL_NUMBER      2
#define COL_PRICE       4
#define COL_DELETE      5


bill_edition_window::bill_edition_window(waiter *w_p, bartender *b_r, employee* a_p ,  QWidget *parent) :
    QWidget(parent),
    w(w_p), br(b_r), active(a_p),
    ui(new Ui::bill_edition_window)
{
    ui->setupUi(this);

    QPalette Pal(palette());
    // set black background
    Pal.setColor(QPalette::Background, QColor(100, 149, 237));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    ui->product_list->setRowCount(0);
    ui->product_list->setColumnCount(6);
    ui->product_list->setColumnWidth(COL_PRODUCT, 300);
    ui->product_list->setColumnWidth(COL_ADD_ONE, 40);
    ui->product_list->setColumnWidth(COL_REMOVE_ONE, 40);
    ui->product_list->setColumnWidth(COL_DELETE, 60);

    QStringList a;
    a<<"Produkt"<<""<<"Ilość"<<""<<"Cena"<<"Usuń";

    ui->product_list->setHorizontalHeaderLabels(a);

    connect(ui->product_list, &QTableWidget::cellClicked, this, &bill_edition_window::manage_click);
    connect(ui->button_add_product, &QPushButton::clicked, this, &bill_edition_window::add_product_slot);
    connect(ui->button_tables, &QPushButton::clicked, this, &bill_edition_window::goto_table_edition);
    connect(ui->button_print_bill, &QPushButton::clicked, this, &bill_edition_window::send_bill_print_signal);
    connect(ui->button_logging, &QPushButton::clicked, this, &bill_edition_window::goto_logging);
    connect(ui->button_new_bill,&QPushButton::clicked, this, &bill_edition_window::add_bill);
    connect(ui->button_delete_bill, &QPushButton::clicked, this, &bill_edition_window::on_button_delete_bill_clicked);

    connect(ui->box_bills, SIGNAL(highlighted(QString)), this, SLOT(update_product_list(QString)));


    db = database_connector::get_instance();

    list_bills = db->get_bills(br->get_pesel(), w->get_pesel());

    for(int i=0; i<list_bills.size(); ++i)
    {
        QString number = list_bills[i].get_bill_number();
        QString card = list_bills[i].get_card_number();
        QString date = list_bills[i].get_date();
        ui->box_bills->addItem(tr("%1\t%2\t%3").arg(number).arg(card).arg(date));
    }

    QString s;
    if (active->is_waiter()) s = tr("Zalogowany jako: kelner %1 %2").arg(active->get_name()).arg(active->get_surname());
    else s = tr("Zalogowany jako: barman %1 %2").arg(active->get_name()).arg(active->get_surname());
    ui->label_logged_as->setText(s);
}

bill_edition_window::~bill_edition_window()
{
    delete ui;
}

void bill_edition_window::update_product_list(QString index)
{
    bill_selected = index;
    list_products.clear();
    list_products = db->get_products_from_bill(index);
    ui->product_list->clear();

    QStringList a;
    a<<"Produkt"<<""<<"Ilość"<<""<<"Cena"<<"Usuń";

    ui->product_list->setHorizontalHeaderLabels(a);
    ui->product_list->setRowCount(0);


    for(int i=0; i<list_products.count(); ++i)
    {
        QTableWidgetItem* item[6];
        for(int k=0; k<6; ++k)
            item[k] = new QTableWidgetItem();

        ui->product_list->insertRow(i);
        item[COL_PRODUCT]->setText(list_products[i].get_name());
        item[COL_ADD_ONE]->setText(tr("+"));
        item[COL_NUMBER]->setText(tr("%1").arg(list_products[i].get_number_of_products()));
        item[COL_REMOVE_ONE]->setText(tr("-"));
        item[COL_PRICE]->setText(tr("%1").arg(list_products[i].get_price()));
        item[COL_DELETE]->setText(tr("X"));

        for(unsigned int j=0; j<6; ++j)
            ui->product_list->setItem(i, j, item[j]);
    }

    value = 0;

    foreach(product p, list_products)
        value += p.get_price() * p.get_number_of_products();

    ui->label_value->setText(tr("%1").arg(value));

    QString client = db->get_client(bill_selected);
    ui->label_client_number->setText(tr("Stały klient nr: %1").arg(client));
}

void bill_edition_window::update_product_number(int p, int number)
{
    //set the new number
    QTableWidgetItem* item = ui->product_list->item(p, COL_NUMBER);

    int newnumber = item->text().toInt() + number;

    if(newnumber >=1)
    {
        product pr = list_products[p];
        if( db->change_number_of_products(&pr, bill_selected, number))
        {
            list_products[p].set_number_of_products(newnumber);
            item->setText(tr("%1").arg(newnumber));
        }

        //update the bill cost
        value += pr.get_price() * number;
        ui->label_value->setText(tr("%1").arg(value));
    }
}

void bill_edition_window::remove_product(int pr_n)
{
    //remove the product from list
    product pr = list_products[pr_n];
    int number = pr.get_number_of_products();

    value -= pr.get_price() * number;

    db->remove_product(pr, bill_selected);
    list_products.removeAt(pr_n);
    ui->product_list->removeRow(pr_n);

    ui->label_value->setText(tr("%1").arg(value));
}

void bill_edition_window::add_product()
{

}

void bill_edition_window::manage_click(int row, int col)
{
    switch(col)
    {
        //case COL_PRODUCT: break;
        case COL_ADD_ONE:
            //dodaj jeden
            update_product_number(row, 1);
        break;

        //case COL_NUMBER: break;

        case COL_REMOVE_ONE:
            //usun o jeden
            update_product_number(row, -1);
        break;

        //case COL_PRICE: break;

        case COL_DELETE:
            //usun wpis
            remove_product(row);
        break;
    }
}

void bill_edition_window::send_bill_print_signal()
{
    emit goto_bill_print(this->bill_selected);
}

void bill_edition_window::add_bill()
{
    QDate dat = QDate::currentDate();
    QString d = dat.toString(Qt::ISODate);

    bill b("", "", w->get_pesel(), br->get_pesel(), d);

    db->add_bill(&b);

    bill_selected = b.get_bill_number();
    QString number = b.get_bill_number();
    QString card = b.get_card_number();
    QString date = b.get_date();
    ui->box_bills->addItem(tr("%1\t%2\t%3").arg(number).arg(card).arg(date));
    list_bills.append(b);
    int size = list_bills.size();
    ui->box_bills->setCurrentIndex(size -1);
}

void bill_edition_window::add_product_slot()
{
    emit goto_product_add(bill_selected);
}


void bill_edition_window::on_button_scan_client_card_clicked()
{
    db->set_random_client(bill_selected);
    QString client = db->get_client(bill_selected);
    ui->label_client_number->setText(tr("Stały klient numer: %1").arg(client));
}

void bill_edition_window::on_button_delete_bill_clicked()
{
    foreach (product p, list_products)
    {
        db->remove_product(p, bill_selected);
        list_products.removeFirst();
    }
    db->remove_bill(bill_selected);

    list_bills = db->get_bills(br->get_pesel(), w->get_pesel());
    ui->box_bills->clear();

    for(int i=0; i<list_bills.size(); ++i)
    {
        QString number = list_bills[i].get_bill_number();
        QString card = list_bills[i].get_card_number();
        QString date = list_bills[i].get_date();
        ui->box_bills->addItem(tr("%1\t%2\t%3").arg(number).arg(card).arg(date));
    }
    value = 0;
    ui->label_value->setText(tr("%1").arg(value));
}
