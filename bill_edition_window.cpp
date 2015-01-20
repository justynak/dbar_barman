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

    if(!(this->waiter))
        connect(ui->button_print_bill, &QPushButton::clicked, this, &bill_edition_window::goto_bill_print);
    else
        connect(ui->button_tables, &QPushButton::clicked, this, &bill_edition_window::on_button_tables_clicked);


    update_product_list();

    QSqlQuery query;
    query.exec("SELECT pesel FROM `d_kelner`");

    ui->label_logged_as->setText(query.value(0).toString());
}

bill_edition_window::~bill_edition_window()
{
    delete ui;
}

void bill_edition_window::update_product_list()
{
    //get all products from database and display
    list_products.append(product(tr("Żywiec"), 10.0, 29));
    list_products.append(product(tr("Wódka shot"), 6.0, 5));
    list_products.append(product(tr("Herbata"), 7.5, 1));
    list_products.append(product(tr("Piwo z sokiem"), 13, 3));
    list_products.append(product(tr("Woda gazowana"), 6, 1));

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
    this->waiter = waiter;
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

void bill_edition_window::on_button_tables_clicked()
{
}
