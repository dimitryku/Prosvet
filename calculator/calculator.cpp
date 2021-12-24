#include "calculator.h"

Calculator::Calculator()
    : calculators_()
    , queueToCalculate_()
{}

void Calculator::notify(const QString& name)
{
    queueToCalculate_.enqueue(name);
    calculateNext();                            //TODO это временно, потом отдельно поток
}

void Calculator::calculateNext()
{
    if(queueToCalculate_.empty())
        return;                                 //TODO мб bool

    // Вытаскиваем следующее имя данных
    auto name = queueToCalculate_.dequeue();
    if(!calculators_.contains(name))
        return;

    // Получаем список обработчиков для полученного
    // названия данных и обрабатываем полученные значения
    auto calcs = calculators_.values(name);
    for(auto calc : calcs)
        calc->handle();

}

void Calculator::addConcreteCalculator(ConcreteCalculator* calculator)
{
    calculators_.insert(calculator->getSrcName(), calculator);
}

Calculator::~Calculator()
{
    // Получаем список ключей
    // и вытаскиваем по ним все значения из хранилища,
    // попутно освобождая память
    auto keys = calculators_.keys();
    for(auto key : keys)
    {
        while(calculators_.contains(key))
        {
            auto tmp = calculators_.take(key);
            delete tmp;
        }
    }
}
