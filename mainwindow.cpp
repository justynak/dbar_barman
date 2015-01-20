#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
            
    w = NULL;
    br = NULL;
    active= NULL;

    db = database_connector::get_instance();
    db->init();

    this->set_logging_widget();
}

MainWindow::~MainWindow()
{
    delete ui;
    //delete l,b,p,t,a;
}

void MainWindow::set_bill_edition_widget_bartender()
{
    if(br != NULL)
        delete br;

    br = db->get_bartender();
    active = br;

    if(w == NULL)
        w = db->get_waiter();

    b = new bill_edition_window(w, br, active);

    connect(b, &bill_edition_window::goto_bill_print, this, &MainWindow::set_print_bill_widget);
    connect(b, &bill_edition_window::goto_product_add, this, &MainWindow::set_add_product_widget);
    connect(b, &bill_edition_window::goto_logging, this, &MainWindow::set_logging_widget);

    this->setCentralWidget(b);
}


void MainWindow::set_bill_edition_widget_waiter()
{
    if(w != NULL)
        delete w;

    w = db->get_waiter();
    active = w;

    if(br == NULL)
        br = db->get_bartender();

    b = new bill_edition_window(w, br, active);

    connect(b, &bill_edition_window::goto_product_add, this, &MainWindow::set_add_product_widget);
    connect(b, &bill_edition_window::goto_table_edition, this, &MainWindow::set_tables_widget);
    connect(b, &bill_edition_window::goto_logging, this, &MainWindow::set_logging_widget);
    this->setCentralWidget(b);
}

void MainWindow::set_logging_widget()
{
    l = new logging_window();
    connect(l, &logging_window::waiter_logged, this, &MainWindow::set_bill_edition_widget_waiter);
    connect(l, &logging_window::bartender_logged, this, &MainWindow::set_bill_edition_widget_bartender);
    this->setCentralWidget(l);
}

void MainWindow::set_tables_widget()
{
    t = new tables_window();
    connect(t, &tables_window::tables_set, this, &MainWindow::set_bill_edition_widget_waiter);
    this->setCentralWidget(t);
}

void MainWindow::set_print_bill_widget(QString bill_selected)
{
    p = new print_bill_window(bill_selected);
    bool is_waiter = active->is_waiter();

    connect(p, &print_bill_window::bill_closed, this, &MainWindow::set_bill_edition_widget_bartender);
    this->setCentralWidget(p);
}

void MainWindow::set_add_product_widget()
{
    a = new add_products_window();
    bool is_waiter = active->is_waiter();
    if(is_waiter)
        connect(a, &add_products_window::return_to_bill_edition_window, this, &MainWindow::set_bill_edition_widget_waiter);
    else
        connect(a, &add_products_window::return_to_bill_edition_window, this, &MainWindow::set_bill_edition_widget_bartender);

    this->setCentralWidget(a);
}

