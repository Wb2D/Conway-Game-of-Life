#ifndef LIFE_H
#define LIFE_H

#include <QObject>
#include <QLabel>
#include <QSize>
#include <QVector>

#include "Model/Pair.h"

class Life
{
public:
    // конструктор с параметрами : высота, ширина
    Life(const Pair&);

    // геттер поля _fieldSize
    Pair getFieldSize() const { return _fieldSize; }
    // возвращает элемент _generation
    bool getElement(const Pair& obj) const { return _generation[obj.getX()][obj.getY()]; }

    // мето для изменения размера текущего вектора с очисткой
    void resize(const Pair&);
    // метод, дающий жизнь
    void setLife(const Pair&);
    // апокалипсис
    void killAll();
    // генерация нового поколения на основе старого
    void changeGeneration();

private:
    // метод для подсчета числа живых соседей заданной клетки
    int calcEnvironment(const Pair&) const;

    Pair _fieldSize; // высота/ширина поля
    QVector<QVector<bool>> _generation; // текущее поколение

    /* траектория движения при обходе клетки:
     * 2 1 8
     * 3 x 7
     * 4 5 6
    */
    const QVector<int> _kPathX = {-1, -1,  0,  1, 1, 1, 0, -1};
    const QVector<int> _kPathY = { 0, -1, -1, -1, 0, 1, 1,  1};
};

#endif // LIFE_H
