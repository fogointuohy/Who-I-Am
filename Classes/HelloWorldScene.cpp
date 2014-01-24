#include "HelloWorldScene.h"
#include "AppMacros.h"
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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

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
		hello->setPosition(ccp(hello->getPosition().x - .5f, hello->getPosition().y));
	}
	if(GetKeyState(VK_RIGHT) & shifted)
	{
		hello->setPosition(ccp(hello->getPosition().x + .5f, hello->getPosition().y));
	}
	else
	{
		hello->setPosition(ccp(hello->getPosition().x + 0, hello->getPosition().y));
	}
}
