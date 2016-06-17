#pragma once
#ifndef __GAME_PROPS__H_
#define __GAME_PROPS__H_
#include "cocos2d.h"
#include "role\GameAnimation.h"
#include "config\GmaeConfig.h"
USING_NS_CC;
class GameProps :public Node
{
public:
	GameProps();
	~GameProps();
	static GameProps* createProps(const size_t propType);
	void setPropType(size_t type);
	void setExplosionRange(size_t range);
	size_t getPropType() const { return _propType; };
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(GameProps);
private:
	void animationFinish();
	void playExplosionAnimation(const Direction dir, size_t range);
	void playExplosion();
	Node* _gameProp;
	size_t _propType;
	size_t _explosionRange;
	int _injuryValue;
};


#endif // !__GAME_PROPS__H_