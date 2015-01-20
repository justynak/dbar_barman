#include "tables_window.h"
#include "ui_tables_window.h"

tables_window::tables_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tables_window)
{
    ui->setupUi(this);

    database = database_connector::get_instance();

    ui->list_tables->setRowCount(0);
    ui->list_tables->setColumnCount(3);

    QStringList a;
    a.append(tr("Numer stolika"));
    a.append(tr("Stan"));
    a.append(tr("Oznacz"));

    ui->list_tables->setHorizontalHeaderLabels(a);

    list = database->get_tables();

    for(int i=0; i<list.count(); ++i)
    {
        ui->list_tables->insertRow(i);
        QTableWidgetItem* item[3];
        for(int k=0; k<3; ++k)
            item[k] = new QTableWidgetItem();

            item[0]->setText(tr("%1").arg(list[i].get_number()));

        if(list[i].get_occupied())
        {
            item[1]->setText(tr("Zajety"));
            item[2]->setText(tr("X"));
        }
        else
        {
            item[1]->setText(tr("Wolny"));
            item[2]->setText(tr(""));
        }

        for(unsigned int j=0; j<3; ++j)
            ui->list_tables->setItem(i, j, item[j]);
    }

    connect(ui->button_discard, &QPushButton::clicked, this, &tables_window::on_button_discard_clicked);
    connect(ui->button_ok, &QPushButton::clicked, this, &tables_window::on_button_ok_clicked);
    connect(ui->list_tables, &QTableWidget::cellClicked, this, &tables_window::on_list_tables_cellClicked);
}

void tables_window::update_tables()
{
    ui->list_tables->clear();
    list.clear();

    list = database->get_tables();

    for(int i=0; i<list.count(); ++i)
    {
        ui->list_tables->insertRow(i);
        QTableWidgetItem* item[3];
        for(int k=0; k<3; ++k)
            item[k] = new QTableWidgetItem();

            item[0]->setText(tr("%1").arg(list[i].get_number()));

        if(list[i].get_occupied())
        {
            item[1]->setText(tr("Zajety"));
            item[2]->setText(tr("X"));
        }
        else
        {
            item[1]->setText(tr("Wolny"));
            item[2]->setText(tr(""));
        }

        for(unsigned int j=0; j<3; ++j)
            ui->list_tables->setItem(i, j, item[j]);
    }
}

tables_window::~tables_window()
{
    delete ui;
}



void tables_window::on_button_ok_clicked()
{

}

void tables_window::on_button_discard_clicked()
{

}

//stan
void tables_window::on_list_tables_cellClicked(int row, int column)
{
    switch(column)
    {
        case 0: break;
        case 1: break;
        case 2:
            //send to db
            bool now_occupied = true;
            if(ui->list_tables->item(row, column)->text() == "X")
            {
                ui->list_tables->item(row, column)->setText("");
                now_occupied = false;
            }
            else
                ui->list_tables->item(row, column)->setText("X");

            list[row].set_occupied(now_occupied);
            database->update_table(list[row]);

        break;
    }

}
