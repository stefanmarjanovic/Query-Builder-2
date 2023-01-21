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

        }

    }
    else {
        qCritical() << "File not found";

        alert.setText("File not found. Please check your file path.");
        alert.exec();

        return false;
    }

    writeToFile(words);

    return true;
}


/*
*   WRITE FILE
*   write to the uploaded text file
*/

bool QueryBuilder::writeToFile(QList<QString> words)
{
    QFile file("/Users/stefanmarjanovic/Git/Query Builder/output.txt");


    if(file.open(QFile::WriteOnly | QFile::Text | QFile::Append)){

        QTextStream stream(&file);

        //stream << "Hello World";
        qDebug() << "Printing Stream: ";

        stream << "(";
        for(int i = 0; i < words.size(); i++)
        {
            //wrap words with quotes
            //check if integer or string
            //words per line
            stream << words[i] << "," << words[i+1] << "," << words[i+2] << "," << words[i+3] << "\n";
            i += 3;
        }
        stream << ")";

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


    for(int i = 0; i < line.size(); i++)
    {

        QChar c = line[i];

        //add word to arrayList
        if(c == ','|| i == line.size()-1) {

            w.replace(" ","");                      // trim any white spaces
            words.append(w);
            w.clear();                              // reset string for further usage

            wordsPerLine++;                         // counter for words per line
            continue;
        }

        w.append(c);                             // add letter to form a word
    }

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

void QueryBuilder::validateTextString(QString w){

      if(!w.toInt()) {

          w.append('"');
          w.prepend('"');

      }

}

void QueryBuilder::on_pushButton_clicked(){

    readFile();
}


