#include "data.h"
#include "QtCore/qforeach.h"
#include <QRegularExpression>

Data::Data()
{

    s = new Statements();
    wordCounter = 0;
    lineNumber = 0;
    querySelector = -1;             // -1 = no current selection
    qDebug() << "Constructor wordCounter: " << wordCounter;
    qDebug() << "Constructor lineNumber: " << lineNumber;
    qDebug() << "Constructor querySelector: " << querySelector;
}


Data::~Data(){

    qDebug() << "Data delete constructor activated";
}



/*
*   READ FILE
*   read the uploaded text file
*/
bool Data::readFile(QString inputPath, QString outputPath, int queryOption){

    QFile dataFile(inputPath);
    QTextStream read(&dataFile);

    if(dataFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File found successfully.\nReading file in progress\n";
        qDebug() << "Read Function Line number: " << lineNumber;

        //count lines
        countLines(&read);
        dataFile.reset();

        //read line into Class
        for(int i = 0; i < (lineNumber-1); i++)
        {
            QByteArray line = dataFile.readLine();
            splitLine(line);
        }
    }
    else {

        qCritical() << "File not found";
        //ui->setAlert("File not found. Please check your file path.");

        return false;
    }

    dataFile.flush();
    dataFile.close();
    writeToFile(matrix,outputPath,queryOption);
    debugMatrix(matrix);

    return true;
}



/*
*   WRITE FILE
*   write to the uploaded text file
*/
bool Data::writeToFile(QVector<QList<QString>> data, QString outputPath, int queryOption){

    QFile file(outputPath);
    querySelector = queryOption;

    qDebug() << "Query Selector: " << querySelector;

    if(file.open(QFile::WriteOnly | QFile::Text | QFile::Append)){

        switch(querySelector){
            case 1:

                //s.setWhere(ui->getWhereClause());
                s->updateStatement(data, lineNumber,wordCounter, file);
                qDebug() << "Update Statement";
                break;

            case 2:

               // s.setWhere(ui->getWhereClause());
                s->insertStatement(data, lineNumber,wordCounter, file);
                qDebug() << "Insert Statement";
                break;

            case 3:

                //s.setWhere(ui->getWhereClause());
                s->deleteStatement(data, lineNumber,wordCounter, file);
                qDebug() << "Delete Statement";
                break;
        }
        //  - /Users/Personal/Git/query-builder-2/suspects.txt
        //ui->setAlert("File exported successfully.");
        qDebug() << "File exported successfully";
    }
    else {

        qCritical() << "Output path not set.";
       // ui->setAlert("Output path not set. Please enter a valid folder path and filename");

        return false;
    }

    return true;
}



/*
 *  TRIME SPECIAL CHARACTERS
 *  remove trailing characters from each word and strip new line \n \r
 */
QString Data::trimRegex(QString s){

   QString rm = "[\'\"]*[\n\r]*";

    return (s.contains(QRegularExpression(rm))) ? s.remove(QRegularExpression(rm)): s;
}



/*
*   TRIM STRING
*   remove trailing spaces from a word
*/
QString Data::trim(QString s){

    return ((s[0] == ' ') || (s.back() == ' ')) ? s.replace(" ","") : s;
}



/*
 *  LINE COUNTER
 *  counts the number of lines in a file.
 */
void Data::countLines(QTextStream *in){
    QString line;

    do
    {
        line = in->readLine();
        lineNumber++;
    }
    while(!line.isNull());
}



/*
*   SPLIT LINE
*   Split line into words separated by comma
*/
void Data::splitLine(QByteArray line){

    QList<QString> row;
    QString w;

    foreach(QByteArray word, line.split(',')){

        w = word;
        row.append(trimRegex(trim(w)));
        wordCounter++;
    }


    matrix.append(row);
}


/*
 *  RETURN COLUMN INDEX
 *  retrieve a value at the index of the column list
 */
QString Data::getColumnList(int position){

    return columns[position];
}




/*
 *  ADD COLUMN
 *  add string from UI to column list
 */
void Data::addColumnToList(QString c){

       columns.append(c);

       qDebug() << c << " added to columns list";
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
