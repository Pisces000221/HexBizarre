#include "GameScene.h"
#include "StartupScene.h"
using namespace cocos2d;

bool GameLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255))) return false;

    Size size = Director::getInstance()->getVisibleSize();
    _hexLayer = HexagonLayer::create();
    this->addChild(_hexLayer);

    auto action = RepeatForever::create(Sequence::create(
        EaseSineInOut::create(TintTo::create(1.2, 255, 255, 0)),
        EaseSineInOut::create(TintTo::create(1.2, 192, 192, 0)), nullptr));
    action->setTag(HexagonLayer::REPEAT_CURRENT_POS_TINT_TAG);
    _hexLayer->getHexagonRegion().find(0, 0)->runAction(action);
    _hexLayer->getHexagonRegion().find(0, 0)->setTag(HexagonLayer::CANNOT_BE_TINTED);
    // slowly slide down at the very beginning
    _hexLayer->setPosition(Vec2(0, size.height * 0.618));
    _hexLayer->runAction(EaseSineOut::create(MoveTo::create(2, Vec2::ZERO)));

    // the back button
    auto backMenu = MenuItemImage::create("images/back.png", "images/back.png", "images/back.png",
        CC_CALLBACK_1(GameLayer::goBack, this));
    backMenu->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    backMenu->setPosition(Vec2(0, size.height));
    auto menu = Menu::create(backMenu, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1000);

    return true;
}

void GameLayer::goBack(Ref *sender)
{
    auto cover = LayerColor::create(Color4B(0, 0, 0, 255));
    this->addChild(cover, INT_MAX);
    cover->setOpacity(0);
    cover->runAction(Sequence::create(
        FadeIn::create(0.4),
        CallFunc::create([]() { Director::getInstance()->popScene(); }), nullptr));
}
