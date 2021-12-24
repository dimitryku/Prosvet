#include "cameraudpprotocolcodec.h"
#include "QDebug"
CameraUdpProtocolCodec::CameraUdpProtocolCodec(SignalsStorage& storage ) : ICodec(storage)
{

}
bool CameraUdpProtocolCodec::decode(QByteArray data, QString source)
{

    //Перевели байты в структуру UDP пакета
    QPointer<cameraUdpProtocol> packet;
    packet =  new cameraUdpProtocol(); // reinterpret_cast<cameraUdpProtocol*>(&data);

    int shift = 0;
    qstrcpy(packet->UniqID.get(), (const char*)(data.left(packetId)));
    packet->reserv1            = *reinterpret_cast<quint8*>  (data.data() + (shift += packetId));
    packet->globalFrameCounter = *reinterpret_cast<quint32*> (data.data() + (shift += sizeof(packet->reserv1)));
    packet->localFrameCounter  = *reinterpret_cast<quint32*> (data.data() + (shift += sizeof(packet->globalFrameCounter)));
    packet->fullFrameSize      = *reinterpret_cast<quint32*> (data.data() + (shift += sizeof(packet->localFrameCounter)));
    packet->currentDataShift   = *reinterpret_cast<quint32*> (data.data() + (shift += sizeof(packet->fullFrameSize)));
    packet->currentDataSize    = *reinterpret_cast<quint16*> (data.data() + (shift += sizeof(packet->currentDataShift)));
    packet->reserv2            = *reinterpret_cast<quint8*>  (data.data() + (shift += sizeof(packet->currentDataSize)));
    packet->chanelID           = *reinterpret_cast<quint8*>  (data.data() + (shift += sizeof(packet->reserv2)));
    packet->data               = data.right(packet->currentDataSize);

    currentPacket = packet;

    if(analysisVar.contains("Raw")){
        Signal sig(data);
        storage_.add(source+"_Raw", sig);
    }
    transferSignals(source);

    udpInfo* info = new udpInfo();

    //проверяем есть ли данные из этого источника
    if(!infosUdpPackets.contains(source)) /*&& infosUdpPackets.end().key() == ""*/
    {
        infosUdpPackets.insert(source, *info);

        QByteArray bytes;
        buffers.insert(source, bytes);
    }
    else
    {
        info = &infosUdpPackets[source];
    }

    info->tempNumOfPackets++;
    if(packet->currentDataSize <= 1200)
    {
       // qDebug()<<packet->data.data();
        if(packet->currentDataShift == 0)
        {

            // qstrcpy(frameData.UniqID.get(), (const char*)packet.data.left(frameId));
            // nextCodec->decode()
            // udpPacketToFrameData(packet, &frameData, info.tempData[packet.currentDataShift]);
            //cheackHuffman();

            info->tempData[0] = packet->data;
          //  qDebug()<<info->tempData[0];
            info->packetsSumm = packet->fullFrameSize / packet->currentDataSize + (packet->fullFrameSize % packet->currentDataSize == 0 ? 0 : 1);
            if(info->packetsSumm > 1024 || info->packetsSumm <= 0)
                return false;
        }
        else
        {
            if(packet->currentDataShift > 1024 || packet->currentDataShift <= 0)
                return false;
            info->tempData[packet->currentDataShift] = packet->data;
        }


        if((packet->currentDataShift + 1 == info->packetsSumm && info->tempNumOfPackets >= info->packetsSumm) \
                || (  info->tempNumOfPackets >= info->packetsSumm  && ! info->tempData[info->packetsSumm - 1].isEmpty()) )
        {
            buffers[source].clear();
            for(unsigned int i = 0; i <  info->packetsSumm; i++)
            {
                buffers[source] += info->tempData[i];
                info->tempData[i].clear();
            }
            nextCodec->decode(buffers[source], source);
            info->tempNumOfPackets = 0;
            info->packetsSumm = INT_MAX;
            return true;
        }

        if(info->tempNumOfPackets >= info->packetsSumm)
            info->tempNumOfPackets = info->packetsSumm - 1;
    }

    return false;

}

void CameraUdpProtocolCodec::transferSignals(QString source){

    if(analysisVar.contains("UniqID")){
        Signal sig(currentPacket->UniqID.get());
        storage_.add(source+"_UniqID", sig);
    }

    if(analysisVar.contains("reserv1")){
        Signal sig(currentPacket->reserv1);
        storage_.add(source+"_reserv1", sig);
    }

    if(analysisVar.contains("globalFrameCounter")){
        Signal sig(currentPacket->globalFrameCounter);
        storage_.add(source+"_globalFrameCounter", sig);
    }

    if(analysisVar.contains("globalFrameCounter")){
        Signal sig(currentPacket->globalFrameCounter);
        storage_.add(source+"_globalFrameCounter", sig);
    }

    if(analysisVar.contains("localFrameCounter"))
    {
        Signal sig(currentPacket->localFrameCounter);
        storage_.add(source+"_localFrameCounter", sig);
    }

    if(analysisVar.contains("fullFrameSize"))
    {
        Signal sig(currentPacket->fullFrameSize);
        storage_.add(source+"_fullFrameSize", sig);
    }

    if(analysisVar.contains("currentDataShift"))
    {
        Signal sig(currentPacket->currentDataShift);
        storage_.add(source+"_currentDataShift", sig);
    }

    if(analysisVar.contains("currentDataSize"))
    {
        Signal sig(currentPacket->currentDataSize);
        storage_.add(source+"_currentDataSize", sig);
    }

    if(analysisVar.contains("reserv2")){
        Signal sig(currentPacket->reserv2);
        storage_.add(source+"_reserv2", sig);
    }

    if(analysisVar.contains("chanelID")){
        Signal sig(currentPacket->chanelID);
        storage_.add(source+"_chanelID", sig);
    }

    if(analysisVar.contains("data")){
        Signal sig(currentPacket->data);
        storage_.add(source+"_data", sig);
    }



}
