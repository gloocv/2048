
#include"StarLayer.h"
#include "StarSprite.h"

USING_NS_CC;


bool StarLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}
bool StarLayer::initwhitvirtue(float self_w, float self_h, float sp_w, float sp_h, float offset)
{
	_self_w = self_w;
	_self_h = self_h;
	_sp_w = sp_w;
	_sp_h = sp_h;
	_offset = offset;
	count = 0;
	this->setContentSize(Size(_self_w, _self_h));
	for (int i = 0; i < 4;i++)
	for (int j = 0; j < 4;j++)
	{
		rowcal[i][j] = 0;
		spritearry[i][j] = nullptr;
		auto ilayer = LayerColor::create(Color4B(255, 255, 255, 50),_sp_w,_sp_h);
		ilayer->setPosition((_sp_w + _offset)*j, (_sp_h + _offset)*i);
		this->addChild(ilayer);
	}
	return true;
}
bool StarLayer::insertsprite(int row, int cal)
{
	if (spritearry[row][cal] != nullptr)
		return false;
	auto isprite = StarSprite::create();
	isprite->runAction(Hide::create());
	spritearry[row][cal] = isprite;
	isprite->initwhitvirtue(Color4B(128, 255, 255, 50), _sp_w, _sp_h);
	isprite->setPosition(_sp_w*(cal+0.5) + _offset*cal, _sp_h*(row+0.5) + _offset*row);
	isprite->setnumber(2);
	this->addChild(isprite);
	rowcal[row][cal] = 2;
	return true;
}
void StarLayer::reset()
{
	for (int i = 0; i < 4;i++)
	for (int j = 0; j < 4; j++)
	{
		rowcal[i][j] = 0;
		if (spritearry[i][j] != nullptr)
			spritearry[i][j]->removeFromParent();
			spritearry[i][j] = nullptr;
	}
}
bool StarLayer::moveto(MYROWCOL* starsprite, MYROWCOL*destination)
{
	spritearry[destination->row][destination->cal] = spritearry[starsprite->row][starsprite->cal];
	spritearry[starsprite->row][starsprite->cal] = nullptr;
	rowcal[starsprite->row][starsprite->cal] = 0;
	rowcal[destination->row][destination->cal] = spritearry[destination->row][destination->cal]->getnumber();
	

	spritearry[destination->row][destination->cal]->runAction(MoveTo::create(0.15, getpositionbyrowcal(destination->row, destination->cal)));
	return true;
}
bool StarLayer::moveto(MYROWCOL *starsprite1, MYROWCOL *starsprite2, MYROWCOL* destination)
{
	spritearry[starsprite1->row][starsprite1->cal]->runAction(MoveTo::create(0.15, getpositionbyrowcal(destination->row, destination->cal)));
	spritearry[starsprite2->row][starsprite2->cal]->runAction(Sequence::create(MoveTo::create(0.15, getpositionbyrowcal(destination->row, destination->cal)), ScaleTo::create(0.1, 1.1), ScaleTo::create(0.1, 1),nullptr));
	spritearry[starsprite1->row][starsprite1->cal]->removeFromParent();
	spritearry[starsprite1->row][starsprite1->cal] = nullptr;
	spritearry[destination->row][destination->cal] = spritearry[starsprite2->row][starsprite2->cal];
	spritearry[starsprite2->row][starsprite2->cal] = nullptr;

	rowcal[starsprite1->row][starsprite1->cal] = 0;
	rowcal[starsprite2->row][starsprite2->cal] = 0;
	spritearry[destination->row][destination->cal]->setnumber(spritearry[destination->row][destination->cal]->getnumber()*2);
	rowcal[destination->row][destination->cal] = spritearry[destination->row][destination->cal]->getnumber();
	count += rowcal[destination->row][destination->cal];
	return true;
}
Vec2 StarLayer::getpositionbyrowcal(int row, int cal)
{
	return Vec2(_sp_w*(cal + 0.5) + _offset*cal, _sp_h*(row + 0.5) + _offset*row);
}
