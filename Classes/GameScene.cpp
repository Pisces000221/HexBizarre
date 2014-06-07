#include "GameScene.h"
#include "StartupScene.h"
using namespace cocos2d;

bool GameLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255))) return false;

    Size size = Director::getInstance()->getVisibleSize();

    auto aHexagon = Sprite::create("images/hexagon.png");
    aHexagon->setPosition(Vec2(300, 300));
    this->addChild(aHexagon);

    aHexagon = Sprite::create("images/hexagon.png");
    aHexagon->setPosition(Vec2(300, 300 + HEX_HEIGHT));
    this->addChild(aHexagon);

    return true;
}
