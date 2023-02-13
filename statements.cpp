#include "statements.h"

Statements::Statements()
{
    _delete = "DELETE FROM {table_name}\n";
    _column = "`column_name`";
    _insert = "INSERT INTO  {table_name}()\n";
    _update = "UPDATE {table_name}\n";
    _value  = "VALUES ";
    _where  = "WHERE ";
    orderBy = 0;
    groupBy = 0;
    whereActive = 0;
    columnsSet = false;
    qDebug() << "Statement Constructor called";
}

Statements::~Statements(){

    delete this;
    qDebug() << "Statements delete constructor activated";
}



/*
*   MYSQL DELETE STATEMENT
*   drop rows based on the first column of data
*/
bool Statements::deleteStatement(QVector<QList<QString>> &data, QFile &file, int lineNumber, int columnIndex){

    QTextStream stream(&file);

    for(int i = 0; i < lineNumber; i++)
    {
       stream << _delete;
       stream << _where << " ";
       stream << validateTextString(data[i][columnIndex]) << ";\n\n";
       qDebug() << data[i][columnIndex] << ";\n\n";
    }
    stream << "\n";

    file.flush();
    file.close();

    return true;
}



/*
*   MYSQL INSERT STATEMENT
*   output data into a complete insert statement format
*/
bool Statements::insertStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet){

    QTextStream stream(&file);    

    //check for columns
    columnsSet = isColSet;
    qDebug() << "Columns set:" << columnsSet;
    int wordsPerLine = (wordCounter/lineNumber);

    //pass columns names, index (not required), query type
    formatColumnsInsert(&columns, columnsSet, wordsPerLine);
    stream << _insert;

    for(int i = 0; i < lineNumber; i++)
    {
        stream << _value << " (";
        for(int o = 0; o < wordsPerLine; o++){

            (o != (wordsPerLine)-1) ? (stream << validateTextString(data[i][o]) << ",") : (stream << validateTextString(data[i][o]));
        }

        (i == lineNumber-1) ? (stream << ")") : (stream << "),\n");
    }
    stream << ";\n";

    file.flush();
    file.close();

    return true;
};



/*
*   MYSQL UPDATE STATEMENT
*   compile a list of data to update
*/
bool Statements::updateStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet){

    QTextStream stream(&file);

    //check for columns
    columnsSet =  isColSet;

    //validate where clause
    (_where != "WHERE ") ? whereActive = 1 : whereActive;

    for(int i = 0; i < lineNumber; i++)
    {
        stream << _update;

        switch(whereActive){

            case 1:

                for(int o = 0; o < (wordCounter/lineNumber); o++){ // row data

                    formatColumnsUpdate(&columns,o,columnsSet);
                    //IF First line                                                                                 //ELSE if not last word of row                                                                               // if last word of row
                    (o == 0) ? (stream << "SET " <<  _column << " = " << validateTextString(data[i][o]) << ", ") : (o != (wordCounter/(lineNumber)-1)) ? (stream << _column << " = " << validateTextString(data[i][o]) << ", ") : (stream <<  _column << " = " << validateTextString(data[i][o]) << "\n");

                }

                stream << _where << ";\n\n";
                break;

            default:

                for(int o = 0; o < (wordCounter/lineNumber); o++){ // row data

                    formatColumnsUpdate(&columns,o,columnsSet);
                    //IF First line                                                                                 //ELSE if not last word of row                                                                               // if last word of row
                    (o == 0) ? (stream << "SET " <<  _column << " = " << validateTextString(data[i][o]) << ", ") : (o != (wordCounter/(lineNumber)-1)) ? (stream << _column << " = " << validateTextString(data[i][o]) << ", ") : (stream << _column << " = " << validateTextString(data[i][o]) << ";\n");

                }

                stream << "\n\n";
                break;
        }
    }
    stream << "\n";

    file.flush();
    file.close();

    return true;
};



/*
*   GET WHERE CLAUSE
*   return where string
*/
QString Statements::getWhere(){

    return (!_where.isEmpty()) ? _where : _where = ";\n";
}



/*
 *  PRINT NEXT COLUMN
 *  prints the column at the index if it has been initialised, otherwise print the {column} placeholder
 */
QString Statements::getColumn(QVector<QString> *columns, int index){

    QString w = columns->at(index);

    return (!w.isEmpty() ? w : _column );
}



/*
*   VALIDATE TYPE
*   if string wrap in double quotes
*/
QString Statements::validateTextString(QString w){

      if(!w.toInt()) {

          w.append('"');
          w.prepend('"');

      }

      return w;
}



/*
*   SELECT STATEMENT
*   construct a select statement - unused
*/
QString Statements::selectStatement(){

    QString columns;
    QString tableName;
    QString where;
    //QString orderBy;
    //QString groupBy;

    QString select = QString("SELECT ").arg(columns).append(" FROM ").arg(tableName);

    if(!where.isEmpty()) select.append(where);


    return select;
}



/*
*   SET WHERE CLAUSE
*   set a where clause
*/
void Statements::setWhere(QString s){

    _where += s;
}




/*
 *  FORMAT COLUMN
 *  Based on the type of query select format the columns in the appropriate format before printing
 */
// update statement
void Statements::formatColumnsUpdate(QVector<QString> *columns, int index, bool columnsSet){

    try{
        if(columnsSet) {

            _column = getColumn(columns, index);

        } else {

            throw (_column);
            _column.clear();
            _column = "`column_name`";
        }

    } catch(QString col){

        qCritical() << "Columns uninstantiated" << col;

    }
}


// insert statement
void Statements::formatColumnsInsert(QVector<QString> *columns,bool columnsSet, int wordPerLine){

    switch(columnsSet){
        case 0:         // columns undefined

            _insert = "INSERT INTO  {table_name} (";
            for(int i = 0; i < wordPerLine; i++){

                 (i == wordPerLine-1) ? _insert += "`column_name`)\n" : _insert += "`column_name`,";
            }

            break;

        case 1:         //  columns defined

            _insert = "INSERT INTO  {table_name} (";
            for(int i = 0; i < columns->size(); i++){

                (i == columns->size()-1) ? _insert += (getColumn(columns, i) += ")\n") : _insert += (getColumn(columns, i) += ",");

            }

            break;
    }
}


// delete statement
void Statements::formatColumnsDelete(QVector<QString> *columns, int index, bool columnsSet){




}

