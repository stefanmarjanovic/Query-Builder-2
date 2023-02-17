#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QObject>

class Statements : public QObject
{
public:

    Statements();
    ~Statements();
    bool deleteStatement(QVector<QList<QString>> &data, QFile &file, int lineNumber, QString column,int columnIndex);
    bool insertStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet);
    bool updateStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet);
    QString getWhere();
    QString getColumn(QVector<QString> *columns, int index);
    QString validateTextString(QString w);
    QString selectStatement();
    void clearWhere();
    void setWhere(QString s);
    void formatColumnsUpdate(QVector<QString> *columns, int index, bool columnsSet);
    void formatColumnsInsert(QVector<QString> *columns, bool columnsSet, int wordPerLine);

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
