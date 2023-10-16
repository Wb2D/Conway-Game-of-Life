#include "dataworker.h"

bool DataWorker::saveLife(const Life &life, const QString &path) {
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)) {
        QJsonDocument data(life.toJSON());
        file.write(data.toJson());
        file.close();
        return true;
    }
    return false;
}


bool DataWorker::loadLife(Life &life, const QString &path) {
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)) {
        QJsonDocument data = QJsonDocument::fromJson(file.readAll());
        life.fromJSON(data.object());
        file.close();
        return true;
    }
    return false;
}
