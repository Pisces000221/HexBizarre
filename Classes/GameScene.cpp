#include "GameScene.h"
#include "StartupScene.h"
using namespace cocos2d;

#define HEXAGON_TAG(i, j) (i * 23476 + j * 887 + 3245)

bool GameLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255))) return false;

    Size size = Director::getInstance()->getVisibleSize();
    Vec2 centre = Vec2(size.width * 0.5, HEX_SIDE_LEN * 2.5);

    for (int i = -size.width * 0.5 / HEX_DIAMETRE - 2; i <= size.width * 0.5 / HEX_DIAMETRE + 2; i++)
        for (int j = -centre.y / HEX_HEIGHT - 1; j <= (size.height - centre.y) / HEX_HEIGHT + 1; j++) {
            Vec2 p;
            if (i % 2) p = Vec2(i * HEX_SIDE_LEN * 1.5, j * HEX_HEIGHT) + centre;
            else p = Vec2(i * HEX_SIDE_LEN * 1.5, (j + 0.5) * HEX_HEIGHT) + centre;
            // create a solid hexagon (I'm too lazy to use a DrawNode)
            auto hf = Sprite::create("images/hexagon_fill.png");
            hf->setPosition(p);
            hf->setColor(Color3B(0, 0, 0));
            this->addChild(hf, 0, HEXAGON_TAG(i, j) - 9);   // border tag - 9 = filling tag
            // create its border
            auto hb = Sprite::create("images/hexagon_border.png");
            hb->setPosition(p);
            this->addChild(hb, 1, HEXAGON_TAG(i, j));
        }
    this->getChildByTag(HEXAGON_TAG(0, 0) - 9)->setColor(Color3B(255, 255, 0));

    return true;
}
