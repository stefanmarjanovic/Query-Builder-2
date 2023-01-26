#ifndef DATA_H
#define DATA_H

#include "mainwindow.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QList>

class Data
{
public:

    Data();
    bool readFile();
    bool writeToFile(QVector<QList<QString>> data);
    QString trim(QString s);
    void splitLine(QByteArray line);
    void debugMatrix(QVector<QList<QString>> data);

private:
    MainWindow interface;
    QVector<QList<QString>> matrix;
    int wordCounter;
    int lineCounter;
    int querySelector;

};

#endif // DATA_H
