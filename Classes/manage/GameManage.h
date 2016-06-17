#pragma once
#ifndef __GAME_MANAGE__H_
#define __GAME_MANAGE__H_
#include "config\GmaeConfig.h"
#include "config\MapConfig.h"
#include "map\MapItem.h"
class GameManage
{
public:
	GameManage();
	~GameManage();
	static GameManage* getIns();
	void startGame();//开始游戏
	void continueGame();//继续游戏
	void checkGameStatus();//检查游戏状态
	void endGame();//结束游戏
	size_t getStatue() const { return _status; };//游戏状态

	void setGameMapData(Vector2_Size_t mapData);//游戏地图数据
	Vector2_Size_t getGameMapData() const { return _gameMapData; };

	std::vector<std::vector<MapItem*>> getMapItems();//游戏地图项
	void clearMapItems();//清楚游戏地图项
	void clearMapItem(MapItem* item,int injuryValue, size_t col, size_t row);//清楚游戏地图项
	void collectProps(MapItem* item, size_t col, size_t row);//获得道具
	void pushMapItem(MapItem* item,size_t row);
	/*void addProps(size_t row, size_t col);*/
	void setCurrentLevel(size_t level);//当前关卡
	size_t getCurrentLevel() const { return _currentLevel; };
	bool isEmptyFloor(size_t mapType, size_t row, size_t col);//是否是空的地板
	bool isBox(size_t mapType);//是否箱子
	bool isPlayer(size_t col, size_t row);
	bool isEnemy(size_t col, size_t row);
	MapItem* getPlayer();
	MapItem* getEnemy(int enemyType = -1);
	MapItem* getEnemy(size_t col, size_t row);
private:
	void setStatus(size_t status);
	void initEnemyItems();
	MapItem* getHitMapItem(size_t col, size_t row);
	size_t _status;//
	size_t _currentLevel;//
	static GameManage* _ins;
	Vector2_Size_t _gameMapData;
	MapItem* _player;
	std::vector<std::vector<MapItem*>> _mapItems;
	std::vector<MapItem*> _enemyItems;
};

#endif // !__GAME_MANAGE__H_