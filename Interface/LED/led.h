#ifndef LED_H
#define LED_H

#include <QObject>
#include <QLabel>

/*
 * Данный класс реализует LED-индикаторы, которые используются для
 * информирования пользователя о состоянии симуляции в реальном времени
*/

class LED : public QLabel
{
    Q_OBJECT

public:
    // конструктор
    LED(QWidget *parent = nullptr);

    // состояния LED-индикатора
    enum State {
        On,
        Off,
        Unused,
    };

public slots:
    // позволяет устанавливать состояние индикатора
    void set(State);

private:
    const int SIZE = 20;
    const QString green = QString("color: white;border-radius: %1;background-color: "
                                  "qlineargradient(spread:pad, x1:0.145, y1:0.16,"
                                  " x2:1, y2:1, stop:0 rgba(20, 252, 7, 255),"
                                  " stop:1 rgba(25, 134, 5, 255));").arg(SIZE/2);
    const QString red = QString("color: white;border-radius: %1;background-color: "
                                "qlineargradient(spread:pad, x1:0.145, y1:0.16, "
                                "x2:0.92, y2:0.988636, stop:0 rgba(255, 12, 12, 255), "
                                "stop:0.869347 rgba(103, 0, 0, 255));").arg(SIZE/2);
    const QString blue = QString("color: white;border-radius: %1;background-color: "
                                 "qlineargradient(spread:pad, x1:0.04, y1:0.0565909, "
                                 "x2:0.799, y2:0.795, stop:0 rgba(203, 220, 255, 255), "
                                 "stop:0.41206 rgba(0, 115, 255, 255), "
                                 "stop:1 rgba(0, 49, 109, 255));").arg(SIZE/2);

};

#endif // LED_H
