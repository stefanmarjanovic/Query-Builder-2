#include "data.h"
#include "QtCore/qforeach.h"
#include <QRegularExpression>

Data::Data()
{

    s = new Statements();
    wordCounter = -1;
    lineCounter = -1;
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

        //read line into Class
        qDebug() << "Line Count" << lineCounter;
        for(int i = 0; i < lineCounter; i++)
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

    //debugMatrix(matrix);

    return true;
}


/*
*   READ FILE
*   read the uploaded text file and trigger the ouput file
*/
bool Data::generate(QString inputPath, QString outputPath, int queryOption){

    parseText(inputPath);
    writeToFile(matrix,outputPath,queryOption);

    return true;
}



/*
*   WRITE FILE
*   write to the uploaded text file
*/
bool Data::writeToFile(QVector<QList<QString>> data, QString outputPath, int queryOption){

    QFile file(outputPath);
    querySelector = queryOption;

    if(file.open(QFile::WriteOnly | QFile::Text | QFile::Append)){

        switch(querySelector){
            case 1:

                s->setWhere(this->getWhere());
                s->updateStatement(data, lineCounter,wordCounter, file);
                qDebug() << "Update Statement";
                break;

            case 2:

                s->setWhere(this->getWhere());
                s->insertStatement(data, lineCounter,wordCounter, file);
                qDebug() << "Insert Statement";
                break;

            case 3:

                s->setWhere(this->getWhere());
                s->deleteStatement(data, lineCounter,/*wordCounter,*/ file);
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
bool Data::validateColumns(QString s){

    // read words text
    // calculate words per line
    // compare to column list
    QFile dataFile(s);
    QTextStream read(&dataFile);

    if(dataFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Counting lines\n";

        //count lines
        countLines(&read);
        dataFile.reset();

        qDebug() << "Counting words\n";
        //count words
        countWords(&dataFile);

        dataFile.flush();
        dataFile.close();
    }
    else {

        dataFile.flush();
        dataFile.close();
        qCritical() << "File not found";
        return false;
    }

    qDebug() << "Words per line: " << (wordCounter / lineCounter);

    return true;
}


/*
 *  VALIDATE FILE
 *  Check if the source file exists
 */
bool Data::validateFile(QString s){

    QString inputfilepath = s;

    QFile dataFile(inputfilepath);
    if(dataFile.open(QFile::ReadOnly | QFile::Text)) return true;

    return false;
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
        lineCounter++;

        qDebug() << "Line: " << lineCounter << " " << line;

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
        line = dataFile->readLine();

        // split line into words and count words per line
        foreach(QString word, line.split(',')){

            wordCounter++;
            qDebug() << "Word " << wordCounter  << ": " << word ;
        }

    }
    while(!line.isNull());

    qDebug() << "Total Words: " << wordCounter;
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
 *  RETURN THE NUMBER OF WORDS PER LINE
 *  returns the amount of elements a.k.a words per line use for comparison
 */
int Data::getTotalWordsPerLine(){

    qDebug() << "Column Count in Data class: " << (wordCounter / lineCounter);

    return (wordCounter / lineCounter);
}



/*
 *  CLEAR COLUMNS
 *  clear columns added to the columns array list
 */
void Data::clearList(){

    qDebug() << "Clear columns list";
    columns.clear();
}
