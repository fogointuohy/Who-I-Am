#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "MainMenu.h"
#include <string>

USING_NS_CC;

#define shifted 0x8000

#define PTM_RATIO 32.0


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
	dialogOn = false;
	
	//Maurice
	maurice=CCSprite::create("maurice.png");
	maurice->setPosition(ccp(150,100));
	this->addChild(maurice);

	//Dialog Test
	dialog1 = CCSprite::create("dialog1.png");
	dialog1->setPosition(ccp(-150,-150));
	this->addChild(dialog1);
	saveLabel = CCLabelTTF::create("Save Here", "Arial", 6.0f);
	saveLabel->setPosition(ccp(-150,-150));
	this->addChild(saveLabel);
	dontSaveLabel = CCLabelTTF::create("Dont save her", "Arial", 6.0f);
	dontSaveLabel->setPosition(ccp(-150,-150));
	this->addChild(dontSaveLabel);

	
	hello = CCSprite::create("player.png");
	hello->setPosition(ccp(100,100));
	this->addChild(hello);

	b2Vec2 gravity = b2Vec2(0,-20);
		
	world = new b2World(gravity);
	debug_draw = new GLESDebugDraw( 32.0f );
	world->SetDebugDraw(debug_draw);

	map = CCTMXTiledMap::create("map.tmx");
	map->setPosition(ccp(origin.x, origin.y));
	map_object_group = map->objectGroupNamed("Collision");

	this->addChild(map);

	CCDictionary *dictionary;
	CCString string;

	/*dictionary = map_object_group->objectNamed("Outline");
	string = (*dictionary->valueForKey("polyline"));*/

	std::string parse = string.getCString();
	std::istringstream is(parse);
	int i = 0;
	b2Vec2 vertices[300];

	CCPoint position;

	for (int j = 0; j < 4; j++)
	{
		CCString * test = CCString::create("Outline" + std::to_string(j));
		dictionary = map_object_group->objectNamed(test->getCString());
		string = (*dictionary->valueForKey("polyline"));
		
		float actualY = (*dictionary->valueForKey("y")).floatValue() + origin.y + 30;
		float actualX = (*dictionary->valueForKey("x")).floatValue() + origin.x ;

		position.x = actualX / PTM_RATIO / CC_CONTENT_SCALE_FACTOR();
		position.y = actualY / PTM_RATIO / CC_CONTENT_SCALE_FACTOR();

		std::string parse = string.getCString();
		std::istringstream is(parse);
		b2Vec2 vertices[300];
		vertices->SetZero();

		
		

		for(i = 0; is.good(); i++)
		{
			int x,y;
			char comma;
			is >> x >> comma >> y;
			std::cout << x << ", " << y << std::endl;
			vertices[i].x = (x / PTM_RATIO / CC_CONTENT_SCALE_FACTOR());
			vertices[i].y = (y / PTM_RATIO / CC_CONTENT_SCALE_FACTOR()) * -1;
		}

		b2ChainShape boundaries;
		boundaries.CreateChain(vertices, i);

		b2FixtureDef boundariesFixtureShape;
		b2BodyDef boundariesBodayBef;

		boundariesFixtureShape.shape = &boundaries;
		boundariesFixtureShape.friction = 3;
		boundariesFixtureShape.userData = (void*)1;

		boundariesBodayBef.position.Set(position.x,position.y);
		
		b2Body* bound_body = world->CreateBody(&boundariesBodayBef);
		bound_body->CreateFixture(&boundariesFixtureShape);
	}



	PlayerBodyDef.type = b2BodyType::b2_dynamicBody;

	PlayerShape.SetAsBox(.2f, .45);

	PlayerFixtureDef.shape = &PlayerShape;
	PlayerFixtureDef.density = .5;
	PlayerFixtureDef.userData = (void*)2;

	PlayerBodyDef.position.Set(3.5,4.0);
	PlayerBodyDef.fixedRotation = true;

	PlayerBody = world->CreateBody(&PlayerBodyDef);
	PlayerBody->CreateFixture(&PlayerFixtureDef);

	/***************************************************************/

	SensorPlayerShape.m_radius =.4;
	SensorPlayerShape.m_p.Set(0,-.3 ); 

	SensorPlayerFixtureDef.shape = &SensorPlayerShape;
	SensorPlayerFixtureDef.userData = (void*)3;
	SensorPlayerFixtureDef.isSensor = true;
		
	PlayerBody->CreateFixture(&SensorPlayerFixtureDef);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	debug_draw->SetFlags(flags);

	contactListener = new ContactListener();
	world->SetContactListener(contactListener);

	facingLeft =true;
	facingRight = false;

	camPos = CCPoint(this->getPositionX() + visibleSize.width, 0);

	playerPos = CCPoint(visibleSize.width,visibleSize.height);
	playerPosy = CCPoint(visibleSize.width,visibleSize.height);

	saveMenuCounter= 0;

	disabled = false;
	down = false;
	up = true;

	schedule(schedule_selector(HelloWorld::Update, 0.0f));

	return true;
}

