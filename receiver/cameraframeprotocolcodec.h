#ifndef CAMERAFRAMEPROTOCOLCODEC_H
#define CAMERAFRAMEPROTOCOLCODEC_H

#include "icodec.h"
#include "cameraframeprotocol.h"
#pragma pack(1)
class CameraFrameProtocolCodec : public ICodec
{
public:
    CameraFrameProtocolCodec(SignalsStorage &storage );
    bool decode(QByteArray data, QString source = "") override;
    void transferSignals(QString source) override;
    cameraFrameProtocol* current;
private:
    static const int frameId     = 4;
    static const int frameHeaderSize = 36;
};

#endif // CAMERAFRAMEPROTOCOLCODEC_H
