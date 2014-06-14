#include "HexagonRegion.h"
#include "../Global.h"
using namespace cocos2d;

HexagonRegion::HexagonRegion()
{
    _hexagons.reserve(16);
}

HexagonRegion::~HexagonRegion()
{
    while (!_hexagons.empty()) _hexagons.popBack();
}

void HexagonRegion::insert(Hexagon *obj)
{
    _hexagons.pushBack(obj);
}

void HexagonRegion::erase(Hexagon *obj)
{
    _hexagons.eraseObject(obj);
}

Hexagon *HexagonRegion::find(int row, int col)
{
    for (auto &obj : _hexagons)
        if (obj->row == row && obj->col == col) return obj;
    return nullptr;
}

void HexagonRegion::move(int direction)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 delta = Vec2::ZERO;    // the move distance of every hexagon
    int d[2][2];    // the delta of row and column data. see below
    #define ODD_LINE_DELTA_ROW d[0][1]
    #define EVEN_LINE_DELTA_ROW d[0][0]
    #define ALL_DELTA_ROW d[0][0] = d[0][1] // used in assignments
    #define DELTA_ROW d[0]                  // used as getters
    #define ODD_LINE_DELTA_COL d[1][1]
    #define EVEN_LINE_DELTA_COL d[1][0]
    #define ALL_DELTA_COL d[1][0] = d[1][1]
    #define DELTA_COL d[1]

    // calculate delta row & col
    if (direction & HexagonDirection::LEFT) {
        delta.x += HEX_HEIGHT;
        ALL_DELTA_COL = 1;
    } else {    // moving right
        delta.x -= HEX_HEIGHT;
        ALL_DELTA_COL = -1;
    }
    if (direction & HexagonDirection::UP) {
        delta.y -= HEX_SIDE_LEN * 1.5;
        delta.x *= 0.5;
        ALL_DELTA_ROW = -1;
        if (direction & HexagonDirection::LEFT) EVEN_LINE_DELTA_COL = 0;
        else ODD_LINE_DELTA_COL = 0;
    } else {
        ALL_DELTA_ROW = 0;
    }

    // c'mon, move!
    for (auto cur : _hexagons) {
        Vec2 p = cur->getPosition();
        int odd = abs(cur->row % 2);
        cur->row += DELTA_ROW[odd]; cur->col += DELTA_COL[odd];
        cur->runAction(EaseSineOut::create(MoveBy::create(0.5, delta)));
    }
    // flush invisible hexagons away
    // don't worry, we'll get 'em back soon :)
    // see HexagonLayer::refill()
    for (auto cur : _hexagons) {
        Vec2 p = cur->getPosition();
        if (p.x < -HEX_SIDE_LEN || p.x > size.width + HEX_SIDE_LEN
          || p.y < -HEX_APOTHEM || p.y > size.height + HEX_APOTHEM) {
            cur->removeFromParent();
            this->erase(cur);
            CCLOG("erased: %d, %d (0x%x), current find: 0x%x", cur->row, cur->col, cur, this->find(cur->row, cur->col));
        }
    }
    #undef ODD_LINE_DELTA_ROW
    #undef EVEN_LINE_DELTA_ROW
    #undef ALL_DELTA_ROW
    #undef DELTA_ROW
    #undef ODD_LINE_DELTA_COL
    #undef EVEN_LINE_DELTA_COL
    #undef ALL_DELTA_COL
    #undef DELTA_COL
}
