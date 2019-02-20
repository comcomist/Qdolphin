#ifndef AESTEST_H
#define AESTEST_H
#include "qtaes.h" ///#include "qaesencryption.h"
#include "crypt/qdagron2/qdagron2.h"
#include <QObject>
#include <QTest> //QCOMPARE
#include <QCryptographicHash>
#include <QFile>
class AesTest : public QObject
{
    Q_OBJECT

//private slots:

Q_SLOT void initTestCase()
{
    quint8 key_16[16] =  {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    for (int i=0; i<16; i++)
        key16.append(key_16[i]);

    quint8 key_24[24] = { 0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52, 0xc8, 0x10, 0xf3, 0x2b, 0x80, 0x90, 0x79, 0xe5, 0x62, 0xf8,
                       0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b};
    for (int i=0; i<24; i++)
        key24.append(key_24[i]);

    quint8 key_32[32]= { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                       0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 };
    for (int i=0; i<32; i++)
        key32.append(key_32[i]);

    quint8 iv_16[16]     = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
    for (int i=0; i<16; i++)
        iv.append(iv_16[i]);

    quint8 in_text[16]    = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
    quint8 out_text[16]   = { 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97 };
    quint8 out_text_2[16] = { 0xbd, 0x33, 0x4f, 0x1d, 0x6e, 0x45, 0xf2, 0x5f, 0xf7, 0x12, 0xa2, 0x14, 0x57, 0x1f, 0xa5, 0xcc };
    quint8 out_text_3[16] = { 0xf3, 0xee, 0xd1, 0xbd, 0xb5, 0xd2, 0xa0, 0x3c, 0x06, 0x4b, 0x5a, 0x7e, 0x3d, 0xb1, 0x81, 0xf8 };

    for (int i=0; i<16; i++){
        in.append(in_text[i]);
        outECB128.append(out_text[i]);
        outECB192.append(out_text_2[i]);
        outECB256.append(out_text_3[i]);
    }

    quint8 text_cbc[64]   = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a,
                              0xae, 0x2d, 0x8a, 0x57, 0x1e, 0x03, 0xac, 0x9c, 0x9e, 0xb7, 0x6f, 0xac, 0x45, 0xaf, 0x8e, 0x51,
                              0x30, 0xc8, 0x1c, 0x46, 0xa3, 0x5c, 0xe4, 0x11, 0xe5, 0xfb, 0xc1, 0x19, 0x1a, 0x0a, 0x52, 0xef,
                              0xf6, 0x9f, 0x24, 0x45, 0xdf, 0x4f, 0x9b, 0x17, 0xad, 0x2b, 0x41, 0x7b, 0xe6, 0x6c, 0x37, 0x10 };

    quint8 output_cbc[64] = { 0x76, 0x49, 0xab, 0xac, 0x81, 0x19, 0xb2, 0x46, 0xce, 0xe9, 0x8e, 0x9b, 0x12, 0xe9, 0x19, 0x7d,
                              0x50, 0x86, 0xcb, 0x9b, 0x50, 0x72, 0x19, 0xee, 0x95, 0xdb, 0x11, 0x3a, 0x91, 0x76, 0x78, 0xb2,
                              0x73, 0xbe, 0xd6, 0xb8, 0xe3, 0xc1, 0x74, 0x3b, 0x71, 0x16, 0xe6, 0x9e, 0x22, 0x22, 0x95, 0x16,
                              0x3f, 0xf1, 0xca, 0xa1, 0x68, 0x1f, 0xac, 0x09, 0x12, 0x0e, 0xca, 0x30, 0x75, 0x86, 0xe1, 0xa7 };

    for (int i=0; i<64; i++){
        inCBC128.append(text_cbc[i]);
        outCBC128.append(output_cbc[i]);
    }
}


//==================ECB TESTING=========================

Q_SLOT void ECB128Crypt(){
    QByteArray hexText, outputHex;
    QtAes encryption(QtAes::AES_128, QtAes::ECB);
    QCOMPARE(encryption.encode(in, key16), outECB128);
}

Q_SLOT void ECB128Decrypt(){
    QByteArray hexText, outputHex;
    QtAes encryption(QtAes::AES_128, QtAes::ECB);
    QCOMPARE(encryption.decode(outECB128, key16), in);
}

Q_SLOT void ECB192Crypt(){
    QByteArray outputHex;
    QtAes encryption(QtAes::AES_192, QtAes::ECB);
    QCOMPARE(encryption.encode(in, key24), outECB192);
}

Q_SLOT void ECB192Decrypt()
{
    QByteArray hexText;
    QtAes encryption(QtAes::AES_192, QtAes::ECB);

    QCOMPARE(encryption.decode(outECB192, key24), in);
}

Q_SLOT void ECB256Crypt()
{
    QtAes encryption(QtAes::AES_256, QtAes::ECB);

    QCOMPARE(encryption.encode(in, key32), outECB256);
}

Q_SLOT void ECB256Decrypt(){
    QtAes encryption(QtAes::AES_256, QtAes::ECB);
    QCOMPARE(encryption.decode(outECB256, key32), in);
}

Q_SLOT void ECB256String(){
    QtAes encryption(QtAes::AES_256, QtAes::ECB, QtAes::Padding::ISO);
    QString inputStr("The Advanced Encryption Standard (AES), also known by its original name Rijndael "
                        "is a specification for the encryption of electronic data established by the U.S. "
                        "National Institute of Standards and Technology (NIST) in 2001");
    QString key("123456789123");

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);

