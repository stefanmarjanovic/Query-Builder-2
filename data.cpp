#include "data.h"
#include "QtCore/qforeach.h"
#include <QRegularExpression>

Data::Data()
{

    s = new Statements();
    wordCounter = 0;
    lineNumber = 0;
    querySelector = -1;             // no current selection
    qDebug() << "Data Constructor called";

}


Data::~Data(){

    qDebug() << "Data delete constructor activated";
}



/*
 *  READ TEXT FILE
 *  Reads the text file & counts the words when the file path is added but does not trigger the output yet.
 */
bool Data::parseText(QString i){

    QFile dataFile(i);
    QTextStream read(&dataFile);

    if(dataFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File found successfully.\nReading file in progress\n";

        //count lines
        countLines(&read);
        dataFile.reset();

        //count words
        countWords(&dataFile);
        dataFile.reset();

        //read line into Class
        for(int i = 0; i < (lineNumber-1); i++)
        {
            QByteArray line = dataFile.readLine();
            splitLine(line);
        }

        dataFile.flush();
        dataFile.close();
    }
    else {

        dataFile.flush();
        dataFile.close();
        qCritical() << "File not found";
        return false;
    }

    return true;
}


/*
*   READ FILE
*   read the uploaded text file and trigger the ouput file
*/
bool Data::generate(QString inputPath, QString outputPath, int queryOption){

    parseText(inputPath);
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

                s->setWhere(this->getWhere());
                s->updateStatement(data, lineNumber,wordCounter, file);
                qDebug() << "Update Statement";
                break;

            case 2:

                s->setWhere(this->getWhere());
                s->insertStatement(data, lineNumber,wordCounter, file);
                qDebug() << "Insert Statement";
                break;

            case 3:

                s->setWhere(this->getWhere());
                s->deleteStatement(data, lineNumber,/*wordCounter,*/ file);
                qDebug() << "Delete Statement";
                break;
        }
        //  - /Users/Personal/Git/query-builder-2/suspects.txt


        setAlert("File exported successfully.");
        qDebug() << "File exported successfully";
    }
    else {

        qCritical() << "Output path not set.";
        setAlert("Output path not set. Please enter a valid folder path and filename");

        return false;
    }

    return true;
}




/*
 *
 *
 */
bool Data::validateColumns(){

    // read words text
    // calculate words per line
    // compare to column list



    return true;
}



bool validateFile(){


}



/*
 *  GET WHERE CLAUSE
 *  return where input string from wherediag box
 */
QString Data::getWhere(){


    return _where;
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
 *  ADD COLUMN
 *  add string from UI to column list
 */
void Data::addColumnToList(QString c){

       columns.append(c);

       qDebug() << c << " added to columns list";
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
 *  WORD COUNTER
 *  counts the number of fields a.k.a "words" in a file.
 */
void Data::countWords(QFile *dataFile){
    QString line;

    do
    {
        QByteArray line = dataFile->readLine();
        splitLine(line);
    }
    while(!line.isNull());
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



/*
*   ALERT MESSAGE BOX
*   call this function to alert the user of any issues
*/
void Data::setAlert(QString s){

    alert.setText(s);
    alert.show();
}



/*
 *  SET WHERE CLAUSE
 *  set where input string from wherediag box
 */
void Data::setWhere(QString s){

    _where = s;
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
 *  CLEAR COLUMNS
 *  clear columns added to the columns array list
 */
void Data::clearList(){

    qDebug() << "Clear columns list";
    columns.clear();
}
