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
};

#endif
