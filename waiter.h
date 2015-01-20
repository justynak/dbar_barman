#ifndef WAITER_H
#define WAITER_H


#include "employee.h"



class waiter : public employee
{
public:
    //explicit B(int x) : A(x) { }
    waiter();
    bool is_waiter(){return true;}
    explicit waiter(QString p, QString n, QString s ) : employee(p,n,s) {}
    ~waiter();
};

#endif // WAITER_H
