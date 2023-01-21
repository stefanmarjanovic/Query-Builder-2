#include "querybuilder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QueryBuilder w;

    w.show();

    return a.exec();
}
