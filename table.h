#ifndef TABLE_H
#define TABLE_H


class table
{
public:
    table();
    table(int n, bool o) : number(n), occupied(o) {}
    ~table();
    bool get_occupied(){return occupied;}
    int get_number(){return number;}
    void set_occupied(bool o){occupied = o;}

private:
    bool occupied;
    int number;
};

#endif // TABLE_H
