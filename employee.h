#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>

class employee
{
public:
    employee(QString p, QString n, QString s ): pesel(p), name(n), surname(s){}
    employee(){}
    ~employee();

    QString get_name(){return name;}
    QString get_surname(){return surname;}
    QString get_pesel(){return pesel;}

protected:
    QString name;
    QString surname;
    QString pesel;
};

#endif // EMPLOYEE_H
