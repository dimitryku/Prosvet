#ifndef ICODEC_H
#define ICODEC_H


#include <QByteArray>
#include <QPointer>
#include <QHash>

#include "IProtocol.h"
#include "storage/signalsstorage.h"
#include "signal.h"

class ICodec : public QObject
{
    Q_OBJECT


protected:
    ICodec* nextCodec = nullptr;
    QHash<QString, QByteArray> buffers;
    QHash<QString, QPointer<IProtocol>> signalMap;
    QStringList analysisVar;
    SignalsStorage& storage_;

public:
    ICodec(SignalsStorage& storage);


    //virtual void encode(Signal signal); ///Кодировка команд
    virtual bool decode(QByteArray data, QString source = "") = 0; ///Декодировка данных с ЦС, если источник пришел, значит пришло из менеджера ,
                                                                    ///если нет, то пришло из другого кодека, а следовательно данные полные
    virtual void transferSignals(QString source = "") = 0;
    void setCodec(ICodec* codec);
    QPointer<IProtocol> getSignal(QString source);
    void addAnalysisVar(QStringList variables);





};

#endif // ICODEC_H

