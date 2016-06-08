#include "Player.h"
#include "manage\EventManager.h"
#include "config\MapConfig.h"
#include "map\MapItem.h"
#include "props\GameProps.h"
#include <new>

Player::Player()
{
}

Player::~Player()
{
}

bool Player::init()
{
	if (!RoleNode::init())
	{
		return false;
	}
	_gameManage = GameManage::getIns();
	this->createRole(g_animationNames.at(RoleType::Player));
	this->setRoleType(RoleType::Player);
	this->moveRole(Direction::STOP);
	this->setSpeed(PLAYER_NORMAL_SPEED);
	this->setHealth(100);
	this->initListener();
	this->setMoveFunc(std::bind(&Player::moveFinish, this, std::placeholders::_1));
	return true;
}

void Player::initListener()
{
	auto eventManage = EventManager::getIns();
	eventManage->addEventListener(EVENT_PLAYER_MOVE, "", [=](EventCustom* event) {
		auto direction = *(int*)event->getUserData();
		Direction dir = static_cast<Direction>(direction);
		this->moveRole(dir, true);
	}, this);
	eventManage->addEventListener(EVENT_PLAYER_PUT_BOMB, "", [=](EventCustom* event) {
		auto prop = GameProps::createProps(PropType::PROP_Z_DAN_1);
		prop->setPosition(this->getPosition());
		this->getParent()->addChild(prop);
	}, this);
}

void Player::moveFinish(Vec2 pos)
{
	/*auto items = _gameManage->getMapItems();*/
	Vec2 vec2 = this->getColAndRow(pos);
	size_t row = vec2.y;
	size_t col = vec2.x;
	//用来矫正位置
	switch (this->getDirection())
	{
	case Direction::RIGHT:
		this->setPositionY(row * MAP_UTILE);
		break;
	case Direction::LEFT:
		this->setPositionY(row * MAP_UTILE);
		break;
	case Direction::BOTOOM:
		this->setPositionX(col * MAP_UTILE);
		break;
	case Direction::TOP:
		this->setPositionX(col * MAP_UTILE);
		break;
	}
}


