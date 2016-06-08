#pragma once
#ifndef __ENEMY__H_
#define __ENEMY__H_
#include "cocos2d.h"
#include "RoleNode.h"
#include "manage\GameManage.h"
class Enemy :public RoleNode
{
public:
	Enemy();
	~Enemy();
	virtual bool init();
	static Enemy* create(int type);
	// implement the "static create()" method manually
	void setEnemyType(int type);
	CREATE_FUNC(Enemy);
private:
	int _enemyType;
	void moveFinish(Vec2 pos);
	void pathfinding(size_t row,size_t col);
	size_t toLeft(size_t row, size_t col);
	size_t toRight(size_t row, size_t col);
	size_t toTop(size_t row, size_t col);
	size_t toBottom(size_t row, size_t col);
	GameManage* _gameManage;
};

#endif // !__ENEMY__H_