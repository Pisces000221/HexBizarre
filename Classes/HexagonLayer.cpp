#include "GameScene.h"
#include "StartupScene.h"
#include "structures/Hexagon.h"
using namespace cocos2d;

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
            auto hexagon = Hexagon::create();
            hexagon->setPosition(p);
            hexagon->row = i; hexagon->col = j;
            _hr.insert(hexagon);
            /*hexagon->initLabel();
            char s[5]; sprintf(s, "%d", hexagon->col);
            hexagon->label->setString(s);*/
            this->addChild(hexagon);
        }

    return true;
}
