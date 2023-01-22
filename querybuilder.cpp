#include "querybuilder.h"
#include "ui_querybuilder.h"

QueryBuilder::QueryBuilder(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

QueryBuilder::~QueryBuilder()
{
    delete ui;
}


/*
*   READ FILE
*   read the uploaded text file
*/

bool QueryBuilder::readFile(){

    this->setPath();

    QFile dataFile(fileName);

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

bool QueryBuilder::writeToFile(QVector<QList<QString>> matrix)
{
    QFile file("/Users/stefanmarjanovic/Git/Query Builder/output.txt");


    if(file.open(QFile::WriteOnly | QFile::Text | QFile::Append)){

        QTextStream stream(&file);

        //stream << "Hello World";
        qDebug() << "Printing Stream: ";

        qDebug() << "Words Per line: " << wordCounter;
        qDebug() << "Lines: " << lineCounter;


        for(int i = 0; i < lineCounter; i++)
        {
            for(int o = 0; o < wordCounter; o++){

                stream << matrix[i][o] << ",";
            }
        }

        //  - /Users/stefanmarjanovic/Git/Query Builder/suspects.txt
        file.close();
        alert.setText("File exported successfully.");
        alert.show();
    }
    else {
        qCritical() << "File stream already closed";

        alert.setText("File stream has been closed. Please contact your software engineer.");
        alert.exec();


        return false;
    }

    return true;
}


/*
*   TRIM STRING
*   remove spaces from a word
*/

QString QueryBuilder::trim(QString s){

    s.replace(" ","");

   return s;
}

/*
*   SPLIT LINE
*   Split line into words separated by comma
*/

void QueryBuilder::splitLine(QByteArray line){
     QString w;
     QList<QString> row;

    for(int i = 0; i < line.size(); i++)
    {

        QChar c = line[i];


        //add word to arrayList
        if(c == ','|| i == line.size()-1) {

            w.replace(" ","");                      // trim any white spaces
            //words.append(w);
            row.append(w);

            w.clear();                              // reset string for further usage

            if(lineCounter == 0) wordCounter++;     // counter for words per line
            continue;
        }

        w.append(c);                             // add letter to form a word
    }

    matrix.append(row);
    debugMatrix(matrix);
}

/*
*   SET FILEPATH
*   Define the location of the data file
*/

bool QueryBuilder::setPath(){

    fileName = ui->filePath->text();
    qDebug() << "Path : " << fileName;

    return true;
}


/*
*   RETURN FILEPATH
*   retrieve the file path and print to console
*/

QString QueryBuilder::getPath(){

    qDebug() << "Path : " << fileName;

    return fileName;
}


/*
*   VALIDATE TYPE
*   if string wrap in double quotes
*/

QString QueryBuilder::validateTextString(QString w){

      if(!w.toInt()) {

          w.append('"');
          w.prepend('"');

      }

      return w;
}


/*
*   DEBUG 2D ARRAY
*   print the matrix rows and columns to the console logging
*/

void  QueryBuilder::debugMatrix(QVector<QList<QString>> matrix){

    qDebug() << "Matrix size: " << matrix.size();
    for(int i = 0; i < matrix.size(); i++)
     {
         qDebug() << "Row " << i+1 << ": " << matrix[i];

         for(int o = 0; o < matrix[i].size(); o++){

            qDebug() << "Column " << o+1 << ": " << matrix[i][o];
         }
     }
}

void QueryBuilder::on_pushButton_clicked(){

    readFile();
}

