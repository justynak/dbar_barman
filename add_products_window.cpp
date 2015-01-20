#include "add_products_window.h"
#include "ui_add_products_window.h"

add_products_window::add_products_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_products_window)
{
    ui->setupUi(this);

    db = database_connector::get_instance();
    get_categories();

    connect(ui->box_categories, SIGNAL(highlighted(int)), this, SLOT(get_products(int)));
    connect(ui->box_products, SIGNAL(highlighted(int)), this, SLOT(set_product(int)));

    connect(ui->button_add, &QPushButton::clicked, this, &add_products_window::on_button_add_clicked);
    connect(ui->button_remove, &QPushButton::clicked, this, &add_products_window::on_button_remove_clicked);

    connect(ui->button_approve, &QPushButton::clicked, this, &add_products_window::on_button_approve_clicked);
    connect(ui->button_discard, &QPushButton::clicked, this, &add_products_window::on_button_discard_clicked);
}

void add_products_window::get_categories()
{
    category_list.clear();
    category_list = db->get_categories();
    ui->box_categories->clear();

    foreach(QString cat, category_list)
        ui->box_categories->addItem(cat);
}

void add_products_window::set_access_rights(employee *e)
{

}

void add_products_window::get_products(int highlighted)
{
    //from db
    QString cat = category_list[highlighted];

    product_list.clear();
    product_list = db->get_products_by_category(cat);

    //delete the products from combobox
    ui->box_products->clear();

    //print products from selected category from db
    foreach(product p, product_list)
    {
        ui->box_products->addItem(tr("%1").arg(p.get_name()));
    }
}

void add_products_window::set_product(int highlighted)
{
    QString number = tr("%1").arg(product_list[highlighted].get_number_of_products());
    ui->label_available->setText(tr("Dostępna liczba: %1").arg(number));
}


add_products_window::~add_products_window()
{
    delete ui;
}


void add_products_window::on_button_approve_clicked()
{
    //update db
   // emit on_product_chosen(prod);
}

void add_products_window::on_button_add_clicked()
{
   // int current_number = prod.get_number_of_products() + 1;
   // prod.set_number_of_products(current_number);
   // ui->label_number->setText(tr("%1").arg(current_number));

    //+ zapytanie sql
}

void add_products_window::on_button_remove_clicked()
{
   // int current_number = prod.get_number_of_products() - 1;
   // prod.set_number_of_products(current_number);
    //ui->label_number->setText(tr("%1").arg(current_number));

    //+ zapytanie sql
}

void add_products_window::on_button_discard_clicked()
{
    emit return_to_bill_edition_window();
}
