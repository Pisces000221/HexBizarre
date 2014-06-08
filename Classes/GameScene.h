#ifndef __HexBizarre__GameScene_h__
#define __HexBizarre__GameScene_h__

#include "cocos2d.h"
#include "Global.h"

class GameLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();  
    CREATE_FUNC(GameLayer);
    SCENE_FUNC(GameLayer);

    // we need: left, up-left, up-right, right
    const int HEXAGON_RIGHT = 0;
    const int HEXAGON_LEFT = 1 << 1;
    const int HEXAGON_UP = 1 << 2;
    void move(int direction);
};

#endif
