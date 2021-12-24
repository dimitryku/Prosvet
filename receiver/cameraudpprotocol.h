#ifndef CAMERAUDPPROTOCOL_H
#define CAMERAUDPPROTOCOL_H

#include "IProtocol.h"
#include <QSharedPointer>

#pragma pack(1)
class cameraUdpProtocol : public IProtocol
{
public:
        QSharedPointer<char> UniqID; // = {'O','E','S'};
        qint8 reserv1               = 0;
        quint32 globalFrameCounter  = 0;
        quint32 localFrameCounter   = 0;
        quint32 fullFrameSize;
        quint32 currentDataShift;
        quint16 currentDataSize;
        quint8 reserv2              = 0;
        qint8  chanelID;
        QByteArray data;  //часть от frameStructure
    cameraUdpProtocol();
};

struct udpInfo{
    //QByteArray huffman;
    //QByteArray huffman2;
    static const int packetId = 3;
    unsigned int packetsSumm = INT_MAX;
    QByteArray tempData[1024];
    quint32 tempNumOfPackets = 0;
};
#endif // CAMERAUDPPROTOCOL_H
