#include "querybuilder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QueryBuilder w;

    w.show();
    w.setPath("/Users/stefanmarjanovic/Git/Query Builder/suspects.txt");

    //    QString fileName = "/Users/stefanmarjanovic/Git/Query Builder/suspects.txt";            //turn this into a variable
    //QFile dataFile(fileName);

    w.readFile();                        // read file

    qDebug() << "Application Exited";

    return a.exec();
}
