/*
* Developed, owned and distributed by Stefan Marjanovic
* This product is free for personal use but not for paid disgtribution.
* Copyright https://www.stefanmarjanovic.com
*/


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
