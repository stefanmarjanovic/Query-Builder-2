#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QFile>
#include <QDebug>
#include <QTextStream>

class statements
{
public:

    statements();
    bool alterStatement(QList<QString> data, int lineCounter, int wordCounter, QFile &file);
    bool deleteStatement(QList<QString> data, int lineCounter, int wordCounter, QFile &file);
    bool insertStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file);
    bool updateStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file);
    QString setWhere(QString s);
    QString validateTextString(QString w);

private:

    QString _alter;
    QString _insert;
    QString _update;
    QString _value;
    QString _where;
};

#endif // STATEMENTS_H
