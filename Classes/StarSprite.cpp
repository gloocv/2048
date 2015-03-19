#include "StarSprite.h"

USING_NS_CC;

bool StarSprite::init()
{
	if (!Sprite::init())
		return false;
	return true;
}
bool StarSprite::initwhitvirtue(Color4B color4b, float sp_w, float sp_h)
{
	auto cardbg = LayerColor::create(color4b, sp_w, sp_h);
	this->setContentSize(Size(sp_w, sp_h));
	this->setAnchorPoint(Vec2(0.5, 0.5));

	this->addChild(cardbg);
	auto cardnum = LabelTTF::create();
	cardnum->setPosition(Vec2(sp_w / 2, sp_h / 2));
	cardnum->setTag(2);
	cardnum->setFontSize(30);
	this->addChild(cardnum);
	this->runAction(Sequence::create(ScaleTo::create(0, 0), Show::create(), ScaleTo::create(0.2, 1), nullptr));
	return true;
}
void StarSprite::setnumber(int num)
{
	number = num;
	LabelTTF *cardnum = (LabelTTF*)this->getChildByTag(2);
	cardnum->setString(String::createWithFormat("%d", num)->getCString());
}
int StarSprite::getnumber()
{
	return number;
}
