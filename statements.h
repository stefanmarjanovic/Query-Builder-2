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
    bool deleteStatement(QVector<QList<QString>> &data, QFile &file, int lineNumber, QString column,int columnIndex, QString table);
    bool insertStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet, QString table);
    bool updateStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet, QString table);
    QString getColumn(QVector<QString> *columns, int index);
    QString getWhere();
    QString validateTextString(QString w);
    QString selectStatement();
    void clearWhere();
    void setWhere(QString s);
    void formatColumnsInsert(QVector<QString> *columns, bool columnsSet, int wordPerLine, QString table);
    void formatColumnsUpdate(QVector<QString> *columns, int index, bool columnsSet);

private:

    QString _column;
    QString _delete;
    QString _insert;
    QString _table;
    QString _update;
    QString _value;
    QString _where;
    bool columnsSet;
    bool orderBy;
    bool groupBy;
    int whereActive;

};

#endif // STATEMENTS_H