    QByteArray encodeText = encryption.encode(inputStr.toLocal8Bit(), hashKey);
    QByteArray decodedText = encryption.removePadding(encryption.decode(encodeText, hashKey));

    QCOMPARE(QString(decodedText), inputStr);
}


////==================CBC TESTING=========================

Q_SLOT void CBC128Crypt(){
    QtAes encryption(QtAes::AES_128, QtAes::CBC);
    QCOMPARE(encryption.encode(inCBC128, key16, iv), outCBC128);
}

Q_SLOT void CBC128Decrypt(){
    QtAes encryption(QtAes::AES_128, QtAes::CBC);
    QCOMPARE(encryption.decode(outCBC128, key16, iv), inCBC128);
}

//=================== CFB TESTING ============================

Q_SLOT void CFB256String()
{
    QtAes encryption(QtAes::AES_256, QtAes::CFB);

    QString inputStr("The Advanced Encryption Standard (AES), also known by its original name Rijndael "
                        "is a specification for the encryption of electronic data established by the U.S. "
                        "National Institute of Standards and Technology (NIST) in 2001");
    QString key("123456789123");

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);

    QByteArray encodeText = encryption.encode(inputStr.toLocal8Bit(), hashKey, iv);
    QByteArray decodedText = encryption.removePadding(encryption.decode(encodeText, hashKey, iv));
    QCOMPARE(QString(decodedText), inputStr);
}

Q_SLOT void CFB256LongText()
{
    QtAes encryption(QtAes::AES_256, QtAes::CFB);

    QFile textFile("qrc/longText.txt");
    QByteArray input;
    if (textFile.open(QFile::ReadOnly))
        input = textFile.readAll();
    else
        QFAIL("File longText.txt not found!");

    QString key("123456789123");

    QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray encodeText = encryption.encode(input, hashKey, iv);
    QByteArray decodedText = encryption.removePadding(encryption.decode(encodeText, hashKey, iv));
    QCOMPARE(decodedText, input);
}

   Q_SLOT void cleanupTestCase(){}

private:
    QByteArray key16;
    QByteArray key24;
    QByteArray key32;
    QByteArray iv;
    QByteArray in;
    QByteArray outECB128;
    QByteArray outECB192;
    QByteArray outECB256;
    QByteArray inCBC128;
    QByteArray outCBC128;
};

#endif // AESTEST_H
/// End herE
//#include <QByteArray>

//#include <QCryptographicHash>
/////
////

/*
  Q_SLOT  void initTestCase();
  Q_SLOT  void ECB128Crypt();
   Q_SLOT void ECB128Decrypt();

   Q_SLOT void ECB192Crypt();
   Q_SLOT void ECB192Decrypt();

   Q_SLOT void ECB256Crypt();
   Q_SLOT void ECB256Decrypt();

   Q_SLOT void ECB256String();

   Q_SLOT void CBC128Crypt();
   Q_SLOT void CBC128Decrypt();

   Q_SLOT void CFB256String();

   Q_SLOT void CFB256LongText();
*/
