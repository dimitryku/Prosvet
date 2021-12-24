#ifndef CONCRETECALCULATOR_H
#define CONCRETECALCULATOR_H

#include <QString>

class SignalsStorage;

class ConcreteCalculator
{
protected:
    // Имя входного сигнала
    const QString srcName_;
    // Ссылка на источник входного сигнала
    SignalsStorage& srcStorage_;
    // Имя выходного сигнала
    const QString destName_;
    // Ссылка на место записи выходного сигнала
    SignalsStorage& destStorage_;

public:
    ConcreteCalculator(SignalsStorage& srcStorage, const QString& srcName,
                       SignalsStorage& destStorage, const QString& destName);
    // Метод обработки данных, заданых защищенными полями
    virtual void handle() = 0;

    QString getSrcName() const;
    virtual ~ConcreteCalculator();
};

#endif // CONCRETECALCULATOR_H
