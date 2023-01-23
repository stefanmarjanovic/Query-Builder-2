/*
* Developed, owned and distributed by Stefan Marjanovic
* This product is free for personal use but not for paid disgtribution.
* Copyright stefanmarjanovic.com
*/

#include "querybuilder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QueryBuilder w;

    w.show();

    return a.exec();
}
