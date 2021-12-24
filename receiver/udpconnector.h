#ifndef UDPCONNECTOR_H
#define UDPCONNECTOR_H

#include <QObject>
#include <QUdpSocket>
#include <QPointer>

#include "iconnecter.h"

class UdpConnector : public IConnecter
{
    Q_OBJECT
public:
    UdpConnector(QString IP, int port, QString protocolName);
    void startConnection();
    void closeConnection();


public slots: void fromCodecRead(QByteArray data) override; /// Слот, который должен срабатывать на сигнал из Кодека при подготовленных данных для отправки
              void fromDeviceRead() override;

private:
    QPointer<QUdpSocket> socket;
    QString ip;
    int port;
};

#endif // UDPCONNECTOR_H
