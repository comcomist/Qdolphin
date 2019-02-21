/// Under the Humanitarian Agpl License: http://namzezam.wikidot.com/humanitarian-agpl-license
#include "import/qdolphin.h" // the directory to add plugins, path and db
int main(int argc, char **argv) {
 Application app(argc, argv);
 app.setWindowIcon(QIcon("qrc/dolphin-2-48.ico"));
    QCoreApplication::setOrganizationName("Postnational-Solutions-Makers");
    QCoreApplication::setOrganizationDomain("no.com");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//    QCoreApplication::setAttribute(Qt::AA_UseStyleSheetPropagationInWidgetStyles, true);//   QCoreApplication::setApplicationName("Qdolphin");//== TARGET=Qdolphin in.pro. If not set, the application name defaults to the executable name (since 5.0).
 QQmlApplicationEngine appEngine;
 QtWebView::initialize();//appEngine,"RemoteData"
 if ( addPlagins() && // see:import/qdolphin.h, each class is added as plugin in 1 line
      adddbpath(&appEngine,"LocalData/db") )
         QSqlDatabase  db= addddb("LocalData/db/myDb.db");
    else return 1;
// appEngine.load(QUrl("file:qrc/LocalObj.qml"));
 appEngine.load( QUrl::fromLocalFile("qrc/LocalObj.qml"));
 QMetaObject::invokeMethod(appEngine.rootObjects().first(),"webLoad",//"load",
                           Q_ARG(QVariant, QStringLiteral("")));
 return app.exec();
}
