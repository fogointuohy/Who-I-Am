#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "GLES-Render.h"
#include "ContactListener.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	void Update(float dt);

	void PlayerMovement(float dt);
	void draw();
	CCSprite *hello;

	CCTMXTiledMap *map;
	CCTMXLayer map_layer;
	CCTMXObjectGroup *map_object_group;
	GLESDebugDraw *debug_draw;
	b2World *world;
	static const char* valueForKey(const char *key, std::map<std::string, std::string>* dict);

private:
	float speed;
	float maxSpeed;
	float jumpSpeed;
	bool jump;
	bool startY;
	bool collision;
	float time;
	CCTMXTiledMap *tileMap;
	CCTMXLayer *background;
	CCSize visibleSize;
	CCPoint origin;
	bool jumped;


	CCPoint sceneForwardVector;
	CCPoint sceneBackVector;

	b2PolygonShape PlayerShape;
	b2FixtureDef PlayerFixtureDef;
	b2BodyDef PlayerBodyDef;
	b2Body *PlayerBody;
	b2Fixture* PlayerFixture;

	b2CircleShape SensorPlayerShape;
	b2FixtureDef SensorPlayerFixtureDef;
	b2BodyDef SensorPlayerBodyDef;
	b2Body *SensorPlayerBody;
	b2Fixture* SensorPlayerFixture;

	ContactListener *contactListener;

	bool doneTransfer;

	CCPoint camPos;
	CCPoint playerPos;
	bool facingRight;
	bool facingLeft;

};

#endif // __HELLOWORLD_SCENE_H__
