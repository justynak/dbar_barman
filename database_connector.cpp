#include "database_connector.h"
#include <QObject>
#include <QDate>

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

 //from m_artykul as a join m_artykul_skladnik as a_s on a.nazwa = a_s.m_Artykul_nazwa join m_skladnik as s on a_s.m_Artykul_nazwa = s.nazwa group by a.nazwa
    QString command = QString("select a.nazwa, cena_aktualna, min(s.ilosc)"
                              "from m_artykul as a "
                              "join m_artykul_skladnik as a_s "
                              "on a.nazwa = a_s.m_Artykul_nazwa "
                              "join m_skladnik as s "
                              "on a_s.m_Artykul_nazwa = s.nazwa "
                              "where kategoria = \"%1\" "
                              "group by a.nazwa ").arg(category);
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
    QString command = QObject::tr("select * from d_zamowienie "
                                  "where d_kelner_PESEL = '%1' "
                                  "AND d_barman_PESEL = '%2' "
                                  "AND zamkniety = 0").arg(w_pesel).arg(b_pesel);
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

QString database_connector::get_client(QString bill)
{
    this->connect();

    int whitespace = bill.indexOf('\t');
    bill = bill.left(whitespace);

    QSqlQuery query(db);
    query.exec(QObject::tr("select d_numer_karty from d_zamowienie where nr_zamowienia = '%1'").arg(bill));
    query.first();

    return query.value(0).toString();
}

bool database_connector::add_product(product p)
{
    return false;
}

bool database_connector::change_number_of_products(product p, int n)
{
    return false;
}

bool database_connector::add_bill(bill *b)
{
    this->connect();
    QSqlQuery query;

    QString command = QObject::tr("INSERT INTO d_zamowienie(d_numer_karty, d_kelner_PESEL, d_barman_PESEL, data_zamowienia) VALUES('%1', '%2', '%3', '%4'"
                                  ")").arg(b->get_card_number()).arg(b->get_waiter()).arg(b->get_bartender()).arg(b->get_date());

    bool ok = query.exec(command);
    query.finish();

    if(ok)
    {
        command = QString("SELECT MAX(nr_zamowienia) FROM d_zamowienie");
        query.exec(command);
        query.first();
        b->set_bill_number(query.value(0).toString());
    }
    return ok;
}

bool database_connector::remove_bill(QString b)
{
    this->connect();

    int whitespace = b.indexOf('\t');
    b = b.left(whitespace);

    QSqlQuery query;

    QString command = QObject::tr("UPDATE d_zamowienie set zamkniety = 1 WHERE nr_zamowienia =%1").arg(b);
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

bool database_connector::set_client(QString number, QString bill)
{
    this->connect();
    QSqlQuery query;

    int whitespace = bill.indexOf('\t');
    bill = bill.left(whitespace);

    /*
UPDATE table_name
SET column1=value1,column2=value2,...
WHERE some_column=some_value;
*/
    return query.exec(QObject::tr("UPDATE d_zamowienie SET d_numer_karty = '%1 "
                                  "WHERE nr_zamowienia = %2").arg(number).arg(bill));
}

bool database_connector::set_random_client(QString bill)
{
    this->connect();

    int whitespace = bill.indexOf('\t');
    bill = bill.left(whitespace);

    QSqlQuery query;
    query.exec(QObject::tr("SELECT COUNT(numer_karty) FROM d_staly_klient"));
    query.first();
    int number = query.value(0).toInt();
    int limit = rand() % (number);
    query.finish();

    query.exec(QObject::tr("SELECT numer_karty from d_staly_klient limit 1 offset %1").arg(limit));
    query.first();
    QString numer = query.value(0).toString();
    query.finish();

    return query.exec(QObject::tr("UPDATE d_zamowienie SET d_numer_karty = '%1' "
                                  "WHERE nr_zamowienia = '%2'").arg(numer).arg(bill));
}

waiter *database_connector::get_waiter()
{
    this->connect();
    QSqlQuery query;
    query.exec(QObject::tr("SELECT COUNT(pesel) FROM d_kelner"));
    query.first();
    int number = query.value(0).toInt();
    int limit = rand() % (number);
    query.finish();

    query.exec(QObject::tr("SELECT pesel, imie, nazwisko from d_kelner limit 1 offset %1").arg(limit));
    query.first();
    QString pesel = query.value(0).toString();
    QString name = query.value(1).toString();
    QString surname = query.value(2).toString();

    waiter *w = new waiter(pesel, name, surname);

    return w;
}

bartender *database_connector::get_bartender()
{
    this->connect();
    QSqlQuery query;
    query.exec(QObject::tr("SELECT COUNT(pesel) FROM d_barman"));
    query.first();
    int number = query.value(0).toInt();
    int limit = rand() % (number);
    query.finish();

    query.exec(QObject::tr("SELECT pesel, imie, nazwisko from d_barman limit 1 offset %1").arg(limit));
    query.first();
    QString pesel = query.value(0).toString();
    QString name = query.value(1).toString();
    QString surname = query.value(2).toString();

    bartender *b = new bartender(pesel, name, surname);

    return b;
}
