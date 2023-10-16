#ifndef DATAWORKER_H
#define DATAWORKER_H

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include "Model/Life.h"

class DataWorker
{
public:
    // запись в файл
    static bool saveLife(const Life &life, const QString &path);

    // чтение из файла
    static bool loadLife(Life &life, const QString &path);
};

#endif // DATAWORKER_H
