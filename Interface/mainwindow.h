#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>

#include "Model/Pair.h"
#include "Interface/LifeWidget/lifewidget.h"
#include "Interface/LED/led.h"
#include "Interface/SettingWindow/ColorData/colordata.h"
#include "Interface/SettingWindow/settingdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void recieveNewColor(ColorData*);
    void updateGeneration(const int&);
    void generationEnd();

signals:
    void sendColor(ColorData*);

private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();

    void on_verticalSlider_1_valueChanged(int action);
    void on_verticalSlider_2_valueChanged(int value);
    void on_verticalSlider_3_valueChanged(int value);

    void on_pushButton_8_clicked();

private:
    void setLED(const bool&) const;
    void changeState(const bool&) const;

    Ui::MainWindow *ui;
    SettingDialog *settingDialog;
};

#endif // MAINWINDOW_H
