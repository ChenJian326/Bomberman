#pragma once
#ifndef __PLAYER__H_
#define __PLAYER__H_
#include "cocos2d.h"
#include "RoleNode.h"
#include "manage\GameManage.h"
USING_NS_CC;
class Player :public RoleNode
{
public:
	Player();
	~Player();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(Player);
private:
	void initListener();
	void moveFinish(Vec2 pos);
	GameManage* _gameManage;
};

#endif // !__PLAYER__H_