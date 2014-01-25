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

	//Padraigs stuff
	speed = 0;
	maxSpeed = 12;
	jumpSpeed = 0;
	jump = false;
	time = 0;
	collision = true;
	
	hello = CCSprite::create("hello.png");
	hello->setPosition(ccp(100,100));
	this->addChild(hello);

	startY= hello->getPositionY();

	schedule(schedule_selector(HelloWorld::Update, 0.0f));

	return true;
}

void HelloWorld::Update(float dt)
{
	PlayerMovement(dt);
}

void HelloWorld::PlayerMovement(float dt)
{
	time=time+dt;
	

	if(GetKeyState(VK_LEFT) & shifted)
	{
		if(speed>maxSpeed)
			speed-=0.1;
		if(speed>-maxSpeed)
			speed-=1;

		hello->setPosition(ccp(hello->getPosition().x +speed, hello->getPosition().y));
	}
	else if(GetKeyState(VK_RIGHT) & shifted)
	{
		if(speed<maxSpeed)
			speed+=0.1;
		if(speed<maxSpeed)
			speed+=1;

		hello->setPosition(ccp(hello->getPosition().x + speed, hello->getPosition().y));
	}
	else
	{
		for(int k=0;k<1;k++)
		{
			if(speed<0)
				speed+=.5;
			else if(speed >0)
				speed -=.5;
		}

		hello->setPosition(ccp(hello->getPosition().x + 0, hello->getPosition().y));
	}

	if(jump&&!collision)
	{
		hello->setPositionY(hello->getPositionY()-jumpSpeed);
		jumpSpeed+=1;

	}
	else
	{
		if((GetKeyState(VK_UP)&shifted))
		{
			collision = false;
			jump=true;
			jumpSpeed=-14;
		}
	}

	if(GetKeyState(VK_F1) & shifted)
	{
		collision = true;
	}
	
	

	if(GetKeyState(VK_NUMPAD0) & shifted)
	{
		CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
	}
}
