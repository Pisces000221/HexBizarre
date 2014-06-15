#ifndef __HexBizarre__HexagonLayer_h__
#define __HexBizarre__HexagonLayer_h__

#include "cocos2d.h"
#include "Global.h"
#include "structures/HexagonRegion.h"
#include <functional>
#include <map>

class HexagonLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(HexagonLayer);
    void setCallbacks(std::function<void(int)> onMove) { _onMove = onMove; }
    static const int REPEAT_CURRENT_POS_TINT_TAG = 147106;

    void move(int direction) { _hr.move(direction); }
    void refill();
    void tintRow(int row, cocos2d::Color3B c);
    void tintHexagon(int row, int col, cocos2d::Color3B c);

    inline HexagonRegion getHexagonRegion() { return _hr; }

protected:
    HexagonRegion _hr;
    std::function<void(int)> _onMove;
    std::map<int, cocos2d::Color3B> _tintRows;

    void tintAllAskedRows();

};

#endif
