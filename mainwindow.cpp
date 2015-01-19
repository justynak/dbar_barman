#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    l = new logging_window();
    b = new bill_edition_window();
    a = new add_products_window();
    p = new print_bill_window();

    connect(l, &logging_window::waiter_logged, this, &MainWindow::set_bill_edition_widget);
    connect(l, &logging_window::bartender_logged, this, &MainWindow::set_bill_edition_widget);
    connect(b, &bill_edition_window::goto_bill_print, this, &MainWindow::set_print_bill_widget);
    connect(b, &bill_edition_window::goto_product_add, this, &MainWindow::set_add_product_widget);

    this->set_logging_widget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_logging_widget()
{
    this->setCentralWidget(l);
}

void MainWindow::set_print_bill_widget()
{
    this->setCentralWidget(p);
}

void MainWindow::set_bill_edition_widget()
{
    this->setCentralWidget(b);
}

void MainWindow::set_add_product_widget()
{
    this->setCentralWidget(a);
}
