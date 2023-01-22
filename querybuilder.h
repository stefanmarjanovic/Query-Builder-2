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
    bool writeToFile(QVector<QList<QString>> matrix);
    bool setPath();
    QString getPath();
    QString trim(QString s);
    QString validateTextString(QString w);
    void splitLine(QByteArray line);
    void debugMatrix(QVector<QList<QString>>);

private:
    Ui::MainWindow *ui;
    QVector<QList<QString>> matrix;
    int wordCounter = 0;
    int lineCounter = 0;
    QString fileName;
    QMessageBox alert;

public slots:
    void on_pushButton_clicked();

signals:

};
#endif // QUERYBUILDER_H
