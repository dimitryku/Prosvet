#include "storagewatcher.h"

StorageWatcher::StorageWatcher()
    : calculators_()
{}

void StorageWatcher::addCalculator(Calculator* calculator)
{
    calculators_.push_back(calculator);
}


void StorageWatcher::notify(const QString& name) const
{
    //TODO добавить проверку накопления нужного числа данных
    for(auto calc : calculators_)
        calc->notify(name);
}

