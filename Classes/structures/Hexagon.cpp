#include "Hexagon.h"
#include "Global.h"
using namespace cocos2d;

Hexagon::Hexagon() {}
Hexagon::~Hexagon() { CCLOG("~Hexagon"); this->removeAllChildren(); }

bool Hexagon::init()
{
    // create a solid hexagon (I'm too lazy to use a DrawNode)
    if (!Sprite::initWithFile("images/hexagon_fill.png")) return false;
    this->setColor(Color3B(0, 0, 0));   // black by default

    // create the border
    auto border = Sprite::create("images/hexagon_border.png");
    border->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    border->setPosition(Vec2::ZERO);
    this->addChild(border, 1);

    // set label to nullptr. call initLabel() if you want to use it.
    this->label = nullptr;

    return true;
}

bool Hexagon::initLabel()
{
    auto mysize = this->getContentSize();
    // create the label
    this->label = Label::createWithTTF(TTF_CONFIG_R(mysize.height * 0.618), "");
    if (!this->label) return false;
    this->label->setPosition(Vec2(mysize.width / 2, mysize.height / 2));
    this->addChild(this->label);
    return true;
}
