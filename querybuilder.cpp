#include "querybuilder.h"
#include "ui_mainwindow.h"

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

    if(dataFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File found successfully./nReading file in progress/n";

        while(!dataFile.atEnd()){

            QByteArray line = dataFile.readLine();
            split(line);

        }

        for(int s = 0; s < words.size(); s++){
            qDebug() << words[s];
        }

    }
    else {
        qCritical() << "File not found";

        return false;
    }

    return true;
}


/*
*   WRITE FILE
*   write to the uploaded text file
*/
bool QueryBuilder::writeToFile(QFile file)
{

    if(file.open(QFile::WriteOnly)){

        QTextStream stream(&file);

        stream << "Hello World";
        file.rename(fileName);
    }
    else {
        qCritical() << "File stream already closed";

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
 * SPLIT LINE
* Split line into words separated by comma
*/
void QueryBuilder::split(QByteArray line){
     QString w;

    for(int i =0; i < line.size()-1; i++)
    {

        QChar c = line[i];

        if(c == ',') {                              //add word to arrayList

            w.replace(" ","");                      //trim any white spaces
            words.append(w);
            w.clear();                              //reset string for further usage

            continue;
        }

        w.append(c);                             //add letter to a word
    }

}

/*
* SET FILEPATH
* Define the location of the data file
*/
bool QueryBuilder::setPath(QString path){

    fileName = path;

    return true;
}
