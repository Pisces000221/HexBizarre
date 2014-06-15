#include "Foggy.h"
using namespace cocos2d;

namespace hb_gameplay {

bool Foggy::init()
{
    if (!GameLayer::init()) return false;

    Size size = Director::getInstance()->getVisibleSize();
    _hexLayer->setCallbacks([](int direction) {});

    return true;
}

}
