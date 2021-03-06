#ifndef Qdlocal_H
#define Qdlocal_H/// \brief Providing the Qml back-end of the local side in
/// Qdolphin via addPlagins in import/qdolphin.h.
/// Under the Humanitarian Agpl License: http://namzezam.wikidot.com/humanitarian-agpl-license
/// The classes have Q_DISABLE_COPY and are:
///  Qdstring:QObject        ??  - Completing the missing api of Qstring in qml.
///  Qdurl:QObject           ??  - the url of QtWebView@qdremote.h  to control the search engine from the url (CTRL-l) in
///  Qdlib:QLibrary              - loading lib and configuration file according which Qdolphin is to connect qmlRegisterType with QLibrary in the run time,
///  Qdprocess:QProcess          - other local programs to start, kill and communicate.
///  Qdfiles:QFileSystemModel    - local filesystem access.
///  Qdkeeper:QTreeView         ?- cryptography from the crypt directory. ?why in qml it is not m28 unreachable..?
///  Qdselforg:QObject           - liquid union implementation.
////////// todo cleanning including qDebug() and Ended herE ...///
#include <QDebug>// qDebug()
////// #include <QLibrary>
#ifndef Qdstring_H///  \brief  Completing the missing api of Qstring in qml
#define Qdstring_H
class Qdstring : public QObject { Q_OBJECT Q_DISABLE_COPY(Qdstring) public:
    explicit Qdstring(QObject *parent= nullptr ): QObject(parent){       }
Q_INVOKABLE int indexOf(QString data, const QString &str, int from = 0){
                          return data.indexOf(str, from);}
Q_INVOKABLE QString remove(QString data,int position, int n){
                          return data.remove( position,  n);} };//  console.log(d.substr(Pos,len)  );
#endif  // Qdstring_H

///  \brief Qdurl Url, Runing the local app
#ifndef Qdurl_H/// The local Url / command-line
#define Qdurl_H
#include <QUrl>
#include <QFileInfo>
class Qdurl : public QObject { Q_OBJECT Q_DISABLE_COPY(Qdurl) public:
    explicit Qdurl(QObject *parent= nullptr ): QObject(parent){    }
 //  QUrl startupUrl(); //main.cpp implementation
  //  Q_SLOT  QUrl fromUserInput(const QString& userInput);// main.cpp implementation qml call


//inline
Q_SLOT QUrl fromUserInput(const QString& userInput) { /// using the url as a commenad line
  switch(userInput[0].toLatin1()){// case 'h':return QUrl::fromUserInput(userInput);
  // case '!':{startProcess(userInput.split(" ")); break;}
   case '+':{break;}// prefrfences
   case '@':{break;}// qml editor of the files in this directory
   case '?':{switch(userInput[1].toLatin1()){
             // case 'n': return QUrl::fromUserInput("https://www.google.com/ncr");
             // case 'd': return QUrl::fromUserInput("https://duckduckgo.com/?q="+userInput.right(userInput.length() -2));
            //  case 's': return QUrl::fromUserInput("https://www.startpage.com/?q="+userInput.right(userInput.length() -2));
              default:  return QUrl::fromUserInput("https://encrypted.google.com/search?q="+userInput.right(userInput.length()-1));
             }}//(ctrl K) search engine,, ?g google , ?y yahoo esc
   default: {QFileInfo fileInfo(userInput);// browse files
             if (fileInfo.exists())
                     return QUrl::fromLocalFile(fileInfo.absoluteFilePath());
            }
  }
  return QUrl::fromUserInput(userInput);// default
}
/*
QUrl //Qdurl::
startupUrl(){qDebug() << "Qdurl::startupUrl";
    QUrl ret;
    QStringList args(qApp->arguments());
    args.takeFirst();
    Q_FOREACH (const QString& arg, args) {
        if (arg.startsWith(QLatin1Char('-')))
             continue;
        ret= Qdurl::fromUserInput(arg);//if (ret.isValid()) // return ret;
    }
    return ret;
}//   return QUrl(QStringLiteral("http://liquid-unions.wikidot.com/i"));
*/
};
#endif //Qdurl_H

//? /QPluginLoader
#ifndef QQdlib_H///  \brief
#define QQdlib_H
//#include <QtNetwork/QtNetwork> // for download
#include <QPluginLoader>//providing api connecting server providing service via qdolphin client.Compared to QLibrary, QPluginLoader checks that a plugin is linked against the same version of Qt as the application. QPluginLoader provides direct access to a root component object (instance()), instead of forcing you to resolve a C function manually.
#include <QDir>
//#include <QLibrary>/// Qdlib can be used before the use of loader in any qml
//#include "~/Qt/5.11.3/gcc_64/include/QQmlEngine"//not found?
//#include "~/Qt/5.11.3/gcc_64/include/QtQml/QQmlEngine"//<QQmlEngine>
class Qdlib : public QLibrary
{ Q_OBJECT Q_DISABLE_COPY(Qdlib) public:
  explicit Qdlib(QObject *parent= nullptr ): QLibrary  (parent){
  //q should be set to qmlenging already used to regstation
  // q->addImportPath();// if yhe qml path and the lib pat are in the same irectory ....
//q->offlineStoragePath
//q.clearComponentCache();
    setLoadHints(QLibrary::ResolveAllSymbolsHint);   }//QLibrary lib(parent);
~Qdlib(){unload();}//q.clearComponentCache();

Q_SLOT QString currentDir(){return QDir::currentPath();}

Q_SLOT bool loadlib(QString libPath){
    setFileName(libPath);return (load());}//all symbols will be resolved at load time if the platform supports it.

Q_SLOT QByteArray getConfig(QString qdPath){
    QFile file(qdPath);///The .qd configuration file according which to connect qmlRegisterType with QLibrary in the run time.
    if(!file.open(QIODevice::ReadOnly)) return "";
    return (file.readAll());}

/*how-to-use-a-qml-plugin
 * https://stackoverflow.com/questions/42739317/how-to-use-a-qml-plugin

//https://doc.qt.io/qt-5/qtqml-modules-cppplugins.html
// https://doc.qt.io/qt-5/qtqml-modules-qmldir.html

See "Creating C++ Plugins for QML".
In your case, you already have a plugin (from your previous question),
 but the steps involve:

    Write a project file for the plugin
    Create a qmldir file to describe the plugin

    QML extension plugins are for either application-specific or library-like plugins.
    Library plugins should limit themselves to registering types, as any manipulation of the engine's root context may cause conflicts or other issues in the library user's code.

The "Module Definition qmldir Files" is where you declare a plugin to be made available by the module.

plugin <Name> [<Path>]

        <Name> is the plugin library name. This is usually not the same as the file name of the plugin binary, which is platform dependent; e.g. the library MyAppTypes would produce libMyAppTypes.so on Linux and MyAppTypes.dll on Windows.
        <Path> (optional) specifies either:
            an absolute path to the directory containing the plugin file, or
            a relative path from the directory containing the qmldir file to the directory containing the plugin file.

    By default the engine searches for the plugin library in the directory that contains the qmldir file.
    The plugin search path can be queried with QQmlEngine::pluginPathList() and modified using QQmlEngine::addPluginPath().


*/
Q_SLOT bool qmlRegister (QByteArray qdLine){

//return ( qmlRegisterType<Qdurl>    ("Qdurl",    1, 0, "Qdurl"   ) );


}/**  Each line has these, or empty, comma seprated elements:
  * qmlName.verNumber (being used in the import statment in the qmlFile),
  * path to qml file  (qmlFile which is using the qmlName, will be cheacked before using Loader),
  * path to libary    (libPath to be loaded as QLibrary before runnig)
  * path to to h file (hPath to be compailed befor implementing className by qmlName)
  ***/
//private:
//QQmlEngine *q;
};
#endif  // Qdlib_H


/// \brief Qdprocess

#ifndef QdPROCESS_H /// The local Run by QProcess
#define QdPROCESS_H
#include "include.5.11.3/QProcess"//"~/Qt/5.11.3/gcc_64/include/QtCore/QProcess"//<QProcess>
//#include "include.5.11.3/QQmlPropertyMap"//
//#include "QtLocalHeaders/QtQml/QQmlPropertyMap"

//#define TEST_H1 "../some_path/test.h"

//#define L_H1 QtLocalHeaders "/QtQml/QQmlPropertyMap"
//#include L_H1
  //QtLocalHeaders "/QtQml/QQmlPropertyMap"

