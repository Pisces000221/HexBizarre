#include "Foggy.h"
using namespace cocos2d;

namespace hb_gameplay {

bool Foggy::init()
{
    if (!GameLayer::init()) return false;

    Size size = Director::getInstance()->getVisibleSize();
    _hexLayer->setCallbacks([this](int direction) {
        // refresh score display
        char s[10]; sprintf(s, "%d", ++_score);
        _scoreLabel->runAction(Sequence::create(
            FadeTo::create(0.1, 128),
            CallFunc::create([=]() { _scoreLabel->setString(s); }),
            FadeTo::create(0.1, 255), nullptr));
        // refresh colours of the hexagons
        _hexLayer->tintRow(0, Color3B(128, 0, 0));
    });

    _score = 0;
    _scoreLabel = Label::createWithTTF(TTF_CONFIG_B(64), "0");
    _scoreLabel->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    _scoreLabel->setPosition(Vec2(size.width, size.height));
    this->addChild(_scoreLabel, 5);

    return true;
}

}
