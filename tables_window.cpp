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

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, QColor(100, 149, 237));
    this->setAutoFillBackground(true);
    this->setPalette(Pal);

    QPalette pal = ui->button_ok->palette();
    pal.setBrush(QPalette::ButtonText, Qt::white);

    ui->button_ok->setPalette(pal);
    ui->button_ok->setStyleSheet("*{background-color: rgb(70,130,180)}");
    ui->button_ok->update();


    pal.setBrush(QPalette::WindowText, Qt::white);
    ui->label->setPalette(pal);

    ui->list_tables->setHorizontalHeaderLabels(a);

    list.clear();
    list = database->get_tables();

    for(int i=0; i<list.count(); ++i)
    {
        ui->list_tables->insertRow(i);
        QTableWidgetItem* item[3];
        for(int k=0; k<3; ++k)
        {
            item[k] = new QTableWidgetItem();
            item[k]->setFlags(item[k]->flags() ^ Qt::ItemIsEditable);
        }

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

    connect(ui->button_ok, &QPushButton::clicked, this, &tables_window::tables_set);
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



//stan
void tables_window::on_list_tables_cellClicked(int row, int column)
{
    switch(column)
    {
        case 0: break;
        case 1: break;
        case 2:
            update_table(&list[row]);

            if(list[row].get_occupied())
            {
                ui->list_tables->item(row, 1)->setText("Zajety");
                ui->list_tables->item(row, 2)->setText("X");
            }
            else
            {
                ui->list_tables->item(row, 1)->setText("Wolny");
                ui->list_tables->item(row, 2)->setText("");
            }
        break;
    }

}

bool tables_window::update_table(table* t)
{
    bool occupied = t->get_occupied();
    t->set_occupied(!occupied);

    return database->update_table(*t);
}
