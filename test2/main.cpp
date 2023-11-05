#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
     w.resize(1900, 1080);
    w.show();
    return a.exec();
}
