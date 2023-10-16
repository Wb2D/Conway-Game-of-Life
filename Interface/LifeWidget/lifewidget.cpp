#include "lifewidget.h"

#include <QDebug>

LifeWidget::LifeWidget(QWidget *parent) :
    QGraphicsView(parent),
    _life(Pair(100, 100)),
    _timer(new QTimer(this)),
    _colorData(new ColorData(Qt::green, Qt::gray, Qt::black, true)) {

    // отключение полос прокрутки
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // установка сцены и ограничение видимой области
    setSceneRect(0, 0, _life.size().getX(), _life.size().getY());

    // таймер
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateLife()));
    _timer->setInterval(1000); // интервал в мс, ставлю дефолтный в 1с

    // ЗДЕСЬ КОГДА-ТО БЫЛ ВЕЛИКИЙ КОСТЫЛЬ, НО ТЕПЕРЬ ЕГО НЕТ Т_Т
    // НИЧТО НЕ ВЕЧНО. ЖИЗНЬ - ТЛЕН.
}

void LifeWidget::setSettings(QPainter &painter) const {
    // коэффициенты масштабирования
    qreal scaleX = width() / (sceneRect().width() * _kCellSize);
    qreal scaleY = height() / (sceneRect().height() * _kCellSize);

    // установка масштабирования для QPainter
    painter.setWorldTransform(QTransform().scale(scaleX, scaleY), false);

    // сглаживание
    painter.setRenderHint(QPainter::Antialiasing, _colorData->getFlagB());
    painter.setRenderHint(QPainter::HighQualityAntialiasing, _colorData->getFlagB());
}

QPen LifeWidget::createPen() const {
    QPen pen(_colorData->getColorB());
    if(!_colorData->getFlagB()) {
        pen.setStyle(Qt::NoPen);
    }
    return pen;
}

void LifeWidget::drawCells(QPainter &painter) const {
    for(int i = 0; i < _life.size().getX(); ++i) {
        for(int j = 0; j < _life.size().getY(); ++j) {
            int x = i * _kCellSize;
            int y = j * _kCellSize;
            QRect square(x, y, _kCellSize, _kCellSize);

            // определение цвета, зависящего от состояния
            QColor state = (_life.get(Pair(i, j))) ?
                        _colorData->getColorA() : _colorData->getColorD();

            painter.fillRect(square, QBrush(state));
            painter.drawRect(square);
        }
    }
}

void LifeWidget::paintEvent(QPaintEvent*) {
    QPainter painter(viewport());  // QPainter для отображения виджета
    setSettings(painter);     // применение настроек масштабирования и сглаживания
    painter.setPen(createPen());
    drawCells(painter); // отрисовка ячеек
    painter.end();  // завершаю рисование
}

void LifeWidget::updateLife() {
    _life.next();
    viewport()->update();
    emit generationUpdate(_life.getGens());
    if(!_life.getStatus()) {
        emit generationStopped();
    }
}

void LifeWidget::start() const {
    _timer->start();
}

void LifeWidget::stop() const {
    _timer->stop();
}

void LifeWidget::step() {
    _life.next();
    viewport()->update();
    emit generationUpdate(_life.getGens());
}

/*
 * f(x) = pos(x) / scale(x) / size, где
 * scale(x) = window(x) / (rect(x) *  size) =>
 * если подставить scale(x) в формулу, то видно,
 * как переменную size можно сократить
*/
void LifeWidget::mousePressEvent(QMouseEvent *event) {
    Pair obj = Pair((event->pos().x() * sceneRect().width()) / width(),
                    (event->pos().y() * sceneRect().height()) / height());

     _life.invert(obj);
     viewport()->update();
}

void LifeWidget::speed(const int &interval) const {
    _timer->setInterval(interval);
}

void LifeWidget::resize(const Pair &newSize) {
    _life.resize(newSize);
    setSceneRect(0, 0, newSize.getX(), newSize.getY()); // размер сцены
    viewport()->update();
}

void LifeWidget::clear() {
    _life.clear();
    viewport()->update();
}

void LifeWidget::setColors(const ColorData &colorData) {
    if(_colorData->getColorA() != colorData.getColorA()) {
        _colorData->setColorA(colorData.getColorA());
    }
    if(_colorData->getColorD() != colorData.getColorD()) {
        _colorData->setColorD(colorData.getColorD());
    }
    if(_colorData->getColorB() != colorData.getColorB()) {
        _colorData->setColorB(colorData.getColorB());
    }
    if(_colorData->getFlagB() != colorData.getFlagB()) {
        _colorData->setFlagB(colorData.getFlagB());
    }

    viewport()->update();
}
