#include "GameScene.h"
#include "StartupScene.h"
#include "structures/Hexagon.h"
using namespace cocos2d;

bool isInHexagon(Vec2 target, Vec2 centre)
{
    //CCLOG("is (%.2f, %.2f) in (%.2f, %.2f)?", target.x, target.y, centre.x, centre.y);
    return (target.x - centre.x) * (target.x - centre.x)
        + (target.y - centre.y) * (target.y - centre.y) < HEX_APOTHEM * HEX_APOTHEM * 1.44;
}

bool HexagonLayer::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 255))) return false;

    // enable touching
    auto _listener = EventListenerTouchOneByOne::create();
    _listener->setSwallowTouches(true);
    // get something advanced
    _listener->onTouchBegan = [=](Touch *touch, Event *event) {
        Vec2 pos = touch->getLocation();
        // which hexagon do you live in??
        // I'm lazy... so I use a circle with a radius of apothem * 1.2 to detect...
        // see isInHexagon(cocos2d::Vec2, cocos2d::Vec2)
        int moveDirection = 0;
        if (isInHexagon(pos, _hr.find(0, 1)->getPosition()))
            moveDirection = HexagonDirection::RIGHT;
        else if (isInHexagon(pos, _hr.find(0, -1)->getPosition()))
            moveDirection = HexagonDirection::LEFT;
        else if (isInHexagon(pos, _hr.find(1, 0)->getPosition()))
            moveDirection = HexagonDirection::RIGHT | HexagonDirection::UP;
        else if (isInHexagon(pos, _hr.find(1, -1)->getPosition()))
            moveDirection = HexagonDirection::LEFT | HexagonDirection::UP;
        else return false;
        this->move(moveDirection);
        if (_onMove) _onMove(moveDirection);
        _hr.find(0, 0)->runAction(RepeatForever::create(Sequence::create(
            EaseSineInOut::create(TintTo::create(1.2, 255, 255, 0)),
            EaseSineInOut::create(TintTo::create(1.2, 192, 192, 0)), nullptr)));
        // check for missing tiles, get them back
        this->refill();
        return true;
    };
    _listener->onTouchMoved = [=](Touch *touch, Event *event) {
        //Vec2 pos = touch->getLocation();
    };
    _listener->onTouchEnded = [=](Touch *touch, Event *event) {
        //Vec2 pos = touch->getLocation();
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_listener, this);

    // initialize all hexagons
    this->refill();
    return true;
}

void HexagonLayer::refill()
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 centre = Vec2(size.width * 0.5, HEX_SIDE_LEN * 2.5);
    Vec2 moveDist = _hr.getMoveDistance();

    // This IS Dad-tricking, I have to say.
    // So, let's celebrate Fathers' Day through this Dad-tricking code!
    // a bigger i means a bigger y
    int max_j = (size.width * 0.5 - HEX_SIDE_LEN) / HEX_DIAMETRE + 1;
    for (int i = -centre.y / HEX_HEIGHT - 1; i <= (size.height - centre.y) / HEX_HEIGHT + 1; i++)
        for (int j = -max_j - abs(i) % 2; j <= max_j; j++)
            if (!_hr.find(i, j)) {
                auto hexagon = Hexagon::create();
                // if it's in an odd line (e.g. line 1 or line -1), move it right by half length
                hexagon->setPosition(i % 2 == 0 ?
                    Vec2(j * HEX_HEIGHT, i * HEX_SIDE_LEN * 1.5) + centre - moveDist :
                    Vec2((j + 0.5) * HEX_HEIGHT, i * HEX_SIDE_LEN * 1.5) + centre - moveDist);
                hexagon->row = i; hexagon->col = j;
                _hr.insert(hexagon);
                hexagon->runAction(_hr.getMoveAction());
                this->addChild(hexagon);
            }
}
