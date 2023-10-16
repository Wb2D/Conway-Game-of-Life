#include "settingdialog.h"
#include "ui_settingdialog.h"


SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::SettingDialog) {
    ui->setupUi(this);

    _colorData = new ColorData();
    connect(this, SIGNAL(sendNewColor(ColorData*)), parent, SLOT(recieveNewColor(ColorData*)));
}


SettingDialog::~SettingDialog() {
    delete ui;
}


void SettingDialog::setA(const QColor &color) const {
    ui->infoA->setText(color.name());
    ui->colorA->setStyleSheet(ColorData::getColor(color));
    _colorData->setColorA(color);
}


void SettingDialog::setD(const QColor &color) const {
    ui->infoD->setText(color.name());
    ui->colorD->setStyleSheet(ColorData::getColor(color));
    _colorData->setColorD(color);
}


void SettingDialog::setB(const QColor &color) const {
    ui->infoB->setText(color.name());
    ui->colorB->setStyleSheet(ColorData::getColor(color));
    _colorData->setColorB(color);
}


void SettingDialog::setFlag(const bool &flag) const {
    ui->infoB->setDisabled(!flag);
    ui->colorB->setDisabled(!flag);
    ui->changeB->setDisabled(!flag);
    _colorData->setFlagB(flag);
}


void SettingDialog::recieveColor(ColorData *colorData) {
    setA(colorData->getColorA());
    setD(colorData->getColorD());
    setB(colorData->getColorB());
    setFlag(colorData->getFlagB());
}


QColor SettingDialog::getNewColor() const {
    QColor color = QColorDialog::getColor();
    if(color.isValid()) {
        return color;
    }
    else {
        QMessageBox::critical(nullptr, "Error", "Invalid color");
        getNewColor();
    }
}


void SettingDialog::on_changeA_clicked() {
    QColor color = getNewColor();
    setA(color);
}

void SettingDialog::on_changeD_clicked() {
    QColor color = getNewColor();
    setD(color);
}


void SettingDialog::on_changeB_clicked() {
    QColor color = getNewColor();
    setB(color);
}


void SettingDialog::on_applyButton_clicked() {
    emit this->sendNewColor(_colorData);
    accept();
}


void SettingDialog::on_saveButton_clicked() {
    emit this->sendNewColor(_colorData);
}


void SettingDialog::on_cancelButton_clicked() {
    reject();
}


void SettingDialog::on_gridBox_stateChanged(int arg1) {
    setFlag(arg1);
}
