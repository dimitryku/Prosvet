#include "tmpconfig.h"

#include <QDebug>

TmpConfig::TmpConfig()
    : calc()
    , watcher()
    //, storage()
    //, storageToView()
{
    //storage.addConcreteStorage("1");
    //storageToView.addConcreteStorage("11");
    watcher.addCalculator(&calc);
    //storage.addWatcher(&watcher);
    //calc.addConcreteCalculator(new Transfer(storage, "1", storageToView, "11"));
}

void TmpConfig::test()
{
    for(int i = 0; i < 1000; i++)
    {
        Signal bb = Signal(i);
        //storage.add("1", bb);
        bool flag = false;
//        auto tmp = storageToView.getNextSignal(flag, "11");
//        if(flag)
//            qDebug() << tmp.toInt();
    }
}

void TmpConfig::test2(SignalsStorage& storage)
{
     QString source="10.13.255.255_";
    CameraFrameProtocolCodec* frameCodec;
    CameraUdpProtocolCodec* udpCodec;
    QPointer<Coder> coder;
    UdpConnector* connector;

    storage.addConcreteStorage(source+"UniqID");
    storage.addConcreteStorage(source+"dataSize");
    //storage.addConcreteStorage(source+"reserv1");
    storage.addConcreteStorage(source+"timeMark");
    storage.addConcreteStorage(source+"chanelID");
    storage.addConcreteStorage(source+"imageWidth");
    //storage.addConcreteStorage(source+"reserv2");
    storage.addConcreteStorage(source+"visionAngle");
    storage.addConcreteStorage(source+"imageHeight");
    storage.addConcreteStorage(source+"amountOfColors");
    storage.addConcreteStorage(source+"colorSpaceType");
    //storage.addConcreteStorage(source+"reserv3");
    storage.addConcreteStorage(source+"imageFormat");
    storage.addConcreteStorage(source+"imageData");

    frameCodec = new CameraFrameProtocolCodec(storage);
    QStringList list;
    list.append("UniqID");
    list.append("dataSize");
    //list.append("reserv1");
    list.append("timeMark");
    list.append("chanelID");
    list.append("imageWidth");
    //list.append("reserv2");
    list.append("visionAngle");
    list.append("imageHeight");
    list.append("amountOfColors");
    list.append("colorSpaceType");
    //list.append("reserv3");
    list.append("imageFormat");
    list.append("imageData");

    frameCodec->addAnalysisVar(list);
    udpCodec = new CameraUdpProtocolCodec(storage);
    udpCodec->setCodec(frameCodec);
    coder = new Coder();

    coder->addNewCodec("cameraProtocol", udpCodec);
    QString ip = "10.13.255.255";
    connector = new UdpConnector(ip, 8000, "cameraProtocol");
    connector->setCoder(coder);

    connector->startConnection();

    qDebug()<<storage.getSignals(source+"imageData");
    qDebug()<<storage.getSignals(source+"UniqID");
    qDebug()<<storage.getSignals(source+"timeMark");



}