//#include "~/Qt/5.11.3/gcc_64/include/QtQml/QQmlPropertyMap"//

#include <QtQml/QQmlPropertyMap> //rLog

#define nqdpMax 64

class Qdprocess : public QProcess { Q_OBJECT Q_DISABLE_COPY(Qdprocess) public: //This class exposes the start and readAll methods to QML; other methods can be exposed similarly if needed. All of QProcess' signals are automatically exposed to QML.
    explicit Qdprocess(QObject *parent= nullptr ): QProcess(parent){
       rLog.insert(QString::number(nqdp = -1),  "Single Process Log:\n");}
     ~Qdprocess(){qDebug()<<" ~Qdprocess"<<QString::number(nqdp);
     while(nqdp>-1)endProcess( nqdp--);
     }
    Q_CLASSINFO("DefaultProperty", "Index")//QQmlListProperty ?//https://doc.qt.io/qt-5/qtqml-referenceexamples-properties-main-cpp.html
    Q_SIGNAL void reading();//qml usage: Process{id:qdprocess;onReading:...//Signals are automatically generated by the moc and must not be implemented in the .cpp file. They can never have return types (i.e. use void). https://doc.qt.io/archives/qt-4.8/signalsandslots.html#signals
    Q_SLOT QByteArray readAll() {reading();return readAll(Index); }
    Q_PROPERTY(int Index READ getIndex WRITE setIndex)
    Q_SLOT int  getIndex(){return Index;}
    Q_SLOT void setIndex(const int i){Index=i;}

    Q_SLOT void endProcess(int n){//int n=Index;
    if (n<=nqdp &&n>=0){qDebug()<<" endProcess"<<QString::number(n);
       qdprocess[n]->kill(); rLog.clear(QString::number(n));}}

    Q_SLOT QByteArray updateLog(int n){
       return rLog.value(QString::number(n)).toByteArray();}//              rLog.insert(QString::number(i) ,(qdprocess[i]->readAllStandardOutput()));
    Q_SLOT int start(const QString &program){//}, const bool MultiProcess=false ){
     if (++nqdp >= nqdpMax)
          {qDebug()<<" to many opened app"; return -1;}
     qDebug()<<nqdp<<"st program:"<< program;
     qint64 processId;
     if(Index>-1)
     {qdprocess[nqdp] = new QProcess();
         qdprocess[nqdp]->start(program);
         if (!qdprocess[nqdp]->waitForStarted())
             {qDebug()<<"not started."; return -1;}
         connect(qdprocess[nqdp], SIGNAL(readyReadStandardOutput()),
               this, SLOT(readAll()) );
        connect(qdprocess[nqdp], SIGNAL(readyReadStandardError()),
              this, SLOT(readAll()) );
         processId=qdprocess[nqdp]->processId();
     }else {QProcess::start(program);
         if (!QProcess::waitForStarted())
            {qDebug()<<"not started."; return -1;}
         processId=QProcess::processId();
     }
     rLog.insert(QString::number(nqdp), "Running the "+program+" is the "+QString::number(nqdp)+" id "+QString::number(processId)+"\n");
     qDebug()<<"rLog.count is"<<QString::number(rLog.count())<<"="<<rLog.value(QString::number(nqdp)).toString();
     return nqdp;
    }
    Q_SLOT QByteArray readAll(int n) { //int n=Index;//-1

    qDebug()<<"\n readAll n="<<QString::number(n);
         QString a=rLog.value(QString::number(n)).toString();
         (n==-1)? a.append(QProcess::readAllStandardOutput())://readAll())://
                  a.append(qdprocess[n]->readAllStandardOutput()); //readAll());
           rLog.insert(QString::number(n),a);
   qDebug()<< a<<'\n'<<rLog.value(QString::number(n)).toByteArray()<<'\n';
           return rLog.value(QString::number(n)).toByteArray();}
private:
    QQmlPropertyMap rLog;//QQmlPropertyMap for to set key-value pairs that can be used in QML bindings.
    int             nqdp;
    int Index;
    QProcess        *qdprocess[nqdpMax];
};
#endif //QdPROCESS_H


//////////////////////////
#ifndef Qdfiles_H /// The local files access
#define Qdfiles_H
#include <QDateTime>
//#include <QtTest/QTest>//"~/Qt/5.11.3/gcc_64/include/QtTest/QTest"//<QTest>
#include <QCoreApplication> //applicationDirPath
#include <QtWidgets/QFileSystemModel>//"~/Qt/5.11.3/gcc_64/include/QtWidgets/QFileSystemModel"//<QFileSystemModel>
#include <QtCore/QFileSystemWatcher>//"~/Qt/5.11.3/gcc_64/include/QtCore/QFileSystemWatcher"//<QFileSystemWatcher>// addpath
#include <QtSql/QSqlQuery>//"~/Qt/5.11.3/gcc_64/include/QtSql/QSqlQuery"//<QSqlQuery> // QSqlDatabase
#include <QMimeDatabase>
/// \brief The Qdfiles class The local files access
class Qdfiles:public QFileSystemModel{Q_OBJECT Q_DISABLE_COPY(Qdfiles) public:

 explicit Qdfiles(QObject *engine= nullptr):
   QFileSystemModel(engine){
//if (firsttimehere) {
  //               if(dotest())//if(dotest(&aest))
   //                  qDebug()<< "Did not pass";
                 setResolveSymlinks(true);
                 // firsttimehere=false;}
    } //setRoot(QDir::currentPath());
//Q_SLOT    int dotest(){AesTest aest;  return(QTest::qExec(&aest ));}

    Q_SLOT bool isDir(const QModelIndex &index) const{
    return QFileSystemModel::isDir(index);

    }
   Q_SLOT QString thisDir()const{   return QCoreApplication::applicationDirPath();}
    Q_SLOT QModelIndex getRootIndex() const{    return mRootIndex;}
    Q_SLOT QModelIndex setRoot(const QString path){
      mRootIndex=setRootPath(path);
       return mRootIndex;    }   // Q_SLOT QString RootPath() const {return(rootPath());}
    Q_SLOT QString search(const QString& filter, const QString& what) {//    qDebug() << "what="+ what+"where"+filter;  //return ( what+"in"+where);
      return searchForFiles(filter, what).join('\n'); }
    Q_SLOT QByteArray  Uncompress(const uchar *data, int nbytes){
      return (qUncompress(data,nbytes));}
    Q_SLOT QByteArray  Compress(const uchar *data, int nbytes, int compressionLevel = -1) {
      return (qCompress(data,  nbytes,  compressionLevel )); }
//    Q_SLOT void   setCurrentIndex(QString &path){    return QFileSystemModel::setCurrentIndex(indexOf(path),QItemSelectionModel::Rows);}
// to do findfiles  setCurrentIndex
    Q_SLOT  QModelIndex indexOf(const QString &path) const{//, int column = 0
      return( QFileSystemModel::index(path));}
    Q_SLOT QIcon     fileIcon(const QModelIndex &index) const{
      return( QFileSystemModel::fileIcon(index));}
    Q_SLOT QFileInfo fileInfo(const QModelIndex &index) const{
      return( QFileSystemModel::fileInfo(index));}
    Q_SLOT QString 	 fileName(const QModelIndex &index) const{
      return( QFileSystemModel::fileName(index));}
    Q_SLOT QString   filePath(const QModelIndex &index) const{
     // pathview=QFileSystemModel::filePath(index);
      return(QFileSystemModel::filePath(index) ) ;}
    Q_SLOT QModelIndex Index(const QString &path, int column = 0) const {
      return QFileSystemModel::index(path, column); }//https://stackoverflow.com/questions/50255197/get-qmodelindex-from-filepath-and-filename-in-qfilesystemmodel
    Q_SLOT void sortit(int column, Qt::SortOrder order = Qt::AscendingOrder){
      sort( column,  order);}
    Q_SLOT void setWriting(bool isreadonly){
    setReadOnly(isreadonly);  }
    Q_SLOT void setnameFilters(const QStringList &nameFilters){  // QStringList &nameFilters;
      setNameFilters(nameFilters);}
    Q_SLOT void setRootup(){
       QString r=rootDirectory().path().section(QDir::separator(),0,-2);//.cdUp();
       qDebug()<<"setRootup:" << r;//rootDirectory().path().section(QDir::separator(),0,-2);
       setRootPath(r);}// //QModelIndex?  to go to uper directory do left(...on the old path


