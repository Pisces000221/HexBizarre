#ifndef __HexBizarre__HexagonRegion_h__
#define __HexBizarre__HexagonRegion_h__

#include "cocos2d.h"
#include "Hexagon.h"

class HexagonRegion
{
public:
    HexagonRegion();
    ~HexagonRegion();
    void insert(Hexagon *obj);
    void erase(Hexagon *obj);
    Hexagon *find(int row, int col);

    // we need: left, up-left, up-right, right
    const int HEXAGON_RIGHT = 0;
    const int HEXAGON_LEFT = 1 << 1;
    const int HEXAGON_UP = 1 << 2;
    void move(int direction);

    inline cocos2d::Vector<Hexagon *> allHexagons() { return _hexagons; }
protected:
    cocos2d::Vector<Hexagon *> _hexagons;
};

#endif
