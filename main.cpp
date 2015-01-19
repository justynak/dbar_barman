#include "mainwindow.h"
#include <QApplication>
#include "logging_window.h"
#include "print_bill_window.h"
#include "bill_edition_window.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
