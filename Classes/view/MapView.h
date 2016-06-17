#pragma once
#ifndef __MAP_VIEW__H_
#define __MAP_VIEW__H_
#include "cocos2d.h"
#include "manage\GameManage.h"
#include "config\MapConfig.h"

USING_NS_CC;
class MapView :public Node
{
public:
	MapView();
	~MapView();
	static MapView* createMap(size_t level);
	size_t getCurentLevel() const { return _currentlevel; };
	void setCurentLevel(size_t level);
	void showMap();
	Size getMapSize() const { return Size(MAP_COLUMN_NUMBER * MAP_UTILE, MAP_ROW_NUMBER * MAP_UTILE); };
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(MapView);
private:
	void drawBox(size_t row, size_t col);
	void drawFloor(size_t row, size_t col);
	void drawPlayer(size_t row, size_t col);
	void drawEnemy(size_t row, size_t col);
	void drawProps(size_t row, size_t col);
	void addMapItem(Node* child,int mapType, size_t col);
	size_t _currentlevel;
	size_t _nextlevel;
	Vector2_Size_t _vMaps;
	GameManage *_manage;
};


#endif // !__MAP_VIEW__H_