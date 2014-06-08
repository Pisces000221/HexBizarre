#include "StartupScene.h"
#include "GameScene.h"
using namespace cocos2d;

bool Startup::init()
{
    if (!Layer::init()) return false;

    Size size = Director::getInstance()->getVisibleSize();

    auto label_1 = Label::createWithTTF(TTF_CONFIG_B(64), "HEX\nBIZARRE", TextHAlignment::RIGHT);
    label_1->setAnchorPoint(Vec2(1, 0.5));
    label_1->setPosition(Vec2(size.width - 16, size.height * 0.8));
    this->addChild(label_1);
    // highlight 'bizarre'
    for (int i = 4; i < 11; i++) label_1->getLetter(i)->setColor(Color3B(32, 255, 32));

    auto newGameMenu = MenuItemLabel::create(
        Label::createWithTTF(TTF_CONFIG_R(36), "New Game"), CC_CALLBACK_1(Startup::newGame, this));
    newGameMenu->setAnchorPoint(Vec2(0, 0.5));
    newGameMenu->setPosition(Vec2(24, size.height * 0.5));
    auto menu = Menu::create(newGameMenu, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void Startup::newGame(Ref *sender)
{
    CCLOG("New game");
    auto nextScene = GameLayer::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.8, nextScene, Color3B(0, 0, 0)));
}
