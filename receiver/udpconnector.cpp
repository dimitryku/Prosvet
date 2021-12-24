#include "udpconnector.h"


UdpConnector::UdpConnector(QString IP, int port, QString protocolName) : IConnecter(protocolName)
{

    this->ip = IP;
    this->port = port;

}
void UdpConnector::startConnection()
{
    qDebug()<<"connect";
    socket = new QUdpSocket();
    socket->bind(QHostAddress(ip), port);
    connect(socket, SIGNAL(readyRead()),this, SLOT(fromDeviceRead()));
}

void UdpConnector::closeConnection()
{
    socket->close();
    delete socket;
}


void UdpConnector::fromCodecRead(QByteArray data)
{

}

void UdpConnector::fromDeviceRead()
{

    while(socket->hasPendingDatagrams())
    {
        buffer.resize(socket->pendingDatagramSize());
        socket->readDatagram(buffer.data(), buffer.size());
        coder->read(buffer, ip, protocolName);
        buffer.clear();
    }
}
