#ifndef PRINT_BILL_WINDOW_H
#define PRINT_BILL_WINDOW_H

#include <QWidget>

namespace Ui {
class print_bill_window;
}

class print_bill_window : public QWidget
{
    Q_OBJECT

public:
    explicit print_bill_window(QWidget *parent = 0);
    ~print_bill_window();
    
signals:
    void bill_closed();

private:
    Ui::print_bill_window *ui;
};

#endif // PRINT_BILL_WINDOW_H
