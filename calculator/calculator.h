#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QMultiHash>
#include <QQueue>

#include "concretecalculator.h"

class Calculator
{
private:
    // HashMap для связи данных и обработчиков
    QMultiHash<QString, ConcreteCalculator*> calculators_;
    // Очередь на обработку
    QQueue<QString> queueToCalculate_;

public:
    Calculator();
    ~Calculator();

    // Метод для добавления имени входных данных в очередь обработки
    void notify(const QString& name);
    // Метод для рассчета следующих данных из очереди
    void calculateNext();
    // Метод добавления обработчиков
    void addConcreteCalculator(ConcreteCalculator* calculator);
};

#endif // CALCULATOR_H
