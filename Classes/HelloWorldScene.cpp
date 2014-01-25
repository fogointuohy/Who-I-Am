#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "MainMenu.h"
USING_NS_CC;

#define shifted 0x8000


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();

	tileMap = new CCTMXTiledMap();
	tileMap->initWithTMXFile("map.tmx");
	background = tileMap->layerNamed("Tile Layer 1");
		
	jumped = false;

	tileMap->setPosition(ccp(origin.x,origin.y));

	this->addChild(tileMap);

	hello = CCSprite::create("hello.png");
	hello->setPosition(ccp(100,100));
	this->addChild(hello);

	schedule(schedule_selector(HelloWorld::Update, 0.0f));

	return true;
}

void HelloWorld::Update(float dt)
{
	if(GetKeyState(VK_LEFT) & shifted)
	{
		hello->setPosition(ccp(hello->getPosition().x - 1.5f, hello->getPosition().y));
	}
	if(GetKeyState(VK_RIGHT) & shifted)
	{
		hello->setPosition(ccp(hello->getPosition().x + 1.5f, hello->getPosition().y));
	}
	else
	{
		hello->setPosition(ccp(hello->getPosition().x + 0, hello->getPosition().y));
	}

	if(GetKeyState(VK_NUMPAD0) & shifted)
	{
		CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
	}
}