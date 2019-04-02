/// Under the Humanitarian Agpl License: http://namzezam.wikidot.com/humanitarian-agpl-license

#ifndef Qddownload_H
#define Qddownload_H
#include <QtCore>
#include <QtNetwork/QtNetwork>
//#include <QtNetwork/QSslError>
//#include <QtQml/QQmlEngine>
//#include <QtQml/QQmlContext> //setContextProperty the context within a QML engine.

#include <cstdio>

QT_BEGIN_NAMESPACE
class QSslError;
QT_END_NAMESPACE

using namespace std;

class DownloadManager: public QObject{
    Q_OBJECT
    QNetworkAccessManager manager;
    QVector<QNetworkReply *> currentDownloads;

public:
    DownloadManager(){
    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
}

 Q_SLOT   void doDownload(const QUrl &url){
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

#if QT_CONFIG(ssl)
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            SLOT(sslErrors(QList<QSslError>)));
#endif

    currentDownloads.append(reply);
}

    static QString saveFileName(const QUrl &url){
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}
    bool saveToDisk(const QString &filename, QIODevice *data){
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename),
                qPrintable(file.errorString()));
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}
    static bool isHttpRedirect(QNetworkReply *reply){
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}


public ://slots

//template <typename tp>
//https://stackoverflow.com/questions/44506515/passing-specified-template-type-as-template-parameter
//Q_SLOT
//int qmlRegisterTy(QString it)
//
//{return(  qmlRegisterType<DownloadManager>(it,  1, 0, it   ));
//}

    void execute(){
    QStringList args = QCoreApplication::instance()->arguments();
    args.takeFirst();           // skip the first argument, which is the program's name
    if (args.isEmpty()) {
        printf("Qt Download example - downloads all URLs in parallel\n"
               "Usage: download url1 [url2... urlN]\n"
               "\n"
               "Downloads the URLs passed in the command-line to the local directory\n"
               "If the target file already exists, a .0, .1, .2, etc. is appended to\n"
               "differentiate.\n");
        QCoreApplication::instance()->quit();
        return;
    }

    for (const QString &arg : qAsConst(args)) {
        QUrl url = QUrl::fromEncoded(arg.toLocal8Bit());
        doDownload(url);
    }
}
    void downloadFinished(QNetworkReply *reply){
    QUrl url = reply->url();
    if (reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
    } else {
        if (isHttpRedirect(reply)) {
            fputs("Request was redirected.\n", stderr);
        } else {
            QString filename = saveFileName(url);
            if (saveToDisk(filename, reply)) {
                printf("Download of %s succeeded (saved to %s)\n",
                       url.toEncoded().constData(), qPrintable(filename));
            }
        }
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();

    if (currentDownloads.isEmpty()) {
       qDebug()<< "all downloads finished";
       // QCoreApplication::instance()->quit();
    }
}
    void sslErrors(const QList<QSslError> &errors){
     qDebug()<< "sslErrors:"<<errors;
    //todo  ???  Q_UNUSED(sslErrors);
/*
#if QT_CONFIG(ssl)
    for (const QSslError &error : sslErrors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
*/
}
void useExample(){//(int argc, char **argv)
    DownloadManager manager;
    QTimer::singleShot(0, &manager, SLOT(execute()));}

};












#endif  //Qddownload_H





