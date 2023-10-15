#include "lifewidget.h"

#include <QDebug>

LifeWidget::LifeWidget(QWidget *parent) :
    QGraphicsView(parent), _life(Pair(10, 10)), _timer(new QTimer(this)) {
    _color = Qt::black;
    // отключение полос прокрутки
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // установка сцены и ограничение видимой области
    setSceneRect(0, 0, _life.getFieldSize().getX(), _life.getFieldSize().getY());
    // таймер
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateLife()));
    _timer->setInterval(1000); // интервал в миллисекундах, 1000мс = 1с
    // это костыль для заполнения начальной матрицы, мб позже сделаю по клику
    _life.setLife(Pair(1, 2));
    _life.setLife(Pair(1, 3));
    _life.setLife(Pair(1, 4));
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
    for(int i = 0; i < _life.getFieldSize().getX(); ++i) {
        for(int j = 0; j < _life.getFieldSize().getY(); ++j) {
            int x = i * _kCellSize;
            int y = j * _kCellSize;
            QRect square(x, y, _kCellSize, _kCellSize);

            QColor state = (_life.getElement(Pair(i, j))) ? _kAlive : _kDead;
            painter.fillRect(square, QBrush(state));

            painter.setPen(cellPen);
            painter.drawRect(square);
        }
    }

    painter.end();  // Завершаю рисование
}

void LifeWidget::updateLife() {
    _life.changeGeneration();
    viewport()->update();
}

void LifeWidget::start() const {
    _timer->start();
}

void LifeWidget::stop() const {
    _timer->stop();
}

void LifeWidget::step() {
    _life.changeGeneration();
    viewport()->update();
}
