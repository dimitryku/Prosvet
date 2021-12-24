#include "iconnecter.h"

IConnecter::IConnecter(QString protocolName)
{
    this->protocolName = protocolName;
}

IConnecter::~IConnecter()
{

}


void IConnecter::setCoder(QPointer<Coder> coder)
{
    this->coder = coder;
}

