#ifndef __HexBizarre__Global_h__
#define __HexBizarre__Global_h__

#define SCENE_FUNC(__type__) \
    static cocos2d::Scene* createScene() \
    { \
        auto scene = cocos2d::Scene::create(); \
        auto layer = __type__::create(); \
        scene->addChild(layer); \
        return scene; \
    }

#define TTF_CONFIG_R(__fontsize__) TTFConfig("fonts/ProximaNova-Regular.ttf", __fontsize__)
#define TTF_CONFIG_B(__fontsize__) TTFConfig("fonts/ProximaNova-Bold.ttf", __fontsize__)

#endif
