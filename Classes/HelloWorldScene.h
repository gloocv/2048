#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"StarLayer.h"

class HelloWorld : public cocos2d::Layer
{
public:
	StarLayer *starLayer;
	cocos2d::LabelTTF* score;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	cocos2d::Vec2 touchstartp;
	bool moveanctionrunning;
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void menucallback(cocos2d::Object * pSender);
	void restart(cocos2d::Object * pSender);
	bool HelloWorld::left();
	bool HelloWorld::right();
	bool HelloWorld::up();
	bool HelloWorld::down();
	void HelloWorld::game_winover(bool);

};

#endif // __HELLOWORLD_SCENE_H__
