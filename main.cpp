#include "querybuilder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QueryBuilder w;
    QList<QString> words;

     /*
    *   READ FILE
    *   read the uploaded text file
    */
    QString fileName = "/Users/stefanmarjanovic/Git/Query Builder/suspects.txt";
    QFile file(fileName);

    if(file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File found successfully./nReading file in progress/n";

        while(!file.atEnd()){

            QByteArray line = file.readLine();
            QString w;

            /*
            * Split line into words separated at the comma
            */
            for(int i =0; i < line.size()-1; i++)
            {

                QChar c = line[i];

                if(c == ',') {                              //add word to arrayList

                    w.replace(" ","");                      //trim any white spaces
                    words.append(w);
                    w.clear();                              //reset string for further usage

                    continue;
                }

                w.append(c);                             //add letter to a word
            }

        }

        for(int s = 0; s < words.size(); s++){
            qDebug() << words[s];
        }

    }
    else {
        qCritical() << "File note found";
    }


    /*
    *   WRITE FILE
    *   write to the uploaded text file
    */
//    if(file.open(QFile::WriteOnly)){

//        QTextStream stream(&file);

//        while(!file.atEnd()){

//           stream << "'";
//        }
//    }



    file.flush();                           // flush the file
    file.close();                           // close the file

    qDebug() << "Application Exited";
    //w.show();
    return a.exec();
}
