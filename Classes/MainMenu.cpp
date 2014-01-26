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
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSize origin = CCDirector::sharedDirector()->getVisibleOrigin();

	background = CCSprite::create("title.png");
	background->setPosition(ccp( visibleSize.width / 2,visibleSize.height / 2));
	this->addChild(background);

	schedule(schedule_selector(MainMenu::Update, 0.0f));

	return true;
}

void MainMenu::Update(float dt)
{

	if(GetKeyState(VK_RETURN) & shifted)
	{
		CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
	}
}