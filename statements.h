#ifndef STATEMENTS_H
#define STATEMENTS_H

//#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QObject>

class Statements : public QObject
{
public:

    Statements();
    ~Statements();
    bool deleteStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber);
    bool insertStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter);
    bool updateStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter);
    QString getWhere();
    QString getNextColumn(QVector<QString> *columns, int index);
    QString validateTextString(QString w);
    void setWhere(QString s);
    void formatColumns(QVector<QString> *columns, int index, int queryType);


private:

    QString _delete;
    QString _column;
    QString _insert;
    QString _update;
    QString _value;
    QString _where;
    int whereActive;
    bool columnsSet;


};

#endif // STATEMENTS_H
