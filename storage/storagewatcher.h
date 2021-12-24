#ifndef STORAGEWATCHER_H
#define STORAGEWATCHER_H
#include <QString>
#include <QHash>

#include "calculator/calculator.h"
#include <QList>

class StorageWatcher
{
private:
    QList<Calculator*> calculators_;
    //TODO добавить мапу количества информации (продумать)

public:
    StorageWatcher();
    // Добавление слушателей
    void addCalculator(Calculator* calculator);
    // Получение и пересылка далее информации о поступивших данных
    void notify(const QString& name) const;
};

#endif // STORAGEWATCHER_H
