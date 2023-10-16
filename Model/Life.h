#ifndef LIFE_H
#define LIFE_H

#include <QObject>
#include <QLabel>
#include <QSize>
#include <QVector>

#include "Model/Pair.h"

/*
 * [Программная реализация игры "Жизнь" Джона Конвея]
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
*/

class Life
{
public:
    // конструктор с параметрами : размер поля
    Life(const Pair&);


    // геттеры
    Pair size() const { return _fieldSize; }
    unsigned int getGens() const { return _gens; }
    bool getStatus() const { return _status; }

    // возвращает элемент _generation
    bool get(const Pair& obj) const { return _generation[obj.getX()][obj.getY()]; }
    // мето для изменения размера текущего вектора с очисткой
    void resize(const Pair&);
    // метод, дающий жизнь
    void invert(const Pair&);
    // апокалипсис
    void clear();
    // генерация нового поколения на основе старого
    void next();

private:
    // метод для подсчета числа живых соседей заданной клетки
    int calcEnvironment(const Pair&) const;

    Pair _fieldSize; // размеры поля
    QVector<QVector<bool>> _generation; // текущее поколение
    unsigned int _gens; // число поколений, сменивших друг друга
    bool _status; // все уже вымерли или еще нет?

    /* траектория движения при обходе клетки:
     * 2 1 8
     * 3 x 7
     * 4 5 6
    */
    const QVector<int> _kPathX = {-1, -1,  0,  1, 1, 1, 0, -1};
    const QVector<int> _kPathY = { 0, -1, -1, -1, 0, 1, 1,  1};
};

#endif // LIFE_H
