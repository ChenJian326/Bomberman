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
	void startGame();//��ʼ��Ϸ
	void continueGame();//������Ϸ
	void checkGameStatus();//�����Ϸ״̬
	void endGame();//������Ϸ
	size_t getStatue() const { return _status; };//��Ϸ״̬

	void setGameMapData(Vector2_Size_t mapData);//��Ϸ��ͼ����
	Vector2_Size_t getGameMapData() const { return _gameMapData; };

	std::vector<std::vector<MapItem*>> getMapItems();//��Ϸ��ͼ��
	void clearMapItems();//�����Ϸ��ͼ��
	void clearMapItem(size_t row, size_t col);//�����Ϸ��ͼ��
	void pushMapItem(MapItem* item,size_t row);
	void addBomb(size_t row, size_t col);
	void setCurrentLevel(size_t level);//��ǰ�ؿ�
	size_t getCurrentLevel() const { return _currentLevel; };
	bool isEmptyFloor(size_t mapType, size_t row, size_t col);//�Ƿ��ǿյĵذ�
	bool isBox(size_t mapType);//�Ƿ�����
	bool isPlayer(size_t col, size_t row);
	Node* getPlayer();
private:
	void setStatus(size_t status);
	size_t _status;//
	size_t _currentLevel;//
	static GameManage* _ins;
	Vector2_Size_t _gameMapData;
	Node* _player;
	std::vector<std::vector<MapItem*>> _mapItems;
};

#endif // !__GAME_MANAGE__H_