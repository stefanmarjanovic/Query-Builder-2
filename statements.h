#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QList>
#include <QMessageBox>

class statements
{
public:

    statements();
    bool alterStatement(QList<QString> data, int lineCounter, int wordCounter, QFile &file);
    bool deleteStatement(QList<QString> data, int lineCounter, int wordCounter, QFile &file);
    bool insertStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file);
    bool updateStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file);
    QString setWhere(QVector<QString> columns, QString s);
    QString validateTextString(QString w);

private:

    QString _alter;
    QString _insert;
    QString _update;
    QString _value;
    QString _where;
};

#endif // STATEMENTS_H
