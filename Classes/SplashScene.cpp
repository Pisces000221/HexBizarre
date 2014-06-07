#include "SplashScene.h"
#include "StartupScene.h"
using namespace cocos2d;

bool Splash::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) return false;

    Size size = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("images/cocos2dx_portrait.png");
    sprite->setAnchorPoint(Vec2(1, 0));
    sprite->setPosition(Vec2(size.width + 24, -48));
    sprite->setOpacity(144);
    this->addChild(sprite);

    auto label_1 = Label::createWithTTF(TTF_CONFIG_R(56), "Powered by");
    label_1->setPosition(Vec2(size.width * 0.25, size.height * 0.382));
    label_1->setColor(Color3B(0, 0, 0));
    this->addChild(label_1);

    auto label_2 = Label::createWithTTF(TTF_CONFIG_B(84), "Cocos2d-x");
    label_2->setPosition(Vec2(size.width * 0.25, size.height * 0.382 - 64));
    label_2->setColor(Color3B(0, 0, 0));
    this->addChild(label_2);

    this->scheduleOnce(schedule_selector(Splash::goOn), 2);

    return true;
}

void Splash::goOn(float dt)
{
    auto nextScene = Startup::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.8, nextScene, Color3B(0, 0, 0)));
}
