#ifndef __HexBizarre__Gameplay_Foggy_h__
#define __HexBizarre__Gameplay_Foggy_h__

#include "cocos2d.h"
#include "basics/GameScene.h"

namespace hb_gameplay {

class Foggy : public GameLayer
{
public:
    virtual bool init();  
    CREATE_FUNC(Foggy);
    SCENE_FUNC(Foggy);
};

}

#endif
