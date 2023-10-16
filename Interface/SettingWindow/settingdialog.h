#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QColor>
#include <QColorDialog>
#include <QMessageBox>
#include <QDialogButtonBox>

#include "Interface/SettingWindow/ColorData/colordata.h"

/*
 * Данный класс реализует диаологовое окно для настройки цвета
 * отображемого поля. С возможность изменить цвет живых клеток, мертвых
 * или сетки (также последнюю можно выключить)
*/

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    // конструктор
    SettingDialog(QWidget *parent = nullptr);
    // деструктор
    ~SettingDialog();

public slots:
    // приемник
    void recieveColor(ColorData*);

signals:
    // отправитель
    void sendNewColor(ColorData*);

private slots:
    //слоты кнопок
    void on_changeA_clicked();
    void on_changeD_clicked();
    void on_changeB_clicked();
    void on_applyButton_clicked();
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

    // вкл/выкл сетки
    void on_gridBox_stateChanged(int arg1);

private:
    // вызывает диалоговое окно выбора нового цвета
    QColor getNewColor() const;

    // задают параметры СolorData
    void setA(const QColor&) const;
    void setD(const QColor&) const;
    void setB(const QColor&) const;
    void setFlag(const bool&) const;

    Ui::SettingDialog *ui;
    ColorData *_colorData;
};

#endif // SETTINGDIALOG_H