    enum Roles  {
        SizeRole = Qt::UserRole + 4,
        DisplayableFilePermissionsRole = Qt::UserRole + 5,
        LastModifiedRole = Qt::UserRole + 6,
        UrlStringRole = Qt::UserRole + 7
    };
    Q_ENUM(Roles)
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE
    {
        if (index.isValid() && role >= SizeRole) {
            switch (role) {
            case SizeRole:
                return QVariant(sizeString(fileInfo(index)));
            case DisplayableFilePermissionsRole:
                return QVariant(permissionString(fileInfo(index)));
            case LastModifiedRole:
  return QVariant(fileInfo(index).lastModified().toString(Qt::SystemLocaleShortDate));
//                return QVariant(fileInfo(index).lastModified().toString(Qt::SystemLocaleShortDate));// depnded on QTest
            /*
             QDateTime birthTime() const;
    QDateTime metadataChangeTime() const;
    QDateTime lastModified() const;
    QDateTime lastRead() const;
    QDateTime fileTime(QFile::FileTime time) const;

            */

            case UrlStringRole:
                return QVariant(QUrl::fromLocalFile(filePath(index)).toString());
            default:
                break;
            }
        }
        return QFileSystemModel::data(index, role);
    }

//bool firsttimehere=true;

private:
//String pathview;
int currenti;
    QHash<int,QByteArray> roleNames() const Q_DECL_OVERRIDE
    {
         QHash<int, QByteArray> result = QFileSystemModel::roleNames();
         result.insert(SizeRole, QByteArrayLiteral("size"));
         result.insert(DisplayableFilePermissionsRole, QByteArrayLiteral("displayableFilePermissions"));
         result.insert(LastModifiedRole, QByteArrayLiteral("lastModified"));
         return result;
    }


