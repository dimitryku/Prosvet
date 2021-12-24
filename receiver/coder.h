#ifndef CODER_H
#define CODER_H

#include <QHash>

#include "icodec.h"
#include "QObject"


class Coder : public QObject
{
    Q_OBJECT
protected: QHash<QString, QPointer<ICodec>> codecs;

public:
    Coder(QObject* parent = nullptr);
    void addNewCodec(QString protocolName, QPointer<ICodec> protocol);
    void read(QByteArray data, QString source, QString protocolName); //Читает поступающие данные, если нужна декодировка отправляет в кодировщик,
    //если получены необходимые данные отправляет в Storage
signals: void sendImg(QByteArray);

};

#endif // CODER_H
