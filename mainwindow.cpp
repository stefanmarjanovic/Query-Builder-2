#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "data.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wui = new QDialog();
    wd.setupUi(wui);
    querySelector = -1;
}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow delete constructor activated";
    delete ui;
}



/*
*   TRIM STRING
*   remove trailing spaces from a word
*/
QString MainWindow::trim(QString s){

    return ((s[0] == ' ') || (s.back() == ' ')) ? s.replace(" ","") : s;
}



/*
*   SET FILEPATH
*   Define the location of the data file
*/
QString MainWindow::getInputPath(){

    inputFilename = ui->inputPath->text();

    qDebug() << "File Input Path: " << ui->inputPath->text();

    return inputFilename;
}



/*
*   SET OUTPUT FILEPATH
*   Define the location of the data file
*/
QString MainWindow::getOutputPath(){

    outputFilename = ui->outputPath->text();

    qDebug() << "File Output Path: " << ui->outputPath->text();

    return outputFilename;
}



/*
*   RETURN THE SELECTED QEURY
*   returns the integer representation of the query selected by the user
*/
int MainWindow::getSelection(){

    return querySelector;
}



/*
*   ALERT MESSAGE BOX
*   call this function to alert the user of any issues
*/
void MainWindow::setAlert(QString s){

    alert.setText(s);
    alert.show();
}

void MainWindow::setButtonChecked(int querySelection){

    switch(querySelection){

        case 1:  // Update
            ui->deleteBtn->setChecked(0);
            ui->insertBtn->setChecked(0);
            ui->updateBtn->setChecked(1);

            break;

        case 2: // Insert
            ui->deleteBtn->setChecked(0);
            ui->insertBtn->setChecked(1);
            ui->updateBtn->setChecked(0);

            break;

        case 3: // Delete
            ui->deleteBtn->setChecked(1);
            ui->insertBtn->setChecked(0);
            ui->updateBtn->setChecked(0);

            break;
    }
}

// Slots
void MainWindow::on_submitBtn_clicked(){            //generate output
    Data *d = new Data(*this);
    d->readFile();
}

void MainWindow::on_addWhereBtn_clicked(){          //open popup to add where clause

    wui->show();
}

void MainWindow::on_updateBtn_clicked(){

    querySelector = 1;
    setButtonChecked(querySelector);
}

void MainWindow::on_insertBtn_clicked(){

    querySelector = 2;
    setButtonChecked(querySelector);
}

void MainWindow::on_deleteBtn_clicked(){

    querySelector = 3;
    setButtonChecked(querySelector);
}