    QStringList searchForFiles(const QString& Sfilter, const QString& what){
         QString fileName       = Sfilter;// = fileComboBox->currentText();
         QString text           = what;// = textComboBox->currentText();
         QString path           = QFileSystemModel::rootPath();// = QDir::cleanPath(directoryComboBox->currentText());
         currentDir             = QDir(path);
         QStringList filter;
         if (!fileName.isEmpty())  filter << fileName;
         QDirIterator it(path, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
         QStringList files;
         while (it.hasNext()) files << it.next();
         if (!text.isEmpty()) files = findInFiles(files, text);
         files.sort();
//         qDebug() <<files;
         return (files);
        }
    QStringList findInFiles(const QStringList &files,
                            const QString &text){
            QMimeDatabase mimeDatabase;
            QStringList foundFiles;
            for (int i = 0; i < files.size(); ++i) {
                const QString fileName = files.at(i);
                const QMimeType mimeType = mimeDatabase.mimeTypeForFile(fileName);
                if (mimeType.isValid() && !mimeType.inherits(QStringLiteral("text/plain"))) {
                   qDebug()  << "Not searching binary file ";// << QDir::toNativeSeparators(fileName);
                    continue;
                }
                QFile file(fileName);
                if (file.open(QIODevice::ReadOnly)) {
                    QString line;
                    QTextStream in(&file);
                    while (!in.atEnd()) { //if (progressDialog.wasCanceled())  break;
                        line = in.readLine();
                        if (line.contains(text, Qt::CaseInsensitive)) {
                            foundFiles << files[i];//foundFiles =foundFiles+ files[i]+'/n';
                         break;// todo: no break but adding the line number to be viewed in table
            }}}}
            return foundFiles;
        }
//private:

 // QFileSystemWatcher *watch;

  QModelIndex  mRootIndex;
  //QString

  void createFilesTable();
  void showFiles(const QStringList &paths);
  QDir currentDir;
  enum { absoluteFileNameRole = Qt::UserRole + 1 };
  static inline QString permissionString(const QFileInfo &fi){
   const QFile::Permissions permissions = fi.permissions();
   QString result = QLatin1String("----------");
    if (fi.isSymLink())
        result[0] = QLatin1Char('l');
    else if (fi.isDir())
        result[0] = QLatin1Char('d');
    if (permissions & QFileDevice::ReadUser)
        result[1] = QLatin1Char('r');
    if (permissions & QFileDevice::WriteUser)
        result[2] = QLatin1Char('w');
    if (permissions & QFileDevice::ExeUser)
        result[3] = QLatin1Char('x');
    if (permissions & QFileDevice::ReadGroup)
        result[4] = QLatin1Char('r');
    if (permissions & QFileDevice::WriteGroup)
        result[5] = QLatin1Char('w');
    if (permissions & QFileDevice::ExeGroup)
        result[6] = QLatin1Char('x');
    if (permissions & QFileDevice::ReadOther)
        result[7] = QLatin1Char('r');
    if (permissions & QFileDevice::WriteOther)
        result[8] = QLatin1Char('w');
    if (permissions & QFileDevice::ExeOther)
        result[9] = QLatin1Char('x');
    return result;
  }
  static inline QString sizeString(const QFileInfo &fi){
    if (!fi.isFile())
        return QString();
    const qint64 size = fi.size();
    if (size > 1024 * 1024 * 10)
        return QString::number(size / (1024 * 1024)) + QLatin1Char('M');
    if (size > 1024 * 10)
        return QString::number(size / 1024) + QLatin1Char('K');
    return QString::number(size);
  }
};
#endif // Qdfiles_H

#ifndef Qdkeeper_H /// The local files access
#define Qdkeeper_H///
#include <QBuffer>//
#include <QDataStream>//serlaize writeRawData
#include <QThread> //QThread::idealThreadCount()
#include <QLibrary>
#include <QHash>
#include <QStringListModel>
#include <QtWidgets/QTreeView>//#include "~/Qt/5.11.3/gcc_64/include/QtWidgets/QTreeView"//<QTreeView>// what the user can see
#include <QtCore/QCryptographicHash>//"~/Qt/5.11.3/gcc_64/include/QtCore/QCryptographicHash"//<QCryptographicHash>
/////////
#include "crypto/qtaes.h"///#include "crypt/qaesencryption.h"
#include <string.h>//memcmp
#include "crypto/argon2.h"
#include "crypto/ctr.h"
#include "crypto/threefish.h"


/////////
//#include "crypto/aestest.h"
//// #include "crypt/cppcrypto-0.17-src/cppcrypto/cppcrypto.h"

/*
#include "crypt/qtaes.h"///#include "crypt/qaesencryption.h"
#include "crypt/aestest.h"
//// #include "crypt/cppcrypto-0.17-src/cppcrypto/cppcrypto.h"
#include <string.h>//memcmp
#include "crypt/cppcrypto-0.17-src/cppcrypto/argon2.h"
#include "crypt/cppcrypto-0.17-src/cppcrypto/ctr.h"
#include "crypt/cppcrypto-0.17-src/cppcrypto/threefish.h"
*/
#define nCast reinterpret_cast
#define sCast static_cast
/**  \brief Qdkeeper
///???using cppcrypto or crypt/cryptopp/ https://www.cryptopp.com/
/// \brief The Qdkeeper class manages encryption by unique key per each file, by
/// PBKDF2 key = Argon2hash(path+pass+elnum+salt), in simple ui and protocol
/// for storing or backpacking, where
///  the manager acts uniquely per directory,
///  elnum is the number of the elment of the file being cut
///  and the salt is used as a combination ( each os its parts belong to
///     different) administrative authorities and/or for proof of continuity
///     (using hash of the previous).
/// Protocol:
/// 1. cut the file to some elements.
/// 2. encrypt each with different elnum then join and cut them again to feet
///    some boundaries.
/// 3. update the manger to include all those name=hash( element)
/// 3. separate many such element into few compressed packages
/// 4. upload the package (remote)
/// Use case: Qdselforg for sell, share, transmit or transfer files to specific individual
/// or group but still in somewhat the public domain search upload share files:
///  Box,Dropbox,GDrive,IDrive,OneDrive,SugarSync,CertainSafe ,SpiderOak
///   wetransfer, transfer.sh,file.io, 	uploadfiles.io ,pcloud.
///////////
/// Use it for increasing brute-force attack resistance,
/// even in spaces provided in (cheap/free) upload and share or storage services,
/// such as gdrive/dropbox/uploadfiles.io/affiliates.
///////////////////////////
/// on creation a encryptes in some path 2 data objects serlized by QDataStream
/// these 2 objects are joined ., if have the joined object we use it otherwise creating it.
/// to unlock existing the user must provide path and pass .
///  papthes QTreeView of only path
///cppcrypto { Q_OBJECT Q_DISABLE_COPY(Qdkeeper) public: explicit Qdkeeper(cppcrypto *parent= nullptr ): cppcrypto(parent){
/// todo: hash it by agron2 as argon2_hash in crypt/qdagron2/test.c see README.md
///  https://en.wikipedia.org/wiki/Argon2
///     and to hash also of element number
///     and salt Salt as an administrative authority per directory
  \brief   Each block is encrypted such that b(n)+=H(enc(b(n-1))),
    /// such that in decoding hasing  befure decrypting each block b.
    ///     this can help for
    /// 1. insuring the ordering of the blocks
    /// 2. the b(0) could be inserted by hashed of  some  privuse to this such that in root the pub k of the messenger or the hash of the last message.
    /// 3. with another round  the hash is added to create new key lppp  https://github.com/comcomized/lppp---Located-Password-Protected-Protocol
    /// 4. using stuck in pile way were we have more than 1 hash as parent
 //private:
// QHash <QByteArray,QByteArray>Secrets;///  in files manager:
///////////////////////////////
       /// To do update this - the seprations of the secerts..:
       ///  3 or 4 manage files, of which path and pass are the main secert,
       ///                             momorixed or kep encrypted sepratly,
       ///          where the manage files could  be compresed togather or stored sepratly stored.
       ///         these files are encrypted in specifc order,
       ///            while the hash of the clear text of one is used
       ///           as additional argument to the path , pass and elementnumber
       ///           to create the key of the next file, so that dependcy is
       ///           created, so that without having  them all,
       ///                      the infromation is sealed and such that
       ///                      when updating each except of the last,
       ///                   all of them must be recreated.
       //////////////////
       ///         pathesFile: text file, in each line l, it has diferent path, where
       ///                       the order is secret,
       ///                        but for perfomces it can be sorted,
       ///                           without losing the orginal l, by the path.
       ///                     ??  this  file can have also noise pathes,
       ///                     ??       assuming the  use would never ask of
       ///                     ??       those or some tech nic to idntify which
       ///                     ??      is real or niose.
       ///                     ??
       ///         lFile: binary file of 32bit signed long elments,
       ///                  the filrst maxl are of the paths in pathefile,
       ///                       the rest are of the jumps, where
       ///                       postive indicates n being the line number in namesFile,
       ///                       zero indicates  empty line in pathes
       ///                       negative indicates for jump of maxl or the amount if bigger than 2 . these are for next elementnumber.
       ///      [optional] linksFiles: text file sorted by n, each line has
       ///                              1 or more elemnts of (link, experation-date)
       ///        namesFile: text file sorted by n, each line has
       ///                     the name, being the hash of the content, of the ecnrypted files,
       ///                     but only pointed by lfile are used other are noise,
       ///                     these files are stat and touch and moves to be redated
       //////////////////////
       ///  To do if passowrd is longer than resuired cut it to some element and receyprt by each element
       /// To do: cat the file to smaller piece, each pieace has difernet elementnumber incresed in the jump of
       /// To do: have pathinview in private and all extyprion in seprated class and get path in pub function
       /// To do: change it for kdf2 try to Rijndael Rijndael-sbox.c to have not only 256 bit format try blowfish creating underrated xbox
       /// Rijndael allows key and block sizes of 32 bit increments;
       /// //  R as the number of round keys needed in Rijndael variants require max(N, B) + 7 round keys, where B is the block size in 32bits words
          //see also CTR https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Counter_(CTR)
// when user traverse in the encrypted files directory each file is name /////// *****/
/** Use case: A notfication system communicating via OEMO+ XMPP/signal ,wire,,telegram etc, where
 * userid is a number some time attached to pubK and topics are manged as directories, such that
 *  the pubK are distrebuted and stored and replaced in the clients on a flash deamd and new with any new comer event send
 *  as a normal msg under op topic by  any existing member. (by add to this group button)
 * ( meaning,  the nickname or telephone number  is made in/by the client via other means and not on the server)
 * the clain also has containers to implement topic signaled by #...
 *  eg: send.firefox.com https://list.jabber.at/ https://chat.prosody.im/ https://serverfault.com/questions/835635/what-prosody-modules-do-i-need-to-support-conversations
 * as the user has inbox having topic into which it  read after decrypt,
 * while the messages are wruten in the client in the form of:
 * qualifier then attribute: then message and the qualifiers are:
 * 1. @ where the attribute is userid for private messaging,
 * as the message is encrypted by the pubK and written only to the inbox
 *   of the recipient under (the topic) of the sending userid and
 * 2. # where the attribute is topic and the message with its sending
 *    userid is written to the directory of the topic,
 * where some  topics  are also copied into inboxes when are special like,
 * the op notifying about  newcomer and her/his pubk + userid.
 *
 * private messages can then include the link and the key to shared data encrypted in the Qdkeeper.
 * this system is a pull system like rss, where user choose to what to listen / useid or topic.
 * if autenticetion is there than only the user can listem to her/his inbox.
 *
 * here we should also manage mulipal accounts in some serverrs ...
***/
//Qdkeeper
class Qdkeeper: public QTreeView { Q_OBJECT Q_DISABLE_COPY(Qdkeeper) public:
explicit Qdkeeper(QTreeView *parent=nullptr):QTreeView(parent){
  cppcrypto::ctr ctr(This.cipher);
   Subject.isOn=false;//Subject.errN=0;
//   QString sbj=getLatestSbj();

   }//trying to read the sbj for making isOn true




~Qdkeeper(){updateSubject();clearThis();}  //WriteSubject(pass,path,sbj);

void clearThis(){//to complete..
  //This.cipher.~threefish1024_1024();
 Subject.lastBlocks->clear();
 Subject.pathes.clear();Subject.pathes.~QStringList();
 Subject.Secrets.clear();Subject.Secrets.~QMap();
 Subject.Subject2path.clear();Subject.Subject2path.~QMap();
 Subject.salt.clear(); Subject.Hsalt.clear(); Subject.pool.clear();
 This.pass.clear(); This.path.clear();This.sbj.clear();
 Subject.isOn=false;
}
Q_SLOT QString getLatestSbj(QString sbj="sbj"){
 qDebug()<<"getLatestSbj1";

 QDir dir(sbj);
 if (!dir.exists()|| dir.count()<3)
 {qDebug()<<"dir does not exists or empty";
   //if(dir.mkdir(sbj)){dir.mkdir(sbj);
 //dir.mkdir("tst"); dir.mkdir("encfiles");
  // qDebug()<<"Creating new directories "+sbj +"tst and encfiles";
   //}
return "";}//return "";

 dir.setFilter(QDir::Files);
 dir.setSorting(QDir::Time);
 qDebug()<<"getLatestSbj2";

 return dir.entryList()[0];
}// combine with readSubject

Q_SLOT bool isOn(){return (Subject.isOn);}
Q_SLOT void updateStrength(uint s){if (Subject.isOn)Subject.strength=s;}

Q_SLOT void updateSubject(){if(Subject.isOn)
    writeSubject(This.pass, This.path, This.sbj,
                 Subject.salt, Subject.strength,  Subject.pool,false);
 qDebug()<<"The subject is Updated";
                 }

Q_SLOT bool writeSubject(QByteArray pass, QByteArray path, QByteArray sbj,
                     QByteArray salt="is this some salt?", uint32_t h=1,
                     QByteArray pool="encfiles/",bool totest=true)
{return initSubject(pass, path, sbj, false, salt, h, pool, totest);}

Q_SLOT bool readSubject(QByteArray pass, QByteArray path, QByteArray sbj,
                     QByteArray salt="is this some salt?", uint32_t h=1,
                     QByteArray pool="encfiles/",bool totest=true)
{return initSubject(pass, path, sbj,true, salt, h, pool, totest);}

Q_SLOT QByteArray decryptFile(QByteArray pass,QByteArray path, int dbg=2){
 if (!Subject.isOn)return"";//initSubject( pass, path,);
 if(path.isEmpty()||pass.isEmpty()) {Subject.errN=1;return"";}//{qDebug()<<"missing argument";return 1;}
 QByteArray Secret= Subject.Secrets.value(path);/// find in secret the path
 if (Secret.isEmpty())
      {Subject.errN=2;return"";}//            /// not (having)   encrypted file
 QList<QByteArray>  LSecret=Secret.split(',');// ,.!
 //QByteArray n="", prek=pass+path+Subject.salt,data,out;
 bool ok;
//ulong nblocks;
 uchar key[128];//, dcrpt[4096];
 QFile * file;
 QByteArray orginalData;
char  *o =nullptr;
 if(dbg)
 {file= new QFile(path);
  if(file->open(QIODevice::ReadOnly))
   {orginalData=file->readAll();o=orginalData.data();}
    file->close();
   }
 else orginalData.~QByteArray();//if (!dbgthis(o,sCast<ulong>(orginalData.length())))return "";
 uchar decrpt[4096];// Subject.cipher.init(dbgkey, cppcrypto::block_cipher::encryption);                    /// Declaring the Key buffer in init of the cipher
 QByteArray out;//data,

 for(int elnum=0,outL=4096,Nfiles=LSecret[0].toInt(&ok,16);elnum<Nfiles;elnum++){// joining the files while dexrypting them
   QList<QByteArray>  NSecret=LSecret[elnum+1].split('.');
   if(NSecret[4].isEmpty()) outL=4096;else outL=NSecret[4].toInt(&ok,16);
   file = new QFile(Subject.pool+NSecret[0]);                                   ///  the file in the path for the pool for such files
   if(!file->open(QIODevice::ReadOnly))return "";
   int   padL    = (outL%128!=0)*(128-outL%128);
   ulong nblocks = sCast<ulong>(outL/128+(outL%128!=0));
   if(file->size()!=outL+padL) qDebug()<<"reading size proeblem"<<file->size()<<"!="<<outL+padL;
   QByteArray d = file->readAll();
   file->close();
   renderKey   (pass, path,  key, elnum);
   decrypt_blocks(   nCast<uchar*>( d.data()), nCast<uchar*>(decrpt),  nblocks);

  // if(memcmp(decrpt, o, sCast<ulong>(outL)))  //return 6;//
  //      qDebug()<<"not ok!! not decrepetd well in reading";
   if(dbg) {
     if(memcmp(decrpt, o, sCast<ulong>(outL)))  //return 6;//
        qDebug()<<"not ok!! not decrepetd well in reading";
     o+=4096;}
   out.append(nCast<const char*>(decrpt),sCast<int>(outL)); //  out+=nCast<const char*>(decrpt);//
  }// Subject.cipher.clear();
 return out;
}


Q_SLOT int encryptFile(QByteArray pass,QByteArray path, int dbg=2){//p=4 , uint32_t  m=4096, uint32_t  t=250,//=1000,
 if (!Subject.isOn) return 92;//initSubject( pass, path); //return 91;
 if(path.isEmpty()||pass.isEmpty()) return 1;//qDebug()<<"missing argument";
 QFile *file      = new QFile(path); //char *data;//data[ file->size() ];
 if(!file->open(QIODevice::ReadOnly)) return 2;//file.close(); ?qDebug()<<"coud not open:"<<path;
 int        dataL = sCast<int>(file->size());
 QByteArray da    = file->readAll();
 char       *data = da.data();
 file->close();
 if(!dataL)   return 3;/// empty file
 if(std::binary_search(Subject.pathes.begin(),Subject.pathes.end(),path))
   return 4; /// this file was encrypted, should we update it?//return pathes[FindInPathes(path)];
 Subject.pathes.insert(FindInPathes(path),path);///to be added to Subjecter fileno
 int   elnum      = 0,
       outL       = 4096,// length of out, which is the max size of each encrypted file ....  packing 32 elments of 4 or 128 b/k/m/g
       remain     = dataL%outL,
       Nfiles     = dataL/outL+(remain!=0);
 QByteArray// prek  = pass+path+Subject.salt,//, path1st=path;
           Secret = QByteArray::number(Nfiles, 16).toUpper()+",";             /**  Each Secret is a concatenated string of:    Nfiles: amount-of-elments.
        elment-name: outName is the hash of content
        colosion:  noramly non as zero or as theoretically same hash could be resulted from different content , the number of n colosied hash
        elnum: noramly non or when haveing nonces this number can be repeted.
        offset-in-the-file-overwhich-to-jump: normally  non as zero , but used when having nonces or joining files
        size-to-decrypt: normally non as outL , but last element might be smaller than outL
        number-of-such-copies-to-mange!expartion-date!url!: noremally non as zero
      ,,
 ** Split by seperators:
   , elements
   . descriptors
   ! copies */
 ulong nblocks    = 0;
 uchar key[128];//using threefish1024
 for(char out[4096],decrpt[4096],*in=data;dataL>0;in+=outL,dataL-=outL,elnum++){        /// Starting the loop per each element
   if(dataL<outL) outL = dataL;                                                 /// and adjusting for the last step when is so
   nblocks = sCast<ulong>(outL/128+(outL%128!=0));                               /// Calculating the mumber of encrypt_block steps
   renderKey(pass,path,key,elnum);
   encrypt_blocks(nCast<uchar*>(in),nCast<uchar*>(out),nblocks);                /// Creating the ciphertext as the content of the file
   if(dbg>0){
    preUseKey(key);
    decrypt_blocks(nCast<uchar*>(out),nCast<uchar*>(decrpt),nblocks);
    if(memcmp(decrpt, in, sCast<ulong>(outL)))
      return 6;//  qDebug()<<"not ok";
   }  /** *
     prek+=QByteArray::number(elnum,16).toUpper();                              /// Located-Password-Protected-Protocol under the humanitarian-agpl-license https://github.com/comcomist/lppp---Located-Password-Protected-Protocol
     renderKey(prek.data(), key, prek.length(), 128, p,m, t);                     /// Creating the key cipher
     prek.resize(prekL);
   //prek+=QByteArray::number(elnum,16).toUpper();                              /// Located-Password-Protected-Protocol under the humanitarian-agpl-license https://github.com/comcomist/lppp---Located-Password-Protected-Protocol
  // renderKey(pass,path,key,elnum);
   //   prek.data(), key, prek.length(), 128);                     /// Creating the key cipher
   //prek.resize(prekL);

 //int   prekL      = prek.length();
    *///  //dbgdata(out,outL);
   QByteArray name=QCryptographicHash::hash(out,QCryptographicHash::Keccak_224).toHex().toUpper();///Less agresive hash used for
   file = new QFile(Subject.pool+name);
   if(!file->open(QIODevice::WriteOnly|QIODevice::NewOnly))// return 5;//ReadWrite))//  // todo error could not create file
    {qDebug()<<"file exist";
    return 5;}
    else { int padL =(outL%128!=0)*(128-outL%128);//dataL  +=(outL%128!=0)*(128-outL%128);// should it also be padded??
           file->write(sCast<char *> (out),outL+padL);
           file->close();}
   Secret += name + ".....,";
   if(dbg>1){//fail on memeory mangment of qbytearray, not clear why?
    file = new QFile(Subject.pool+name);                                          ///  the file in the path for the pool for such files
    if(!file->open(QIODevice::ReadOnly))return 31;
    int padL =(outL%128!=0)*(128-outL%128);
    if(file->size()!=outL+padL) qDebug()<<"reading size proeblem"<<file->size()<<outL;
    QByteArray d = file->readAll();if (d.length()!=outL+padL) qDebug()<<"probelm in reading size the d";
    memset(decrpt,0,4096);
    preUseKey(key);
    decrypt_blocks(nCast<uchar*>(d.data()),nCast<uchar*>(decrpt),nblocks);
    file->close();
    if(memcmp(decrpt, in, sCast<ulong>(outL)))  //return 6;//
      qDebug()<<in<<"\n"<<"==not as=="<<nblocks<<"\n"<<decrpt;
   }
 }
 if (remain) Subject.Secrets.insert(path,Secret.left(Secret.length()-2)
                                  +QByteArray::number(outL,16).toUpper() +".");  ///removing the coma and copies  and adding size-to-decrypt with no copies
 else        Subject.Secrets.insert(path.data(),Secret);                            /// added to the Secret file name with 5 non, assuming nocolusion no noces and no joining files
// should and how now to save the Subject by writeSubject?

 memset(key,0,128);
 file->~QFile();
 qDebug()<<"encrypted file: ok in debug="<<dbg;
 updateSubject();
 return 0;
}


Q_SLOT int testScript (QByteArray key,QByteArray path,bool readonly=false,ulong compL=0){
 if (!Subject.isOn)return 92;//initSubject( key, path);
  QByteArray in;//,dcrp;
  qDebug()<<"testing the:"<<path;
  QFile file(path);                                   ///  the file in the path for the pool for such files
  if(file.open(QIODevice::ReadOnly)) in=file.readAll();else   return 3;
  uint fsize=sCast<uint>(file.size());// assuming files < 4t
  file.close();
 if(!readonly) if  ( (Subject.errN=encryptFile( key,path)) )
   return 4;// to make error more clear , leftshi and or it.
  QByteArray dcrp=decryptFile( key,path);
  if(Subject.errN)
   {   if(Subject.errN==2) qDebug()<<"Secret isEmpty ";
   return Subject.errN;
   }
  if(memcmp(dcrp.data(), in.data(),(compL==0)?fsize:compL))
    return 5;
  qDebug()<<"decryptFile is ok";//dcrp<<"decrept in Test: not ok"<<in;//  if  (in == dcrp)    return 0;
  return 0;   //
}

private:/** manged by initSubject todo:
///  save the Subject as file named by the user in [ath choosen by the user.
///     how and whn to update it on changes of the Subject.
 /// use Subject.lastBlocks[]
 ///  touch the files??
 /// deactivationMode
 ///  add to Secert hex(keycahed) and   p,m, t parmeters, so that  user can define if  Subjecting the key in the Subject file or ram and for how long
 /// to add to usecase: server letting its user directory (with expretion date),
 ///  which are personal or shared  of group, used as catgory tag , task ,
 /// events documents etc, such that the server only soply appload/download,
 ///  notifcation by rss, most of the the data can be nonredant and in
 ///  cold or other services, and shared work is done by direct omemo xmpp
 /// service  between the witers, and all liveries and algo  which are not
 ///   specifcally atorized by user  simply cannot work.
 ///
 ///  this cliant can run libary on this device by qproces, compiled statically
 ///  with TEMPLATE = lib, and by QLibrary  loading shared libraries at runtime.
 /// QPluginLoader
 ///
 /// hence . the work is done on the user/s locally , where the server only
 /// provide storage/access
 /// in this the sepration betweem appended history or updated conclution is
 /// important.
 /// the users work on a task can be autmated (ethereum), but now with the Subject mangment
 /// the suer must autrize any thing about it.
 ///
 /// another way is to have vpn that is cleared after completing task
 /// (payed per hour or less+data out) of
 /// genrating key and encrypting, such that the Subject is send back to use and
 /// the encfiles to other (shred or  prviate ) Storage Service service or s3 etc
 /// **/
 struct ThisType{
  QByteArray pass, path,  sbj;// For update use to be cleared  with QTime. This is information is the most secert!!
  cppcrypto::threefish1024_1024 cipher;/** c3fish1024;   cppcrypto::ctr ctr(cipher); the threefish 1024 cipher for ctr usage */
 }This;

