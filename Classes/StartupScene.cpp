#include "StartupScene.h"
using namespace cocos2d;

bool Startup::init()
{
    if (!Layer::init()) return false;

    Size size = Director::getInstance()->getVisibleSize();
    return true;
}
