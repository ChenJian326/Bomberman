#pragma once
#ifndef __GAME_CONDUCT__SCENE__H_
#define __GAME_CONDUCT__SCENE__H_
#include "cocos2d.h"
#include "view\MapView.h"
USING_NS_CC;
class GameConductScene :public Node
{
public:
	GameConductScene();
	~GameConductScene();
	static Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameConductScene);
private:
	void showMap(size_t level);
	MapView* _mapView;
};

#endif // !__GAME_CONDUCT__SCENE__H_
