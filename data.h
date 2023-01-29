#ifndef DATA_H
#define DATA_H

#include "statements.h"
#include "mainwindow.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QObject>

class Data : public QObject
{

   Q_OBJECT

public:

    Data(MainWindow &u);
    ~Data();
    bool readFile();
    bool writeToFile(QVector<QList<QString>> data);
    QString trim(QString s);
    void splitLine(QByteArray line);
    void debugMatrix(QVector<QList<QString>> data);

private:
    MainWindow *ui;
    Statements s;
    QVector<QList<QString>> matrix;
    int wordCounter;
    int lineCounter;
    int querySelector;

};

#endif // DATA_H
