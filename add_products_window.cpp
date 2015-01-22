#include "add_products_window.h"
#include "ui_add_products_window.h"

add_products_window::add_products_window(QString bill, QWidget *parent) :
    QWidget(parent), bill_selected(bill),
    ui(new Ui::add_products_window)
{
    ui->setupUi(this);

    db = database_connector::get_instance();
    get_categories();


    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(100, 149, 237));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    QPalette pal = ui->button_add->palette();
    pal.setBrush(QPalette::ButtonText, Qt::white);

    ui->button_add->setPalette(pal);
    ui->button_add->setStyleSheet("*{background-color: rgb(70,130,180)}");
    ui->button_add->update();

    ui->button_approve->setPalette(pal);
    ui->button_approve->setStyleSheet("*{background-color: rgb(70,130,180)}");
    ui->button_approve->update();

    ui->button_discard->setPalette(pal);
    ui->button_discard->setStyleSheet("*{background-color: rgb(70,130,180)}");
    ui->button_discard->update();

    ui->button_remove->setPalette(pal);
    ui->button_remove->setStyleSheet("*{background-color: rgb(70,130,180)}");
    ui->button_remove->update();

    pal.setBrush(QPalette::WindowText, Qt::white);
    ui->label->setPalette(pal);
    ui->label_available->setPalette(pal);
    ui->label_number->setPalette(pal);

    number_of_current_product = 0;
    max_number_of_current_product = 0;
    chosed_product= 0;
    ui->label_number->setText(tr("%1").arg(number_of_current_product));

    connect(ui->box_categories, SIGNAL(highlighted(int)), this, SLOT(get_products(int)));
    connect(ui->box_products, SIGNAL(highlighted(int)), this, SLOT(set_product(int)));

    //connect(ui->button_add, &QPushButton::clicked, this, &add_products_window::on_button_add_clicked);
    connect(ui->button_remove, &QPushButton::clicked, this, &add_products_window::on_button_remove_clicked);

    //connect(ui->button_approve, &QPushButton::clicked, this, &add_products_window::on_button_approve_clicked);
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
    chosed_product = highlighted;
    max_number_of_current_product = product_list[highlighted].get_number_of_products();
    ui->label_available->setText(tr("Dostępna liczba: %1").arg(max_number_of_current_product));
}


add_products_window::~add_products_window()
{
    delete ui;
}


void add_products_window::on_button_approve_clicked()
{
    //update db
    product p = product_list[chosed_product];
    p.set_number_of_products(number_of_current_product);
    db->add_product(p, bill_selected);
    ui->label_number->setText(tr("%1").arg(number_of_current_product));

    emit return_to_bill_edition_window();
}

void add_products_window::on_button_add_clicked()
{
    number_of_current_product +=1;
    if(number_of_current_product > max_number_of_current_product)
        number_of_current_product = max_number_of_current_product;

    ui->label_number->setText(tr("%1").arg(number_of_current_product));
}

void add_products_window::on_button_remove_clicked()
{
    number_of_current_product -=1;
    if(number_of_current_product < 0)
        number_of_current_product = 0;
    ui->label_number->setText(tr("%1").arg(number_of_current_product));
}

void add_products_window::on_button_discard_clicked()
{
    emit return_to_bill_edition_window();
}
