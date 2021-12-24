#include "cameraframeprotocol.h"

cameraFrameProtocol::cameraFrameProtocol()
{
    this->protocolName = "cameraFrameProtocol";
    UniqID = QSharedPointer<char>(new char[frameId],[](char* x){delete[] x;});
}
