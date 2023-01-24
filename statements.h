#ifndef STATEMENTS_H
#define STATEMENTS_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class statements
{
public:
    statements();
    bool insertStatement(QVector<QList<QString>> data);
    bool alterStatement(QVector<QList<QString>> data);
    bool deleteStatement(QVector<QList<QString>> data);
    bool updateStatement(QVector<QList<QString>> data);

private:
    QString _insert;
    QString _alter;
    QString _delete;
};

#endif // STATEMENTS_H
