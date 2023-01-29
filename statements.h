#ifndef STATEMENTS_H
#define STATEMENTS_H

#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QObject>

class Statements : public QObject
{
public:

    Statements();
    ~Statements();
    bool deleteStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file);
    bool insertStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file);
    bool updateStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file);
    QString setWhere(QString s);
    QString validateTextString(QString w);

private:

    QString _delete;
    QString _insert;
    QString _update;
    QString _value;
    QString _where;
    int whereActive;


};

#endif // STATEMENTS_H
