#ifndef SAVER_H
#define SAVER_H
#include "concretecalculator.h"
#include "storage/signalsstorage.h"

// Класс, который просто сохраняет данные из 1 во 2 хранилище
class Transfer : public ConcreteCalculator
{
public:
    Transfer(SignalsStorage& srcStorage, const QString& srcName,
          SignalsStorage& destStorage, const QString& destName);
    void handle() override;
    ~Transfer() override;

};

#endif // SAVER_H
