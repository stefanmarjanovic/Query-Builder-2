#include "querybuilder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QueryBuilder w;

    w.show();
    //w.setPath("/Users/stefanmarjanovic/Git/Query Builder/suspects.txt");
    w.setPath();
    w.getPath();

    //w.readFile();                        // read file

    qDebug() << "Application Exited";

    return a.exec();
}
