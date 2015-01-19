#-------------------------------------------------
#
# Project created by QtCreator 2015-01-17T21:49:22
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dbar_barman
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    logging_window.cpp \
    bill_edition_window.cpp \
    add_products_window.cpp \
    print_bill_window.cpp \
    waiter.cpp \
    bartender.cpp \
    table.cpp \
    product.cpp \
    employee.cpp


HEADERS  += mainwindow.h \
    logging_window.h \
    bill_edition_window.h \
    add_products_window.h \
    print_bill_window.h \
    waiter.h \
    bartender.h \
    table.h \
    product.h \
    employee.h


FORMS    += mainwindow.ui \
     logging_window.ui \
     bill_edition_window.ui \
     add_products_window.ui \
     print_bill_window.ui
