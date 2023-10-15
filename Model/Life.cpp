#include "Life.h"

Life::Life(const Pair &obj) :
    _fieldSize(obj.getX(), obj.getY()) {
    _generation.resize(_fieldSize.getX());
    for(int i = 0; i < _fieldSize.getX(); ++i) {
        _generation[i].resize(_fieldSize.getY());
    }
}

void Life::setLife(const Pair &cell) {
    if(cell.getX() >= 0 && cell.getX() < _fieldSize.getX() &&
            cell.getY() >= 0 && cell.getY() < _fieldSize.getY()) {
        _generation[cell.getX()][cell.getY()] = true;
    }
}

void Life::killAll() {
    for (int i = 0; i < _fieldSize.getX(); ++i) {
        for(int j = 0; j < _fieldSize.getY(); ++j) {
            _generation[i][j] = false;
        }
    }
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

void Life::changeGeneration() {
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
        }
    }
    _generation = result;

}

void Life::resize(const Pair &newSize) {
    killAll();
    _fieldSize = newSize;
    _generation.resize(newSize.getX());
    for(int i = 0; i < newSize.getX(); ++i) {
        _generation[i].resize(newSize.getY());
    }
}
