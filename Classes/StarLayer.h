#ifndef STARLAYER_H
#define STARLAYER_H

#include "cocos2d.h"
#include "StarSprite.h"

#define ROW 4
#define CAL 4


typedef struct ROWCOL{
	int row;
	int cal;
}MYROWCOL;
class StarLayer : public cocos2d::Layer
{
public: 
	float _self_w, _self_h, _sp_w, _sp_h, _offset;
	int count;
	int rowcal[ROW][CAL];
	StarSprite * spritearry[ROW][CAL];

	CREATE_FUNC(StarLayer);
	virtual bool init();
	bool initwhitvirtue(float self_w, float self_h, float sp_w, float sp_h, float offset);
	bool moveto(MYROWCOL* starsprite, MYROWCOL* destination );
	bool moveto(MYROWCOL*starsprite1, MYROWCOL* starsprite2, MYROWCOL* destination);
	cocos2d::Vec2 getpositionbyrowcal(int row, int cal);
	bool insertsprite(int row, int cal);
	void reset();

};







#endif
