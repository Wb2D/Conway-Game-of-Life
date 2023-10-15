#ifndef LIFEWIDGET_H
#define LIFEWIDGET_H

#include <QGraphicsView>
#include <QColor>
#include <QTimer>
#include <QPainter>
#include <QtMath>

#include "Model/Life.h"
#include "Model/Pair.h"

class LifeWidget : public QGraphicsView
{
    Q_OBJECT

public slots:
    void updateLife();

public:
    // конструктор по умолчанию
    LifeWidget(QWidget *parent = nullptr);

    void start() const;
    void stop() const;
    void step();

protected:
    // метод для отрисовки
    void paintEvent(QPaintEvent *event);

private:
    Life _life; // модель жизни Конвея
    QTimer *_timer;

    QColor _color; // цвеееет ??

    const int _kCellSize = 25; // базовый размер клетки, влияет на качество
    const QColor _kAlive = Qt::green; // цвет живых
    const QColor _kDead = Qt::gray; // цвет мертвых
};

#endif // LIFEWIDGET_H
