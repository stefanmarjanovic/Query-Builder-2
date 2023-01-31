#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_wherebox.h"
#include "data.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wui = new QDialog();
    wd.setupUi(wui);
    querySelector = -1;

    //Create connections between UI, slots & functions
    QObject::connect(ui->submitBtn, &QPushButton::clicked, this, &MainWindow::onGenerateClicked);
    QObject::connect(ui->updateBtn, &QPushButton::clicked, this, &MainWindow::onUpdateClicked);
    QObject::connect(ui->insertBtn, &QPushButton::clicked, this, &MainWindow::onInsertClicked);
    QObject::connect(ui->deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    QObject::connect(ui->addWhereBtn, &QPushButton::clicked, this, &MainWindow::onAddWhereClicked);
    QObject::connect(wd.buttonBox, &QDialogButtonBox::accepted, this, &MainWindow::onWhereSubmitted);
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
*   RETURN WHERE CLAUSE
*   returns the integer representation of the query selected by the user
*/
QString MainWindow::getWhereClause(){

    return inputWhereClause;
}




/*
*   RETURN THE SELECTED QEURY
*   returns the integer representation of the query selected by the user
*/
int MainWindow::getSelection(){

    return querySelector;
}



/*
*   SET WHERE CLAUSE
*   Get the user input from the where popup box and set it as a private string
*/
void MainWindow::setWhereClause(){

    inputWhereClause = wd.textEdit->toPlainText();

    qDebug() << "Where Clause: " << inputWhereClause;
}



/*
*   ALERT MESSAGE BOX
*   call this function to alert the user of any issues
*/
void MainWindow::setAlert(QString s){

    alert.setText(s);
    alert.show();
}



/*
*   SET STATEMENT
*   Allow only one input for the statement selector in the group box
*/
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
void MainWindow::onGenerateClicked(){            //generate output
    Data *d = new Data(*this);
    d->readFile();
}

void MainWindow::onAddWhereClicked(){          //open popup to add where clause

    wui->show();
}

void MainWindow::onUpdateClicked(){

    querySelector = 1;
    setButtonChecked(querySelector);
}

void MainWindow::onInsertClicked(){

    querySelector = 2;
    setButtonChecked(querySelector);
}

void MainWindow::onDeleteClicked(){

    querySelector = 3;
    setButtonChecked(querySelector);
}

void MainWindow::onWhereSubmitted()
{
    this->setWhereClause();
}

