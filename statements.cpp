#include "statements.h"

Statements::Statements()
{
    _delete = "DELETE FROM {table_name}\n";
    _insert = "INSERT INTO  {table_name}()\n";
    _update = "UPDATE {table_name}\n";
    _value  = "VALUES ";
    whereActive = 0;
}

Statements::~Statements(){

    delete this;
    qDebug() << "Statements delete constructor activated";
}



/*
*   MYSQL DELETE STATEMENT
*   drop rows based on the first column of data
*/
bool Statements::deleteStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file){

    QTextStream stream(&file);

    for(int i = 0; i < lineCounter; i++)
    {
       stream << _delete;
       stream << _where;
       stream << validateTextString(data[i][0]) << ";\n\n";
    }
    stream << "\n";
    file.close();

    return true;
}



/*
*   MYSQL INSERT STATEMENT
*   output data into a complete insert statement format
*/
bool Statements::insertStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file){

    QTextStream stream(&file);


    stream << _insert;

    for(int i = 0; i < lineCounter; i++)
    {
        stream << _value << " (";
        for(int o = 0; o < wordCounter; o++){

            (o != data[i].size()-1) ? (stream << validateTextString(data[i][o]) << ",") : (stream << validateTextString(data[i][o]));
        }

        (i == lineCounter-1) ? (stream << ")") : (stream << "),\n");
    }

    stream << ";\n";
    file.close();

    return true;
};



/*
*   MYSQL UPDATE STATEMENT
*   compile a list of data to update
*/
bool Statements::updateStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file){

    QTextStream stream(&file);

    //validate where clause
    (!_where.isEmpty()) ? whereActive = 1 : whereActive;


    for(int i = 0; i < lineCounter; i++)
    {
        stream << _update;

        switch(whereActive){

        case 1:
            for(int o = 0; o < wordCounter; o++){ // row data

                //IF First line                                                                            //ELSE if not last word of row                                                                   // if last word of row
                (o == 0) ? (stream << "SET {column_name} = " << validateTextString(data[i][o]) << ", ") : (o != wordCounter-1) ? (stream << " {column_name} = " << validateTextString(data[i][o]) << ",") : (stream << " {column_name} = " << validateTextString(data[i][o]) << "\n");

            }

            stream << _where << ";\n\n";
            break;

        default:

            for(int o = 0; o < wordCounter; o++){ // row data

                //IF First line                                                                            //ELSE if not last word of row                                                                   // if last word of row
                (o == 0) ? (stream << "SET {column_name} = " << validateTextString(data[i][o]) << ", ") : (o != wordCounter-1) ? (stream << " {column_name} = " << validateTextString(data[i][o]) << ",") : (stream << " {column_name} = " << validateTextString(data[i][o]) << ";\n");

            }

            stream << "\n\n";
            break;
        }
    }
    stream << "\n";
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
*   set a where clause to return
*/
void Statements::setWhere(QString s){

    _where = s;
}
