TEMPLATE    = app
TARGET      = Qdolphin # Qdolphin: The Qdolphin (Q DO Love Peace and Happiness IN) is a browser developed in qt framework for separated in memory and added plugins qml applications with some control over some necessary privacy issues, when surfing cleverly in our evil thinking they are somewhat smart industry making users be their things in their IoT.
HEADERS     = import/qdolphin.h qdlocal.h qdremote.h crypto/crypto_hash.h crypto/argon2.h crypto/blake2.h
SOURCES     = main.cpp\
              crypto/threefish.cpp crypto/cpuinfo.cpp\
              crypto/block_cipher.cpp crypto/crypto_hash.cpp\
              crypto/thread_pool.cpp  crypto/blake2.cpp crypto/ctr.cpp\
              crypto/argon2.cpp
android { message("? android?")}
else::linux:!macx {
QMAKE_LFLAGS_RPATH=# suppress the default RPATH after ldd ./Qdolphin was used for to find the path to copy from. see other such flags in qthelp://org.qt-project.qmake.5113/qmake/qmake-variable-reference.html#qmake-lflags-rpath
QMAKE_LFLAGS = -Wl,-rpath,$$OUT_PWD/qrc/lib/gcc_64/shared# redircated from /usr/lib/x86_64-linux-gnu
# 73m of 11 shared  libs
LIBS       = $$OUT_PWD/qrc/lib/gcc_64/shared/libQt5Core.so.5\ #$$PWD/libs/5.11.3/gcc_64/libQt5Core.a\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libQt5Gui.so.5.11.3\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libQt5Widgets.so.5 \#$$PWD/libs/5.11.3/gcc_64/libQt5Widgets.a\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libQt5Qml.so.5 \#$$PWD/libs/5.11.3/gcc_64/libQt5Qml.a\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libQt5Sql.so.5\ #$$PWD/libs/5.11.3/gcc_64/libQt5Sql.a\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libQt5Quick.so.5\#$$PWD/libs/5.11.3/gcc_64/libQt5Quick.a\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libQt5Network.so.5\ #$$PWD/libs/5.11.3/gcc_64/libQt5Network.a\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libQt5WebView.so.5\ # $$PWD/libs/5.11.3/gcc_64/libQt5WebView.a\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libicui18n.so.56\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libicudata.so.56\
             $$OUT_PWD/qrc/lib/gcc_64/shared/libicuuc.so.56
### static lib todo !? ###
#CONFIG -=QtQuick

#CONFIG      -= import_plugins
#LIBS = $$OUT_PWD/qrc/lib/libQt5Core.a\
#       $$OUT_PWD/qrc/lib/libQt5Widgets.a\
#       $$OUT_PWD/qrc/lib/gcc_64/libQt5Qml.a\
#       $$OUT_PWD/qrc/lib/gcc_64/libQt5Sql.a\
#       $$OUT_PWD/qrc/lib/gcc_64/libQt5Quick.a#\
#     #  $$OUT_PWD/qrc/lib/5.11.3/gcc_64/libQt5Network.a
message("linux:!macx.  PRECOMPILED_HEADER=$$PRECOMPILED_HEADER|| pwd= $$PWD !!! [QT_INSTALL_LIBS]=$$[QT_INSTALL_LIBS]!!DEFINES=$$DEFINES!!OUT_PWD= $$OUT_PWD"!! QTPLUGIN=$$QTPLUGIN !!QMAKE_RPATHLINKDIR= $$QMAKE_RPATHLINKDIR!! QMAKE_QMAKE = $$QMAKE_QMAKE!!qt= $$QT !! QMAKE_LFLAGS= $$QMAKE_LFLAGS!! LIBS= $$LIBS DISTFILES= $$DISTFILES)#, QMAKE_LFLAGS_RPATH =$$QMAKE_LFLAGS_RPATH
}# To view the objects use nm, objdump -s , readelf -a
DISTFILES   += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/AndroidManifest.xml \
#    invoking/invoking.qml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

###### Ended here
# todo rewrite src/quick/items/qquickloader.cpp to only offfline  online
# /home/a/Qt/5.11.3/Src/qtdeclarative/src/quick/items/qquickloader.cpp
# QQuickLoader::setSource
# LoacalLoader or Qt.createComponent(source); should have a ceack in setSource and return nothing if the url contain http
# https://stackoverflow.com/questions/34814738/protecting-qml-source-code-from-plagiarism
# solutions encrypt all qml files and on startup decrypt them  and call them by Qt.createComponent
# when Loader{id:remoteqml;visible:true;width:300; source: http..  we get: invalid qmldir directive contains too many tokens
# but when Image {    source: http is loaded..
#Todo: except of weblib, make all other static lid and call weblib by QLibrary


#debug: QT  += testlib # QTest

#### use QT_INSTALL_HEADERS in header
#INCLUDEPATH = $$[QT_INSTALL_HEADERS]
#DEFINES += localheaders=
#RC_FILE =    $$OUT_PWD/qrc

