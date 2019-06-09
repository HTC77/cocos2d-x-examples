#include "Sample.h"

Scene* Sample::createScene()
{
    return Sample::create();
}

bool Sample::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();  

    return true;
}

