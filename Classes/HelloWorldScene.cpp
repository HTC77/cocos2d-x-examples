/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    winSize = Director::getInstance()->getWinSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + winSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	// _1
	/*Label* label = Label::createWithSystemFont("Hello\ncocos2d-x", "Arial", 40);
	label->setPosition(winSize / 2);
	this->addChild(label);
	label->setHorizontalAlignment(TextHAlignment::CENTER);*/
	
	// _2
	// sec = 0;
	// std::string secString = StringUtils::toString(sec);
	// Label* label = Label::createWithSystemFont(secString, "Arial",40);
	// label->setPosition(winSize / 2);
	// this->addChild(label);
 //
	// this->schedule([=](float dt)
	// {
	// 	sec++;
	// 	std::string secString = StringUtils::toString(sec);
	// 	label->setString(secString);
	// },1.0f,"mCallBackKey");

	// _3 true type font
	// Label* label = Label::createWithTTF("True Type Font",
	// 	"fonts/Marker Felt.ttf", 40.0f);
	// label->setPosition(winSize / 2);
	// this->addChild(label);

	// _4 TTFConfig
	TTFConfig config;
	config.fontFilePath = "fonts/Marker Felt.ttf";
	config.fontSize = 40.0f;
	config.glyphs = GlyphCollection::DYNAMIC;
	config.outlineSize = 0;
	config.customGlyphs = nullptr;
	config.distanceFieldEnabled = false;
	Label* label = Label::createWithTTF(config, "True Type Font");
	label->setPosition(winSize / 2);
	//label->setColor(Color3B::RED);
	//label->enableGlow(Color4B::RED);
	label->enableShadow(Color4B::RED, Size(5,5), 0);
	this->addChild(label);
	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::finishedActions()
{
	CCLOG("FINISHED....");
}

void HelloWorld::callBack(Ref* sender)
{
	CCLOG("Callback");
}
