#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_wherebox.h"


MainWindow::MainWindow(QWidget *parent, Data *d)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //UI instantiation
    ui->setupUi(this);
    wui = new QDialog();
    cdui = new QDialog();
    cd.setupUi(cdui);
    wd.setupUi(wui);
    queryType = -1;

    //User-defined Class
    d = new Data();
    dt = d; //Data

    //Create connections between UI, slots & functions
    QObject::connect(ui->submitBtn, &QPushButton::clicked, this, &MainWindow::onGenerateClicked);
    QObject::connect(ui->updateBtn, &QPushButton::clicked, this, &MainWindow::onUpdateClicked);
    QObject::connect(ui->insertBtn, &QPushButton::clicked, this, &MainWindow::onInsertClicked);
    QObject::connect(ui->deleteBtn, &QPushButton::clicked, this, &MainWindow::onDeleteClicked);
    QObject::connect(ui->addWhereBtn, &QPushButton::clicked, this, &MainWindow::onAddWhereClicked);
    QObject::connect(ui->viewColBtn, &QPushButton::clicked, this, &MainWindow::onViewColumnClick);
    QObject::connect(wd.buttonBox, &QDialogButtonBox::accepted, this, &MainWindow::onWhereSubmitted);
    QObject::connect(cd.addBtn, &QPushButton::clicked, this, &MainWindow::addColumnToList);
    QObject::connect(cd.clearBtn, &QPushButton::clicked, this, &MainWindow::clearColumnToList);
    QObject::connect(cd.backBtn, &QPushButton::clicked, this, &MainWindow::onBackColumnList);
    QObject::connect(cd.listWidget, &QListWidget::itemClicked, this, &MainWindow::getSelectedColumn);
    QObject::connect(ui->inputPath, &QLineEdit::editingFinished, this, &MainWindow::inputTextadded);

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

    return queryType;
}



/*
*   SET WHERE CLAUSE
*   Get the user input from the where popup box and set it as a private string
*/
void MainWindow::setWhereClause(){

    QString inputWhereClause = wd.textEdit->toPlainText();
    dt->setWhere(inputWhereClause);
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
void MainWindow::onGenerateClicked(){

    dt->generate(this->getInputPath(), this->getOutputPath(), this->queryType);
}

void MainWindow::onAddWhereClicked(){          //open popup to add where clause

    wui->show();
}

void MainWindow::onUpdateClicked(){

    queryType = 1;
    setButtonChecked(queryType);
    ui->addWhereBtn->setEnabled(true);
}

void MainWindow::onInsertClicked(){

    queryType = 2;
    setButtonChecked(queryType);
    ui->addWhereBtn->setEnabled(false);
}

void MainWindow::onDeleteClicked(){

    queryType = 3;
    setButtonChecked(queryType);
    ui->addWhereBtn->setEnabled(true);
}

void MainWindow::onWhereSubmitted(){

    this->setWhereClause();
}

void MainWindow::onViewColumnClick(){

    cdui->show();
}

void MainWindow::addColumnToList(){



    try {
        int totalColumns = dt->getTotalWordsPerLine();

        if(cd.listWidget->count() < totalColumns){

            QString c = columnInput.getText(0,"Add Column","Enter column name:");
            dt->addColumnToList(c);
            cd.listWidget->addItem(c);

        }
        else{

            throw (totalColumns);
        }

    } catch (int totalColumns) {

        qCritical() << "Error - cannot add more columns than exists in datasource";
        dt->setAlert(QString("Cannot add more columns than").arg(totalColumns));
    }

;}


void MainWindow::clearColumnToList(){

    dt->clearList();
    cd.listWidget->clear();
}

void MainWindow::onBackColumnList(){

    cdui->hide();
}

void MainWindow::inputTextadded(){

    (dt->validateFile(this->getInputPath()) == false) ? (ui->inputPath->setStyleSheet("border: 1px solid red")) : (ui->inputPath->setStyleSheet(""));

    if(dt->validateFile(this->getInputPath()) != false) dt->validateColumns(this->getInputPath());
}

void MainWindow::getSelectedColumn(){

    QString s = cd.listWidget->currentItem()->text();
    dt->getColumnIndex(s.toInt());

}
