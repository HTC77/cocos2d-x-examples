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
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "ui/UIVideoPlayer.h"

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

    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();

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
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
	EventListenerTouchOneByOne* listener =
		EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	// listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithFixedPriority(
		listener, 1);

	_map = TMXTiledMap::create("TileMap2.tmx");
	_map->setPosition(Vec2() + origin);
	this->addChild(_map);
	
	_mapSize = _map->getContentSize();

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

void HelloWorld::onEnter()
{
	Scene::onEnter();

}



bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 touchPoint = touch->getLocation();
	Vect tilePoint = this->getTilePosition(touchPoint);
	TMXLayer* groundLayer = _map->getLayer("Meta");
	int gid = groundLayer->getTileGIDAt(tilePoint);
	if(gid != 0)
	{
		ValueMap properties =
			_map->getPropertiesForGID(gid).asValueMap();
		if (properties.find("Collidable") != properties.end())
			if (properties.at("Collidable").asBool())
				CCLOG("it's Collidabel!!!");
	}
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	Vec2 center = Vec2(visibleSize / 2) + origin;
	_location = touch->getLocation() - center;
	_location.x = floorf(_location.x);
	_location.y = floorf(_location.y);
	this->scheduleUpdate();
}

void HelloWorld::update(float delta)
{
	Vec2 currentLocation = _map->getPosition();
	if (_location.x > 0){
		currentLocation.x--;
		_location.x--;
	}else if(_location.x < 0) {
		currentLocation.x++;
		_location.x++;
	}	
	if (_location.y > 0) {
		currentLocation.y--;
		_location.y--;
	}
	else if (_location.y < 0) {
		currentLocation.y++;
		_location.y++;
	}

	if (currentLocation.x > origin.x)
		currentLocation.x = origin.x;
	else if (currentLocation.x < winSize.width + origin.x - _mapSize.width)
		currentLocation.x = winSize.width + origin.x - _mapSize.width;
	if (currentLocation.y > origin.y)
		currentLocation.y = origin.y;
	else if (currentLocation.y < winSize.height + origin.y - _mapSize.height)
		currentLocation.y = winSize.height + origin.y - _mapSize.height;

	_map->setPosition(currentLocation);
	if (fabsf(_location.x) < 1.0f && fabsf(_location.y) < 1.0f)
		this->unscheduleUpdate();
}

Vec2 HelloWorld::getTilePosition(Vec2 point)
{
	Vec2 tilePoint = point - _map->getPosition();
	Size tileSize = _map->getTileSize();
	Size mapRowCol = _map->getMapSize();
	float scale = _mapSize.width / (mapRowCol.width *
									tileSize.width);
	tilePoint.x = floorf(tilePoint.x / (tileSize.width * scale));
	tilePoint.y = floorf((_mapSize.height - tilePoint.y) /
										(tileSize.height * scale));
	return tilePoint;
}
