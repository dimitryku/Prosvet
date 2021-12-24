#ifndef CODECCAMERAUDPPROTOCOL_H
#define CODECCAMERAUDPPROTOCOL_H
#include "icodec.h"
#include "cameraudpprotocol.h"


class CameraUdpProtocolCodec : public ICodec
{
public:
    CameraUdpProtocolCodec(SignalsStorage & storage );
    bool decode(QByteArray data, QString source = "") override;
    void transferSignals(QString source = "") override;

private:
    QHash<QString, udpInfo> infosUdpPackets;

    static const int packetId    = 3;
    QPointer<cameraUdpProtocol> currentPacket;
    //void cheackHuffman();
};

#endif // CODECCAMERAUDPPROTOCOL_H
