#ifndef DATABASE_CONNECTOR_H
#define DATABASE_CONNECTOR_H

#include <QtSql>
#include <QMessageBox>
#include <QString>
#include "waiter.h"
#include "bartender.h"
#include "product.h"
#include "bill.h"
#include "table.h"

class database_connector
{
 private:
       database_connector() { db = QSqlDatabase::addDatabase("QMYSQL"); }
       database_connector(const database_connector &);
       database_connector& operator=(const database_connector&);
       ~database_connector() {}

       QSqlDatabase db;

 public:
       static database_connector* get_instance()
       {
         static database_connector instance;
         return &instance;
       }

       void init();
       QList<waiter> get_waiters();
       QList<bartender> get_bartenders();
       QList<QString> get_categories();
       QList<product> get_products_by_category(QString category);
       QList<product> get_products_from_bill(QString b);
       QList<bill> get_bills(QString b_pesel, QString w_pesel);
       QList<table> get_tables();

       bool add_product(product p);
       bool change_number_of_products(product p, int n);

       bool add_bill(bill b);
       bool remove_bill(bill b);

       bool update_table(table t);

       bool connect();
};

#endif // DATABASE_CONNECTOR_H
