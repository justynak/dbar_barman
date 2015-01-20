#ifndef PRINT_BILL_WINDOW_H
#define PRINT_BILL_WINDOW_H

#include <QWidget>
#include "database_connector.h"

namespace Ui {
class print_bill_window;
}

class print_bill_window : public QWidget
{
    Q_OBJECT

public:
    explicit print_bill_window(QWidget *parent = 0);
    void set_bill_number(QString b){bill_number = b; }
    ~print_bill_window();
    
signals:
    void bill_closed();


private slots:
    void on_button_ok_clicked();
    void on_button_discard_clicked();

private:
    Ui::print_bill_window *ui;
    database_connector* db;
    QString bill_number;
};

#endif // PRINT_BILL_WINDOW_H
