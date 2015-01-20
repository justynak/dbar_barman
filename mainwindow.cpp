#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    l = new logging_window();
    b = new bill_edition_window();


    connect(l, &logging_window::waiter_logged, this, &MainWindow::set_bill_edition_widget_waiter);
    connect(l, &logging_window::bartender_logged, this, &MainWindow::set_bill_edition_widget_bartender);
    //connect(b, &bill_edition_window::goto_bill_print, this, &MainWindow::set_print_bill_widget);
    //connect(b, &bill_edition_window::goto_product_add, this, &MainWindow::set_add_product_widget);


   // database_connector* db = database_connector::get_instance();
    database_connector* db = database_connector::get_instance();
    db->init();


    this->set_logging_widget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_bill_edition_widget_bartender()
{
    this->setCentralWidget(b);
    b->set_employee(false);
}


void MainWindow::set_bill_edition_widget_waiter()
{
    this->setCentralWidget(b);
    b->set_employee(true);
}

void MainWindow::set_logging_widget()
{
    this->setCentralWidget(l);
}

