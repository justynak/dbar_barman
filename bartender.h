#ifndef BARTENDER_H
#define BARTENDER_H

#include <QString>
#include "employee.h"

class bartender : public employee
{
public:
    explicit bartender(QString p, QString n, QString s ) : employee(p,n,s) {}
    bartender();
    bool is_waiter(){return false;}
    ~bartender();

private:
    QString name;
    QString surname;
    QString pesel;

};

#endif // BARTENDER_H
