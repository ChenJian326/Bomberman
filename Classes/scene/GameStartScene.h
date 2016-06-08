#pragma once
#ifndef __GAME_START_SCENE__H_
#define __GAME_START_SCENE__H_
#include "cocos2d.h"
#include "ui\UIWidget.h"
USING_NS_CC;
class GameStartScene :public Node
{
public:
	GameStartScene();
	~GameStartScene();

	static Scene* createScene();

	virtual bool init();
	// a selector callback
	void menuCloseCallback(Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameStartScene);

private:
	void startGameCallback(Ref* pSender, ui::Widget::TouchEventType eventType);
};

#endif // !__GAME_START_SCENE__H_