void HelloWorld::Update(float dt)
{
	//Can't move if we're talking
	if(!dialogOn)
	{
		PlayerMovement(dt);
	}
	else
	{

		//TODO
		//Make this block so that it switches the dialog box based on who you talked to
		//Also if it was a special character, accept an item from them
		dialog1->setPosition(ccp(150,150));

		saveLabel->setPosition(ccp(dialog1->getPositionX() + 80 ,dialog1->getPositionY()));
		dontSaveLabel->setPosition(ccp(saveLabel->getPositionX(),saveLabel->getPositionY() -20));

		if(saveMenuCounter == 0)
		{
			up = true;
			down=false;
			saveLabel->setColor(ccc3(255,255,0));
			dontSaveLabel->setColor(ccc3(255,255,255));
		}
		else if(saveMenuCounter == 1)
		{
			up = false;
			down = true;
			dontSaveLabel->setColor(ccc3(255,255,0));
			saveLabel->setColor(ccc3(255,255,255));
		}

		if(GetKeyState(VK_UP) & shifted)
		{
			if(!disabled)
			{
				if(!up)
				{
					saveMenuCounter--;
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
					saveMenuCounter++;
					disabled =true;
				}
			}
		}
		else 
		{
			disabled = false;
		}
	}

	//If we're near, we can talk, then we quit the conversation
	if((GetKeyState(0x5A) & shifted)&&((hello->getPositionX()>maurice->getPositionX()&&hello->getPositionX()<maurice->getPositionX()+50)
	||(hello->getPositionX()<maurice->getPositionX()&&hello->getPositionX()>maurice->getPositionX()-50)))
	{
		dialogOn=true;
	}
	if(dialogOn)
	{
		if((GetKeyState(0x58) & shifted))
		{
			if(saveMenuCounter == 0)
			{
				CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
			}
			else if(saveMenuCounter == 1)
			{
				dialogOn=false;
				saveLabel->setPosition(ccp(-150,-150));
				dontSaveLabel->setPosition(ccp(-150,-150));
				dialog1->setPosition(ccp(-150,-150));
			}
		}
	}
	
	world->Step(dt,10,10);
}

void HelloWorld::PlayerMovement(float dt)
{
	if(GetKeyState(VK_LEFT) & shifted)
	{
		facingLeft = true;
		facingRight = false;

		b2Vec2 vel = PlayerBody->GetLinearVelocity();
		float desiredVel = -4;

		float velChange = desiredVel - vel.x;
		float force = PlayerBody->GetMass() * velChange / (1/60.0); //f = mv/t
		PlayerBody->ApplyForce( b2Vec2(force,0), PlayerBody->GetWorldCenter() );
		hello->setFlipX(1);

	}
	else if(GetKeyState(VK_RIGHT) & shifted)
	{
		facingRight = true;
		facingLeft = false;

		b2Vec2 vel = PlayerBody->GetLinearVelocity();
		float desiredVel = 4;

		float velChange = desiredVel - vel.x;
		float force = PlayerBody->GetMass() * velChange / (1/60.0); //f = mv/t
		PlayerBody->ApplyForce( b2Vec2(force,0), PlayerBody->GetWorldCenter() );
		hello->setFlipX(0);

	}

	hello->setPosition(ccp(PlayerBody->GetPosition().x * PTM_RATIO, PlayerBody->GetPosition().y * PTM_RATIO));

	if(contactListener->CanPlayerJump())
	{
		if((GetKeyState(VK_UP)&shifted))
		{
			float impulse = PlayerBody->GetMass() * 2.0;
			PlayerBody->ApplyLinearImpulse( b2Vec2(0,impulse), PlayerBody->GetWorldCenter() );
		}
	}

	if(facingRight)
	{
		facingLeft = false;
		if(hello->getPositionX() > playerPos.x)
		{
			playerPos = CCPoint(visibleSize.width + playerPos.x,0);
			this->setPositionX(this->getPositionX() - visibleSize.width);			
		}
	}

	if(facingLeft)
	{
		facingRight = false;
		if(hello->getPositionX() < playerPos.x - visibleSize.width)
		{
			playerPos = CCPoint(playerPos.x - visibleSize.width,0);
			this->setPositionX(this->getPositionX() + visibleSize.width);
		}
	}
	if(hello->getPositionY() > playerPosy.y)
	{
		playerPosy = CCPoint(0,visibleSize.height + playerPosy.y);
		this->setPositionY(this->getPositionY() - visibleSize.height);
	}
	if(hello->getPositionY() < playerPosy.y -visibleSize.height)
	{
		playerPosy = CCPoint(0,playerPosy.y - visibleSize.height);
		this->setPositionY(this->getPositionY() + visibleSize.height);
	}

	if(GetKeyState(VK_NUMPAD0) & shifted)
	{
		CCDirector::sharedDirector()->replaceScene(MainMenu::scene());
	}
}

void HelloWorld::draw()
{CCLayer::draw();ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );kmGLPushMatrix();world->DrawDebugData();kmGLPopMatrix();}
