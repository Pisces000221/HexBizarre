#ifndef __HexBizarre__HexagonLayer_h__
#define __HexBizarre__HexagonLayer_h__

#include "cocos2d.h"
#include "Global.h"
#include <set>

class HexagonLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();  
    CREATE_FUNC(HexagonLayer);
    SCENE_FUNC(HexagonLayer);
    void goBack(Ref *sender);

    // we need: left, up-left, up-right, right
    const int HEXAGON_RIGHT = 0;
    const int HEXAGON_LEFT = 1 << 1;
    const int HEXAGON_UP = 1 << 2;
    void move(int direction);

protected:
    std::set<cocos2d::Sprite *> _hexagons;
};

#endif
