#include "coder.h"
#include "QDebug"
#include "cameraframeprotocol.h"
Coder::Coder(QObject* parent)
    : QObject(parent)
    , codecs()
{
}

void Coder::addNewCodec(QString protocolName, QPointer<ICodec> protocol)
{
    codecs.insert(protocolName, protocol);

}

void Coder::read(QByteArray data, QString source, QString protocolName)
{
    if(codecs.contains(protocolName)){
        codecs[protocolName]->decode(data, source);
    }

}


