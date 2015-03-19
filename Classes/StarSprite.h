#ifndef STARSPRITE_H
#define STARSPRITE_H

#include "cocos2d.h"

class StarSprite :public cocos2d::Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(StarSprite);
	bool initwhitvirtue(cocos2d::Color4B,float sp_w,float sp_h);

	void setnumber(int);
	int getnumber();
	int number;
};



#endif