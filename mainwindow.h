#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "ui_table.h"
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
#include <QTableWidget>

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
    void resetButtons(bool active);
    void setWhereClause();
    void setButtonChecked(int querySelection);
    void setAlert(QString s);

private:

    Ui::MainWindow *ui;                 // Main Window user interface
    Ui::WhereDialog wd;                 // where clause dialog box
    Ui::ColumnsDiag cd;                 // column dialog box
    Ui::Table tv;                       // tableview user interface
    Data *dt;
    QDialog *wui;
    QDialog *cdui;
    QDialog *vtui;
    QInputDialog columnInput;
    QTableWidget viewTable;
    QMessageBox alert;
    QString inputFilename;
    QString outputFilename;
    int queryType;

public slots:

    void addColumnToList();
    void clearColumnToList();
    void getSelectedColumn();
    void getTableName();
    void inputTextadded();
    void onAddWhereClicked();
    void onBackColumnList();
    void onDeleteClicked();
    void onGenerateClicked();
    void onInsertClicked();
    void onUpdateClicked();
    void onWhereSubmitted();
    void onViewColumnClick();
    void onCheckedBox();
    void onViewTableClicked();

};
#endif // SQLINJECTOR_H
