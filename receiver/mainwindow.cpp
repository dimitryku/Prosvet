#include "mainwindow.h"

#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

     ui->setupUi(this);

      frameCodec = new CameraFrameProtocolCodec();
      udpCodec = new CameraUdpProtocolCodec();
      udpCodec->setCodec(frameCodec);
      coder = new Coder();

     coder->addNewCodec("cameraProtocol", udpCodec);
     connector = new UdpConnector("10.13.255.255", 8000, "cameraProtocol");
     connector->setCoder(coder);

     connector->startConnection();
     connect(coder,SIGNAL(sendImg(QByteArray)), this, SLOT(grab(QByteArray)));
}

MainWindow::~MainWindow(){
         delete ui;
         delete frameCodec;
         delete udpCodec;
         delete connector;
     }

void MainWindow::grab(QByteArray bytes)
{
    ui->label->setPixmap( QPixmap::fromImage(QImage::fromData(bytes)));
}
