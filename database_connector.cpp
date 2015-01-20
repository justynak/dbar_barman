#include "database_connector.h"
#include <QObject>


void database_connector::init()
{

}

QList<waiter> database_connector::get_waiters()
{
    QSqlQuery query;
    //QString command = QString("SELECT pesel, imie, nazwisko FROM d_kelner");
    //query.exec(command);
    query.exec("SELECT pesel, imie, nazwisko FROM d_kelner");

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
    QString command = QString("select distinct kategoria from m_artykul order by kategoria");
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
    QString command = QString("select a.nazwa, cena_aktualna, ilosc from m_artykul as a join m_skladnik as s on a.nazwa = s.nazwa where kategoria = \"%1\"").arg(category);
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

QList<product> database_connector::get_products_from_bill(QString b)
{
    this->connect();
    int whitespace = b.indexOf('\t');
    b = b.left(whitespace);


    QSqlQuery query;
    QString command = QObject::tr("select d_nazwa_artykulu, ilosc from d_zamowienie_artykul where d_numer_zamowienia =%1").arg(b);
    query.exec(command);
    QList<product> list;

    while (query.next())
    {
        QString name = query.value(0).toString();
        int number = query.value(1).toInt();

        this->connect();
        QSqlQuery q;
        q.exec(QObject::tr("select cena_aktualna from m_artykul where nazwa = \"%1\" ").arg(name));
        q.first();
        double price = q.value(0).toDouble();
        q.finish();

        list.append(product(name, price, number));
    }
    return list;
}

QList<bill> database_connector::get_bills(QString b_pesel, QString w_pesel)
{
    db.setHostName("localhost");
    db.setDatabaseName("mydb");
    db.setUserName("bar");
    db.setPassword("kelner2015");
    qDebug() <<db.open();

    QSqlQuery query(db);
    QString command = QString("select * from d_zamowienie where d_kelner_PESEL = 8511273456 AND d_barman_PESEL =87020586446 AND zamkniety = 0");
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
        QString date = query.value(4).toString();

        list.append(bill(bill_number, card_number, w_pesel, b_pesel, date));
    }
    return list;
}

QList<table> database_connector::get_tables()
{
    this->connect();

    QSqlQuery query(db);
    //QString command = QString("select inumer_stolika, zajetosc from d_stolik;");
    query.exec("select inumer_stolika, zajetosc from d_stolik;");

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

bool database_connector::connect()
{
    //db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("mydb");
    db.setUserName("bar");
    db.setPassword("kelner2015");


    if(db.open() == false)
    {
       QSqlError err = db.lastError();
       QMessageBox::information(0, QObject::tr("Błąd"), err.text());
    }

    return true;
}
