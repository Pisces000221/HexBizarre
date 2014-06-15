#include "Foggy.h"
using namespace cocos2d;

namespace hb_gameplay {

bool Foggy::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255))) return false;

    Size size = Director::getInstance()->getVisibleSize();
    _hexLayer->setCallbacks([](int direction) {});

    return true;
}

}
