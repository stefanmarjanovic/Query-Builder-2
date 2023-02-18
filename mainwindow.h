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

    Ui::MainWindow *ui;
    Ui::WhereDialog wd;
    Ui::ColumnsDiag cd;
    Data *dt;
    QDialog *wui;
    QDialog *cdui;
    QInputDialog columnInput;
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





signals:



};
#endif // QUERYBUILDER_H
