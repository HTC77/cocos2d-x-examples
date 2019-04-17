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
using namespace experimental;
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

	// _1 BackgroundMusic
	CocosDenshion::SimpleAudioEngine* audioEngine =
		CocosDenshion::SimpleAudioEngine::getInstance();
	// audioEngine->preloadBackgroundMusic("background.mp3");
	// audioEngine->playBackgroundMusic("background.mp3",true);

	// set music based on target platform:
	/*
	 * 	#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	 * 	#define MUSIC_FILE "background.ogg"
	 * 	#else
	 * 	#define MUSIC_FILE "background.caf"
	 * 	#endif
	 * 	audioEngine->playBackgroundMusic(MUSIC_FILE, true);
	 */
	// change how many sounds to play simultaneously on android :
	/*
	 * Cocos2dxSound.java > MAX_SIMULTANEOUS_STREAMS_DEFULT (default is 5)
	 */
	// _2 effect with options
	// audioEngine->setEffectsVolume(0.5);
	// float pitch = 1.0f;
	// float pan = 1.0f;
	// float gain = 1.0f;
	// unsigned int _soundId = audioEngine->playEffect("background.mp3", true, pitch, pan, gain);
	//
	// audioEngine->resumeEffect(_soundId);

	// _3 background music
	int id = AudioEngine::play2d("background.mp3");
	AudioEngine::setLoop(id,true);
	AudioEngine::setVolume(id, 0.5);
	AudioEngine::pause(id);
	AudioEngine::resume(id);
	//AudioEngine::stop(id);
	AudioEngine::setCurrentTime(id, 5.0);
	AudioEngine::setFinishCallback(id, [](int audioId, std::string filePath)
	{
		// this is the process when the background music was finished
	});


	// Unloading Audio Files
	/*AudioEngine::uncache("background.mp3");
	AudioEngine::uncacheAll();*/

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
