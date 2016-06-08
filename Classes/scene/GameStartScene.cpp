#include "GameStartScene.h"
#include "manage\GameManage.h"
#include "ui\UIButton.h"
GameStartScene::GameStartScene()
{
}

GameStartScene::~GameStartScene()
{
}

Scene * GameStartScene::createScene()
{
	auto scene = Scene::create();
	auto node = GameStartScene::create();
	scene->setName("GameStartScene");
	scene->addChild(node);
	auto transition = TransitionFade::create(1.2f, scene);
	return transition;
}

bool GameStartScene::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("startScene.png");
	auto startBtn = ui::Button::create("startGame.png");
	startBtn->addTouchEventListener(CC_CALLBACK_2(GameStartScene::startGameCallback,this));
	startBtn->setPosition(Vec2(0, -size.height * 0.3f));
	this->addChild(bg);
	this->addChild(startBtn);
	this->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
	return true;
}

void GameStartScene::menuCloseCallback(cocos2d::Ref * pSender)
{
}

void GameStartScene::startGameCallback(cocos2d::Ref * pSender, ui::Widget::TouchEventType eventType)
{
	if (eventType == ui::Widget::TouchEventType::ENDED)
	{
		CCLOG("start game");
		GameManage::getIns()->startGame();
	}
}

