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

using namespace  ui;
using namespace experimental;
Scene* HelloWorld::createScene()
{
	Scene* scene = Scene::createWithPhysics();
    HelloWorld* layer = HelloWorld::create();
	scene->addChild(layer);
	PhysicsWorld* world = scene->getPhysicsWorld();
	Vec2 gravity = Vec2(0, -98.0f);
	world->setGravity(gravity);
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	return scene;
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
	EventListenerTouchOneByOne* listener =
		EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	// listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	// listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithFixedPriority(
		listener, 1);
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

void HelloWorld::callBack(Ref* sender)
{
	CCLOG("Callback");
}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_world = Director::getInstance()->getRunningScene()->getPhysicsWorld();
	EventListenerPhysicsContact* contactListener =
		EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [](PhysicsContact& contact)
	{
		static int _contacts = 0;
		PhysicsShape* shapeA = contact.getShapeA();
		PhysicsBody* bodyA = shapeA->getBody();

		PhysicsShape* shapeB = contact.getShapeB();
		PhysicsBody* bodyB = shapeB->getBody();

		if (bodyA->getTag() == 11 && bodyB->getTag() == 11)
		{
			CCLOG("CONTACT BALL!!! %d", ++_contacts);
		}
		return true;
	};

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		contactListener, this);

	//wall
	Node* wall = Node::create();
	PhysicsBody* wallBody = PhysicsBody::createEdgeBox(winSize,
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	wallBody->setContactTestBitmask(1);
	wall->setPosition(winSize.width / 2 + origin.x, winSize.height / 2 + origin.y);
	wall->setPhysicsBody(wallBody);
	addChild(wall);

	Sprite* sprite = Sprite::create("CloseNormal.png");
	sprite->setPosition(winSize / 2);
	PhysicsBody* circleBody =
		PhysicsBody::createCircle(sprite->getContentSize().width / 2);
	circleBody->setDynamic(true);
	circleBody->setTag(11);
	circleBody->setContactTestBitmask(true);
	sprite->setPhysicsBody(circleBody);
	this->addChild(sprite);
	
}

void HelloWorld::makeSprite(Vec2 position)
{
	Sprite* sprite = Sprite::create("CloseNormal.png");
	sprite->setPosition(position);
	PhysicsBody* circleBody =
		PhysicsBody::createCircle(sprite->getContentSize().width / 2);
	circleBody->setDynamic(true);
	circleBody->setContactTestBitmask(true);
	circleBody->setTag(11);
	sprite->setPhysicsBody(circleBody);
	this->addChild(sprite);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 location = Director::getInstance()->convertToGL(
		touch->getLocationInView());
	makeSprite(location);
	return true;
}
