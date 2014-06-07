#include "AppDelegate.h"
#include "SplashScene.h"
using namespace cocos2d;

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
		glview = GLView::createWithRect("HexBizarre", Rect(0, 0, 960, 640));
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    auto scene = Splash::createScene();
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
