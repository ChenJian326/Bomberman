#include "GameProps.h"
#include "config\MapConfig.h"
#include "manage\GameManage.h"
#define PLAY_TIME  6

GameProps::GameProps()
	:_explosionRange(0),
	_injuryValue(0)
{
}

GameProps::~GameProps()
{
}
GameProps * GameProps::createProps(const size_t propType)
{
	auto props = GameProps::create();
	props->setPropType(propType);
	return props;
}

void GameProps::playExplosionAnimation(const Direction dir, size_t range)
{
	if (this->_propType <= PropType::PROP_XIE_Z_DAN || range <= 0)
	{
		return;
	}

	auto sprite = Sprite::create(PROP_NAMES[this->_propType]);
	Vec2 pos;
	switch (dir)
	{
	case Direction::LEFT:
		pos = Vec2(range * MAP_UTILE, 0);
		pos.x = -pos.x;
		break;
	case Direction::RIGHT:
		pos = Vec2(range * MAP_UTILE, 0);
		break;
	case Direction::TOP:
		pos = Vec2(0, range * MAP_UTILE);
		break;
	case Direction::BOTOOM:
		pos = Vec2(0, range * MAP_UTILE);
		pos.y = -pos.y;
		break;
	}
	sprite->setPosition(pos);
	this->addChild(sprite);
}

void GameProps::playExplosion()
{
	auto manage = GameManage::getIns();
	auto pos = this->getPosition();
	auto items = manage->getMapItems();
	size_t row = round(pos.y / MAP_UTILE);
	size_t col = round(pos.x / MAP_UTILE);
	for (size_t i = 1; i <= _explosionRange; i++)
	{
		auto leftItem = items[row][col - i];
		auto rightItem = items[row][col + i];
		auto topItem = items[row + i][col];
		auto bottomItem = items[row - i][col];
		if (leftItem->getMapType() != MAP_TYPE::FLOOR) {
			this->playExplosionAnimation(Direction::LEFT, i);
			manage->clearMapItem(leftItem, _injuryValue, col - i, row);
		}
		if (rightItem->getMapType() != MAP_TYPE::FLOOR) {
			this->playExplosionAnimation(Direction::RIGHT, i);
			manage->clearMapItem(rightItem, _injuryValue, col + i, row);
		}
		if (topItem->getMapType() != MAP_TYPE::FLOOR) {
			this->playExplosionAnimation(Direction::TOP, i);
			manage->clearMapItem(topItem, _injuryValue, col, row + i);
		}
		if (bottomItem->getMapType() != MAP_TYPE::FLOOR) {
			this->playExplosionAnimation(Direction::BOTOOM, i);
			manage->clearMapItem(bottomItem, _injuryValue, col, row - i);
		}
	}
}

void GameProps::setPropType(size_t type)
{
	this->_propType = type;
	if (this->_propType <= PropType::PROP_XIE_Z_DAN)
	{
		this->_gameProp = Sprite::create(PROP_NAMES[type]);
	}
	else
	{
		std::vector<int> injuryValue = PROP_Z_DAN_VALUE.at(type - 2);
		_injuryValue = random(injuryValue.at(0), injuryValue.at(1));
		this->_gameProp = GameAnimation::creatAnimation(PROP_Z_DAN[type - 3]);
		dynamic_cast<GameAnimation*>(this->_gameProp)->play(PLAY_TIME, 1);
		dynamic_cast<GameAnimation*>(this->_gameProp)->setFinishFunc(std::bind(&GameProps::animationFinish, this));
	}
	this->addChild(this->_gameProp);
}

void GameProps::setExplosionRange(size_t range)
{
	_explosionRange = range;
}

inline bool GameProps::init()
{
	if (!Node::init()) {
		return false;
	}
	return true;
}

void GameProps::animationFinish()
{
	this->playExplosion();
	this->runAction(
		Sequence::create(
			DelayTime::create(0.3f),
			RemoveSelf::create(),
			nullptr));
}
