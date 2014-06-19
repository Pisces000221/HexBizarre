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
        // check for missing tiles, get them back
        this->refill();
        if (_onMove) _onMove(moveDirection);
        // tint the hexagon at the current position of the player
        auto action = RepeatForever::create(Sequence::create(
            EaseSineInOut::create(TintTo::create(1.2, 255, 255, 0)),
            EaseSineInOut::create(TintTo::create(1.2, 192, 192, 0)), nullptr));
        action->setTag(REPEAT_CURRENT_POS_TINT_TAG);
        _hr.find(0, 0)->runAction(action);
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
    // i, j means row and col
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

    // check if the entire map is moved up/down
    // http://stackoverflow.com/questions/3884572/how-to-modify-key-values-in-stdmap-container
    std::map<int, cocos2d::Color3B> t;
    if (_hr.getLastMoveDirection() & HexagonDirection::UP) {
        for (auto it = _tintRows.begin(); it != _tintRows.end(); ++it)
            t[it->first - 1] = it->second;
        _tintRows = t;
    }
    // ... and tint them all!
    this->tintAllAskedRows();
}

void HexagonLayer::tintRow(int row, Color3B c)
{
    //if (_tintRows.find(row) == _tintRows.end()) _tintRows[row] = c;
    //else _tintRows.find(row)->second = c;
    _tintRows[row] = c;
    this->tintAllAskedRows();
}

void HexagonLayer::tintHexagon(int row, int col, Color3B c)
{
    auto target = _hr.find(row,col);
    if (target && target->getTag() != CANNOT_BE_TINTED) {
        target->stopActionByTag(REPEAT_CURRENT_POS_TINT_TAG);
        target->runAction(TintTo::create(0.3, c.r, c.g, c.b));
    }
}

void HexagonLayer::tintAllAskedRows()
{
    // tint the rows that we're asked to tint
    // http://stackoverflow.com/questions/4844886/how-to-loop-through-a-c-map
    Size size = Director::getInstance()->getVisibleSize();
    int max_col = (size.width * 0.5 - HEX_SIDE_LEN) / HEX_DIAMETRE + 1;
    for (auto it = _tintRows.begin(); it != _tintRows.end(); ++it) {
        int row = it->first;
        if (_hr.find(row, 0))   // if this row did exist, we tint it
            for (int col = -max_col - abs(row) % 2; col <= max_col; col++) tintHexagon(row, col, it->second);
        else                    // otherwise we just remove it from the list
            _tintRows.erase(it);
    }
}
