#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_wherebox.h"
#include "ui_columnsdiag.h"
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
    QString getWhereClause();
    int getSelection();
    void setWhereClause();
    void setButtonChecked(int querySelection);
    void setAlert(QString s);

private:

    Ui::MainWindow *ui;
    Ui::WhereDialog wd;
    Ui::ColumnsDiag cd;
    QDialog *wui;
    QDialog *cdui;
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
    void onAddColumnClick();
};
#endif // QUERYBUILDER_H
