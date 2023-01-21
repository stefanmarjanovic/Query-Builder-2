#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <QMainWindow>
#include <QTextStream>
#include <QFileDialog>
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
    bool writeToFile(QList<QString> words);
    bool setPath();
    void split(QByteArray line);
    QString getPath();
    QString trim(QString s);


private:
    Ui::MainWindow *ui;
    QList<QString> words;
    QString fileName;
    QMessageBox err;

public slots:
    void on_pushButton_clicked();

signals:

};
#endif // QUERYBUILDER_H
