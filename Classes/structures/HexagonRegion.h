#ifndef __HexBizarre__HexagonRegion_h__
#define __HexBizarre__HexagonRegion_h__

#include "cocos2d.h"
#include "Hexagon.h"

class HexagonDirection {
public:
    // we need: left, up-left, up-right, right
    static const int RIGHT = 0;
    static const int LEFT = 1 << 1;
    static const int UP = 1 << 2;
};

class HexagonRegion
{
public:
    HexagonRegion();
    ~HexagonRegion();
    void insert(Hexagon *obj);
    void erase(Hexagon *obj);
    Hexagon *find(int row, int col);

    void move(int direction);

    inline cocos2d::Vector<Hexagon *> allHexagons() { return _hexagons; }
    inline cocos2d::ActionInterval *getMoveAction() { return _moveAction->clone(); }
    inline cocos2d::Vec2 getMoveDistance() { return _moveDist; }
protected:
    cocos2d::Vector<Hexagon *> _hexagons;
    cocos2d::ActionInterval *_moveAction;
    cocos2d::Vec2 _moveDist;
};

#endif