//#ifndef Qdrlu_H/// Completing the missing api of Qstring in qml
//#define Qdrlu_H
#ifndef QT_NO_WIDGETS//#define QT_NO_WIDGETS // crashing
#include <QtWidgets/QApplication>//"/home/a/Qt/5.11.3/gcc_64/include/QtWidgets/QApplication"//<QtWidgets/QApplication>
typedef QApplication Application;
#include <QtWebView/QtWebView>// "/home/a/Qt/5.11.3/gcc_64/include/QtWebView/QtWebView"//<QtWebView>
#else
#include <QtGui/QGuiApplication>
#include <QtWebView>
typedef QGuiApplication Application;
#endif  //QT_NO_WIDGETS

  /** todo: seperate QdflatOrg between
   * qdolphin.h qdlocal.h and qdremote.h
  *
  * The QdflatOrg is a class for use of fedral/organizational notekeeping
  *  in flat Organizations. The notekeeping is maintained (encrypted/compressed)
  *  in nodes on (user/IPFS/owncloud), by updatable conclusion files paired with
  *  addedable history files, of bidirectional and mutually authenticated
  *  transactions, where all transactions in history files must be proven
  *  as coherent with the latest conclusion files.
  *
  *  Each of the transactions is mutually authenticated and signed while having
  *    2 directions - of: an offer and of an acceptance of that specific offer,
  *    so that the acceptance is approved only when accept(hash(offer)) is found,
  *    where each direction is singed and autticated by iiaom
  *    (facetoface or in omemo chat) and/or could (also) matching auttucation
  *       on a server such as as in SitE=http://liquid-unions.wikidot.com.
  *
  *  The conclusion format files: They
  *    are csv files, processed by QString and corresponding to 'tableid' tables,
  *    has constant maximum number of lines, marked as maxlines (32,1k,,,*32),
  *    can be easily transformed to (QSql, QSqlQuery) tables on the fly
  *     (see also QSqlRelationalTableModel class and "sql-programming.html"),
  *    sometimes, some of which, with a timestamp, are used as a cache of
  *      previous processing,
  *    their line is empty, or has first its header, then its body, of which all
  *      field are encoded as numbers, to ease the use in transaction
  *      transmission and
  *    their line number
  *      is as the 'rowid' row in the 'tableid',
  *      is used also as a foreign key in another such tables,
  *      optionally corresponds to a page, such as in SitE/tableid:rowid
  *        and hence if the corresponding page is not available,
  *                     then the line is empty.
  *
  *  The history files are blocks added into any blockchain, or to simple log
  *    files directory, with the latest validited transactions, of which terms
  *    are specified as numbers in corresponding conclusion files and then are
  *    updated in the current conclusion, while being digitally (and blindly)
  *    signed by the historyPubKey, after being authenticated with the iiaom of
  *    the mutual transaction person, where, communicated separately, the
  *    conclusionPubKey is used for signing the replacement of the historyPubKey
  *    for next such transaction of the person who signed.
  *      The history blockchain (as in Blockchain Structure): The blocks hold
  *      batches of valid transactions that are hashed and encoded into a Merkle
  *      tree. Each block includes the cryptographic hash of the prior block in
  *      the blockchain, linking the two. The linked blocks form a chain.
  *      This iterative process confirms the integrity of the previous block,
  *      all the way back to the original genesis block.
  *
  *  rowid>>(5*n).nlu for netowrk -
  *     tableid: n,
  *     header : describe the prlatform showing these tables, such as
  *         the servers and protocols, to be used for to
  *          provide prlatform of (nonredundant) servers,
  *              such as their url, rss  autnutcate, about  faces
  *     body   : rowid of its projects;
  *
  *  rowid>>(5*n).ulu for union -
  *     tableid: u,
  *     header : the union's name and then the total of participants of all its projects,
  *                total budget,
  *                the contacts page of its 3 offcials: Director, Deputy, Treasury
  *                                      and its 3 comities: Board, Control,Export
  *     body   : rowid of its projects;
  *
  *  rowid>>(5*n).plu for porject -
  *     tableid: p,
  *     header : name, rowid of its union, particpants,  budget,
  *     body   : every 3 items are for different branch:
  *        "name_of_the_branch",n_particpants, "#color normber";
  *
  *  rowid>>(5*n).blu for branch -
  *     tableid: c,
  *     header : rowid of its project,
  *     body   : rowid of its partipants;
  *
  *   rowid>>(5*n).ilu for partipants -
  *     tableid: i,
  *     header : iiaom,conclusionPubKey, historyPubKey
  *     body   : rowid of its branchs;
  ********** todo:
  * #define maxlines 32
  ********** todo: in sepreted channel
  *   concludeUpdate(n,l, iORo) ==> +n fo u - fo poroject , l fo line ,
  *      and trnasaction end up in concludeUpdate
  *
  *  + add, - substruct
  *  +particapnt
  *  +project
  *  +brache
  *  +file
  *
  * class Block {
       constructor(index, previousHash, timestamp, data, hash) {
        this.index = index;
        this.previousHash = previousHash.toString();
        this.timestamp = timestamp;
        this.data = data;
        this.hash = hash.toString();
       }
     }
  *********** todo:
 *   wikidot allow cloaning!!!
 *  the wikidot user is updating . this app cannot and must not update!!
 *  the rss  + autenttivted updating could be seprated from the pages being
 *      in xmlrpc format ,
 *   in the wikidot example we could have other server Bserver
 *      loading on ping from rss client seeing new feed which driking/update
 *         from wikidot to  xmlrpc format in the Bserver,
 *             this way data is redundant and abale to be reproduce on other severs/tools
 *              trafic can be balanced
 *                and data is  formated for blocking into chain
 *  http://xmlrpc-c.sourceforge.net/
 * http://xmlrpc-c.sourceforge.net/doc/libxmlrpc_client++.html
 * Use XML-RPC API only for View and Annonceing but Not for Updating i.e only pages.get_one
 *
 *  https://www.wikidot.com/doc https://www.wikidot.com/doc:api
////////////////
// enum maxLines{32, 1024, 32768, 1048576, 33554432, 1073741824}
//#include <xmlrpc-c-1.43.08/include/xmlrpc-c/girerr.hpp>
//#include <xmlrpc-c-1.43.08/include/xmlrpc-c/base.hpp>
//#include <xmlrpc-c-1.43.08/include/xmlrpc-c/client_simple.hpp>
//enum maxLines{32, 1024, 32768, 1048576, 33554432, 1073741824}
************ todo:
csv cache files per each lu named by id_number.lu and avialble on http://liquid-unions.wikidot.com/u:id
the first line is of
   the union name, the total of participants of all its projects,
      the contacts of
            its 3 offcials: Director, Deputy, Treasury
        and its 3 comities: Board, Control,Export
 and then every line is for difrenet project and straing in its:
    name, particpants ,budget
 and then every 3 items in that line are for difrenent bransh:
   "name_of_the_branch",n_particpants, "#color normber".
 */
//#endif
//#include "moc_qdremote.cpp"
