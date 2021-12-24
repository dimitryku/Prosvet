#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto tm = QTime::currentTime();
       TmpConfig cfg;
        storage = new SignalsStorage();

       cfg.test2(*storage);
       qDebug() << tm.msecsTo(QTime::currentTime());

}

MainWindow::~MainWindow()
{
    delete ui;
}

