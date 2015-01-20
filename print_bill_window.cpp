#include "print_bill_window.h"
#include "ui_print_bill_window.h"

print_bill_window::print_bill_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::print_bill_window)
{
    ui->setupUi(this);

    QPalette Pal(palette());
    // set black background
    Pal.setColor(QPalette::Background, QColor(100, 149, 237));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    db = database_connector::get_instance();

    connect(ui->button_ok, &QPushButton::clicked, this, &print_bill_window::on_button_ok_clicked);
    connect(ui->button_ok, &QPushButton::clicked, this, &print_bill_window::bill_closed);
}

print_bill_window::~print_bill_window()
{
    delete ui;
}

void print_bill_window::on_button_ok_clicked()
{
    db->remove_bill(this->bill_number);
    emit bill_closed();
}

void print_bill_window::on_button_discard_clicked()
{

}
