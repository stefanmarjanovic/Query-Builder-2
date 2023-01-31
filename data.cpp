#include "data.h"


Data::Data(MainWindow &u)
{
    ui = &u;
    wordCounter = 0;
    lineCounter = 0;
    querySelector = -1;             // -1 = no current selection
}


Data::~Data(){

    qDebug() << "Data delete constructor activated";
}



/*
*   READ FILE
*   read the uploaded text file
*/
bool Data::readFile(){

    QFile dataFile(ui->getInputPath());

    if(dataFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File found successfully.\nReading file in progress\n";

        // split by line
        while(!dataFile.atEnd()){

            QByteArray line = dataFile.readLine();
            splitLine(line);

            lineCounter++;
        }

    }
    else {

        qCritical() << "File not found";
        ui->setAlert("File not found. Please check your file path.");

        return false;
    }

    writeToFile(matrix);

    return true;
}



/*
*   WRITE FILE
*   write to the uploaded text file
*/
bool Data::writeToFile(QVector<QList<QString>> data){

    QFile file(ui->getOutputPath());

    qDebug() << "Selection query selection: " << ui->getSelection();

    if(file.open(QFile::WriteOnly | QFile::Text | QFile::Append)){

        switch(ui->getSelection()){
            case 1:

                s.setWhere(ui->getWhereClause());
                s.updateStatement(data, lineCounter,wordCounter, file);
                qDebug() << "Update Statement";
                break;

            case 2:

                s.setWhere(ui->getWhereClause());
                s.insertStatement(data, lineCounter,wordCounter, file);
                qDebug() << "Insert Statement";
                break;

            case 3:

                s.setWhere(ui->getWhereClause());
                s.deleteStatement(data, lineCounter,wordCounter, file);
                qDebug() << "Delete Statement";
                break;
        }
        //  - /Users/Personal/Git/query-builder-2/suspects.txt
        ui->setAlert("File exported successfully.");
    }
    else {

        qCritical() << "Output path not set.";
        ui->setAlert("Output path not set. Please enter a valid folder path and filename");

        return false;
    }

    return true;
}



/*
*   TRIM STRING
*   remove trailing spaces from a word
*/
QString Data::trim(QString s){

    return ((s[0] == ' ') || (s.back() == ' ')) ? s.replace(" ","") : s;
}



/*
*   SPLIT LINE
*   Split line into words separated by comma
*/
void Data::splitLine(QByteArray line){

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
*   DEBUG 2D ARRAY
*   print the matrix rows and columns to the console logging
*/
void  Data::debugMatrix(QVector<QList<QString>> matrix){

    qDebug() << "Matrix size: " << matrix.size();
    for(int i = 0; i < matrix.size(); i++)
     {
         qDebug() << "Row " << i + 1 << ": " << matrix[i];

         for(int o = 0; o < matrix[i].size(); o++){

            qDebug() << "Column " << o + 1 << ": " << matrix[i][o];
         }
     }
}
