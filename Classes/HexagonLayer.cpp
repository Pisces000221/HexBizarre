#include "GameScene.h"
#include "StartupScene.h"
#include "structures/Hexagon.h"
using namespace cocos2d;

bool HexagonLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255))) return false;
    this->refill();
    return true;
}

void HexagonLayer::refill()
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 centre = Vec2(size.width * 0.5, HEX_SIDE_LEN * 2.5);

    // a bigger i means a bigger y
    int max_j = (size.width * 0.5 - HEX_SIDE_LEN) / HEX_DIAMETRE + 1;
    for (int i = -centre.y / HEX_HEIGHT - 1; i <= (size.height - centre.y) / HEX_HEIGHT + 1; i++)
        for (int j = -max_j - abs(i) % 2; j <= max_j; j++)
            if (!_hr.find(i, j)) {
                auto hexagon = Hexagon::create();
                // if it's in an odd line (e.g. line 1 or line -1), move it right by half length
                hexagon->setPosition(i % 2 == 0 ?
                    Vec2(j * HEX_HEIGHT, i * HEX_SIDE_LEN * 1.5) + centre :
                    Vec2((j + 0.5) * HEX_HEIGHT, i * HEX_SIDE_LEN * 1.5) + centre);
                hexagon->row = i; hexagon->col = j;
                _hr.insert(hexagon);
                hexagon->initLabel();
                hexagon->label->setColor(Color3B(0, 128, 255));
                hexagon->setTag(2);
                this->addChild(hexagon);
            } else {
                CCLOG("skipping %d, %d (0x%x exists)", i, j, _hr.find(i, j));
                _hr.find(i, j)->label->setColor(Color3B(255, 255, 0));
            }

    for (auto hexagon : _hr.allHexagons()) {
        char s[5]; sprintf(s, "%d", hexagon->col);
        hexagon->label->setString(s);
        if (hexagon->getTag() == 2) {
            hexagon->setTag(0);
        } else {
            hexagon->label->setColor(Color3B(255, 255, 255));
        }
    }
}
