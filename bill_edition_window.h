#ifndef BILL_EDITION_WINDOW_H
#define BILL_EDITION_WINDOW_H

#include <QWidget>
#include "employee.h"
#include "product.h"
#include "bill.h"
#include "database_connector.h"


namespace Ui {
class bill_edition_window;
}

class bill_edition_window : public QWidget
{
    Q_OBJECT

public:
    explicit bill_edition_window(QWidget *parent = 0);
    ~bill_edition_window();
    void update_product_number(int product, int number);
    void remove_product(int p);
    void add_product();
    void set_employee(bool waiter);

public slots:
    void manage_click(int, int);
    void send_bill_print_signal();
    void add_bill();

signals:
    void goto_product_add();
    void goto_bill_print(QString bill_selected);
    void goto_table_edition();
    void goto_bill_ediotion();
    void goto_logging();


private slots:
    void update_product_list(QString index);

private:
    Ui::bill_edition_window *ui;
    employee emp;
    bool waiter;
    QList<product> list_products;
    QList<bill> list_bills;
    QString bill_selected;
    database_connector *db;
};

#endif // BILL_EDITION_WINDOW_H
