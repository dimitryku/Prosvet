#ifndef TMPCONFIGFORSTORAGESCALULATOR_H
#define TMPCONFIGFORSTORAGESCALULATOR_H
#include "calculator/calculator.h"
#include "calculator/concretecalculator.h"
#include "storage/signalsstorage.h"
#include "storage/storagewatcher.h"
#include "calculator/transfer.h"
#include "receiver/udpconnector.h"
#include "receiver/coder.h"
#include "receiver/cameraudpprotocolcodec.h"
#include "receiver/cameraframeprotocolcodec.h"

class TmpConfig
{
private:
    Calculator calc;
    StorageWatcher watcher;
    //SignalsStorage storage;
    //SignalsStorage storageToView;
public:
    TmpConfig();
    void test();
    void test2(SignalsStorage& storage);
};

#endif // TMPCONFIGFORSTORAGESCALULATOR_H
