#include "cameraudpprotocol.h"


cameraUdpProtocol::cameraUdpProtocol()
{
    this->protocolName = "cameraUdpProtocol";
    UniqID = QSharedPointer<char>(new char[udpInfo::packetId],[](char* x){delete[] x;});
}
