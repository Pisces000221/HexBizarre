#ifndef  __HexBizarre__AppDelegate_h__
#define  __HexBizarre__AppDelegate_h__

#include "cocos2d.h"

class AppDelegate : private cocos2d::Application
{
public:
    AppDelegate() {}
    virtual ~AppDelegate() {}

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};

#endif
