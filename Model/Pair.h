#ifndef PAIR_H
#define PAIR_H

class Pair {
public:
    Pair(const int &x, const int &y) :
        _x(x), _y(y) {}

    int getX() const { return _x; }
    void setX (const int &x) { _x = x; }
    int getY() const { return _y; }
    void setY(const int &y) { _y = y; }

private:
    unsigned int _x;
    unsigned int _y;
};

#endif // PAIR_H
