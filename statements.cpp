#include "statements.h"

statements::statements()
{
    _alter = "ALTER TABLE {table_name}\n";
    _insert = "INSERT INTO  {table_name}()\n";
    _update = "UPDATE {table_name}\n";
    _where = "WHERE ";
    _value = "VALUES ";
}


/*
*   MYSQL ALTER STATEMENT
*

bool statements::alterStatement(QList<QString> data, int lineCounter, int wordCounter, QFile &file){


}
*/


/*
*   MYSQL DELETE STATEMENT
*

bool statements::deleteStatement(QList<QString> data, int lineCounter, int wordCounter, QFile &file){


}
*/


/*
*   MYSQL INSERT STATEMENT
*   output data into a complete insert statement format
*/
bool statements::insertStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file){

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

    stream << ";";
    file.close();

    return true;
};



/*
*   MYSQL UPDATE STATEMENT
*   compile a list of data to update
*/
bool statements::updateStatement(QVector<QList<QString>> data, int lineCounter, int wordCounter, QFile &file){

    QTextStream stream(&file);

    for(int i = 0; i < lineCounter; i++)
    {
        stream << _update;

        for(int o = 0; o < wordCounter; o++){

            (o == 0) ? (stream << "SET {column_name} = " << validateTextString(data[i][o]) << ", ") : (stream << " {column_name} = " << validateTextString(data[i][o]) << ",");

        }

        stream << "\n"<< _where <<" \n;\n";
    }

    //If where clause is instantied
    (_where != "WHERE ") ? stream << _where : stream << "";

    stream << "\n";
    file.close();

    return true;
};



/*
*   SET WHERE CLAUSE
*   set a where clause to return
*/
QString setWhere(QString s){

    s = NULL;

    return (!s.isEmpty()) ? s : s = ";\n";
}



/*
*   VALIDATE TYPE
*   if string wrap in double quotes
*/
QString statements::validateTextString(QString w){

      if(!w.toInt()) {

          w.append('"');
          w.prepend('"');

      }

      return w;
}
