#ifndef SIGNALSTORAGE_H
#define SIGNALSTORAGE_H
#include <QHash>
#include <QList>

#include "signal.h"
#include "concretestorage.h"
#include "storage/storagewatcher.h"

//TODO:
// removeStorage
class SignalsStorage
{
private:
    // HashMap хранилищ по именам сигналов
    QHash<QString, ConcreteStorage*> storage_;
    // Объект уведомления обработчиков о новых данных
    QList<StorageWatcher*> watchers_;

public:
    SignalsStorage();
    // метод добавления нового наблюдателя
    void addWatcher(StorageWatcher *watcher);
    // Метод добавления нового хранилища
    void addConcreteStorage(const QString &name, ConcreteStorage* storage = new ConcreteStorage());
    // Метод добавления нового сигнала в хранилище
    void add(const QString& name, Signal& signal);

    // Метод получения следующего сигнала по имени
    Signal& getNextSignal(bool& validValue, const QString& name);
    // Метода получения num сигналов по имени
    QList<Signal> getSignals(const QString& name, int num = INT_MAX) const;
    // Метод получения числа сигналов по имени
    int getQuantity(const QString& name);

    // Метод сброса позиции поэлементного прохода конкретного хранилища
    void resetPosition(const QString& name);
    // Метод удаления сигнала из конкретного хранилища
    void deleteAt(const QString& name, const int pos);
    // Перегруженный метод удаления num сигналов, начиная с позиции start из конкретного хранилища
    void deleteAt(const QString& name, const int start, const int num);

    ~SignalsStorage();

private:
    // Метод проверки наличия хранилища с таким названием
    // При отсутствии выбрасывает исключение
    void checkIfNotExists(const QString& name) const;
};

#endif // SIGNALSTORAGE_H
