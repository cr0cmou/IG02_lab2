#include "mainwindow.h"

#include <QApplication>

// MARIAM PINTON

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
