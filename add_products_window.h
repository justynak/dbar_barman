#ifndef ADD_PRODUCTS_WINDOW_H
#define ADD_PRODUCTS_WINDOW_H

#include <QWidget>
#include "product.h"

namespace Ui {
class add_products_window;
}

class add_products_window : public QWidget
{
    Q_OBJECT

public:
    explicit add_products_window(QWidget *parent = 0);
    void get_categories();
    ~add_products_window();

private slots:
    void on_button_approve_clicked();
    void on_button_add_clicked();
    void on_button_remove_clicked();
    void on_button_discard_clicked();

    void get_products(int highlighted);
    void set_product(int highlighted);
    void send_chosen_product();

private:
    Ui::add_products_window *ui;
    product prod;

signals:
    void new_product(product p);
    void on_product_chosen(product p);
    void return_to_bill_edition_window();
};

#endif // ADD_PRODUCTS_WINDOW_H
