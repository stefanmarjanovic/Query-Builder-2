#include "statements.h"

Statements::Statements()
{
    _delete = "DELETE FROM {table_name}\n";
    _column = "{column_name}";
    _insert = "INSERT INTO  {table_name}()\n";
    _update = "UPDATE {table_name}\n";
    _value  = "VALUES ";
    _where  = "WHERE ";
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
bool Statements::deleteStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber){

    QTextStream stream(&file);

    for(int i = 0; i < lineNumber; i++)
    {
       stream << _delete;
       stream << _where << " ";
       stream << validateTextString(data[i][0]) << ";\n\n";
       qDebug() << data[i][0] << ";\n\n";
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
bool Statements::insertStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter){

    QTextStream stream(&file);

    //pass columns names, index (not required, query type
    formatColumns(&columns,0,2);
    stream << _insert;

    for(int i = 0; i < lineNumber; i++)
    {
        stream << _value << " (";
        for(int o = 0; o < (wordCounter/lineNumber); o++){

            (o != (wordCounter/(lineNumber)-1)) ? (stream << validateTextString(data[i][o]) << ",") : (stream << validateTextString(data[i][o]));
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
bool Statements::updateStatement(QVector<QList<QString>> &data, QVector<QString> &columns, QFile &file, int lineNumber, int wordCounter){

    QTextStream stream(&file);

    //validate where clause
    (_where != "WHERE ") ? whereActive = 1 : whereActive;

    for(int i = 0; i < lineNumber; i++)
    {
        stream << _update;

        switch(whereActive){

        case 1:

            for(int o = 0; o < (wordCounter/lineNumber); o++){ // row data

                //IF First line                                                                                                 //ELSE if not last word of row                                                                               // if last word of row
                (o == 0) ? (stream << "SET " <<  getNextColumn(&columns, o) << " = " << validateTextString(data[i][o]) << ", ") : (o != (wordCounter/(lineNumber)-1)) ? (stream << getNextColumn(&columns, o) << " = " << validateTextString(data[i][o]) << ", ") : (stream <<  getNextColumn(&columns, o) << " = " << validateTextString(data[i][o]) << "\n");

            }

            stream << _where << ";\n\n";
            break;

        default:

            for(int o = 0; o < (wordCounter/lineNumber); o++){ // row data

                //IF First line                                                                                                 //ELSE if not last word of row                                                                               // if last word of row
                (o == 0) ? (stream << "SET " <<  getNextColumn(&columns, o) << " = " << validateTextString(data[i][o]) << ", ") : (o != (wordCounter/(lineNumber)-1)) ? (stream << getNextColumn(&columns, o) << " = " << validateTextString(data[i][o]) << ", ") : (stream << getNextColumn(&columns, o) << " = " << validateTextString(data[i][o]) << ";\n");

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
 *  prints the next column if it has been initialised, otherwise print the placeholder
 */
QString Statements::getNextColumn(QVector<QString> *columns, int index){

    QString w = columns->at(index);
    qDebug() << "cv: " <<  w;

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
void Statements::formatColumns(QVector<QString> *columns, int index, int queryType){

    switch(queryType){

        //update
        case 1:

            break;

        //insert
        case 2:

             //if(!columnsSet) break;

            _insert = "INSERT INTO  {table_name}(";
            for(int i = 0; i < columns->size(); i++){

                _insert += getNextColumn(columns, i);
                (i == columns->size()-1) ? getNextColumn(columns, i) += ")\n" : getNextColumn(columns, i) += ",";             //if last column add closing bracket
            }
            break;

        //delete
        case 3:

            break;
    }
}






