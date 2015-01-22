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
    explicit bill_edition_window(waiter* w_p, bartender* b_r, employee* a_p , QWidget *parent = 0);
    ~bill_edition_window();
    void update_product_number(int product, int number);
    void remove_product(int p);
    void add_product();

public slots:
    void manage_click(int, int);
    void nope(int, int){}
    void send_bill_print_signal();
    void add_bill();
    void add_product_slot();

signals:
    void goto_product_add(QString bill_selected);
    void goto_bill_print(QString bill_selected);
    void goto_table_edition();
    void goto_bill_ediotion();
    void goto_logging();


private slots:
    void update_product_list(QString index);

    void on_button_scan_client_card_clicked();

    void on_button_delete_bill_clicked();

private:
    Ui::bill_edition_window *ui;
    waiter* w;
    bartender* br;
    employee* active;
    QList<product> list_products;
    QList<bill> list_bills;
    QString bill_selected;
    database_connector *db;
    double value;
};

#endif // BILL_EDITION_WINDOW_H
