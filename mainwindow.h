#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool readFile();                                                //move to data.cpp
    bool writeToFile(QVector<QList<QString>> matrix);               //move to data.cpp
    QString getOutputPath();
    QString getPath();
    QString trim(QString s);                    //move to data.cpp
    void splitLine(QByteArray line);            //move to data.cpp
    void debugMatrix(QVector<QList<QString>>);  //move to data.cpp
    void setButtonChecked(int querySelection);
    void setAlert(QString s);

private:
    Ui::MainWindow *ui;
    QVector<QList<QString>> matrix;             //move to data.cpp
    int wordCounter;                            //move to data.cpp
    int lineCounter;                            //move to data.cpp
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