 struct SubjectType{// manged by initSubject //QHash
  QMap <QByteArray,QByteArray>  Secrets;   /** \brief Secrets.value(path)=Secret
  It is emptied after some timeout interval for rerequiring the pass of the Secrets.
  Its elment-name is hash of the encrypted content.
  Its colution is number that increase with mulitipal hash for diferent content.
  Each "path" can have some other secerts, such as salt etc.
  Each Secret is a concatenated string of:
     Nfiles: amount-of-elments.
      elment-name: outName is the hash of content
        colosion:  noramly non as zero or as theoretically same hash could be resulted from different content , the number of n colosied hash
        elnum: noramly non or when haveing nonces this number can be repeted.
        offset-in-the-file-overwhich-to-jump: normally  non as zero , but used when having nonces or joining files
        size-to-decrypt: normally non as outL , but last element might be smaller than outL
        number-of-such-copies-to-mange!expartion-date!url!: noremally non as zero
      ,,
 ** Split by seperators:
   , elements
   . descriptors
   ! copies
      ****/
  QStringList                   pathes;/** \brief sorted and used for separately being easily
     viewed by setModel(new QStringListModel(Subject.pathes)); as the Model of
     the QTreeView, while functioning even after the Secrets emptied.
     ** Split by the seperators:
                    / parent
              newline path
      ****/
  QByteArrayList                lastBlocks[33];/** \brief
              [0] the filename having the ramins blocks , when nblocks<32
              [n<33] the path by secert for updaeting the chang of name at [0]*/
  QMap <QByteArray,QByteArray>  Subject2path;/** SubjectPath=> decryptingPath :When this Subject file also manage other Subject files */
  QByteArray                    pool;/// \brief the path of the encrypted files, as this file is seprated ... "encfiles/";
  QByteArray                    salt;///
  QByteArray                    Hsalt;//the hash of salt, to  becompared with hash(salt) after decryption for proving success

