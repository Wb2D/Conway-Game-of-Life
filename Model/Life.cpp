#include "Life.h"

Life::Life(const Pair &obj) :
    _fieldSize(obj.getX(), obj.getY()),
    _gens(0),
    _status(false) {
    _generation.resize(_fieldSize.getX());
    for(int i = 0; i < _fieldSize.getX(); ++i) {
        _generation[i].resize(_fieldSize.getY());
    }
}

void Life::invert(const Pair &cell) {
    if(cell.getX() >= 0 && cell.getX() < _fieldSize.getX() &&
            cell.getY() >= 0 && cell.getY() < _fieldSize.getY()) {
        _generation[cell.getX()][cell.getY()] ^= true;
        if(_generation[cell.getX()][cell.getY()]) {
            _status = true;
        }
    }
}

void Life::clear() {
    for (int i = 0; i < _fieldSize.getX(); ++i) {
        for(int j = 0; j < _fieldSize.getY(); ++j) {
            _generation[i][j] = false;
        }
    }
    _status = false;
    _gens = 0;
}

int Life::calcEnvironment(const Pair &cell) const {
    int result = 0;
    for(int i = 0; i < 8; ++i) {
        int x = cell.getX() + _kPathX[i];
        int y = cell.getY() + _kPathY[i];
        if(x >= 0 && x < _fieldSize.getX() &&
                y >= 0 && y < _fieldSize.getY()) {
            result += _generation[x][y];
        }
    }
    return result;
}

void Life::next() {
    if(_status) {
        bool marker1 = false;
        bool marker2 = false;
        QVector<QVector<bool>> result = _generation;
        for(int i = 0; i < _fieldSize.getX(); ++i) {
            for(int j = 0; j < _fieldSize.getY(); ++j) {
                int stat = calcEnvironment(Pair(i, j));
                if(_generation[i][j] && (stat < 2 || stat > 3 )) {
                    result[i][j] = false;
                }
                if(!_generation[i][j] && stat == 3) {
                    result[i][j] = true;
                }
                // если хоть одно значение true, то считаю поколение живым
                if(result[i][j]) {
                    marker1 = true;
                }
                // поколения должны отличаться
                if(_generation[i][j] != result[i][j]) {
                    marker2 = true;
                }
            }
        }
        _status = marker1 && marker2;
        ++_gens;
        _generation = result;
    }
}

void Life::resize(const Pair &newSize) {
    clear();
    _fieldSize = newSize;
    _generation.resize(newSize.getX());
    for(int i = 0; i < newSize.getX(); ++i) {
        _generation[i].resize(newSize.getY());
    }
}

QJsonObject Life::toJSON() const {
    QJsonObject life;
    life["fieldSize"] = QJsonObject {
        {"x", _fieldSize.getX()},
        {"y", _fieldSize.getY()}
    };
    life["gens"] = static_cast<int>(_gens);
    life["status"] = _status;
    QJsonArray generation;
    for(int i = 0; i < _fieldSize.getX(); ++i) {
        QJsonArray tmp;
        for(int j = 0; j < _fieldSize.getY(); ++j) {
            tmp.append(_generation[i][j]);
        }
        generation.append(tmp);
    }
    life["generation"] = generation;
    return life;
}

void Life::fromJSON(const QJsonObject &obj) {
    resize(Pair(obj["fieldSize"].toObject()["x"].toInt(),
            obj["fieldSize"].toObject()["y"].toInt()));
    _gens = obj["gens"].toInt();
    _status = obj["status"].toBool();
    QJsonArray generation = obj["generation"].toArray();
    for(int i = 0; i < _fieldSize.getX(); ++i) {
        QJsonArray tmp = generation[i].toArray();
        for(int j = 0; j < _fieldSize.getY(); ++j) {
            _generation[i][j] = tmp[j].toBool();
        }
    }
}
