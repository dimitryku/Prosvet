#include "signalsstorage.h"
#include <QDebug>
#define dbg 1

SignalsStorage::SignalsStorage()
    : storage_()
    , watchers_()
{}

void SignalsStorage::addWatcher(StorageWatcher *watcher)
{
    watchers_.push_back(watcher);
}

void SignalsStorage::add(const QString& name, Signal& signal)
{
    checkIfNotExists(name);
#if dbg
    qDebug() << "cs add " << signal.toInt() << " " << signal.data();
#endif
    storage_[name]->signals_.append(signal);
#if dbg
    qDebug() << "cs added as " << (storage_[name]->signals_.end() - 1)->toInt() << " " << (storage_[name]->signals_.end() - 1)->data();
#endif
    for(auto watcher : watchers_)
    watcher->notify(name);
}

void SignalsStorage::addConcreteStorage(const QString &name, ConcreteStorage* storage)
{
    if(storage_.contains(name))
        throw QString("Попытка создать хранилище с уже имеющимся ключом!");
    storage_.insert(name, storage);
}

Signal& SignalsStorage::getNextSignal(bool& validValue, const QString& name)
{
    checkIfNotExists(name);
    // Если пусто или дошли до конца, выставляем false в флаг и возвращаем управление
    if(storage_[name]->signals_.empty() ||
       storage_[name]->currentPos_ >= storage_[name]->signals_.size())
    {
        validValue = false;
        return *(storage_[name]->signals_.end());
    }
    validValue = true;
#if dbg
    qDebug() << "сs gtnxt " << storage_[name]->signals_[storage_[name]->currentPos_].toInt()
             << " " << storage_[name]->signals_[storage_[name]->currentPos_].data();
#endif
    return storage_[name]->signals_[storage_[name]->currentPos_++];
}

QList<Signal> SignalsStorage::getSignals(const QString& name, int num) const
{
    checkIfNotExists(name);
    if(num < 0)
        throw QString("Количество не может быть меньше 0!");

    // Создаем лист для возврата и определяем число элементов в нем
    QList<Signal> result;
    num = num < storage_[name]->signals_.size() ? num : storage_[name]->signals_.size();

    // Заполняем и возвращаем запрошенные данные
    for(auto i = 0; i < num; i++)
        result.append(storage_[name]->signals_[i]);

    return result;
}

void SignalsStorage::resetPosition(const QString &name)
{
    checkIfNotExists(name);
    storage_[name]->currentPos_ = 0;
}

void SignalsStorage::deleteAt(const QString &name, int pos = 0)
{
    checkIfNotExists(name);
    if(pos >= storage_[name]->signals_.size())
        throw QString("Ошибка удаления: Индекс вышел за границы!");

    // При необходимости, переводим счетчик текущего элемента назад
    storage_[name]->currentPos_ -= storage_[name]->currentPos_ > pos;
#if dbg
    qDebug() << "сs del " << storage_[name]->signals_[pos].toInt() << " " << storage_[name]->signals_[pos].data();
#endif
    storage_[name]->signals_.removeAt(pos);
}

void SignalsStorage::deleteAt(const QString &name, int start, const int num)
{
    checkIfNotExists(name);
    // Проверяем на выход чисел за границы
    auto end = start + num;
    if(start < 0 || end > storage_[name]->signals_.size())
        throw QString("Ошибка удаления: Индекс вышел за границы!");

    // Удаляем элементы
    for(auto i = end - 1; i >= start; i--)
    {
#if dbg
        qDebug() << "сs dela " << storage_[name]->signals_[i].toInt()
                 << " " << storage_[name]->signals_[i].data();
#endif
        storage_[name]->signals_.removeAt(i);
    }

    // При необходимости, переводим счетчик текущего элемента назад
    if(storage_[name]->currentPos_ > start)
        storage_[name]->currentPos_ -= (end < storage_[name]->currentPos_ ? num : storage_[name]->currentPos_ - start);
}

int SignalsStorage::getQuantity(const QString &name)
{
    checkIfNotExists(name);
    return storage_[name]->signals_.count();
}

void SignalsStorage::checkIfNotExists(const QString& name) const
{
    if(!storage_.contains(name))
        throw QString("Не найдено хранилище с названием " + name + "!");
}

SignalsStorage::~SignalsStorage()
{
    // Получаем список ключей, очищаем соответствующие хранилища
    // и освобождаем от них память
    auto keys = storage_.keys();
    for(auto key : keys)
    {
        deleteAt(key, 0, getQuantity(key));
        delete storage_[key];
        storage_.remove(key);
    }
}
