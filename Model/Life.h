#ifndef LIFE_H
#define LIFE_H

#include <QObject>
#include <QLabel>
#include <QSize>
#include <QVector>

class Life : public QObject
{
    Q_OBJECT

public:
    // конструктор с параметрами : высота, ширина
    Life(const QSize&);

    // геттер поля _fieldSize
    QSize getFieldSize() const { return _fieldSize; }
    // возвращает элемент _generation
    bool getElem(const int &i, const int &j) const { return _generation[i][j]; }

    // мето для изменения размера текущего вектора с очисткой
    void resize(const QSize&);
    // метод, дающий жизнь
    void setLife(const QSize&);
    // апокалипсис
    void killAll();
    // генерация нового поколения на основе старого
    void changeGeneration();

private:
    // метод для подсчета числа живых соседей заданной клетки
    int calcEnvironment(const QSize&) const;

    QSize _fieldSize; // высота/ширина поля
    QVector<QVector<bool>> _generation; // текущее поколение
};

#endif // LIFE_H
