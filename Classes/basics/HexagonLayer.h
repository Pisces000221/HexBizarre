#ifndef __HexBizarre__HexagonLayer_h__
#define __HexBizarre__HexagonLayer_h__

#include "cocos2d.h"
#include "Global.h"
#include "structures/HexagonRegion.h"
#include <functional>

class HexagonLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(HexagonLayer);
    void setCallbacks(std::function<void(int)> onMove) { _onMove = onMove; }

    void move(int direction) { _hr.move(direction); }
    void refill();

    inline HexagonRegion getHexagonRegion() { return _hr; }

protected:
    HexagonRegion _hr;
    std::function<void(int)> _onMove;

};

#endif
