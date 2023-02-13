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
    bool deleteStatement(QVector<QList<QString>> &data, QFile &file, int lineNumber, int columnIndex);
    bool insertStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet);
    bool updateStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet);
    QString getWhere();
    QString getColumn(QVector<QString> *columns, int index);
    QString validateTextString(QString w);
    QString selectStatement();
    void setWhere(QString s);
    void formatColumnsUpdate(QVector<QString> *columns, int index, bool columnsSet);
    void formatColumnsInsert(QVector<QString> *columns, bool columnsSet, int wordPerLine);
    void formatColumnsDelete(QVector<QString> *columns, int index, bool columnsSet);

private:

    QString _delete;
    QString _column;
    QString _insert;
    QString _update;
    QString _value;
    QString _where;
    bool orderBy;
    bool groupBy;
    int whereActive;
    bool columnsSet;


};

#endif // STATEMENTS_H
