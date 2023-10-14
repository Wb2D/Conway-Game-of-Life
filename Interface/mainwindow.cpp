#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //lifeWidget = new LifeWidget(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
