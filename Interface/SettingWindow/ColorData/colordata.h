#ifndef COLORDATA_H
#define COLORDATA_H

#include <QColor>

/*
 * Данный класс хранит цветовые параметры отображаемого поля:
 * цвет живых клеток, цвет мертвых клеток, цвет сетки и ее
 * состояние - а также обеспечивает необходимый для работы
 * набор методов
*/

class ColorData
{
public:
    // конструктор без параметров
    ColorData() :
        _colorA(Qt::white), _colorD(Qt::white), _colorB(Qt::white), _flagB(true) {}
    // конструктор с параметрами
    ColorData(const QColor &colorA, const QColor &colorD,
              const QColor &colorB, const bool &flagB) :
        _colorA(colorA), _colorD(colorD), _colorB(colorB), _flagB(flagB) {}
    // конструктор копирования
    ColorData(const ColorData &colorData) {
        this->_colorA = colorData.getColorA();
        this->_colorD = colorData.getColorD();
        this->_colorB = colorData.getColorB();
        this->_flagB = colorData.getFlagB();
    }
    // деструктор
    ~ColorData() {}

    // геттеры
    QColor getColorA() const { return _colorA; }
    QColor getColorD() const { return _colorD; }
    QColor getColorB() const { return _colorB; }
    bool getFlagB() const { return _flagB; }

    // сеттеры
    void setColorA(const QColor &colorA) { _colorA = colorA; }
    void setColorD(const QColor &colorD) { _colorD = colorD; }
    void setColorB(const QColor &colorB) { _colorB = colorB; }
    void setFlagB(const bool &flagB) { _flagB = flagB; }

    // возвращает в формате строки, чтобы сделать жизнь проще
    static QString getColor(const QColor &color) {
        return QString("background-color: " + color.name());
    }

private:
    QColor _colorA; // цвет живых
    QColor _colorD; // цвет мертвых
    QColor _colorB; // цвет сетки
    bool _flagB; // наличие сетки
};

#endif // COLORDATA_H
