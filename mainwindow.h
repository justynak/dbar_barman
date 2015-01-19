#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logging_window.h"
#include "print_bill_window.h"
#include "bill_edition_window.h"
#include "add_products_window.h"


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
    print_bill_window* p;
    add_products_window* a;
    bill_edition_window* b;

public slots:
    void set_logging_widget();
    void set_print_bill_widget();
    void set_bill_edition_widget();
    void set_add_product_widget();
};

#endif // MAINWINDOW_H
