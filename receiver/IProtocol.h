#ifndef DEVICEPROTOCOLS_H
#define DEVICEPROTOCOLS_H
/// Хедер который
#include <QString>
#include <QObject>
class IProtocol : public QObject
{
    Q_OBJECT

    protected: QString protocolName;

    public: IProtocol(){ this->protocolName = "";}
            QString getProtocolName(){return  protocolName;}
            virtual ~IProtocol()
            {
            }
};
#endif // DEVICEPROTOCOLS_H
