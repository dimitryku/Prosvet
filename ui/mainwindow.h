#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "tmpconfig.h"
#include <QTime>
#include "storage/signalsstorage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    SignalsStorage* storage;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
