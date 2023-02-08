#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_wherebox.h"
#include "ui_columnsdiag.h"
#include "data.h"
#include <QMainWindow>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QWidget>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr, Data *d = nullptr);
    ~MainWindow();
    QString getOutputPath();
    QString getInputPath();
    QString trim(QString s);

    int getSelection();
    void setWhereClause();
    void setButtonChecked(int querySelection);
    void setAlert(QString s);

private:

    Ui::MainWindow *ui;
    Ui::WhereDialog wd;
    Ui::ColumnsDiag cd;
    Data *dt;
    QDialog *wui;
    QDialog *cdui;
    QInputDialog columnInput;
    QString inputFilename;
    QString outputFilename;
    int querySelector;

public slots:

    void onGenerateClicked();
    void onAddWhereClicked();
    void onUpdateClicked();
    void onInsertClicked();
    void onDeleteClicked();
    void onWhereSubmitted();
    void onViewColumnClick();
    void addColumnToList();
    void clearColumnToList();
    void onBackColumnList();
    void inputTextadded();

signals:

};
#endif // QUERYBUILDER_H
