#include "ui/mainwindow.h"
#include "tmpconfig.h"

#include <QApplication>
#include <qdebug.h>
#include <QTime>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
