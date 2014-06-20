#ifndef __HexBizarre__Hexagon_h__
#define __HexBizarre__Hexagon_h__

#include "cocos2d.h"

class Hexagon : public cocos2d::Sprite
{
public:
    Hexagon();
    ~Hexagon();
    virtual bool init();
    CREATE_FUNC(Hexagon);
    bool initLabel();
    int row, col;
    // this is not iniialized automatically in order to save memory.
    // do not use this directly. use:
    //   if (hexagon->label) { ... }
    // or:
    //   if (!hexagon->label) hexagon->initLabel();
    cocos2d::Label *label;
};

#endif
