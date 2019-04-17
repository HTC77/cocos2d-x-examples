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
#include "ui/CocosGUI.h"
using namespace ui;
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

	// _1 ScrollView
	// ScrollView* scrollView = ScrollView::create();
	// scrollView->setPosition(Vec2(winSize.width/2,winSize.height/2));
	// scrollView->setDirection(ScrollView::Direction::BOTH);
	// scrollView->setBounceEnabled(true);
	// this->addChild(scrollView);
	// Sprite* sprite = Sprite::create("HelloWorld.png");
	// sprite->setScale(2.0f);
	// sprite->setPosition(sprite->getBoundingBox().size / 2);
	// scrollView->addChild(sprite);
	// scrollView->setInnerContainerSize(sprite->getBoundingBox().size);
	// scrollView->setContentSize(sprite->getContentSize());

	// _2 PageView
	//PageView* pageView = PageView::create();
	//pageView->setPosition(winSize / 2);
	//pageView->setContentSize(winSize);
	//this->addChild(pageView);
	//for (int i = 0; i < 3; ++i)
	//{
	//	Layout* page = Layout::create();
	//	page->setContentSize(pageView->getContentSize());
	//	Sprite* sprite = Sprite::create("HelloWorld.png");
	//	sprite->setPosition(sprite->getContentSize() / 2);
	//	page->addChild(sprite);
	//	pageView->insertPage(page, i);
	//}

	///*pageView->addEventListener([](Ref* sender, PageView::EventType type)
	//{
	//	if(type == PageView::EventType::TURNING)
	//	{
	//		PageView* pageView = dynamic_cast<PageView*>(sender);
	//		CCLOG("current page no= %zd",
	//			pageView->getCurrentPageIndex());
	//	}
	//});*/

	// _3 ListView
	ListView* listView = ListView::create();
	listView->setPosition(Vec2(winSize.width / 2 - 100, 0.0f));
	listView->setDirection(ListView::Direction::VERTICAL);
	listView->setBounceEnabled(true);
	listView->setContentSize(winSize);
	this->addChild(listView);
	for (int i = 0; i < 77; ++i)
	{
		Layout* layout = Layout::create();
		layout->setContentSize(Size(50, 13));
		layout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
		layout->setBackGroundColor(Color3B::WHITE);
		Button* button = Button::create();
		button->setPosition(layout->getContentSize() / 2);
		std::string name = StringUtils::format("list item %d", i);
		button->setTitleText(name);
		button->setTitleFontSize(10);
		button->setColor(Color3B::RED);
		layout->addChild(button);
		listView->addChild(layout);
	}

	//listView->addEventListener([](Ref* sender, ListView::EventType type)
	//{
	//	ListView* listView = dynamic_cast<ListView*>(sender);
	//	switch (type)
	//	{
	//		case ListView::EventType::ON_SELECTED_ITEM_START:
	//			CCLOG("select item started");
	//			break;
	//		case ListView::EventType::ON_SELECTED_ITEM_END:
	//			CCLOG("selected item %zd",
	//				listView->getCurSelectedIndex());
	//			break;
	//	}
	//});
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
