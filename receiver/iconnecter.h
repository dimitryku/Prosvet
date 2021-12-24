#ifndef ICONNECTER_H
#define ICONNECTER_H

#include <QObject>
#include <QPointer>
#include "coder.h"

/// Интерфейс Коннектора под различные целевые системы и способы подключения///
class IConnecter : public QObject
{
    Q_OBJECT

public:
    IConnecter(QString protocolName);
    ~IConnecter();
    void setCoder(QPointer<Coder> coder);

public slots:  virtual void fromCodecRead(QByteArray data) = 0; /// Слот, который должен срабатывать на сигнал из Кодека при подготовленных данных для отправки
               virtual void fromDeviceRead() = 0;               /// Слот, который срабатывает при поступлении данных с ЦС

protected:
    QPointer<Coder> coder;
    QByteArray buffer;
    QString protocolName;
};

#endif // ICONNECTER_H
