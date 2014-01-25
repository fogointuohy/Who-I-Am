#include "MainMenu.h"
#include "AppMacros.h"
#include "HelloWorldScene.h"
USING_NS_CC;

#define shifted 0x8000


CCScene* MainMenu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	MainMenu *layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	count =0;
	disabled = false;
	down = false;
	up = true;
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	start = CCLabelTTF::create("Start", "Arial", 12.0f);
	start->setPosition(ccp(visibleSize.width / 2 ,visibleSize.height - 100));
	this->addChild(start);
	about = CCLabelTTF::create("About", "Arial", 12.0f);
	about->setPosition(ccp(start->getPositionX(),start->getPositionY() -20));
	this->addChild(about);
	credits = CCLabelTTF::create("Credits", "Arial", 12.0f);
	credits->setPosition(ccp(about->getPositionX(),about->getPositionY() -20));
	this->addChild(credits);

	schedule(schedule_selector(MainMenu::Update, 0.0f));

	items = menuItems::START;

	return true;
}

void MainMenu::Update(float dt)
{

	if(count == 0)
	{
		up = true;
		start->setColor(ccc3(255,255,0));
		about->setColor(ccc3(255,255,255));
		credits->setColor(ccc3(255,255,255));
		items = menuItems::START;
	}
	else if(count == 1)
	{
		up = false;
		down = false;
		start->setColor(ccc3(255,255,255));
		about->setColor(ccc3(255,255,0));
		credits->setColor(ccc3(255,255,255));
		items = menuItems::ABOUT;
	}
	else if(count == 2)
	{
		start->setColor(ccc3(255,255,255));
		about->setColor(ccc3(255,255,255));
		credits->setColor(ccc3(255,255,0));
		down  =true;
		items = menuItems::CREDITS;
	}


	if(GetKeyState(VK_UP) & shifted)
	{
		if(!disabled)
		{
			if(!up)
			{
				count--;
				disabled =true;
			}
		}
	}
	else if(GetKeyState(VK_DOWN) & shifted)
	{
		if(!disabled)
		{
			if(!down)
			{
				count++;
				disabled =true;
			}
		}
	}
	else 
	{
		disabled = false;
	}

	if(GetKeyState(VK_RETURN) & shifted)
	{
		if(items == START)
		{
			CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
		}
		else  if(items == ABOUT)
		{
		}
		else if(items == CREDITS)
		{
		}
	}
}