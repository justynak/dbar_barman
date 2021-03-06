#ifndef LOGGING_WINDOW_H
#define LOGGING_WINDOW_H

#include <QWidget>
#include "database_connector.h"
#include "bill.h"

namespace Ui {
class logging_window;
}

class logging_window : public QWidget
{
    Q_OBJECT

public:
    explicit logging_window(QWidget *parent = 0);
    ~logging_window();

private:
    Ui::logging_window *ui;
    database_connector *db;

signals:
    void waiter_logged();
    void bartender_logged();
};

#endif // LOGGING_WINDOW_H
