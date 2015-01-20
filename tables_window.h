#ifndef TABLES_WINDOW_H
#define TABLES_WINDOW_H

#include <QDialog>
#include "database_connector.h"
#include "table.h"

namespace Ui {
class tables_window;
}

class tables_window : public QDialog
{
    Q_OBJECT

public:
    explicit tables_window(QWidget *parent = 0);
    void update_tables();
    ~tables_window();

private slots:
    void on_button_ok_clicked();
    void on_button_discard_clicked();
    void on_list_tables_cellClicked(int row, int column);

private:
    Ui::tables_window *ui;
    database_connector* database;
    QList<table> list;
};

#endif // TABLES_WINDOW_H
