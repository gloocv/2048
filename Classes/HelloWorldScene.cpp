#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StarLayer.h"
#include"SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

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
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	this->addChild(LayerColor::create(Color4B(180, 170, 160, 255)));
	auto title = LabelTTF::create("2048", "Arial", 60);
	title->setPosition(visibleSize.width / 2, visibleSize.height - 40);
	this->addChild(title);
	//���ӿ�ʼ��ť
	auto startBtn = MenuItemFont::create("start", CC_CALLBACK_1(HelloWorld::menucallback, this));
	startBtn->setPosition(visibleSize.width / 2, visibleSize.height - 80);
	startBtn->setFontSizeObj(30);
	startBtn->setColor(Color3B(128, 208, 48));
	auto menu = Menu::create(startBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	//����
	auto scoretitle = LabelTTF::create("score", "Arial", 30);
	scoretitle->setPosition(visibleSize.width / 5, visibleSize.height - 110);
	scoretitle->setColor(Color3B(24, 106, 168));
	this->addChild(scoretitle);
	score = LabelTTF::create("0", "Arial", 30);
	score->setPosition(visibleSize.width / 2, visibleSize.height - 110);
	scoretitle->setColor(Color3B(24, 106, 168));
	this->addChild(score);

	starLayer = StarLayer::create();
	starLayer->initwhitvirtue(300, 300, 71.25, 71.25, 5);
	starLayer->setPosition(10, 40);
	this->addChild(starLayer);
	//Ԥ������Ч
	SimpleAudioEngine::getInstance()->preloadEffect("get.mp3");
	//���Ӵ�������
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	for (int i = 0; i<4;i++)
	for (int j = 0; j<4; j++)
	{
		StarSprite * star = starLayer->spritearry[i][j];
		if (star&&star->getNumberOfRunningActions() > 0)
		{
			moveanctionrunning = true;
			return false;
		}
	}
	moveanctionrunning = true;
	moveanctionrunning = false;
	touchstartp = touch->getLocation();
	return true;
}
void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
	if (moveanctionrunning)
		return ;
	auto endpoint = touch->getLocation();
	auto offsetX = endpoint.x - touchstartp.x;
	auto offsetY = endpoint.y - touchstartp.y;
	bool ismove = false;
	if (abs(offsetX) > abs(offsetY))
	{	//left
		if (offsetX < -5)
		{
			ismove = left();
		}

		//right
		else if (offsetX > 5)
		{
			ismove = right();
		}

	}
	else
	{	//down
		if (offsetY< -5)
			ismove = down();
		//up
		else if (offsetY > 5)
			ismove = up();
	}
	if (ismove)
	{
		//music
		SimpleAudioEngine::getInstance()->playEffect("get.mp3");
		//��������
		score->setString(String::createWithFormat("%d", starLayer->count)->getCString());

		//starLayer->rowcal[1][1] = 2048;//����ʤ��,
		for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (starLayer->rowcal[i][j] == 2048)

			{
				//��Ϸʤ��
				game_winover(true);
				return;
			}
		}
		//�����µĿ�Ƭ
		while (!starLayer->insertsprite(CCRANDOM_0_1() * 4, CCRANDOM_0_1() * 4)){ ; }

		//�ж��Ƿ�ʧ��
		for (int i = 0; i < 4;i++)
		for (int j = 0; j < 4; j++)
		{
			 if ((starLayer->rowcal[i][j] == 0) || (i>0 && starLayer->rowcal[i][j] == starLayer->rowcal[i - 1][j]) || (j>0 && starLayer->rowcal[i][j] == starLayer->rowcal[i][j-1]))
			{
				return;
			}
		}
		//��Ϸʧ��
		game_winover(false);
	}
}
void HelloWorld::menucallback(Object * pSender)
{
	auto mstart = (MenuItemFont*)pSender;
	mstart->setString("Restart");
	starLayer->reset();
	score->setString("0");
	starLayer->count = 0;
	for (int i = 0; i < 2; i++)
	{
		while (!starLayer->insertsprite(CCRANDOM_0_1() * 4, CCRANDOM_0_1() * 4)){ ; }
	}

}
bool HelloWorld::left()
{
	bool bmove = false;
	bool ibmove = false;

	for (int irow = 0; irow < 4; irow++)
	{
		for (int icol = 0; icol < 4; icol++)
		{
			if (starLayer->rowcal[irow][icol] == 0)
			{
				for (int icolcol = icol + 1; icolcol < 4; icolcol++)
				{
					ibmove = false;
					if (starLayer->rowcal[irow][icolcol] == 0)
						continue;
					else
					{
						int icolcolcol;
						for (icolcolcol = icolcol + 1; icolcolcol < 4; icolcolcol++)
						{
							if (starLayer->rowcal[irow][icolcolcol] == 0)
								continue;
							else if (starLayer->rowcal[irow][icolcolcol] == starLayer->rowcal[irow][icolcol])
							{
								MYROWCOL starsprite1 = { irow, icolcol };
								MYROWCOL starsprite2 = { irow, icolcolcol };
								MYROWCOL destination = { irow, icol };
								starLayer->moveto(&starsprite1, &starsprite2, &destination);
								bmove = true;
								ibmove = true;
								break;
							}
							else
								break;
						}
						if (!ibmove)
						{
							MYROWCOL starsprite1 = { irow, icolcol };
							MYROWCOL destination = { irow, icol };
							starLayer->moveto(&starsprite1, &destination);
							bmove = true;
							ibmove = true;
							break;
						}
						else
							break;
					}
				}
			}
			else
			{
				int icolcol;
				for (icolcol = icol + 1; icolcol < 4; icolcol++)
				{
					if (starLayer->rowcal[irow][icolcol] == 0)
						continue;
					else if (starLayer->rowcal[irow][icol] == starLayer->rowcal[irow][icolcol])
					{
						MYROWCOL starsprite1 = { irow, icol };
						MYROWCOL starsprite2 = { irow, icolcol };
						MYROWCOL destination = { irow, icol };
						starLayer->moveto(&starsprite1, &starsprite2, &destination);
						bmove = true;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return bmove;
}
bool HelloWorld::right()
{
	bool bmove = false;
	bool ibmove = false;
	for (int irow = 0; irow < 4; irow++)
	{
		for (int icol = 3; icol >-1; icol--)
		{

			if (starLayer->rowcal[irow][icol] == 0)
			{
				for (int icolcol = icol - 1; icolcol > -1; icolcol--)
				{
					ibmove = false;
					if (starLayer->rowcal[irow][icolcol] == 0)
						continue;
					else
					{
						int icolcolcol;
						for (icolcolcol = icolcol - 1; icolcolcol > -1; icolcolcol--)
						{
							if (starLayer->rowcal[irow][icolcolcol] == 0)
								continue;
							else if (starLayer->rowcal[irow][icolcolcol] == starLayer->rowcal[irow][icolcol])
							{
								MYROWCOL starsprite1 = { irow, icolcol };
								MYROWCOL starsprite2 = { irow, icolcolcol };
								MYROWCOL destination = { irow, icol };
								starLayer->moveto(&starsprite1, &starsprite2, &destination);
								bmove = true;
								ibmove = true;
								break;
							}
							else
								break;
						}
						if (!ibmove)
						{
							MYROWCOL starsprite1 = { irow, icolcol };
							MYROWCOL destination = { irow, icol };
							starLayer->moveto(&starsprite1, &destination);
							bmove = true;
							ibmove = true;
							break;
						}
						else
							break;
					}
				}
			}
			else
			{
				int icolcol;
				for (icolcol = icol - 1; icolcol > -1; icolcol--)
				{
					if (starLayer->rowcal[irow][icolcol] == 0)
						continue;
					else if (starLayer->rowcal[irow][icol] == starLayer->rowcal[irow][icolcol])
					{
						MYROWCOL starsprite1 = { irow, icol };
						MYROWCOL starsprite2 = { irow, icolcol };
						MYROWCOL destination = { irow, icol };
						starLayer->moveto(&starsprite1, &starsprite2, &destination);
						bmove = true;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return bmove;
}
bool HelloWorld::up()
{
	bool bmove = false;
	bool ibmove = false;
	for (int icol = 0; icol < 4; icol++)
	{
		for (int irow = 3; irow >-1; irow--)
		{

			if (starLayer->rowcal[irow][icol] == 0)
			{
				for (int irowrow = irow - 1; irowrow > -1; irowrow--)
				{
					ibmove = false;
					if (starLayer->rowcal[irowrow][icol] == 0)
						continue;
					else
					{
						int irowrowrow;
						for (irowrowrow = irowrow - 1; irowrowrow > -1; irowrowrow--)
						{
							if (starLayer->rowcal[irowrowrow][icol] == 0)
								continue;
							else if (starLayer->rowcal[irowrowrow][icol] == starLayer->rowcal[irowrow][icol])
							{
								MYROWCOL starsprite1 = { irowrow, icol };
								MYROWCOL starsprite2 = { irowrowrow, icol };
								MYROWCOL destination = { irow, icol };
								starLayer->moveto(&starsprite1, &starsprite2, &destination);
								bmove = true;
								ibmove = true;
								break;
							}
							else
								break;
						}
						if (!ibmove)
						{
							MYROWCOL starsprite1 = { irowrow, icol };
							MYROWCOL destination = { irow, icol };
							starLayer->moveto(&starsprite1, &destination);
							bmove = true;
							break;
						}
						else
							break;
					}
				}
			}
			else
			{
				int irowrow;
				for (irowrow = irow - 1; irowrow > -1; irowrow--)
				{
					if (starLayer->rowcal[irowrow][icol] == 0)
						continue;
					else if (starLayer->rowcal[irow][icol] == starLayer->rowcal[irowrow][icol])
					{
						MYROWCOL starsprite1 = { irow, icol };
						MYROWCOL starsprite2 = { irowrow, icol };
						MYROWCOL destination = { irow, icol };
						starLayer->moveto(&starsprite1, &starsprite2, &destination);
						bmove = true;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return bmove;
}
bool HelloWorld::down()
{
	bool bmove = false;
	bool ibmove = false;
	for (int icol = 0; icol < 4; icol++)
	{
		for (int irow = 0; irow < 4; irow++)
		{

			if (starLayer->rowcal[irow][icol] == 0)
			{
				for (int irowrow = irow + 1; irowrow < 4; irowrow++)
				{
					ibmove = false;

					if (starLayer->rowcal[irowrow][icol] == 0)
						continue;
					else
					{
						int irowrowrow;
						for (irowrowrow = irowrow + 1; irowrowrow < 4; irowrowrow++)
						{
							if (starLayer->rowcal[irowrowrow][icol] == 0)
								continue;
							else if (starLayer->rowcal[irowrowrow][icol] == starLayer->rowcal[irowrow][icol])
							{
								MYROWCOL starsprite1 = { irowrow, icol };
								MYROWCOL starsprite2 = { irowrowrow, icol };
								MYROWCOL destination = { irow, icol };
								starLayer->moveto(&starsprite1, &starsprite2, &destination);
								bmove = true;
								ibmove = true;
								break;
							}
							else
								break;
						}
						if (!ibmove)
						{
							MYROWCOL starsprite1 = { irowrow, icol };
							MYROWCOL destination = { irow, icol };
							starLayer->moveto(&starsprite1, &destination);
							bmove = true;
							break;
						}
						else
							break;
					}
				}
			}
			else
			{
				int irowrow;
				for (irowrow = irow + 1; irowrow < 4; irowrow++)
				{
					if (starLayer->rowcal[irowrow][icol] == 0)
						continue;
					else if (starLayer->rowcal[irow][icol] == starLayer->rowcal[irowrow][icol])
					{
						MYROWCOL starsprite1 = { irow, icol };
						MYROWCOL starsprite2 = { irowrow, icol };
						MYROWCOL destination = { irow, icol };
						starLayer->moveto(&starsprite1, &starsprite2, &destination);
						bmove = true;
						break;
					}
					else
						break;
				}
			}
		}
	}
	return bmove;
}

void HelloWorld::game_winover(bool winover)
{
	auto  winlayer = LayerColor::create(Color4B(123, 123, 123,80), 300,300);
	winlayer->setPosition(10,50);
	this->addChild(winlayer);
	auto labelgame = LabelTTF::create();
	labelgame->setPosition(150,200);
	labelgame->setFontSize(60);
	if (winover)
	{
		SimpleAudioEngine::getInstance()->playEffect("gamewin.mp3");
		labelgame->setString("Game Win");
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect("gameover.mp3");
		labelgame->setString("Game Over");
	}
	winlayer->addChild(labelgame);
	auto scoretitle = LabelTTF::create(String::createWithFormat("score %d", starLayer->count)->getCString(), "Arial", 40);
	scoretitle->setPosition(150,100);
	winlayer->addChild(scoretitle);
	MenuItemFont* startBtn = MenuItemFont::create("restart", CC_CALLBACK_1(HelloWorld::restart, this));
	startBtn->setFontSize(60);
	startBtn->setPosition(150,40);
	auto menu = Menu::create(startBtn, nullptr);
	menu->setPosition(0,0);
	winlayer->addChild(menu);
}
void HelloWorld::restart(cocos2d::Object * pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.7f, HelloWorld::createScene()));
}