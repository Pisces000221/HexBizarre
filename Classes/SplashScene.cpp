#include "SplashScene.h"
#include "StartupScene.h"
using namespace cocos2d;

bool Splash::init()
{
    if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) return false;

    Size size = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("images/cocos2dx_portrait.png");
    sprite->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    sprite->setPosition(Vec2(-24, size.height + 48));
    sprite->setOpacity(144);
    sprite->setScale(size.width * 0.9 / sprite->getTextureRect().size.width);
    this->addChild(sprite);

    auto label_1 = Label::createWithTTF(TTF_CONFIG_R(28), "Powered by");
    label_1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    label_1->setPosition(Vec2(size.width * 0.65, 48));
    label_1->setColor(Color3B(0, 0, 0));
    this->addChild(label_1);

    auto label_2 = Label::createWithTTF(TTF_CONFIG_B(42), "Cocos2d-x");
    label_2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    label_2->setPosition(Vec2(size.width * 0.65, 3));
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