  uchar                         deactivationMode;/** \brief Using terminoly of
    green-activating-so-decrypt or red-deactivating-so-encrypt files, such that
    the user can modify the current deactivationMode between these ored cases
      0: do nothing about the decrypted file
      1: rename the filename extension of decrypted file to be +=.rmv
      2: move the decrypted file to other location in this or other device
      4: and lastly remove the decrypted file. ****/
  int                           errN;
  //cppcrypto::threefish1024_1024 cipher;/** c3fish1024;   cppcrypto::ctr ctr(Subject.cipher); the threefish 1024 cipher for ctr usage */
  uchar                         tweak[16];// 16=128/8: the tweak value is 128 bits
 uint32_t processes;//        sCast<const uint32_t >(QThread::idealThreadCount()), m, t,
 uint32_t strength;//, uint32_t s=1  h as hardness should be user defined by slider configured in to the Subject

//  uint32_t m = 1024*(Subject.h+3), t = 250*Subject.h;//  uint32_t m = 4096*h*0.25, t = 250*h*0.5;
bool isOn;
 }Subject;/** \brief It is serlized by QDataStream into file from some other
           external user defined path.
char* ExampleEncrypt(uchar * key, char * data, char *out,uint32_t length){
 cppcrypto::ctr ctr(cipher);
 Subject.cipher.init(key, cppcrypto::block_cipher::encryption);
 Subject.cipher.encrypt_blocks((uchar *)data,(uchar *)out,length);
 Subject.cipher.clear();
 return out;
}
///Fast encryption with strong unique derived key per each segment (stream or file):
/// Threefish consists of just three operations on 64-bit words —
/// addition, XOR, and rotations of a fixed amount.
/// Threefish-1024 consists of 80 rounds and encrypts data at 6.5 clock cycles
/// per byte, or 154M per second on 1GHz processor.
///
/// its is in CTR mode: https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Padding
/// CTR modes do not require any special measures to handle messages whose
/// lengths are not multiples of the block size, since the modes work
/// by XORing the plaintext with the output of the block cipher.
//  The last partial block of plaintext is XORed with the first few bytes of
//  the last keystream block, producing a final ciphertext block that is the
//  same size as the final partial plaintext block.
//  This characteristic of stream ciphers makes them suitable
/// for applications that require the encrypted ciphertext data
/// to be the same size as the original plaintext data, and for
/// applications that transmit data in streaming form where it
/// is inconvenient to add padding bytes.

****/




void SerializeFrom(QByteArray it) {
 QBuffer i(&it);
 i.open(QIODevice::ReadOnly);
 QDataStream Serializing(&i);
 Serializing>>Subject.Secrets>>Subject.pathes>>(*Subject.lastBlocks)>>Subject.pool
            >>Subject.salt>>Subject.Hsalt>>Subject.deactivationMode>>Subject.errN>>(*Subject.tweak);
 i.close();
 Serializing.~QDataStream();}

void SerializeInto( QByteArray &it) {
 QBuffer i(&it);
 i.open(QIODevice::WriteOnly);
 QDataStream Serializing(&i);
 Serializing<<Subject.Secrets<<Subject.pathes<<(*Subject.lastBlocks)<<Subject.pool
            <<Subject.salt<<Subject.Hsalt<<Subject.deactivationMode<<Subject.errN<<(*Subject.tweak);
 i.close();
 Serializing.~QDataStream();}

bool SubjectDefault(QByteArray salt,uint32_t strength=1,QByteArray pool="encfiles/"){
  if(Subject.isOn) return false;
       Subject.isOn             = true;
       Subject.deactivationMode = 0;
       Subject.processes        = sCast<const uint32_t >(QThread::idealThreadCount());
       Subject.strength         = strength ;////, uint32_t h=1  h as hardness should be user defined by slider configured in to the Subject
       Subject.pool             = pool;//"encfiles/";
       Subject.errN=0;
if(salt.isEmpty()){
  qDebug()<<"deterministic salt";
  salt ="is this deterministic salt some salt?";}
       Subject.salt             = salt;
       Subject.Hsalt            = QCryptographicHash::hash(salt,QCryptographicHash::Keccak_512).toHex().toUpper();
       memcpy(Subject.tweak,Subject.Hsalt.left(16),16);// first 16  bytes of Hsalt
   return true;}/**  uint32_t m = 1024*(Subject.h+3), t = 250*Subject.h;//  uint32_t m = 4096*h*0.25, t = 250*h*0.5;
         //     cppcrypto::ctr ctr(cipher); /// set the ciper into the ctr mode
         //   setModel(new QStringListModel(Subject.pathes));/// for the view by QTreeView*/

//Q_SLOT
bool initSubject(QByteArray pass, QByteArray path, QByteArray sbj,bool read,
                     QByteArray salt="is this some salt?", uint32_t h=1, QByteArray pool="encfiles/",bool totest=true){//=true//??swaping??
 if(pass.isEmpty()||path.isEmpty()) return false;//?||salt.isEmpty())//||sbj.isEmpty()
 QFile *file;                                              /// file
 uchar key[128];                                           /// key as using threefish1024 ctr
 QByteArray Cleartext, Ciphertext;                         /// working buffers
 int   dataL,dataR;                                        /// data remain and lenght
 ulong nblocks;                                            /// number of 128 byte blocks
/*
 if(Subject.isOn){
  if(read)
    {qDebug()<<"First unloading";///, by writing the existing Subject, so please restart.";
     if( writeSubject(pass, path, sbj, salt, h,  pool))
         qDebug()<<"The Subject was written";
    else qDebug()<<"The Subject not written";
    }
  else     qDebug()<<"Already loaded, having the Subject.Doing nothing.";

  Subject.isOn  = false; }//return false;
*/
 SubjectDefault(salt, h, pool);
 if(read){file  = new QFile(sbj);//:"sbj/"+sbj);
   if(!file->open(QIODevice::ReadOnly)) return false;
   dataL = sCast<int>(file->size());
 }else   {file  = new QFile("sbj/"+sbj);
   if(!file->open(QIODevice::WriteOnly)) return false;
   SerializeInto(Cleartext);
   dataL = sCast<int>(Cleartext.size());}

 nblocks =  sCast<ulong>(dataL/128)+((dataR = dataL%128)!=0);  /// Calculating the mumber of encrypt_block steps
 renderKey(pass, path, key);//, 4, 4096, 250);//500);//  renderKey(prek.data(), key, prek.length(), 128, 4, 4096, 1000);          /// Creating the key cipher
 This.pass=pass;This.path=path;This.sbj=sbj;

 if(read){
  Ciphertext = file->readAll();
  Cleartext.resize(sCast<int>(nblocks*128));//dataL);
  decrypt(nCast< uchar*>(Ciphertext.data()), nCast< uchar*>(Cleartext.data()),nblocks);//,key);
  Cleartext.resize(dataL-Cleartext[dataL-1]);//??
  SerializeFrom(Cleartext);
  if(Subject.Hsalt == QCryptographicHash::hash(Subject.salt,QCryptographicHash::Keccak_512).toHex().toUpper())//" to know that  data is decrypted well Subject should have hash of something like salt, then we can compare the hased salt with that hash ... Subject.salt="<<Subject.salt;
       qDebug()<<"Ok, the data is unlocked successfully";
  else qDebug()<<"Sorry, no match, try again the data is still locked";
 }else{dataL = sCast<int>(nblocks*128);                         /// Although in ctr mode we do not need padding,  for the serialization we do, so we put in the last byte the amount of bytes to ignore.
       Cleartext[dataL-1]=sCast<char> (128-dataR);              /// the pading
       Ciphertext.resize(dataL);                                /// allocating memory
       encrypt(nCast<uchar*>(Cleartext.data()),nCast<uchar*>(Ciphertext.data()),nblocks);/// Encrypting into the ciphertext
       file->write(Ciphertext.data(), dataL);}               /// ciphertext is the content of the file
 file->close();
 file->~QFile();
 memset(key,0,128);
 Cleartext.clear();
 Cleartext.~QByteArray();
 Ciphertext.clear();
 Ciphertext.~QByteArray();
 setModel(new QStringListModel(Subject.pathes));////// using Subject: for the view by QTreeView

if(totest)
{ if((Subject.errN = testScript (pass,"tst/twofishv.dat",read)) != 0)/// testing
      qDebug()<< "Did not pass the test. Err number:"<<Subject.errN;

}
//return updateSubject();//
return true;

// return true;
}


QStringList::Iterator FindInPathes(QString p){
    return std::upper_bound(Subject.pathes.begin(), Subject.pathes.end(), p);}

void encrypt_blocks(const uchar* in, uchar* out, size_t n){
   for (size_t i = 0; i < n; in += 128, out += 128, i++)
         This.cipher.threefish1024_1024::encrypt_block(in, out);
   This.cipher.clear();}

uchar* encrypt(const uchar* in, uchar* out, size_t n){//,uchar*key){preUseKey(key);
            encrypt_blocks(in, out, n); return out;}

void decrypt_blocks(const uchar* in, uchar* out, size_t n){
   for (size_t i = 0; i < n; in += 128, out += 128, i++)
         This.cipher.threefish1024_1024::decrypt_block(in, out);
   This.cipher.clear();}

uchar* decrypt(const uchar* in, uchar* out, size_t n){//,uchar*key){preUseKey(key);
            decrypt_blocks(in, out, n); return out;}

/**
//https://en.wikipedia.org/wiki/Argon2
            //, 4096, // memory in kb
             //t = 250//1000  // Number of iterations t, affecting the time cost. Decide on the maximum time x you can spend on it, choose the largest t such that it takes less than x with your system and other parameter choices. https://crypto.stackexchange.com/questions/37137/what-is-the-recommended-number-of-iterations-for-argon2
            //Figure out how long each call can take. One recommendation for concurent user logins is to Subject it under 0.5 ms. The RFC recommends under 500 ms. The truth is somewhere between those two values: more is more secure, less is a better user experience. argon2_cffi’s defaults try to land somewhere in the middle and aim for ~50ms, but the actual time depends on your hardware.
//Please note though, that even a verification time of 1 second won’t protect you against bad passwords from the “top 10,000 passwords” lists that you can find online.
//Measure the time for hashing using your chosen parameters. Find a time_cost that is within your accounted time. If time_cost=1 takes too long, lower memory_cost.


void hashIt(char* data, uchar* key, int dataL, int keyL){
  cppcrypto::argon2i(data, sCast<u_int>(dataL),
                     nCast<const uchar*>(Subject.salt.constData()),
                            sCast<u_int>(Subject.salt.length()),
                            Subject.p, 1024*(Subject.h+3), 250*Subject.h,// p, m, t,     //        sCast<const uint32_t >(QThread::idealThreadCount()),
                     key, sCast<u_int>(keyL));}/// https://argon2-cffi.readthedocs.io/en/stable/parameters.html //void argon2i(const char* password, uint32_t pwd_len, const unsigned char* salt, uint32_t salt_len, uint32_t p, uint32_t m, uint32_t t, unsigned char* dk, uint32_t dklen,		unsigned char* data, uint32_t datalen, unsigned char* secret, uint32_t secretlen, argon2_version version)           uint32_t  p ,//= 4 ,   // number processed QThread::idealThreadCount()      ) {//https://argon2-cffi.readthedocs.io/en/stable/parameters.html


//  renderKey(preKey.data(), key, preKey.length(), 128);
void renderKey(char* data , uchar* key, int dataL, int keyL){//   qDebug()<<"starting rendering a key";
   hashIt(data, key, dataL, keyL);// m, t);/// creating key=hash(data)
   Subject.cipher.set_tweak(Subject.tweak);
   Subject.cipher.init(key, cppcrypto::block_cipher::encryption); }/// qDebug()<<"ending rendering a key";
  // copying it to the cipher and hence declaring the Key buffer in the init of the cipher
//((uint32_t)QThread::idealThreadCount()==p);
//uint32_t p=4 ,
 //          uint32_t  m=4096, uint32_t  t=250 {////t=1000){/// before encrypt_blocks / decrypt_blocks
 //              uint32_t p=4 , uint32_t  m=409600, uint32_t  t=5000 ){/// before encrypt_blocks / decrypt_blocks
              //uint32_t p=4 , uint32_t  m=4096, uint32_t  t=1000
*/
/** Todo: this should be  finalized.
 *  is this a good idea? if we add Mac adress as a nother argument here ,
 *  then only with knowing this mac or by working in this machine
 *  it is possiable to unloack this file.
 *  QString QNetworkInterface::hardwareAddress() const
 * https://en.wikipedia.org/wiki/MAC_spoofing
Returns the low-level hardware address for this interface. On Ethernet interfaces, this will be a MAC address in string representation, separated by colons.
Other interface types may have other types of hardware addresses. Implementations should not depend on this function returning a valid MAC address.*/
void renderKey(QByteArray pass, QByteArray path, uchar* key, int elmn=0){
/// you must set the Subject salt,h and p, befoure using this function!
  QByteArray preKey  =
  QCryptographicHash::hash(pass+QCryptographicHash::hash(path,QCryptographicHash::Sha512),
                                 QCryptographicHash::Keccak_512)+
  QCryptographicHash::hash(Subject.salt,QCryptographicHash::Sha3_512).toHex().toUpper()+
  QCryptographicHash::hash(QByteArray::number(elmn,16).toUpper(),QCryptographicHash::Keccak_224).toHex().toUpper();     /// Located-Password-Protected-Protocol under the humanitarian-agpl-license https://github.com/comcomist/lppp---Located-Password-Protected-Protocol
  cppcrypto::argon2i(preKey.data(), sCast<u_int>(preKey.length()),
                     nCast<const uchar*>(Subject.salt.constData()),
                      sCast<u_int>(Subject.salt.length()),
                      Subject.processes, 1024*(Subject.strength+3), 250*Subject.strength,// p, m, t,     //        sCast<const uint32_t >(QThread::idealThreadCount()),
                     key, sCast<u_int>(128));//  hashIt(preKey.data(), key, preKey.length(), 128);// m, t);/// creating key=hash(data) 
  preUseKey( key );}
//  Subject.cipher.set_tweak(Subject.tweak);
//  Subject.cipher.init(key, cppcrypto::block_cipher::encryption); }

void preUseKey( uchar* key ){/// before encrypt_blocks / decrypt_blocks
  This.cipher.init(key, cppcrypto::block_cipher::encryption);
  // Subject.cipher.set_tweak(Subject.tweak);
   }

};


/////////////
#endif // Qdkeeper_H

#ifndef Qdselforg_H
#define Qdselforg_H
#include <QFile>
/** * \brief Made for decentralized organizations, such as liquid unions to have
///  separation between history in blockchain and momentary conclusion,
///  where conclusion is encrypted per member and history per group,
///  while and history has only temporal conclusion keys,
///  such that the history is lost when (some) keys are (momentarily) invalidated.
///
///  The moments are made of some QStringList, of which indexes are used as
///  arguments in the history, where one of the lists is of comands used for
///  updating the moments in the historical record  and where each of the
///  moments  at index=0 the hash of the previous such moment. and
/// hence Subjecting just the moments  by indvidualcan be used for
///  matching the collective history.
///
///
///  Files named F storing equal in size segments of A being int arguments,
///  where
/// The Arguments Files contain arguments of type A, being either int Key (C>0)
///                                    or a Single Line Text Expressions (C<0),
///    gathered in segments, of which size is context regulation dependent, where
///    the file name = "ContextNumber"+"-"+"FileNumber" indicates
///       F, as a FileNumber in the ContextNumber C,
///       J, as in Jump, is the offset in steps  of segments in that file,///
///       K=(F,J) is a the key pointing to such segment in such C,
///       A=(K<<2)|flexibilityBitsPair and flexibilityBitsPair describes
///       regular or double size of segment and when this bit is set in the last argument in doulble size segment, the thMS argument tell the size of the rest,
///       and regular or not including C in the pointed arguments
///       in that segment, where  The size of the segment of arguments
///       is defined by its context.
// the  doubled size last argumnet if non regular segment then the argumnet MS tells its size
// C=0 is for decription of context

/////////
///      K or K =(C,F,J)as

///
///
///   the bunderies defined by the Context to including
///       the number of bits 8,16,32,64 of the argument and
///        of which the number of bits of J 3,5,7,15.
///
///  The most LS flexibilityBit in the argument defines regularlty of
///   Segment  to add or not additional Segment, (<<1 .. | 0,1)(>>1), so that
///    the length of the Segment is either regular or not which then additional
///      segment follows the curent and. if the last argumnet in the additional
///       is an iregular seement, then the J,N tels the length of the folower
///       segemnt to that addtional one.
///
///   The Key in the argument indexes
///      either such Segments of integers
///      or expressions being strings in QByteArrayList.
///    Expressions might also be operations updating moment after recording
///     (adding) history (logged or chained) of which arguments are only of type A.
///     Segments are reused such that when segment is deleted,
///         its S, in negative S per any L, is kept for next reused,
/// hence: The exposure is reduced as smaller is file size
///        smaller the length of segment reduces the computation of its movement.
///        in  management of specific operation in big organizational data
///            most of the data is untouched.
/// most of the data can be kept in upload share services then only the
/// recently used file/sements are copied to reuse and linked by rss  (xmlrpc)
///
***/
class Qdselforg : public QObject { Q_OBJECT Q_DISABLE_COPY(Qdselforg) public:
    explicit Qdselforg(QObject *parent= nullptr ): QObject(parent){}
Q_INVOKABLE QStringList open(int i,bool isproject=true){// when i=0 the file has all projects in sepreted line , each has these sepereted by commma item : its union, budget,name,  particpans, color.and
//when i >0 i the file is of the union  http://liquid-unions.wikidot.com/u:i
  QString s=(isproject)?"qrc/"+QString::number(i)+".plu":
                        "qrc/"+QString::number(i)+".ulu"  ;
  QFile f(s);
  if(f.open(QIODevice::ReadOnly | QIODevice::Text)){s=f.readAll();
       f.close();
       return (s.split("/n"));}
  qDebug()<< "coud not open:"<<s;
  return QStringList();
 }//QStringList U = Open(1);// when index is zero the line is of the union otherwise of its projects.
};
#endif //Qdselforg_H
#endif //Qdlocal_H
///Ended Here
///
//    load(); // use unload to relase it
    //lib.resolve(className);
    //Loader...


