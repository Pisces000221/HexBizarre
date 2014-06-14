#ifndef __HexBizarre__HexagonLayer_h__
#define __HexBizarre__HexagonLayer_h__

#include "cocos2d.h"
#include "Global.h"
#include "structures/HexagonRegion.h"

class HexagonLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(HexagonLayer);
    SCENE_FUNC(HexagonLayer);
    void goBack(Ref *sender);

    inline HexagonRegion getHexagonRegion() { return _hr; }

protected:
    HexagonRegion _hr;
};

#endif
