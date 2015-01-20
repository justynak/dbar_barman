#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

#include "logging_window.h"
#include "print_bill_window.h"
#include "bill_edition_window.h"
#include "add_products_window.h"
#include "tables_window.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    logging_window* l;
    bill_edition_window* b;
    print_bill_window* p;
    tables_window* t;
    add_products_window* a;


public slots:
    void set_bill_edition_widget_bartender();
    void set_bill_edition_widget_waiter();
    void set_logging_widget();
    void set_tables_widget();
    void set_print_bill_widget(QString bill_selected);
    void set_add_product_widget();
};

#endif // MAINWINDOW_H
