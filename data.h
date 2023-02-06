#ifndef DATA_H
#define DATA_H

#include "statements.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QObject>

class Data : public QObject
{

   Q_OBJECT

public:

    //Data(Ui::MainWindow &u);
    Data();
    ~Data();
    bool readFile(QString inputPath, QString outputPath, int queryOption);
    bool writeToFile(QVector<QList<QString>> data, QString outputPath, int queryOption);
    QString trimRegex(QString s);
    QString trim(QString s);
    QString getColumnList(int position);
    void addColumnToList(QString c);
    void countLines(QTextStream *in);
    void splitLine(QByteArray line);
    void debugMatrix(QVector<QList<QString>> data);


private:
    Ui::MainWindow *ui;
    Statements *s;
    QVector<QList<QString>> matrix;
    QVector<QString> columns;
    int wordCounter;
    int lineNumber;
    int querySelector;
    const char separator = ',';

};

#endif // DATA_H
