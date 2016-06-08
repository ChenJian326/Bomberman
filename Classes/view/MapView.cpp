#include "MapView.h"
#include "role\Player.h"
#include "role\Enemy.h"
#include "map\MapItem.h"
#include <new>
MapView::MapView()
	:_currentlevel(1)
{
}

MapView::~MapView()
{
}

MapView * MapView::createMap(size_t level)
{
	auto map = MapView::create();
	map->setCurentLevel(level);
	return map;
}

bool MapView::init()
{
	if (!Node::init()) {
		return false;
	}
	_manage = GameManage::getIns();
	return true;
}

void MapView::setCurentLevel(size_t level)
{
	_currentlevel = level;
	_nextlevel = _currentlevel + 1;
	auto map = getMap(_currentlevel);
	_vMaps.clear();
	_vMaps.insert(_vMaps.end(), map.begin(), map.end());
	_manage->setGameMapData(_vMaps);
	if (!_vMaps.empty())
	{
		this->showMap();
	}
}

void MapView::showMap()
{
	this->removeAllChildren();
	auto ROW = MAP_ROW_NUMBER - 1;
	for (size_t row = 0; row < MAP_ROW_NUMBER; row++)
	{
		for (size_t column = 0; column < MAP_COLUMN_NUMBER; column++)
		{
			switch (_vMaps[ROW - row][column])
			{
			case MAP_TYPE::EMPTY:
				this->addMapItem(nullptr, MAP_TYPE::EMPTY, row);
				break;
			case MAP_TYPE::BOX:
				drawBox(row, column);
				break;
			case MAP_TYPE::FLOOR:
				drawFloor(row, column);
				break;
			case MAP_TYPE::PROPS:
				drawBox(row, column);
				break;
			case MAP_TYPE::PLAYER:
				drawPlayer(row, column);
				break;
			case MAP_TYPE::ENEMY:
				drawEnemy(row, column);
				break;
			default:
				break;
			}
		}
	}
}
//绘制木箱
void MapView::drawBox(size_t row, size_t col) {
	auto box = Sprite::create("map2.png");
	box->setPosition(Vec2(col * MAP_UTILE, row * MAP_UTILE));
	this->addMapItem(box, MAP_TYPE::BOX, row);
}
//绘制地板
void MapView::drawFloor(size_t row, size_t col) {
	auto floor = Sprite::create("map1.png");
	floor->setPosition(Vec2(col * MAP_UTILE, row * MAP_UTILE));
	this->addMapItem(floor, MAP_TYPE::FLOOR, row);
}
//绘制主角
void MapView::drawPlayer(size_t row, size_t col) {
	auto player = Player::create();
	player->setPosition(Vec2(col * MAP_UTILE, row * MAP_UTILE));
	this->addMapItem(player, MAP_TYPE::PLAYER, row);
}
//绘制敌人
void MapView::drawEnemy(size_t row, size_t col) {
	auto enemyType = _manage->getCurrentLevel()  == 1 ? RoleType::EnemyA : random(1,3);
	Enemy* enemy = Enemy::create(enemyType);
	enemy->setPosition(Vec2(col * MAP_UTILE, row  * MAP_UTILE));
	this->addMapItem(enemy, MAP_TYPE::ENEMY, row);
}

void MapView::addMapItem(Node * child, int mapType, size_t row)
{
	auto mapItem = MapItem::createMapItem(child, mapType);
	_manage->pushMapItem(mapItem, row);
	if (mapItem->getChild())
		this->addChild(mapItem->getChild());
}

