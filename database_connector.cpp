#include "database_connector.h"
#include <QObject>


void database_connector::init()
{
    db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("mydb");
    db.setUserName("bar");
    db.setPassword("kelner2015");


    if(db.open() == false)
    {
       QSqlError err = db.lastError();
       QMessageBox::information(0, QObject::tr("Błąd"), err.text());
    }
}

QList<waiter> database_connector::get_waiters()
{
    QSqlQuery query;
    QString command = QString("SELECT pesel, imie, nazwisko FROM d_kelner");
    query.exec(command);

    QList<waiter> list;

    while (query.next())
    {
        QString pesel = query.value(0).toString();
        QString name = query.value(1).toString();
        QString surname = query.value(2).toString();

        list.append(waiter(pesel, name, surname));
    }

    return list;
}

QList<bartender> database_connector::get_bartenders()
{
    QSqlQuery query;
    QString command = QString("SELECT pesel, imie, nazwisko FROM d_barman");
    query.exec(command);

    QList<bartender> list;

    while (query.next())
    {
        QString pesel = query.value(0).toString();
        QString name = query.value(1).toString();
        QString surname = query.value(2).toString();

        list.append(bartender(pesel, name, surname));
    }

    return list;
}

QList<QString> database_connector::get_categories()
{
    QSqlQuery query;
    QString command = QString("select kategoria from m_artykul");
    query.exec(command);

    QList<QString> list;

    while (query.next())
    {
        list.append(query.value(0).toString());
    }
    return list;
}

QList<product> database_connector::get_products_by_category(QString category)
{
    QSqlQuery query;
    QString command = QString("select nazwa, cena_aktualna, ilosc from m_artykul as a join m_skladnik as s on a.nazwa = s.nazwa");
    query.exec(command);

    QList<product> list;

    while (query.next())
    {
        QString name = query.value(0).toString();
        double price = query.value(1).toDouble();
        int number = query.value(2).toInt();
        list.append(product(name, price, number));
    }
    return list;
}

QList<bill> database_connector::get_bills(QString b_pesel, QString w_pesel)
{
    QSqlQuery query;
    QString command = QString("select nr_zamowienia, d_numer_karty, data_zamowienia from d_zamowienie where d_kelner_PESEL = ")
                                + w_pesel + QString("AND d_barman_PESEL =") +  b_pesel;
    query.exec(command);

    QList<bill> list;

    //    QString bill_number;
   // QString card_number;
   // QString waiter;
   // QString bartender;
   // QDate date;

    while (query.next())
    {
        QString bill_number = query.value(0).toString();
        QString card_number = query.value(1).toString();
        QString date = query.value(3).toString();

        list.append(bill(bill_number, card_number, w_pesel, b_pesel, date));
    }
    return list;
}

QList<table> database_connector::get_tables()
{
    QSqlQuery query;
    QString command = QString("select inumer_stolika, zajetosc from d_stolik");
    query.exec(command);

    QList<table> list;

    while (query.next())
    {
        int number= query.value(0).toInt();
        bool occupied = query.value(1).toBool();

        list.append(table(number, occupied));
    }
    return list;
}

bool database_connector::add_product(product p)
{
    return false;
}

bool database_connector::change_number_of_products(product p, int n)
{
    return false;
}

bool database_connector::add_bill(bill b)
{
    QSqlQuery query;
    QString command = QString("INSERT INTO d_zamowienie(d_numer_karty, 	d_kelner_PESEL, d_barman_PESEL, data_zamowienia)") +
                      QString("VALUES('") + b.get_card_number() + QString("', ") +
                      QString("VALUES('") + b.get_waiter() + QString("', ") +
                      QString("VALUES('") + b.get_bartender() + QString("', ") +
                      QString("VALUES('") + b.get_date();

    bool ok = query.exec(command);

    if(ok)
    {
        command = QString("SELECT MAX(nr_zamowienia FROM d_zamowienie)");
        query.exec(command);
        b.set_bill_number(query.value(0).toString());
    }

    return ok;
}

bool database_connector::remove_bill(bill b)
{
    QSqlQuery query;

    QString command = QString("DELETE FROM d_zamowienie WHERE nr_zamowienia = ") + b.get_bill_number();
    return query.exec(command);
}

bool database_connector::update_table(table t)
{
    QSqlQuery query;

    QString command = QObject::tr("UPDATE d_stolik SET zajetosc= %1 WHERE inumer_stolika = %2").arg(t.get_occupied()).arg(t.get_number());
    return query.exec(command);
}
