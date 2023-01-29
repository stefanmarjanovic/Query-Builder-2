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
    QString getOutputPath();
    QString getInputPath();
    QString trim(QString s);
    int getSelection();
    void setButtonChecked(int querySelection);
    void setAlert(QString s);

private:

    Ui::MainWindow *ui;
    QString inputFilename;
    QString outputFilename;
    QMessageBox alert;
    int querySelector;

public slots:

    void on_submitBtn_clicked();
    void on_updateBtn_clicked();
    void on_insertBtn_clicked();
    void on_deleteBtn_clicked();
};
#endif // QUERYBUILDER_H
