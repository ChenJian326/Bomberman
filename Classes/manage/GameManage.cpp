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
}

void GameManage::endGame()
{
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
			delete item;
		}
	}
	this->_mapItems.clear();
}

void GameManage::clearMapItem(size_t row, size_t col)
{
	auto item = this->_mapItems[row][col];
	auto mapType = this->_gameMapData[MAP_ROW_NUMBER - row - 1][col];
	if (mapType == MAP_TYPE::PROPS && item->getMapType() == MAP_TYPE::BOX)
	{
		size_t propType = random(0, 2);
		item->addProp(propType);
		item->removeChild();
	}
	else if(item->getMapType() == MAP_TYPE::PLAYER || item->getMapType() == MAP_TYPE::ENEMY)
	{

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

void GameManage::addBomb(size_t row, size_t col)
{
}


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
		size_t c = player->getPositionX() / MAP_UTILE;
		size_t r = player->getPositionY() / MAP_UTILE;
		if (c == col && row == r)
		{
			isPlayer = true;
		}
	}
	return isPlayer;
}

Node * GameManage::getPlayer()
{
	if (nullptr == _player)
	{
		for each (auto items in this->_mapItems)
		{
			for each (auto item in items)
			{
				if (item->getMapType() == MAP_TYPE::PLAYER) {
					_player = item->getChild();
					break;
				}
			}
		}
	}
	return _player;
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
