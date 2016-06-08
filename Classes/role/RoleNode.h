#pragma once
#ifndef __ROLE_NODE__H_
#define __ROLE_NODE__H_
#include "cocos2d.h"
#include "config\GmaeConfig.h"
#include "config\MapConfig.h"
#include "GameAnimation.h"
USING_NS_CC;
class RoleNode :public Node
{
public:
	RoleNode();
	~RoleNode();
	virtual bool init();
	void createRole(std::vector<std::string> names);
	void createRole(std::vector<std::vector<std::string>> names);
	void moveRole(Direction direction, bool isAutoMove = false);//isAutoMove = ture的时候会自己移动，
	void setMoveFunc(std::function<void(Vec2 pos)> moveFunc);//isAutoMove = true 请设置这个参数
	void setSpeed(size_t speed);
	void setHealth(size_t health);
	void setRoleType(int type);
	int getRoleType() const { return _roleType; };
	size_t getHealth() const{ return _health; };
	bool isDeath() const { return _isDeath; };
	size_t getSpeed() const { return _speed; };
	Vec2 getColAndRow(Vec2 colRow);
	Direction getDirection() const { return _currentDirection; };
	// implement the "static create()" method manually
	CREATE_FUNC(RoleNode);
private:
	void startMove();
	void stopMove();
	void roleDeath();//死亡
	bool isMove(Vec2 pos);
	void updateMovePos(float dt);
	Direction _currentDirection;
	size_t _speed;
	size_t _health;
	bool _isDeath;
	float _moveX;
	float _moveY;
	GameAnimation* _roleAnimation;
	int _roleType;
	std::function<void(Vec2 pos)> _moveFunc;
	Vector2_Size_t _gameMapData;
	Vec2 _roleBiasPos;
	Vec2 _rowAndCol;
protected:
	bool _isMove;
	bool _isBox;
	bool _isPlayer;
};

#endif // !__ROLE_NODE__H_
