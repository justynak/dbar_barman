#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class product
{
public:
    product();
    product(QString name, double price, int number)
    {
        this->name = name;
        this->price = price;
        this->number_of_products = number;
    }

    ~product();
    QString get_name()
    {
        return this->name;
    };

    double get_price()
    {
        return this->price;
    }
    int get_number_of_products()
    {
        return this->number_of_products;
    }

    void set_number_of_products(int n)
    {
        this->number_of_products = n;
    }

private:
    QString name;
    double price;
    int number_of_products;
};

#endif // PRODUCT_H
