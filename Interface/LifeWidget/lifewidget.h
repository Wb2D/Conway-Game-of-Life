#ifndef LIFEWIDGET_H
#define LIFEWIDGET_H

#include <QGraphicsView>
#include <QColor>
#include <QTimer>
#include <QPainter>
#include <QtMath>
#include <QMouseEvent>

#include "Model/Life.h"
#include "Model/Pair.h"
#include "Interface/SettingWindow/ColorData/colordata.h"

/*
 * Данный класс отвечает за визуализацию реализованной модели. Набор программных
 * метод, реализованный в нем, обеспеичивает ее отрисовку, а также возможность
 * изменения пользовательских параметров
*/

class LifeWidget : public QGraphicsView
{
    Q_OBJECT

public:
    // конструктор по умолчанию
    LifeWidget(QWidget *parent = nullptr);

    // влючение таймера
    void start() const;
    // остановка таймера
    void stop() const;
    // сделать один шаг независимо от таймера
    void step();
    // скорость, с которой меняются поколения
    void speed(const int&) const;
    // изменить размер поля
    void resize();
    void resize(const Pair&);
    // очистка клеточек
    void clear();
    // изменить цветовую палитру
    void setColors(const ColorData &);
    // вернуть цветовую палитру
    ColorData* getColor() const { return _colorData; }
    // возвращает номер текущего поколения
    unsigned int getGens() const { return _life.getGens(); }
    // возвращает состояние системы
    bool getStatus() const { return _life.getStatus(); }
    // возвращает Life
    Life& getLife() { return _life; }

public slots:
    void updateLife();

signals:
    void generationUpdate(const int&);
    void generationStopped();

protected:
    // метод для отрисовки
    void paintEvent(QPaintEvent *event);
    // метод для закрашивания клетки по клику мыши
    void mousePressEvent(QMouseEvent *event);

private:
    // методы нужные при отрисовке
    QPen createPen() const;
    void setSettings(QPainter&) const;
    void drawCells(QPainter&) const;


    Life _life;
    QTimer *_timer;
    ColorData *_colorData;
    const int _kCellSize = 25; // базовый размер клетки, влияет на качество
};

#endif // LIFEWIDGET_H
