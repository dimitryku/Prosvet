#include "transfer.h"

Transfer::Transfer(SignalsStorage& srcStorage, const QString& srcName,
             SignalsStorage& destStorage, const QString& destName)
    : ConcreteCalculator(srcStorage, srcName, destStorage, destName)
{}


void Transfer::handle()
{
    QList<Signal> sigs = srcStorage_.getSignals(srcName_);
    for(auto& sig : sigs)
        destStorage_.add(destName_, sig);
    srcStorage_.deleteAt(srcName_, 0, sigs.size());
}

Transfer::~Transfer()
{}
