#include "AppDelegate.h"
#include "SplashScene.h"
#include "StartupScene.h"
using namespace cocos2d;

#define _HB_DEBUG 0

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
		glview = GLView::createWithRect("HexBizarre", Rect(0, 0, 320, 480));
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(320, 480, ResolutionPolicy::SHOW_ALL);

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
#if _HB_DEBUG
    auto scene = Startup::createScene();
#else
    auto scene = Splash::createScene();
#endif
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    //SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    //SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
