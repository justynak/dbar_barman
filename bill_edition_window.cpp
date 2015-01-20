#include "bill_edition_window.h"
#include "ui_bill_edition_window.h"
#include <QtSql>
#include "tables_window.h"

#define COL_PRODUCT     0
#define COL_ADD_ONE     1
#define COL_REMOVE_ONE  3
#define COL_NUMBER      2
#define COL_PRICE       4
#define COL_DELETE      5


bill_edition_window::bill_edition_window(QWidget *parent) :
    QWidget(parent),
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
    a.append(tr("Produkt"));
    a.append(tr(""));
    a.append(tr("Ilość"));
    a.append(tr(""));
    a.append(tr("Cena"));
    a.append(tr("Usuń"));

    ui->product_list->setHorizontalHeaderLabels(a);

    connect(ui->product_list, &QTableWidget::cellClicked, this, &bill_edition_window::manage_click);
    connect(ui->button_add_product, &QPushButton::clicked, this, &bill_edition_window::goto_product_add);
    connect(ui->button_tables, &QPushButton::clicked, this, &bill_edition_window::goto_table_edition);
    connect(ui->button_print_bill, &QPushButton::clicked, this, &bill_edition_window::goto_bill_print);
    connect(ui->button_logging, &QPushButton::clicked, this, &bill_edition_window::goto_logging);

    connect(ui->box_bills, SIGNAL(highlighted(QString)), this, SLOT(update_product_list(QString)));


    db = database_connector::get_instance();

    list_bills = db->get_bills("87020586446", "8511273456");


    for(int i=0; i<list_bills.size(); ++i)
    {
        QString number = list_bills[i].get_bill_number();
        QString card = list_bills[i].get_card_number();
        QString date = list_bills[i].get_date();
        ui->box_bills->addItem(tr("%1\t%2\t%3").arg(number).arg(card).arg(date));
    }
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
}

void bill_edition_window::update_product_number(int product, int number)
{
    //set the new number
    QTableWidgetItem* item = ui->product_list->item(product, COL_NUMBER);
    int newnumber = item->text().toInt() + number;

    if(newnumber >=1)
    {
        list_products[product].set_number_of_products(newnumber);
        item->setText(tr("%1").arg(newnumber));
    }

    //update the number to database
}

void bill_edition_window::remove_product(int product)
{
    //remove the product from list
    list_products.removeAt(product);
    ui->product_list->removeRow(product);

    //update the db

}

void bill_edition_window::add_product()
{

}

void bill_edition_window::set_employee(bool waiter)
{
    /*
    if(!initialized)
    {
        this->waiter = waiter;

        if(this->waiter)
        {
            connect(ui->button_tables, &QPushButton::clicked, this, &bill_edition_window::goto_table_edition);
            disconnect(ui->button_print_bill, &QPushButton::clicked, this, &bill_edition_window::goto_bill_print);
        }
        else
        {
            connect(ui->button_print_bill, &QPushButton::clicked, this, &bill_edition_window::goto_bill_print);
            disconnect(ui->button_tables, &QPushButton::clicked, this, &bill_edition_window::goto_table_edition);
        }
        initialized = true;
    }
*/
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

