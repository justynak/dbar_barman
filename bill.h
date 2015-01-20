#ifndef BILL_H
#define BILL_H
#include <QString>
#include <QDate>


class bill
{
public:
    bill();
    bill(QString b, QString c, QString w, QString bt, QString d):
            bill_number(b), card_number(c), waiter(w), bartender(bt), date(d){}
    ~bill();
    QString get_bill_number(){ return bill_number;}
    QString get_card_number(){ return card_number;}
    QString get_waiter(){ return waiter;}
    QString get_bartender(){return bartender;}
    QString get_date(){return date;}

    void set_bill_number(QString n){bill_number = n;}
    void set_date(QString d){date = d;}
    void set_waiter(QString w){waiter = w;}
    void set_bartender(QString br){bartender = br;}
    void set_card_number(QString c){card_number = c;}


private:
    QString bill_number;
    QString card_number;
    QString waiter;
    QString bartender;
    QString date;
};

#endif // BILL_H
