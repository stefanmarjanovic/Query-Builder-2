#ifndef DATA_H
#define DATA_H

#include "statements.h"
#include <QDebug>
#include <QFile>
#include <QList>
#include <QMessageBox>
#include <QObject>
#include <QTextStream>

class Data : public QObject
{

   Q_OBJECT

public:

    Data();
    ~Data();

    // Boolean return types
    bool checkColumnsIsSet();
    bool compareColumnSize();
    bool parseText(QString i);
    bool generate(QString inputPath, QString outputPath, int queryOption);
    bool writeToFile(QVector<QList<QString>> data, QString outputPath, int queryOption);
    bool validateColumns(QString s);
    bool validateFile(QString s);

    // String return types
    QString getWhere();
    QString getNextColumn(int i);
    QString trimRegex(QString s);
    QString trim(QString s);

    // QVector return types
    QVector<QList<QString>> getDataMatrix();

    // Integer return types
    int getTotalWordsPerLine();

    // Void types
    void addColumnToList(QString c);
    void clearColumnList();
    void clearWhere();
    void countLines(QTextStream *in);
    void countWords(QFile *dataFile);
    void debugMatrix(QVector<QList<QString>> data);
    void getColumnIndex(int i);
    void getFirstLine(QByteArray line);
    void printColumns();
    void reset();
    void setAlert(QString s);
    void setFirstLine(bool c);
    void setTableName(QString s);
    void setWhere(QString s);
    void splitLine(QByteArray line);



private:

    const char separator = ',';
    Statements *s;
    QVector<QString> columns;
    QVector<QList<QString>> matrix;
    QMessageBox alert;
    QString _tableName;
    QString _where;
    bool firstLine;
    int columnListSelected;
    int lineCounter;
    int querySelector;
    int wordCounter;


};

#endif // DATA_H
