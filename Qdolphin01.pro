# Under the Humanitarian Agpl License: http://namzezam.wikidot.com/humanitarian-agpl-license
TEMPLATE    = app
TARGET      = Qdolphin # Qdolphin: The Qdolphin (Q DO Love Peace and Happiness IN) is a browser developed in qt framework for separated in memory and added plugins qml applications with some control over some necessary privacy issues, when surfing cleverly in our evil thinking they are somewhat smart industry making users be their things in their IoT.
QT          += webview # QtWebView WebEngine is not relvent in andorid
QT          += sql     # sql is added for having db out of localstorage https://doc.qt.io/qt-5/sql-driver.html
QT          += widgets # QFileSystemModel
QT          += qml     # QQmlPropertyMap sortfilterproxymodel
QT          += testlib # QTest
HEADERS     += qdlocal.h\
   crypto/crypto_hash.h crypto/cbc.h    crypto/cppcrypto.h\
   crypto/argon2.h      crypto/blake2.h
SOURCES     += main.cpp\
   crypto/threefish.cpp    crypto/cpuinfo.cpp\
   crypto/block_cipher.cpp crypto/crypto_hash.cpp crypto/thread_pool.cpp\
   crypto/blake2.cpp crypto/ctr.cpp crypto/argon2.cpp

android { message("? android?")}else::linux {
# message("* Using Linux qca.")
#LIBS        += -L$$PWD/qca/lib/qca-qt5/crypto -lqca-gcrypt
#LIBS        += -L$$PWD/qca/lib -lqca-qt5
#LIBS        += -Lqca/lib/qca-qt5/crypto -lqca-softstore #-lqca-ossl -lqca-logger -lqca-gnupg -lqca-gcrypt
}
DISTFILES += \
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
