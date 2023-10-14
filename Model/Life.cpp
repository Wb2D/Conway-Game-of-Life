#include "Life.h"

Life::Life(const QSize &size) :
    _fieldSize(size) {
    _generation.resize(size.height());
    for(int i = 0; i < size.height(); ++i) {
        _generation[i].resize(size.width());
    }
}

void Life::setLife(const QSize &cell) {
    if(cell.width() >= 0 && cell.width() < _fieldSize.width() &&
            cell.height() >= 0 && cell.height() < _fieldSize.height()) {
        _generation[cell.width()][cell.height()] = true;
    }
}

void Life::killAll() {
    for (int i = 0; i < _fieldSize.width(); ++i) {
        for(int j = 0; j < _fieldSize.height(); ++j) {
            _generation[i][j] = false;
        }
    }
}

int Life::calcEnvironment(const QSize &cell) const {
    /* траектория движения при обходе клетки:
     * 2 1 8
     * 3 x 7
     * 4 5 6
    */
    const QVector<int> kPathX = {-1, -1,  0,  1, 1, 1, 0, -1};
    const QVector<int> kPathY = { 0, -1, -1, -1, 0, 1, 1,  1};

    int result = 0;
    for(int i = 0; i < 8; ++i) {
        int x = cell.width() +kPathX[i];
        int y = cell.height() + kPathY[i];
        if(x >= 0 && x < _fieldSize.width() &&
                y >= 0 && y < _fieldSize.height()) {
            result += _generation[x][y];
        }
    }
    return result;
}

void Life::changeGeneration() {
    QVector<QVector<bool>> result = _generation;
    result.clear();
    for(int i = 0; i < _fieldSize.width(); ++i) {
        for(int j = 0; j < _fieldSize.height(); ++j) {
            int stat = calcEnvironment(QSize(j, i));
            if(_generation[i][j] && (stat < 2 || stat > 3 )) {
                result[i][j] = false;
            }
            if(!_generation[i][j] && stat == 3) {
                result[i][j] = true;
            }
        }
    }

}

void Life::resize(const QSize &newSize) {
    killAll();
    _generation.resize(newSize.height());
    for(int i = 0; i < newSize.height(); ++i) {
        _generation[i].resize(newSize.width());
    }
}
