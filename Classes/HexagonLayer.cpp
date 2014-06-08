#include "GameScene.h"
#include "StartupScene.h"
using namespace cocos2d;

#define HEXAGON_TAG(i, j) (i * 23476 + j * 887 + 324500)

bool HexagonLayer::init()
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
            hb->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
            hf->addChild(hb, 1, HEXAGON_TAG(j, i));
            _hexagons.insert(hf);
        }

    return true;
}

void HexagonLayer::move(int direction)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 delta = Vec2::ZERO;
    if (direction & HEXAGON_LEFT) delta.x += HEX_HEIGHT;
    else delta.x -= HEX_HEIGHT;
    if (direction & HEXAGON_UP) {
        delta.y -= HEX_SIDE_LEN * 1.5;
        delta.x *= 0.5;
    }
    Sprite *cur;
    float maxx = 0, maxy = 0, minx = 0, miny = 0;
    STDSET_FOREACH(cocos2d::Sprite *, _hexagons, cur) {
        Vec2 p = cur->getPosition();
        if (p.x > maxx) maxx = p.x; else if (p.x < minx) minx = p.x;
        if (p.y > maxy) maxy = p.y; else if (p.y < miny) miny = p.y;
        cur->runAction(EaseSineOut::create(MoveBy::create(0.5, delta)));
    }
    STDSET_FOREACH(cocos2d::Sprite *, _hexagons, cur) {
        Vec2 p = cur->getPosition();
        bool x_outofborder = p.x < -HEX_SIDE_LEN || p.x > size.width + HEX_SIDE_LEN,
            y_outofborder = p.y < -HEX_APOTHEM || p.y > size.height + HEX_APOTHEM;
        if (x_outofborder || y_outofborder) {
            cur->removeFromParent();
            _hexagons.erase(it);
        }
    }
}
