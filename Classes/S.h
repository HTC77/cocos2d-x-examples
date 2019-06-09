#ifndef __Prefix__Sample__
#define __Prefix__Sample__

#include "cocos2d.h"
USING_NS_CC;

class Sample : public Scene
{
public:
    static Scene* createScene();

    virtual bool init();
    
    Size visibleSize;
    Size winSize;
    Vec2 origin;

    CREATE_FUNC(Sample);

};

#endif // __Prefix__Sample__
