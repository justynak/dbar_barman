#include "print_bill_window.h"
#include "ui_print_bill_window.h"

print_bill_window::print_bill_window(QString b, QWidget *parent) :
   bill_number(b), QWidget(parent),
    ui(new Ui::print_bill_window)
{
    ui->setupUi(this);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(100, 149, 237));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    QPalette pal = ui->button_ok->palette();
    pal.setBrush(QPalette::ButtonText, Qt::white);

    ui->button_ok->setPalette(pal);
    ui->button_ok->setStyleSheet("*{background-color: rgb(70,130,180)}");
    ui->button_ok->update();

    ui->button_discard->setPalette(pal);
    ui->button_discard->setStyleSheet("*{background-color: rgb(70,130,180)}");
    ui->button_discard->update();

    pal.setBrush(QPalette::WindowText, Qt::white);
    ui->label->setPalette(pal);
    ui->label_2->setPalette(pal);
    ui->label_bill_number->setPalette(pal);
    ui->label_value->setPalette(pal);

    db = database_connector::get_instance();
    product_list.clear();
    product_list = db->get_products_from_bill(bill_number);
    ui->table_costs->setRowCount(0);
    ui->table_costs->setColumnCount(3);
    value = 0;

    for(int i=0; i<product_list.count(); ++i)
    {
        QTableWidgetItem* item[3];
        for(int k=0; k<3; ++k)
        {
            item[k] = new QTableWidgetItem();
            item[k]->setFlags(item[k]->flags() ^ Qt::ItemIsEditable);
        }

        double price = product_list[i].get_price();
        int number = product_list[i].get_number_of_products();

        ui->table_costs->insertRow(i);
        item[0]->setText(product_list[i].get_name());
        item[1]->setText(tr("%1").arg(number));
        item[2]->setText(tr("%1").arg(price));

        for(unsigned int j=0; j<3; ++j)
            ui->table_costs->setItem(i, j, item[j]);
        value+= number * price;
    }

    ui->label_value->setText(tr("%1").arg(value));
    ui->label_bill_number->setText(bill_number);

    connect(ui->button_ok, &QPushButton::clicked, this, &print_bill_window::on_button_ok_clicked);
    connect(ui->button_discard, &QPushButton::clicked, this, &print_bill_window::bill_closed);
}

print_bill_window::~print_bill_window()
{
    delete ui;
}

void print_bill_window::on_button_ok_clicked()
{
    db->close_bill(bill_number);
    emit bill_closed();
}

void print_bill_window::on_button_discard_clicked()
{

}
