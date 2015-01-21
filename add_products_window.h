#ifndef ADD_PRODUCTS_WINDOW_H
#define ADD_PRODUCTS_WINDOW_H

#include <QWidget>
#include "product.h"
#include "database_connector.h"

namespace Ui {
class add_products_window;
}

class add_products_window : public QWidget
{
    Q_OBJECT

public:
    explicit add_products_window(QString bill, QWidget *parent = 0);
    void get_categories();
    void set_access_rights(employee* e);
    ~add_products_window();

private slots:
    void on_button_approve_clicked();
    void on_button_add_clicked();
    void on_button_remove_clicked();
    void on_button_discard_clicked();

    void get_products(int highlighted);
    void set_product(int highlighted);


private:
    Ui::add_products_window *ui;
    QList<QString> category_list;
    QList<product> product_list;
    int number_of_current_product;
    int chosed_product;
    int max_number_of_current_product;
    database_connector* db;
    QString bill_selected;

signals:
    void return_to_bill_edition_window();
};

#endif // ADD_PRODUCTS_WINDOW_H
