#include "lifewidget.h"

#include <QDebug>

LifeWidget::LifeWidget(QWidget *parent) :
    QGraphicsView(parent), _life(QSize(50, 50)) {
    _color = Qt::black;
    // отключение полос прокрутки
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // установка сцены и ограничение видимой области
    setSceneRect(0, 0, _life.getFieldSize().width(), _life.getFieldSize().height());
}

void LifeWidget::paintEvent(QPaintEvent* ) {
    QPainter painter(viewport());  // QPainter для отображения виджета
    // масштабирования для отображения ячеек
    qreal scaleX = width() / (sceneRect().width() * _kCellSize);
    qreal scaleY = height() / (sceneRect().height() * _kCellSize);
    // установка масштабирования для QPainter
    painter.setMatrix(QMatrix().scale(scaleX, scaleY));
    // сглаживание
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
    // задаю цвета для живых и мертвых клеток
    QPen cellPen(_color);
    painter.setPen(cellPen);
    // отрисовка ячеек
    for(int i = 0; i < _life.getFieldSize().height(); ++i) {
        for(int j = 0; j < _life.getFieldSize().width(); ++j) {
            int x = i * _kCellSize;
            int y = j * _kCellSize;
            QRect square(x, y, _kCellSize, _kCellSize);

            // условие для отрисовки, пока костыль
            QColor state = (i == j) ? _kAlive : _kDead;
            painter.fillRect(square, QBrush(state));
            //

            painter.setPen(cellPen);
            painter.drawRect(square);
        }
    }

    painter.end();  // Завершаю рисование
}

