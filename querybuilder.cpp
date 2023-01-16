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
bool QueryBuilder::readFile(QString path)
{
    QString fileName = path;
    QFile file(fileName);

    if(file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File found successfully./nReading file in progress/n";

        while(!file.atEnd()){

            QByteArray line = file.readLine();
            split(line);

        }

        for(int s = 0; s < words.size(); s++){
            qDebug() << words[s];
        }

    }
    else {
        qCritical() << "File note found";

        return false;
    }

    return true;
}


/*
*   WRITE FILE
*   write to the uploaded text file
*/
bool QueryBuilder::writeToFile()
{


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

    return true;
}
