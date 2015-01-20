#ifndef BILL_EDITION_WINDOW_H
#define BILL_EDITION_WINDOW_H

#include <QWidget>
#include "employee.h"
#include "product.h"


namespace Ui {
class bill_edition_window;
}

class bill_edition_window : public QWidget
{
    Q_OBJECT

public:
    explicit bill_edition_window(QWidget *parent = 0);
    ~bill_edition_window();
    void update_product_list();
    void update_product_number(int product, int number);
    void remove_product(int p);
    void add_product();
    void set_employee(bool waiter);

public slots:
    void manage_click(int, int);

signals:
    void goto_product_add();
    void goto_bill_print();

private slots:
    void on_button_tables_clicked();

private:
    Ui::bill_edition_window *ui;
    employee emp;
    bool waiter;
    QList<product> list_products;
};

#endif // BILL_EDITION_WINDOW_H
