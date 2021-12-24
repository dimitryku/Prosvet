#include <QApplication>
#include "cameraframeprotocolcodec.h"
#include "cameraudpprotocolcodec.h"
#include "udpconnector.h"
#include "coder.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
