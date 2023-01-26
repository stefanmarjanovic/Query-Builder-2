#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QList>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QueryBuilder : public QMainWindow
{
    Q_OBJECT

public:
    QueryBuilder(QWidget *parent = nullptr);
    ~QueryBuilder();

    bool readFile();
    bool writeToFile(QVector<QList<QString>> matrix);
    bool setPath();
    bool setOutputPath();
    QString getPath();
    QString trim(QString s);
    void splitLine(QByteArray line);
    void debugMatrix(QVector<QList<QString>>);

private:
    Ui::MainWindow *ui;
    QVector<QList<QString>> matrix;
    int wordCounter;
    int lineCounter;
    int querySelector;
    QString inputFilename;
    QString outputFilename;
    QMessageBox alert;

signals:

private slots:
    void on_submitBtn_clicked();
    void on_alterBtn_clicked();
    void on_deleteBtn_clicked();
    void on_insertBtn_clicked();
    void on_updateBtn_clicked();
};
#endif // QUERYBUILDER_H
