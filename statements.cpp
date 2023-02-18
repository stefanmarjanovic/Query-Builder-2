#include "statements.h"

Statements::Statements()
{
    _delete = "DELETE FROM";
    _column = "`column_name`";
    _insert = "INSERT INTO  `table_name`()\n";
    _table = "`table_name`";
    _update = "UPDATE ";
    _value  = "VALUES ";
    _where  = "WHERE ";
    orderBy = 0;
    groupBy = 0;
    whereActive = 0;
    columnsSet = false;
}

Statements::~Statements(){

    delete this;
}



/*
*   MYSQL DELETE STATEMENT
*   drop rows based on the first column of data
*/
bool Statements::deleteStatement(QVector<QList<QString>> &data, QFile &file, int lineNumber, QString column, int columnIndex, QString table){

    QTextStream stream(&file);
    (!table.isEmpty()) ? _table = table : _table;           //use table name if it is set
    _where = "WHERE ";                                      //reset where clause

    for(int i = 0; i < lineNumber; i++)
    {
       stream << _delete << " " << _table << "\n";
       stream << _where << " " << column << " = ";
       stream << validateTextString(data[i][columnIndex]) << ";\n\n";
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
bool Statements::insertStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet, QString table){

    QTextStream stream(&file);    
    (!table.isEmpty()) ? _table = table : _table;           //use table name if it is set

    //check for columns
    columnsSet = isColSet;
    int wordsPerLine = (wordCounter/lineNumber);

    //pass columns names, index (not required), query type
    formatColumnsInsert(&columns, columnsSet, wordsPerLine, _table);
    stream << _insert;

    for(int i = 0; i < lineNumber; i++)
    {
        stream << _value << " (";
        for(int o = 0; o < wordsPerLine; o++){

            //if not last word in row add a comma
            (o != (wordsPerLine)-1) ? (stream << validateTextString(data[i][o]) << ",") : (stream << validateTextString(data[i][o]));
        }

        //print closing bracket and comma if not last line
        (i == lineNumber-1) ? (stream << ")") : (stream << "),\n");
    }
    stream << ";\n\n";

    file.flush();
    file.close();

    return true;
};



/*
*   MYSQL UPDATE STATEMENT
*   compile a list of data to update
*/
bool Statements::updateStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter, bool isColSet,  QString table){

    QTextStream stream(&file);
    (!table.isEmpty()) ? _table = table : _table;           //use table name if it is set

    //check for columns
    columnsSet =  isColSet;

    //validate where clause
    (_where != "WHERE ") ? whereActive = 1 : whereActive;

    for(int i = 0; i < lineNumber; i++)
    {
        stream << _update << table << "\n";

        switch(whereActive){

            case 1:

                for(int o = 0; o < (wordCounter/lineNumber); o++){ // print row data

                    formatColumnsUpdate(&columns,o,columnsSet);
                    //IF First line                                                                                 //ELSE if not last word of row                                                                               // if last word of row
                    (o == 0) ? (stream << "SET " <<  _column << " = " << validateTextString(data[i][o]) << ", ") : (o != (wordCounter/(lineNumber)-1)) ? (stream << _column << " = " << validateTextString(data[i][o]) << ", ") : (stream <<  _column << " = " << validateTextString(data[i][o]) << "\n");

                }

                stream << _where << ";\n\n";
                break;

            default:

                for(int o = 0; o < (wordCounter/lineNumber); o++){ // print row data

                    formatColumnsUpdate(&columns,o,columnsSet);
                    //IF First line                                                                                 //ELSE if not last word of row                                                                               // if last word of row
                    (o == 0) ? (stream << "SET " <<  _column << " = " << validateTextString(data[i][o]) << ", ") : (o != (wordCounter/(lineNumber)-1)) ? (stream << _column << " = " << validateTextString(data[i][o]) << ", ") : (stream << _column << " = " << validateTextString(data[i][o]) << ";\n");

                }

                stream << "\n";
                break;
        }
    }
    stream << "\n";

    file.flush();
    file.close();

    return true;
};


/*
 *  PRINT NEXT COLUMN
 *  prints the column at the index if it has been initialised, otherwise print the {column} placeholder
 */
QString Statements::getColumn(QVector<QString> *columns, int index){

    QString w = columns->at(index);

    return (!w.isEmpty() ? w : _column = "`column_name`" );
}



/*
*   GET WHERE CLAUSE
*   return where string
*/
QString Statements::getWhere(){

    return (!_where.isEmpty()) ? _where : _where = ";\n";
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

    QString select = QString("SELECT ").arg(columns).append(" FROM ").arg(tableName);

    if(!where.isEmpty()) select.append(where);


    return select;
}



/*
 *  CLEAR WHERE CLAUSE
 *  resets the where clause
 */
void Statements::clearWhere(){

    _where = "WHERE ";

    qDebug() << "STATEMENT CLASS where: " << _where;
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
 *
 *  insert statement
 */
void Statements::formatColumnsInsert(QVector<QString> *columns,bool columnsSet, int wordPerLine, QString table){

    switch(columnsSet){
        case 0:         // columns undefined

            _insert = QString("INSERT INTO  ").append(table).append(" (");
            for(int i = 0; i < wordPerLine; i++){

                 (i == wordPerLine-1) ? _insert += "`column_name`)\n" : _insert += "`column_name`,";
            }

            break;

        case 1:         //  columns defined

            _insert = QString("INSERT INTO  ").append(table).append(" (");
            for(int i = 0; i < columns->size(); i++){

                (i == columns->size()-1) ? _insert += (getColumn(columns, i) += ")\n") : _insert += (getColumn(columns, i) += ",");

            }

            break;
    }
}



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
