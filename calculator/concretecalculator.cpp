#include "concretecalculator.h"
#include "storage/signalsstorage.h"

ConcreteCalculator::ConcreteCalculator(SignalsStorage& srcStorage, const QString& srcName,
                                       SignalsStorage& destStorage, const QString& destName)
    : srcName_(srcName)
    , srcStorage_(srcStorage)
    , destName_(destName)
    , destStorage_(destStorage)
{}

QString ConcreteCalculator::getSrcName() const
{
    return srcName_;
}

ConcreteCalculator::~ConcreteCalculator()
{}

