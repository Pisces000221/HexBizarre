#include "GameScene.h"
#include "StartupScene.h"
using namespace cocos2d;

#define HEXAGON_TAG(i, j) (i * 23476 + j * 887 + 3245)

bool GameLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255))) return false;

    Size size = Director::getInstance()->getVisibleSize();
    Vec2 centre = Vec2(size.width * 0.5, HEX_SIDE_LEN * 2.5);

    // a bigger i means a bigger y
    int max_j = (size.width * 0.5 - HEX_SIDE_LEN) / HEX_DIAMETRE + 1;
    for (int i = -centre.y / HEX_HEIGHT - 1; i <= (size.height - centre.y) / HEX_HEIGHT + 1; i++)
        for (int j = -max_j - abs(i) % 2; j <= max_j; j++) {
            Vec2 p;
            if (!(i % 2)) p = Vec2(j * HEX_HEIGHT, i * HEX_SIDE_LEN * 1.5) + centre;
            else p = Vec2((j + 0.5) * HEX_HEIGHT, i * HEX_SIDE_LEN * 1.5) + centre;
            // create a solid hexagon (I'm too lazy to use a DrawNode)
            auto hf = Sprite::create("images/hexagon_fill.png");
            hf->setPosition(p);
            hf->setColor(Color3B(0, 255, 0));
            this->addChild(hf, 0, HEXAGON_TAG(j, i) - 9);   // border tag - 9 = filling tag
            // create its border
            auto hb = Sprite::create("images/hexagon_border.png");
            hb->setPosition(p);
            this->addChild(hb, 1, HEXAGON_TAG(j, i));
        }
    this->getChildByTag(HEXAGON_TAG(0, 0) - 9)->runAction(RepeatForever::create(Sequence::create(
        TintTo::create(1.2, 255, 255, 0),
        TintTo::create(1.2, 192, 192, 0), nullptr)));
    this->move(HEXAGON_RIGHT | HEXAGON_UP);

    return true;
}

void GameLayer::move(int direction)
{
    Vec2 delta = Vec2::ZERO;
    //CCLOG("%d, %d", direction, direction | HEXAGON_LEFT);
    if (direction & HEXAGON_LEFT) delta.x += HEX_HEIGHT;
    else delta.x -= HEX_HEIGHT;
    if (direction & HEXAGON_UP) {
        delta.y -= HEX_SIDE_LEN * 1.5;
        delta.x *= 0.5;
    }
    //CCLOG("delta: (%f, %f)", delta.x, delta.y);
    this->runAction(EaseSineOut::create(MoveBy::create(3, delta)));
}
