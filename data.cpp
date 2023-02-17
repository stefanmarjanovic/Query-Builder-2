#include "data.h"
#include "QtCore/qforeach.h"
#include <QRegularExpression>

Data::Data()
{

    s = new Statements();
    wordCounter = -1;
    lineCounter = -1;
    querySelector = -1;             // no current selection
    columnListSelected = 0;
    _where = "";
    qDebug() << "Data Constructor called";

}


Data::~Data(){

    qDebug() << "Data delete constructor activated";
}



/*
 *  CHECK COLUMNS SET
 *  return true if the user has input column names
 */
bool Data::checkColumnsSet(){

    return !columns.isEmpty();
}



/*
 *  READ TEXT FILE
 *  Reads the text file & counts the words when the file path is added but does not trigger the output yet.
 */
bool Data::parseText(QString i){

    QFile dataFile(i);
    QTextStream read(&dataFile);

    if(dataFile.open(QFile::ReadOnly | QFile::Text)){

        //read line into Class
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
                s->updateStatement(data, columns, file, lineCounter, wordCounter, checkColumnsSet());

                break;

            case 2:

                s->setWhere(this->getWhere());
                s->insertStatement(data, columns, file, lineCounter, wordCounter, checkColumnsSet());

                break;

            case 3:

                s->setWhere(this->getWhere());
                s->deleteStatement(data, file, lineCounter, getNextColumn(columnListSelected),columnListSelected);

                break;
        }
        //  - /Users/Personal/Git/query-builder-2/suspects.txt


        setAlert("File exported successfully.");
    }
    else {

        qCritical() << "Output path not set.";
        setAlert("Output path not set. Please enter a valid folder path and filename");

        return false;
    }

    return true;
}




/*
 *  VALIDATE COLUMNS
 *  Counts the amount of columns, words, lines in the file being parsed
 */
bool Data::validateColumns(QString s){

    QFile dataFile(s);
    QTextStream read(&dataFile);

    if(dataFile.open(QFile::ReadOnly | QFile::Text)){

        //count lines
        countLines(&read);
        dataFile.reset();

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
 *  RETURN THE NEXT COLUMN NAME
 *  retrieves the column name that will be passed to the statements for printing
 */
QString Data::getNextColumn(int i){

    QString col;
    (!columns.empty()) ? (col = columns[i]) : (col =  "`column_name`");

    return col;
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

        QString col = c.prepend('`').append('`');

       columns.append(col);
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
        }

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
    }


    matrix.append(row);
}



/*
 *  RETURN THE NUMBER OF WORDS PER LINE
 *  returns the amount of elements a.k.a words per line use for comparison
 */
int Data::getTotalWordsPerLine(){

    return (wordCounter / lineCounter);
}



/*
 *  GET COLUMNS INDEX
 *  set the position number of the selected column
 */
void Data::getColumnIndex(int i){

    columnListSelected = i-1;
}



/*
 *  CLEAR COLUMNS
 *  clear columns added to the columns array list
 */
void Data::clearList(){

    columns.clear();
}



/*
 *  CLEAR WHERE CLAUSE
 *  calls the statement class to reset the where clause
 */
void Data::clearWhere(){

    //_where.clear();
    s->clearWhere();

    qDebug() << "DATA CLASS where: " << this->_where;
}
