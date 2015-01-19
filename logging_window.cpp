#include "logging_window.h"
#include "ui_logging_window.h"

logging_window::logging_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logging_window)
{
    ui->setupUi(this);

     QPalette Pal(palette());
     // set black background
     Pal.setColor(QPalette::Background, QColor(100, 149, 237));
     this->setAutoFillBackground(true);
     this->setPalette(Pal);
     QPalette pal = ui->button_waiter->palette();
     pal.setBrush(QPalette::ButtonText, Qt::white);
     ui->button_waiter->setPalette(pal);
     ui->button_waiter->setStyleSheet("*{background-color: rgb(70,130,180)}");
     ui->button_waiter->update();
     ui->button_barman->setPalette(pal);
     ui->button_barman->setStyleSheet("*{background-color: rgb(70,130,180)}");
     ui->button_barman->update();
     pal.setBrush(QPalette::WindowText, Qt::white);
     ui->label_login->setPalette(pal);

     connect(ui->button_barman, &QPushButton::clicked, this, &logging_window::bartender_logged);
     connect(ui->button_waiter, &QPushButton::clicked, this, &logging_window::waiter_logged);

}

logging_window::~logging_window()
{
    delete ui;
}

