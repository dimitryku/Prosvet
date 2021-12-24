#include "icodec.h"
#include "QDebug"
ICodec::ICodec(  SignalsStorage& storage )
    : storage_(storage)
{
}




void ICodec::setCodec(ICodec* codec)
{
    nextCodec =  codec;
}

QPointer<IProtocol> ICodec::getSignal(QString source)
{
    if(nextCodec != nullptr)
        signalMap[source] = nextCodec->getSignal(source);
    return signalMap[source];
}

void ICodec::addAnalysisVar(QStringList variables)
{
    for(QString var : variables){
        if(!analysisVar.contains(var))
            this->analysisVar.append(var);
    }
}
