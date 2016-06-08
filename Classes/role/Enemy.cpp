#include "Enemy.h"
#include <new>
#include "props\GameProps.h"
#include "config\GmaeConfig.h"
Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

bool Enemy::init()
{
	if (!RoleNode::init())
	{
		return false;
	}
	_gameManage = GameManage::getIns();
	this->setSpeed(ENEMY_NORMAL_SPEED);
	this->setMoveFunc(std::bind(&Enemy::moveFinish, this, std::placeholders::_1));
	this->setHealth(100);
	return true;
}

Enemy* Enemy::create(int type)
{
	auto enemy = Enemy::create();
	enemy->createRole(g_animationNames.at(type));
	enemy->setEnemyType(type);
	return enemy;
}

void Enemy::moveFinish(Vec2 pos)
{
	auto items = _gameManage->getMapItems();
	size_t row = pos.y;
	size_t col = pos.x;
	if (this->_isPlayer || this->_isBox)
	{
		int propType;
		size_t range;
		switch (this->_enemyType)
		{
		case RoleType::EnemyA:
			propType = PropType::PROP_Z_DAN_1;
			range = 1;
			break;
		case RoleType::EnemyB:
			propType = PropType::PROP_Z_DAN_2;
			range = 2;
			break;
		case RoleType::EnemyC:
			propType = PropType::PROP_Z_DAN_3;
			range = 2;
			break;
		default:
			propType = PropType::PROP_Z_DAN_1;
			break;
		}
		auto prop = GameProps::createProps(propType);
		prop->setExplosionRange(range);
		prop->setPosition(this->getPosition());
		this->getParent()->addChild(prop);
	}
	if (this->_isMove == false)
	{
		this->pathfinding(row, col);
	}
}

void Enemy::pathfinding(size_t row, size_t col)
{
	//寻找其余三个方向
	size_t left = 0, right = 0, top = 0, bootom = 0;
	if (this->getDirection() != Direction::LEFT)
	{
		left = toLeft(row, col);
	}
	if (this->getDirection() != Direction::RIGHT)
	{
		right = toRight(row, col);
	}
	if (this->getDirection() != Direction::TOP)
	{
		top = toTop(row, col);
	}
	if (this->getDirection() != Direction::BOTOOM)
	{
		bootom = toBottom(row, col);
	}
	std::vector<size_t> pathfind = { left ,right ,top ,bootom };
	std::sort(pathfind.begin(), pathfind.end(), [=](size_t num1, size_t num2)->bool {
		return num1 > num2;
	});
	if (pathfind.at(0) == left) {
		this->moveRole(Direction::LEFT, true);
	}
	else if (pathfind.at(0) == right) {
		this->moveRole(Direction::RIGHT, true);
	}
	else if (pathfind.at(0) == top) {
		this->moveRole(Direction::TOP, true);
	}
	else if (pathfind.at(0) == bootom) {
		this->moveRole(Direction::BOTOOM, true);
	}
}

size_t Enemy::toLeft(size_t row, size_t col)
{
	auto items = _gameManage->getMapItems().at(row);
	auto length = items.size();
	size_t num = 0;
	size_t mapType;
	for (size_t i = col; i >= 0; i--)
	{
		mapType = items.at(i)->getMapType();
		if (_gameManage->isEmptyFloor(mapType, row,i)) {
			num++;
		}
		else
		{
			break;
		}
	}
	return num;
}

size_t Enemy::toRight(size_t row, size_t col)
{
	auto items = _gameManage->getMapItems().at(row);
	auto length = items.size();
	size_t num = 0;
	size_t mapType;
	for (size_t i = col; i < length; i++)
	{
		mapType = items.at(i)->getMapType();
		if (_gameManage->isEmptyFloor(mapType, row, i)) {
			num++;
		}
		else
		{
			break;
		}
	}
	return num;
}

size_t Enemy::toTop(size_t row, size_t col)
{
	auto items = _gameManage->getMapItems();
	auto length = items.size();
	size_t num = 0;
	size_t mapType;
	for (size_t i = row; i < length; i++)
	{
		mapType = items.at(i).at(col)->getMapType();
		if (_gameManage->isEmptyFloor(mapType, i, col)) {
			num++;
		}
		else
		{
			break;
		}
	}
	return num;
}

size_t Enemy::toBottom(size_t row, size_t col)
{
	auto items = _gameManage->getMapItems();
	auto length = items.size();
	size_t num = 0;
	size_t mapType;
	for (size_t i = row; i >= 0; i--)
	{
		mapType = items.at(i).at(col)->getMapType();
		if (_gameManage->isEmptyFloor(mapType, i, col)) {
			num++;
		}
		else
		{
			break;
		}
	}
	return num;
}

void Enemy::setEnemyType(int type)
{
	_enemyType = type;
	this->setRoleType(type);
	this->moveRole(Direction::TOP, true);
}


