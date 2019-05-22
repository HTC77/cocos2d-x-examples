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


Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = HelloWorld::create();
	auto world = scene->getPhysicsWorld();
	scene->addChild(layer);
	world->setGravity(Vec2(0, -98));
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

    auto visibleSize = Director::getInstance()->getVisibleSize();
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

Sprite* HelloWorld::makeSprite()
{
	auto sprite = Sprite::create("CloseNormal.png");
	auto physicsBody = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
	physicsBody->setDynamic(true);
	physicsBody->setContactTestBitmask(true);
	sprite->setPhysicsBody(physicsBody);
	return sprite;
}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_world = Director::getInstance()->getRunningScene()->getPhysicsWorld();

	// wall
	auto wall = Node::create();
	auto wallBody = PhysicsBody::createEdgeBox(visibleSize,
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	wallBody->setContactTestBitmask(true);
	wall->setPhysicsBody(wallBody);
	wall->setPosition(Vec2(visibleSize.width / 2 + origin.x,
		visibleSize.height / 2 + origin.y));
	addChild(wall);

	// gear object 1
	auto sp1 = this->makeSprite();
	sp1->setPosition(visibleSize / 2);
	this->addChild(sp1);
	// gear object 2
	auto sp2 = this->makeSprite();
	sp2->setPosition(Vec2(visibleSize.width / 2 + 2, visibleSize.
		height));
	this->addChild(sp2);
	// joint: gear
	auto body1 = sp1->getPhysicsBody();
	auto body2 = sp2->getPhysicsBody();
	auto pin1 = PhysicsJointPin::construct(body1, wallBody, sp1->getPosition());
	_world->addJoint(pin1);
	auto pin2 = PhysicsJointPin::construct(body2, wallBody, sp2->getPosition());
	_world->addJoint(pin2);
	auto joint = PhysicsJointGear::construct(body1, body2, 0.0f,
		2.0f);
	_world->addJoint(joint);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	auto location = touch->getLocation();
	auto shapes = _world->getShapes(location);
	if (shapes.size() <= 0) {
		return false;
	}
	PhysicsShape* shape = shapes.front();
	PhysicsBody* body = shape->getBody();
	if (body != nullptr) {
		_touchNode = Node::create();
		auto touchBody = PhysicsBody::create(PHYSICS_INFINITY,
			PHYSICS_INFINITY);
		_touchNode->setPhysicsBody(touchBody);
		_touchNode->getPhysicsBody()->setDynamic(false);
		_touchNode->setPosition(location);
		this->addChild(_touchNode);
		PhysicsJointPin* joint = PhysicsJointPin::construct(touchBody, body, location);
		joint->setMaxForce(5000.0f * body->getMass());
		_world->addJoint(joint);
		return true;
	}
	return false;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	if (_touchNode != nullptr) {
		_touchNode->setPosition(touch->getLocation());
	}
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	if (_touchNode != nullptr) {
		_touchNode->removeFromParent();
		_touchNode = nullptr;
	}
}
