#include "cameraframeprotocolcodec.h"
#include "QDebug"
CameraFrameProtocolCodec::CameraFrameProtocolCodec(SignalsStorage & storage ) : ICodec(storage)
{

}

bool CameraFrameProtocolCodec::decode(QByteArray data, QString source)
{
    cameraFrameProtocol* signal  = new cameraFrameProtocol(); // reinterpret_cast<cameraFrameProtocol*>(&data);


    int shift = 0;
    qstrcpy(signal->UniqID.get(), (const char*)data.left(frameId));
    signal->dataSize          = *reinterpret_cast<quint32*> (data.data() + (shift += frameId));
    signal->reserv1           = *reinterpret_cast<quint32*> (data.data() + (shift += sizeof(signal->dataSize)));
    signal->timeMark          = *reinterpret_cast<quint64*> (data.data() + (shift += sizeof(signal->reserv1)));
    signal->chanelID          = *reinterpret_cast<quint8*>  (data.data() + (shift += sizeof(signal->timeMark)));
    signal->imageWidth        = *reinterpret_cast<quint16*> (data.data() + (shift += sizeof(signal->chanelID)));
    signal->reserv2           = *reinterpret_cast<quint8*>  (data.data() + (shift += sizeof(signal->imageWidth)));
    signal->visionAngle       = *reinterpret_cast<quint16*> (data.data() + (shift += sizeof(signal->reserv2)));
    signal->imageHeight       = *reinterpret_cast<quint16*> (data.data() + (shift += sizeof(signal->visionAngle)));
    signal->amountOfColors    = *reinterpret_cast<quint8*>  (data.data() + (shift += sizeof(signal->imageHeight)));
    signal->colorSpaceType    = *reinterpret_cast<quint8*>  (data.data() + (shift += sizeof(signal->amountOfColors)));
    signal->reserv3           = *reinterpret_cast<quint16*> (data.data() + (shift += sizeof(signal->colorSpaceType)));
    signal->imageFormat       = *reinterpret_cast<quint32*> (data.data() + (shift += sizeof(signal->reserv3)));
    signal->imageData         = data.right(data.size()-frameHeaderSize);

    if(!buffers.contains(source)){
        buffers.insert(source, data);
        signalMap.insert(source, signal);
    } else {
        buffers[source] = data;
        signalMap[source] = signal;
    }

    if(analysisVar.contains("Raw")){
        Signal sig(data);
        storage_.add(source+"_Raw", sig);
    }
    current = signal;
    transferSignals(source);

    return true;
}

void CameraFrameProtocolCodec::transferSignals(QString source)
{
    if(analysisVar.contains("UniqID")){
        Signal sig(current->UniqID.get());
        storage_.add(source+"_UniqID", sig);
    }

    if(analysisVar.contains("dataSize")){
        Signal sig(current->dataSize);
        storage_.add(source+"_dataSize", sig);
    }

    if(analysisVar.contains("reserv1")){
        Signal sig(current->reserv1);
        storage_.add(source+"_reserv1", sig);
    }

    if(analysisVar.contains("timeMark")){
        Signal sig(current->timeMark);
        storage_.add(source+"_timeMark", sig);
    }

    if(analysisVar.contains("chanelID")){
        Signal sig(current->chanelID);
        storage_.add(source+"_chanelID", sig);
    }

    if(analysisVar.contains("imageWidth")){
        Signal sig(current->imageWidth);
        storage_.add(source+"_imageWidth", sig);
    }

    if(analysisVar.contains("reserv2")){
        Signal sig(current->reserv2);
        storage_.add(source+"_reserv2", sig);
    }

    if(analysisVar.contains("visionAngle")){
        Signal sig(current->visionAngle);
        storage_.add(source+"_visionAngle", sig);
    }

    if(analysisVar.contains("imageHeight")){
        Signal sig(current->imageHeight);
        storage_.add(source+"_imageHeight", sig);
    }

    if(analysisVar.contains("amountOfColors")){
        Signal sig(current->amountOfColors);
        storage_.add(source+"_amountOfColors", sig);
    }

    if(analysisVar.contains("colorSpaceType")){
        Signal sig(current->colorSpaceType);
        storage_.add(source+"_colorSpaceType", sig);
    }

    if(analysisVar.contains("reserv3")){
        Signal sig(current->reserv3);
        storage_.add(source+"_reserv3", sig);
    }

    if(analysisVar.contains("imageFormat")){
        Signal sig(current->imageFormat);
        storage_.add(source+"_imageFormat", sig);
    }

    if(analysisVar.contains("imageData")){
        Signal sig(current->imageData);
        storage_.add(source+"_imageData", sig);
    }


}

