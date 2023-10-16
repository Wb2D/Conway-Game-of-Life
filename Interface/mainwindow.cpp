#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->pushButton_1->setToolTip("Start");
    ui->pushButton_2->setToolTip("Pause");
    ui->pushButton_3->setToolTip("Step");
    ui->pushButton_4->setToolTip("Clear");
    ui->pushButton_5->setToolTip("Load");
    ui->pushButton_6->setToolTip("Save");
    ui->pushButton_7->setToolTip("Settings");
    ui->pushButton_8->setToolTip("Quit");
    ui->verticalSlider_1->setToolTip("Speed simulation");
    ui->verticalSlider_2->setToolTip("Number of cells horizontally");
    ui->verticalSlider_3->setToolTip("Number of cells vertically");

    settingDialog = new SettingDialog(this);
    connect(ui->pushButton_7, SIGNAL(clicked()), settingDialog, SLOT(show()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(on_pushButton_7_clicked()));
    connect(this, SIGNAL(sendColor(ColorData*)), settingDialog, SLOT(recieveColor(ColorData*)));
    connect(ui->graphicsView, SIGNAL(generationUpdate(int)), this, SLOT(updateGeneration(int)));
    connect(ui->graphicsView, SIGNAL(generationStopped()), this, SLOT(generationEnd()));

    ui->label_2->set(LED::Unused);
    ui->label_3->set(LED::Unused);
}


MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::changeState(const bool &flag) const {
    ui->verticalSlider_2->setDisabled(flag);
    ui->verticalSlider_3->setDisabled(flag);
    ui->pushButton_4->setDisabled(flag);
}


void MainWindow::setLED(const bool &flag) const {
    if(flag) {
        ui->label_2->set(LED::On);
        ui->label_3->set(LED::Off);
    }
    else {
        ui->label_2->set(LED::Off);
        ui->label_3->set(LED::On);
    }
    changeState(flag);
}


void MainWindow::on_pushButton_1_clicked() {
    ui->graphicsView->start();
    setLED(true);
}


void MainWindow::on_pushButton_2_clicked() {
    ui->graphicsView->stop();
    setLED(false);
}


void MainWindow::on_pushButton_3_clicked() {
    ui->graphicsView->step();
    setLED(false);
}


void MainWindow::on_pushButton_4_clicked() {
    ui->graphicsView->clear();
}


void MainWindow::on_pushButton_5_clicked() {
    QString path = getPath();
    if(path == "-1") {
        return;
    }
    else {
        ui->label_4->setText("0");
        DataWorker::loadLife(ui->graphicsView->getLife(), path);
        ui->graphicsView->resize();
        ui->graphicsView->viewport()->update();
    }
}


void MainWindow::on_pushButton_6_clicked() {
    QString path = getPath();
    if(path == "-1") {
        return;
    }
    else {
        DataWorker::saveLife(ui->graphicsView->getLife(), path);
    }
}


void MainWindow::on_pushButton_7_clicked() {
    emit this->sendColor(ui->graphicsView->getColor());
}


void MainWindow::on_verticalSlider_1_valueChanged(int action) {
    ui->graphicsView->speed(action);
}


void MainWindow::on_verticalSlider_2_valueChanged(int value) {
    Pair newSize = Pair(value, ui->verticalSlider_3->value());
    ui->graphicsView->resize(newSize);
    ui->label->setText(newSize.toString());
}


void MainWindow::on_verticalSlider_3_valueChanged(int value) {
    Pair newSize = Pair(ui->verticalSlider_2->value(), value);
    ui->graphicsView->resize(newSize);
    ui->label->setText(newSize.toString());
}

void MainWindow::recieveNewColor(ColorData *newColorData) {
    ui->graphicsView->setColors(*newColorData);
}


void MainWindow::on_pushButton_8_clicked() {
    close();
}


void MainWindow::updateGeneration(const int &gens) {
    ui->label_4->setText(QString::number(gens));
}


void MainWindow::generationEnd() {
    QMessageBox::information(this, "Information", "The simulation is over");
    setLED(false);
    ui->graphicsView->stop();
    //ui->label_4->setText("0");
}


QString MainWindow::getPath() {
    QString path = QFileDialog::getOpenFileName(this, "Choose file", "", "Files JSON (*.json)");
    if(!path.isEmpty()) {
        return path;
    }
    else {
        return "-1";
    }
}
