#ifndef DATA_H
#define DATA_H

#include "statements.h"
#include "ui_mainwindow.h"
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
    bool checkColumnsSet();
    bool parseText(QString i);
    bool generate(QString inputPath, QString outputPath, int queryOption);
    bool writeToFile(QVector<QList<QString>> data, QString outputPath, int queryOption);
    bool validateColumns(QString s);
    bool validateFile(QString s);
    QString getWhere();
    QString getNextColumn(int i);
    QString trimRegex(QString s);
    QString trim(QString s);
    int getTotalWordsPerLine();
    void addColumnToList(QString c);
    void clearList();
    void countLines(QTextStream *in);
    void countWords(QFile *dataFile);
    void debugMatrix(QVector<QList<QString>> data);
    void getColumnIndex(int i);
    void setAlert(QString s);
    void setWhere(QString s);
    void splitLine(QByteArray line);



private:

    const char separator = ',';
    Ui::MainWindow *ui;
    Statements *s;
    QVector<QList<QString>> matrix;
    QVector<QString> columns;
    QMessageBox alert;
    QString _where;
    int lineCounter;
    int wordCounter;
    int querySelector;
    int columnListSelected;


};

#endif // DATA_H
