#ifndef QUERYBUILDER_H
#define QUERYBUILDER_H

#include <QMainWindow>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QList>

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
    bool writeToFile(QFile $file);
    bool setPath();
    void split(QByteArray line);
    QString getPath();
    QString trim(QString s);


private:
    Ui::MainWindow *ui;
    QList<QString> words;
    QString fileName;

public slots:
    void on_pushButton_clicked();

signals:

};
#endif // QUERYBUILDER_H