#localheaders=$$[QT_INSTALL_HEADERS]#$$[QT_INSTALL_LIBS]"/../include" #-qmake
#DEFINES += "localheaders=$$[QT_INSTALL_HEADERS]"
#########
#########  libQt5Qml.so.5
# ~/Qt/5.11.3/gcc_64/bin
# https://doc.qt.io/qt-5/linux-deployment.html
#\#todo  rebuild Qt5WebView : libQt5WebView.so.5  was not found from command line
#\#https://wiki.qt.io/Building_Qt_5_from_Git
#\# https://stackoverflow.com/questions/47100545/how-to-build-qtwebengine-5-10-from-source
#
#             $$OUT_PWD/qrc/lib/gcc_64/libQt5WebView.so.5 \# $$PWD/libs/5.11.3/gcc_64/libQt5WebView.a\
#              $$OUT_PWD/qrc/lib/gcc_64/libicui18n.so.56\ # todo compile statically
#              $$OUT_PWD/qrc/lib/gcc_64/libicuuc.so.56\# tobe compiled stattically
#              $$OUT_PWD/qrc/lib/gcc_64/libicudata.so.56# tobe compiled stattically


### static lib ###
#LIBS = $$OUT_PWD/qrc/lib/libQt5Core.a\
#       $$OUT_PWD/qrc/lib/libQt5Widgets.a\
#       $$OUT_PWD/qrc/lib/gcc_64/libQt5Qml.a\
#       $$OUT_PWD/qrc/lib/gcc_64/libQt5Sql.a\
#       $$OUT_PWD/qrc/lib/gcc_64/libQt5Quick.a#\
#     #  $$OUT_PWD/qrc/lib/5.11.3/gcc_64/libQt5Network.a
###
#how do i force the use of build tree path for libraries over the -L~/Qt/5.11.3/gcc_64/lib ?

#QMAKE_LFLAGS#
#QMAKE_RPATHDIR =?? $$PWD
#$$PWD = rpath
#####
#QMAKE_LFLAGS += -Wl,-rpath,"'$$ORIGIN'"  #rpath=dir


#LIBS        -=-L~/Qt/5.11.3/gcc_64/lib
  #libQt5Core.so.5 use     LIBS -=libicui18n libicuuc libicudata
# -licui18n -licuuc -licudata
#}# To view the objects use nm, objdump -s , readelf -a
#QT          += webview  sql   widgets qml   testlib# For qt doc replace libQt5 with Qt.
#QT          += widgets # QFileSystemModel
#QT          += qml     # QQmlPropertyMap sortfilterproxymodel
#QT          += webview # QtWebView WebEngine is not relvent in andorid
#QT          += sql     # sql is added for having db out of localstorage https://doc.qt.io/qt-5/sql-driver.html
#QT          += testlib # QTest
##############
# to makefile from it:
#$qmake -spec your_desire_platform_spec your_project.pro
#$make
#https://stackoverflow.com/questions/30514092/convert-qmake-file-to-unix-makefile

#$$PWD/libz.so.1
#crypto/cbc.h    crypto/cppcrypto.h\
# message("* Using Linux qca.")
#LIBS        += -L$$PWD/qca/lib/qca-qt5/crypto -lqca-gcrypt
#LIBS        += -L$$PWD/qca/lib -lqca-qt5
#LIBS        += -Lqca/lib/qca-qt5/crypto -lqca-softstore #-lqca-ossl -lqca-logger -lqca-gnupg -lqca-gcrypt
#}
#unix:!macx{
################
#--enable-plugins
#qthelp://org.qt-project.qtdoc.5113/qtdoc/qt-conf.html

#https://blog.qt.io/blog/2011/10/28/rpath-and-runpath/
#QMAKE_RPATHDIR=DESTDIR#QMAKE_LFLAGS_RPATH=# suppress the default RPATH
    # add your own with quoting gyrations to make sure $ORIGIN gets to the command line unexpanded
    #QMAKE_LFLAGS += "-Wl,-rpath,\'\$$ORIGIN\':/usr/lib/qt5.5:/usr/lib/qt5.5/lib"

#QMAKE_RPATHLINKDIR=$$PWD/libs
#QT -= gui
#QMAKE_RPATHLINKDIR = $$QT.gui.libs

###########
#$$PWD/libs/5.11.3/gcc_64/libQt5Core.a\
#                    $$PWD/libs/5.11.3/gcc_64/libQt5Gui.a\
#                    $$PWD/libs/5.11.3/gcc_64/libQt5Widgets.a
#         }#  -lQt5Widgets}# -lQt5Qml -lQt5Sql}#QT           += webview  sql   widgets qml   testlib
#unix:!macx: LIBS += -lQt5Core

#QT          += widgets # QFileSystemModel
#QT          += qml     # QQmlPropertyMap sortfilterproxymodel
#QT          += webview # QtWebView WebEngine is not relvent in andorid
#QT          += sql     # sql is added for having db out of localstorage https://doc.qt.io/qt-5/sql-driver.html
#QT          += testlib # QTest


#INCLUDEPATH += ./linbuild/lib
#LIBS +=./linbuild/lib/libgpgme.a ./linbuild/lib/libgpg-error.a
#-L$$PWD/libs/5.11.3/gcc_64


 #\# $$PWD/libs/5.11.3/gcc_64/libQt5Widgets.a\
#-lQt5Qml \#why!= $$PWD/libs/5.11.3/gcc_64/libQt5Qml.a \#-lQt5Qml\
#-lQt5Sql # $$PWD/libs/5.11.3/gcc_64/libQt5Qml.a\#  -lQt5Qml\# libQt5Qml.a\#-lQt5Qml -lQt5Core
 # $$PWD/libs/5.11.3/gcc_64/libQt5Sql.a#         -lQt5Widgets    -lQt5Sql #-lQt5Test
#libQt5Qml\#
# -lQt5Widgets\#