 //      qDebug() << "library loaded";
 /* *
  * ResolveAllSymbolsHint
  * see also https://doc.qt.io/qt-5/plugins-howto.html#the-lower-level-api-extending-qt-applications

*//*
import
 * the qmlName is as the libary name in its corresponding
 *
 * QLibraryInfo
 */

/// to use wikidot only for rss (xmlrpc) either linking to encrypted  for group shared data or having the page repstative for that autority
/// to have the data as QHash ...
// U[0].split(",");// the first line is of
     //  the union name, the total of participants of all its projects,number of its projects
     //  the contacts of (when it is number it is on http://liquid-unions.wikidot.com/i:number)
     //       its 3 offcials: Director, Deputy, Treasury
     //   and its 3 comities: Board, Control,Export
// U[project_number].split(",") ... http://liquid-unions.wikidot.com/p:project_number
     //and then every line is for difrenet project and straing in its:
     //    name, particpants ,budget
     // and then every 3 items in that line are for difrenent bransh:
     //   "name_of_the_branch",n_particpants, "#color normber".
// when line is empty, it is becouse the coresspending p or i  is not used in the backend

/*Q_INVOKABLE bool Close(int i, QString s){QString inputStr=QString::number(i)+".lu";
    QFile f(inputStr);
    //if (f.open(QFile::ReadOnly))

    //return (f.readAll());
    //qDebug()<< "coud not open:"<<inputStr;
    //return "";
  }*/

//Q_INVOKABLE int indexOf(QString data, const QString &str, int from = 0){   return data.indexOf(str, from);}
//Q_INVOKABLE QString remove(QString data,int position, int n){                          return data.remove( position,  n);}
//  console.log(d.substr(Pos,len)  );
