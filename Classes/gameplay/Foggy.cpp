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
        _hexLayer->tintRow(-1, Color3B(0, 0, 0));
        _hexLayer->tintRow(0, Color3B(128, 0, 0));
        _hexLayer->tintRow(1, Color3B(128, 0, 0));
        _hexLayer->tintRow(2, Color3B(128, 0, 0));
        // lock the colour of the hexagon which is previously stepped on
        Vec2 deltaRowCol = HexagonDirection::deltaRowColForDirection(direction);
        _hexLayer->tintHexagon(-deltaRowCol.y, -deltaRowCol.x, Color3B(0, 192, 0));
        _hexLayer->getHexagonRegion().find(-deltaRowCol.y, -deltaRowCol.x)
            ->setTag(HexagonLayer::CANNOT_BE_TINTED);
    });

    _score = 0;
    _scoreLabel = Label::createWithTTF(TTF_CONFIG_B(64), "0");
    _scoreLabel->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    _scoreLabel->setPosition(Vec2(size.width, size.height));
    this->addChild(_scoreLabel, 5);

    // initially colour them
    _hexLayer->tintRow(0, Color3B(128, 0, 0));
    _hexLayer->tintRow(1, Color3B(128, 0, 0));
    _hexLayer->tintRow(2, Color3B(128, 0, 0));

    return true;
}

}
