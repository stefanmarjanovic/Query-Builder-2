#include "mainwindow.h"
#include "statements.h"
#include "ui_querybuilder.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wordCounter = 0;
    lineCounter = 0;
    querySelector = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}



/*
*   READ FILE
*   read the uploaded text file
*/

bool MainWindow::readFile(){

    this->getPath();

    QFile dataFile(inputFilename);

    if(dataFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File found successfully./nReading file in progress/n";

        // split by line
        while(!dataFile.atEnd()){

            QByteArray line = dataFile.readLine();
            splitLine(line);

            lineCounter++;
        }

    }
    else {
        qCritical() << "File not found";

        alert.setText("File not found. Please check your file path.");
        alert.exec();

        return false;
    }

    writeToFile(matrix);

    return true;
}



/*
*   WRITE FILE
*   write to the uploaded text file
*/

bool MainWindow::writeToFile(QVector<QList<QString>> matrix)
{

    statements s;

    this->getOutputPath();

    QFile file(outputFilename);


    if(file.open(QFile::WriteOnly | QFile::Text | QFile::Append)){

        switch(querySelector){
            case 1:

                qDebug() << "Alter Statement";
                break;

            case 2:

                qDebug() << "Delete Statement";
                break;

            case 3:

                s.insertStatement(matrix, lineCounter,wordCounter, file);
                qDebug() << "Insert Statement";
                break;

            case 4:

                s.updateStatement(matrix, lineCounter,wordCounter, file);
                qDebug() << "Update Statement";
                break;
        }

        //  - /Users/Personal/Git/query-builder-2/suspects.txt
        alert.setText("File exported successfully.");
        alert.show();
    }
    else {
        qCritical() << "Output path not set.";

        alert.setText("Output path not set. Please enter a valid folder path and filename");
        alert.exec();


        return false;
    }

    return true;
}



/*
*   TRIM STRING
*   remove trailing spaces from a word
*/
QString MainWindow::trim(QString s){

    return ((s[0] == ' ') || (s.back() == ' ')) ? s.replace(" ","") : s;
}



/*
*   SPLIT LINE
*   Split line into words separated by comma
*/
void MainWindow::splitLine(QByteArray line){
     QString w;
     QList<QString> row;

    for(int i = 0; i < line.size(); i++)
    {

        QChar c = line[i];


        //add word to arrayList
        if(c == ','|| i == line.size()-1) {

            trim(w);                                // trim any white spaces
            row.append(w);

            w.clear();                              // reset string for further usage

            if(lineCounter == 0) wordCounter++;     // counter for words per line
            continue;
        }

        w.append(c);                                // add letter to form a word
    }

    matrix.append(row);
    //debugMatrix(matrix);
}



/*
*   SET FILEPATH
*   Define the location of the data file
*/
QString MainWindow::getPath(){

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
*   DEBUG 2D ARRAY
*   print the matrix rows and columns to the console logging
*/
void  MainWindow::debugMatrix(QVector<QList<QString>> matrix){

    qDebug() << "Matrix size: " << matrix.size();
    for(int i = 0; i < matrix.size(); i++)
     {
         qDebug() << "Row " << i+1 << ": " << matrix[i];

         for(int o = 0; o < matrix[i].size(); o++){

            qDebug() << "Column " << o+1 << ": " << matrix[i][o];
         }
     }
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
        case 1: // Alter
            ui->deleteBtn->setChecked(0);
            ui->insertBtn->setChecked(0);
            ui->updateBtn->setChecked(0);
            ui->alterBtn->setChecked(1);
            break;

        case 2: // Delete
            ui->deleteBtn->setChecked(1);
            ui->insertBtn->setChecked(0);
            ui->updateBtn->setChecked(0);
            ui->alterBtn->setChecked(0);

            break;
        case 3: // Insert
            ui->deleteBtn->setChecked(0);
            ui->insertBtn->setChecked(1);
            ui->updateBtn->setChecked(0);
            ui->alterBtn->setChecked(0);

            break;
        case 4:  // Update
            ui->deleteBtn->setChecked(0);
            ui->insertBtn->setChecked(0);
            ui->updateBtn->setChecked(1);
            ui->alterBtn->setChecked(0);
            break;
    }
}

void MainWindow::on_submitBtn_clicked()
{
    this->readFile();
}


void MainWindow::on_alterBtn_clicked()
{
    querySelector = 1;
    setButtonChecked(querySelector);
}


void MainWindow::on_deleteBtn_clicked()
{
    querySelector = 2;
    setButtonChecked(querySelector);
}


void MainWindow::on_insertBtn_clicked()
{
    querySelector = 3;
    setButtonChecked(querySelector);
}


void MainWindow::on_updateBtn_clicked()
{
    querySelector = 4;
    setButtonChecked(querySelector);
}

