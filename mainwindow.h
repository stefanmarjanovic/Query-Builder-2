#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_wherebox.h"
#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QWidget>


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
    QString setWhereClause();
    int getSelection();
    void setButtonChecked(int querySelection);
    void setAlert(QString s);

private:

    Ui::MainWindow *ui;
    Ui::whereDialog wd;
    QDialog *wui;
    QString inputFilename;
    QString outputFilename;
    QString inputWhereClause;
    QMessageBox alert;
    int querySelector;

public slots:

    void onGenerateClicked();
    void onAddWhereClicked();
    void onUpdateClicked();
    void onInsertClicked();
    void onDeleteClicked();
    void onWhereSubmitted();
};
#endif // QUERYBUILDER_H
