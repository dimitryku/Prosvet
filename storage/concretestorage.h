#ifndef CONCRETESTORAGE_H
#define CONCRETESTORAGE_H
#include <QList>

#include "signal.h"

class SignalsStorage;

class ConcreteStorage
{
    // Передаем управление к SignalsStorage
    friend SignalsStorage;

protected:
    // Список сигналов с одним именем описания
    QList<Signal> signals_;
    // Текущая позиция поэлементного прохода QList
    int currentPos_ = 0;

public:
    ConcreteStorage();
};

#endif // CONCRETESTORAGE_H
