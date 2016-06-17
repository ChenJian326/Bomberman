#include "GameManage.h"
#include "EventManager.h"
#include "utils\DirectorUtils.h"
#include "utils\GameFileUtils.h"
#include "scene\GameConductScene.h"
#include <new>
GameManage* GameManage::_ins = nullptr;
GameManage::GameManage()
	:_currentLevel(0),
	_player(nullptr)
{
}

GameManage::~GameManage()
{
}

GameManage * GameManage::getIns()
{
	if (nullptr == _ins)
	{
		_ins = new(std::nothrow) GameManage();
	}
	return _ins;
}

void GameManage::startGame()
{
	GameFileUtils::getIns()->initCacheData();
	this->setStatus(GameStatus::START);
}

void GameManage::continueGame()
{
	this->setStatus(GameStatus::CONTINUE);
}

void GameManage::checkGameStatus()
{
	if (this->getPlayer()->isDeath()) {
		this->endGame();
	}
}

void GameManage::endGame()
{
	this->clearMapItems();
	this->_player = nullptr;
	_gameMapData.clear();
	_enemyItems.clear();
	this->setStatus(GameStatus::END);
}

void GameManage::setGameMapData(Vector2_Size_t mapData)
{
	_gameMapData = mapData;
}

std::vector<std::vector<MapItem*>> GameManage::getMapItems()
{
	return this->_mapItems;
}

void GameManage::clearMapItems()
{
	for each (auto var in this->_mapItems)
	{
		for each (auto item in var)
		{
			item->removeChild();
			item->removeProps();
			delete item;
		}
	}
	this->_mapItems.clear();
}

void GameManage::clearMapItem(MapItem* item, int injuryValue, size_t col, size_t row)
{
	auto mapType = item->getMapType();
	if (mapType == MAP_TYPE::PROPS && item->getChild())
	{
		size_t propType = random(0, 2);
		item->addProp(propType);
		item->removeChild();
	}
	else if (mapType == MAP_TYPE::BOX)
	{
		item->clear();
	}
	else
	{
		MapItem* role = this->getHitMapItem(col, row);
		if (role) {
			role->InjuryRole(injuryValue);
			CCLOG("Injury Role %d", injuryValue);
		}
		this->checkGameStatus();
	}
}

void GameManage::collectProps(MapItem * item, size_t col, size_t row)
{
	auto mapType = item->getMapType();
	if (mapType == MAP_TYPE::PROPS && nullptr == item->getChild())
	{
		item->clear();
	}
	MapItem* role = this->getHitMapItem(col, row);
	if (role) {
		CCLOG("%D get props", role->getMapType());
	}
}

void GameManage::pushMapItem(MapItem * item, size_t row)
{
	if (this->_mapItems.size() <= row)
	{
		std::vector<MapItem*> items;
		this->_mapItems.push_back(items);
	}
	this->_mapItems.at(row).push_back(item);
}

//void GameManage::addProps(size_t row, size_t col)
//{
//}


void GameManage::setCurrentLevel(size_t level)
{
	_currentLevel = level;
	GameFileUtils::getIns()->setCacheData(Cache_Current_Level, Value((int)_currentLevel));
}

bool GameManage::isEmptyFloor(size_t mapType, size_t row, size_t col)
{
	bool isEmptyFloor = true;
	bool isProp = true;
	if (mapType == MAP_TYPE::PROPS)
	{
		isProp = nullptr == this->_mapItems[row][col]->getChild();
	}
	if (mapType == MAP_TYPE::FLOOR || mapType == MAP_TYPE::BOX) {
		isEmptyFloor = false;
	}
	return isEmptyFloor && isProp;
}

bool GameManage::isBox(size_t mapType)
{
	bool isBox = false;
	if (mapType == MAP_TYPE::BOX) {
		isBox = true;
	}
	return isBox;
}

bool GameManage::isPlayer(size_t col, size_t row)
{
	bool isPlayer = false;
	auto player = this->getPlayer();
	if (nullptr != player) {
		size_t c = player->getChild()->getPositionX() / MAP_UTILE;
		size_t r = player->getChild()->getPositionY() / MAP_UTILE;
		if (c == col && row == r)
		{
			isPlayer = true;
		}
	}
	return isPlayer;
}

bool GameManage::isEnemy(size_t col, size_t row)
{
	bool isEnemy = false;
	this->initEnemyItems();
	for each (auto item in _enemyItems)
	{
		size_t c = item->getChild()->getPositionX() / MAP_UTILE;
		size_t r = item->getChild()->getPositionY() / MAP_UTILE;
		if (c == col && row == r)
		{
			isEnemy = true;
			break;
		}
	}
	return isEnemy;
}

MapItem * GameManage::getPlayer()
{
	if (nullptr == _player)
	{
		for each (auto items in this->_mapItems)
		{
			for each (auto item in items)
			{
				if (item->getMapType() == MAP_TYPE::PLAYER) {
					_player = item;
					break;
				}
			}
		}
	}
	return _player;
}
//敌人有很多个所以用数组保存起来
//传入敌人类型来获取
MapItem * GameManage::getEnemy(int enemyType)
{
	this->initEnemyItems();
	size_t size = _enemyItems.size();
	MapItem* enemy = nullptr;
	if (enemyType == -1 && size > 0)
	{
		enemy = _enemyItems.at(0);
	}
	else
	{
		for each (auto item in _enemyItems)
		{
			if (item->getMapType() == enemyType) {
				enemy = item;
				break;
			}
		}
	}
	return enemy;
}

MapItem * GameManage::getEnemy(size_t col, size_t row)
{
	MapItem * enemy = nullptr;
	this->initEnemyItems();
	for each (auto item in _enemyItems)
	{
		size_t c = item->getChild()->getPositionX() / MAP_UTILE;
		size_t r = item->getChild()->getPositionY() / MAP_UTILE;
		if (c == col && row == r)
		{
			enemy = item;
			break;
		}
	}
	return enemy;
}

void GameManage::setStatus(size_t status)
{
	_status = status;
	if (_status == GameStatus::START)
	{
		DirectorUtils::runScene(GameConductScene::createScene());
	}
	EventManager::getIns()->dispatchEvent(EVENT_GAME_STATUS_CHANGE, &_status);
}

void GameManage::initEnemyItems()
{
	size_t size = _enemyItems.size();
	if (size <= 0)
	{
		for each (auto items in this->_mapItems)
		{
			for each (auto item in items)
			{
				if (item->getMapType() == MAP_TYPE::ENEMY) {
					_enemyItems.push_back(item);
				}
			}
		}
	}
}

MapItem * GameManage::getHitMapItem(size_t col, size_t row)
{
	MapItem * item = nullptr;
	if (this->isPlayer(col, row)) {
		item = this->getPlayer();
	}
	else
	{
		item = this->getEnemy(col, row);
	}
	return item;
}
