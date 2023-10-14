#include <QApplication>
#include <QStyleFactory>

#include "Interface/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
