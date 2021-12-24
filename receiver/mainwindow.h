#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "cameraframeprotocolcodec.h"
#include "cameraudpprotocolcodec.h"
#include "udpconnector.h"
#include "coder.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); //TODO Тут вылетает SIGFault  Понять и пофиксить

signals:

public slots: void grab(QByteArray bytes);

private:
    Ui::MainWindow *ui;
    CameraFrameProtocolCodec* frameCodec;
    CameraUdpProtocolCodec* udpCodec;
    QPointer<Coder> coder;
    UdpConnector* connector;

};

#endif // MAINWINDOW_H
