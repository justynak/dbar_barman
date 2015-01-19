#ifndef BARTENDER_H
#define BARTENDER_H

#include <QString>
#include "employee.h"

class bartender : public employee
{
public:
    bartender();
    ~bartender();

private:
    QString name;
    QString surname;
    QString pesel;

};

#endif // BARTENDER_H
