#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;



class MainMenu : public cocos2d::CCLayer
{
public:
    virtual bool init(); 
    static cocos2d::CCScene* scene();
	CREATE_FUNC(MainMenu);
	void Update(float dt);
	int count;
	bool disabled;
	bool down;
	bool up;

	CCLabelTTF *start;
	CCLabelTTF *about;
	CCLabelTTF *credits;

	enum menuItems { START, ABOUT, CREDITS };

	menuItems items;

	CCSprite *background;
};

#endif // __MAIN_MENU_SCENE_H__