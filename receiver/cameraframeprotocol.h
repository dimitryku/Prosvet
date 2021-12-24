#ifndef CAMERAFRAMEPROTOCOL_H
#define CAMERAFRAMEPROTOCOL_H

#include <QSharedPointer>
#include "IProtocol.h"

static const int frameId  = 4;
#pragma pack(1)
class cameraFrameProtocol : public IProtocol
{

public:
    QSharedPointer<char> UniqID;//          = {'O','S','I','M'};
    quint32 dataSize;
    quint32 reserv1         = 0;
    qint64  timeMark;
    quint8  chanelID;
    quint16 imageWidth;
    quint8  reserv2         = 0;
    quint16 visionAngle;
    quint16 imageHeight;
    quint8  amountOfColors  = 0;
    quint8  colorSpaceType  = 0;
    quint16 reserv3         = 0;
    qint32  imageFormat;
    QByteArray imageData; // изображение
    cameraFrameProtocol();
};

#endif // CAMERAFRAMEPROTOCOL_H
