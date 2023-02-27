#include "data.h"
#include "QtCore/qforeach.h"
#include <QRegularExpression>

Data::Data()
{

    s = new Statements();
    wordCounter = -1;       // no current selection
    lineCounter = -1;
    querySelector = -1;
    columnListSelected = 0;
    firstLine = 0;
    _where = "";

}


Data::~Data(){

}



/*
 *  CHECK COLUMNS SET
 *  return true if the user has input column names
 */
bool Data::checkColumnsSet(){

    return !columns.isEmpty();
}



/*
 *  COMPARE COLUMN SIZE
 *  Compares the user input columns to the amount of words per line in data source
 */
bool Data::compareColumnSize(){

    if(firstLine && (columns.size() != getTotalWordsPerLine())) {

        setAlert("Columns added do not match file columns in file.");
        return false;
    }

    return true;
}



/*
 *  READ TEXT FILE
 *  Reads the text file & counts the words when the file path is added but does not trigger the output yet.
 */
bool Data::parseText(QString i){

    QFile dataFile(i);
    QTextStream read(&dataFile);
    QByteArray line;

    if(dataFile.open(QFile::ReadOnly | QFile::Text)){

        //read lines into Class
        for(int i = 0; i < lineCounter; i++)
        {            
            if(firstLine == true && i == 0) {                             //read first line and set as columns

                line = dataFile.readLine();
                getFirstLine(line);
                continue;
            }

            line = dataFile.readLine();
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
    this->reset();

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

                // if check first line flag set adjust line & word counter
                (firstLine) ? (lineCounter = matrix.size()) : lineCounter;
                (firstLine) ? (wordCounter = matrix[0].size()*matrix.size()) : wordCounter;

                //if columns don't match do not continue;
                if(!compareColumnSize()) return false;

                s->setWhere(this->getWhere());
                s->updateStatement(data, columns, file, matrix.size(), (matrix[0].size()*matrix.size()), checkColumnsSet(), _tableName);

                break;

            case 2:

                // if check first line flag set adjust line & word counter
                (firstLine) ? (lineCounter = matrix.size()) : lineCounter;
                (firstLine) ? (wordCounter = matrix[0].size()*matrix.size()) : wordCounter;

                //if columns don't match do not continue;
                if(!compareColumnSize()) return false;

                s->setWhere(this->getWhere());
                s->insertStatement(data, columns, file, lineCounter, wordCounter, checkColumnsSet(), _tableName);

                break;

            case 3:

                // if check first line flag set adjust line & word counter
                (firstLine) ? (lineCounter = matrix.size()) : lineCounter;
                (firstLine) ? (wordCounter = matrix[0].size()*matrix.size()) : wordCounter;

                //if columns don't match do not continue;
                if(!compareColumnSize()) return false;

                s->setWhere(this->getWhere());
                s->deleteStatement(data, file, lineCounter, getNextColumn(columnListSelected),columnListSelected, _tableName);

                break;
        }
        //  - /Users/Personal/Git/query-builder-2/dirtsheet.txt



    }
    else {

        qCritical() << "Output path not set.";
        setAlert("Output path not set. Please enter a valid folder path and filename");

        return false;
    }

    setAlert("File exported successfully.");
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
 *  GET WHERE CLAUSE
 *  return where input string from wherediag box
 */
QString Data::getWhere(){


    return _where;
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
 *  RETURN THE NUMBER OF WORDS PER LINE
 *  returns the amount of elements a.k.a words per line use for comparison
 */
int Data::getTotalWordsPerLine(){

    return (wordCounter / lineCounter);
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
 *  CLEAR COLUMNS
 *  clear columns added to the columns array list
 */
void Data::clearColumnList(){

    columns.clear();
}



/*
 *  CLEAR WHERE CLAUSE
 *  calls the statement class to reset the where clause
 */
void Data::clearWhere(){

    _where.clear();
    s->clearWhere();
}



/*
 *  LINE COUNTER
 *  counts the number of lines in a file.
 */
void Data::countLines(QTextStream *in){
    QString line;

    do
    {
        if(firstLine == true && lineCounter == -1) continue;   //skip first line of columns
        line = in->readLine();
        lineCounter++;

    }
    while(!line.isNull());

    if(firstLine == true) lineCounter--;
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

            if(firstLine == true && wordCounter == -1) continue;   //skip first line of columns
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
 *  GET COLUMNS INDEX
 *  set the position number of the selected column
 */
void Data::getColumnIndex(int i){

    columnListSelected = i-1;
}



/*
 *  GET FIRST LINE
 *  Read the first line of data as columns
 */
void Data::getFirstLine(QByteArray line){

    QString w;

    foreach(QByteArray word, line.split(',')){

        w = word;

        addColumnToList(trimRegex(trim(w)));
    }

}

void Data::printColumns(){

    for(int i = 0; i < columns.size(); i++)
    {

        qDebug() << "Column " << i << ": " << columns[i];
    }
}

/*
 *  RESET
 *  reset data class by running the constructor again
 */
void Data::reset(){

    matrix.clear();
    columns.clear();
    wordCounter = -1;
    lineCounter = -1;
    querySelector = -1;
    columnListSelected = 0;
    firstLine = 0;
    _where = "";
}

/*
 *  FIRST LINE
 *  When active, this indicates the first line is to be parsed as column names
 */
void Data::setFirstLine(bool c){

    firstLine = c;
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
 *  SET TABLE NAME
 *  get the table name from the main window
 */
void Data::setTableName(QString s){

    QString table = s;

    if(!table.isEmpty()){

        _tableName = table.prepend("`").append("`");
    } else {

        _tableName = "`table_name`";
    }

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
