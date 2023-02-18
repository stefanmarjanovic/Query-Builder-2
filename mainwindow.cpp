#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_wherebox.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //UI instantiation
    ui->setupUi(this);
    this->setWindowTitle("SQL Injector");
    this->setWindowIcon(QIcon(QPixmap(":icon.icns")));

    //Dialog Box instantiation
    wui = new QDialog();
    cdui = new QDialog();
    cd.setupUi(cdui);
    wd.setupUi(wui);
    queryType = -1;

    //Disable buttons until text file is added
    ui->addWhereBtn->setEnabled(false);
    ui->submitBtn->setEnabled(false);
    ui->viewColBtn->setEnabled(false);

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
    QObject::connect(ui->inputTableName, &QLineEdit::editingFinished, this, &MainWindow::getTableName);

}

MainWindow::~MainWindow()
{
    qDebug() << "MainWindow destructor called";
    delete ui;
}



/*
*   TRIM STRING
*   remove trailing spaces from a word
*   params QString s
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
 *  RESET UI BUTTONS
 *  if the user removes data input reset the UI buttons to prevent adding inputs while no valid data source is present
 *  params
 *
 *  bool active
 */
void MainWindow::resetButtons(bool active){

    switch(active){

        case 0:
            queryType = -1;
            ui->addWhereBtn->setEnabled(false);
            ui->submitBtn->setEnabled(false);
            ui->viewColBtn->setEnabled(false);
            break;

        case 1:
            queryType = -1;
            ui->addWhereBtn->setEnabled(false);
            ui->submitBtn->setEnabled(true);
            ui->viewColBtn->setEnabled(true);
            break;
    }

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
            (dt->validateFile(this->getInputPath()) == true) ? ui->updateBtn->setChecked(1) :  ui->updateBtn->setChecked(0);

            break;

        case 2: // Insert

            ui->deleteBtn->setChecked(0);
            (dt->validateFile(this->getInputPath()) == true) ? ui->insertBtn->setChecked(1) :  ui->insertBtn->setChecked(0);
            ui->updateBtn->setChecked(0);

            break;

        case 3: // Delete

            (dt->validateFile(this->getInputPath()) == true) ? ui->deleteBtn->setChecked(1) : ui->deleteBtn->setChecked(0);
            ui->insertBtn->setChecked(0);
            ui->updateBtn->setChecked(0);

            break;

        default:
            ui->deleteBtn->setChecked(0);
            ui->insertBtn->setChecked(0);
            ui->updateBtn->setChecked(0);
      }
}



// Slots
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


void MainWindow::getSelectedColumn(){

    QString s = cd.listWidget->currentItem()->text();
    dt->getColumnIndex(s.toInt());

}


void MainWindow::getTableName(){

    QString s = ui->inputTableName->text();
    dt->setTableName(s);

}


void MainWindow::inputTextadded(){

    bool i = dt->validateFile(this->getInputPath());

    try {
        switch(i){
            case 0: // no source file detected

                // set red border
                ui->inputPath->setStyleSheet("border: 1px solid red");

                //deselet UI buttons
                queryType = -1;
                setButtonChecked(queryType);
                resetButtons(i);



                throw(this->getInputPath());

                break;

            case 1: // source file found

                // reset border
                ui->inputPath->setStyleSheet("");

                //Create a new instance of Data class
                dt = new Data();
                dt->validateColumns(this->getInputPath());

                // setButtonChecked(queryType);
                resetButtons(i);

                break;
        }
    }
    catch(QString file){

        qCritical() << "File or filename invalid: " <<  file;
    }
}


void MainWindow::onAddWhereClicked(){          //open dialog box to add where clause

    wui->setWindowTitle("Where Clause");
    wui->show();
    if(wd.textEdit->toPlainText().isEmpty()) dt->clearWhere();
}


void MainWindow::onBackColumnList(){

    cdui->hide();
}


void MainWindow::onDeleteClicked(){             //set delete statement selected

    queryType = 3;
    setButtonChecked(queryType);
    ui->addWhereBtn->setEnabled(false);
}


void MainWindow::onGenerateClicked(){

    dt->generate(this->getInputPath(), this->getOutputPath(), this->queryType);
}


void MainWindow::onInsertClicked(){             //set insert statement selected

    queryType = 2;
    setButtonChecked(queryType);
    ui->addWhereBtn->setEnabled(false);
}


void MainWindow::onUpdateClicked(){            //set update statement selected

    queryType = 1;
    setButtonChecked(queryType);
    (dt->validateFile(this->getInputPath()) == true) ? ui->addWhereBtn->setEnabled(true) : ui->addWhereBtn->setEnabled(false);
}


void MainWindow::onWhereSubmitted(){

    this->setWhereClause();
}

void MainWindow::onViewColumnClick(){

    cdui->setWindowTitle("Column List");
    cdui->show();
}
