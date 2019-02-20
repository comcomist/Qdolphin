/// Under the humanitarian agpl License: http://namzezam.wikidot.com/humanitarian-agpl-license
#ifndef Qdolphin_H
#define Qdolphin_H /// Adding path, plugin and db to the Qdolphin:
/// Add your class with its implementation as a plug, by inserting here 2 lines:
///
/// 1. #include your header here
///     and to avoid missing vtable references (in any polymorphism)
///       if the implementation is writen only in the header,
///           also add the Header file name to the .pro file at
///           the line starting with after      the HEADERS +=,
///       otherwise also add the .cpp after the SOURCES +=
///
/// 2. Expose each of your classed to the qml usage in the
///      qrc/import @ build-directory, by adding
///     one or more of the corresponding line
///      qmlRegisterType.. && ...
///     to the addPlagins function here.
#include <QQmlApplicationEngine>// QQmlApplicationEngine qmlRegisterType #include <QQmlEngine>
///
//#include <QQuickStyle>
//#include <QSettings>
///
#include "../qdlocal.h"/// Qdurl, Qdfiles ,Qdprocess :The Qml back-end of the local side in Qdolphin.
#include "../qdremote.h"/// QtWebView, QdflatOrg
bool addPlagins(){/// Registering C++ type, such as classes, for qml use.
 return (qmlRegisterType<Qdprocess>("Process",  1, 0, "Process"   ) &&
         qmlRegisterType<Qdfiles>  ("Qdfiles",  1, 0, "Qdfiles"   ) &&
         qmlRegisterType<Qdkeeper> ("Qdkeeper", 1, 0, "Qdkeeper"  ) &&
         qmlRegisterType<Qdselforg>("Qdselforg",1, 0, "Qdselforg" ) &&
//     qmlRegisterType<Qdstring>   ("Qdstring", 1, 0, "Qdstring") &&
         qmlRegisterType<Qdurl>    ("Qdurl",    1, 0, "Qdurl"   )
     ); }

#include <QtQml/QQmlContext> //setContextProperty the context within a QML engine.
bool adddbpath(QQmlApplicationEngine *engine, QString customPath ){//file:qrc/db   this directory  have also linked db each as ablock of transactions
 QDir dir;//qDebug() << "customPath="+customPath;
 if(dir.mkpath(QString(customPath))){ //customPath="file:"+customPath;
  // qDebug() << "offlineStoragePath = "+engine->offlineStoragePath();
   engine->setOfflineStoragePath(QString(customPath));
   qDebug() << "offlineStoragePath = "+engine->offlineStoragePath();
   engine->offlineStorageDatabaseFilePath(customPath);//openDatabaseSync
   engine->rootContext()->setContextProperty("offlineStoragePath", customPath);
   return true;}
  return false;
}

QSqlDatabase  addddb(QString path){
 QSqlDatabase db;
 db = QSqlDatabase::addDatabase("QSQLITE","pdb");//not dbConnection
 db.setDatabaseName(path);
 if(! db.open() )  qDebug() << "db not open: " ;//<<db.lastError();
 QSqlQuery query(db);
 query.exec("create table person "
            "(id integer primary key, "
            "firstname varchar(20), "
            "lastname varchar(30), "
            "age integer)");
 return db;
}
#endif // Qdolphin_H
