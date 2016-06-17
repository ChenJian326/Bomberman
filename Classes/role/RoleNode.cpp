#include "RoleNode.h"
#include "manage\GameManage.h"
RoleNode::RoleNode()
	:_health(0),
	_speed(0),
	_isDeath(false),
	_isBox(false),
	_isMove(true),
	_isPlayer(false),
	_TotalHealth(0)
{
}

RoleNode::~RoleNode()
{
}

bool RoleNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}
void RoleNode::createRole(std::vector<std::vector<std::string>> names) {
	_roleAnimation = GameAnimation::creatAnimation(names);
	this->addChild(_roleAnimation);
}
void RoleNode::createRole(std::vector<std::string> names)
{
	_roleAnimation = GameAnimation::creatAnimation(names);
	this->addChild(_roleAnimation);
}

void RoleNode::moveRole(Direction direction, bool isAutoMove)
{
	if (nullptr == _roleAnimation)
	{
		return;
	}
	_currentDirection = direction;
	bool flippedX = _roleAnimation->getFlippedX();
	_roleAnimation->setFlippedX(false);
	_moveY = _moveX = this->_speed;
	_roleBiasPos = Vec2(0, 0);
	switch (direction)
	{
	case Direction::LEFT:
		_roleAnimation->setFlippedX(true);
		_moveX = -_moveX;
		_moveY = 0.0F;
		_roleBiasPos.set(ROLE_SIZE.width, 0);
		_roleAnimation->play(ANIMMATION_PLAY_TIME, -1, 0);
		break;
	case Direction::RIGHT:
		_moveX = abs(_moveX);
		_moveY = 0.0F;
		_roleAnimation->play(ANIMMATION_PLAY_TIME, -1, 0);
		break;
	case Direction::BOTOOM:
		_moveX = 0.0F;
		_moveY = -_moveY;
		_roleBiasPos.set(0, ROLE_SIZE.height);
		_roleAnimation->play(ANIMMATION_PLAY_TIME, -1, 1);
		break;
	case Direction::TOP:
		_moveX = 0.0F;
		_moveY = abs(_moveY);
		_roleAnimation->play(ANIMMATION_PLAY_TIME, -1, 2);
		break;
	case Direction::STOP:
		_roleAnimation->setFlippedX(flippedX);
		_roleAnimation->gotoAndStop(2);
		break;
	default:
		break;
	}
	if (isAutoMove) {
		if (direction != Direction::STOP)
		{
			this->startMove();
		}
		else
		{
			this->stopMove();
		}
	}
}

void RoleNode::setMoveFunc(std::function<void(Vec2 pos)> moveFunc)
{
	_moveFunc = moveFunc;
}


void RoleNode::setSpeed(size_t speed)
{
	this->_speed = speed;
}

void RoleNode::roleDeath()
{
	if (nullptr == this->getChildByName("animation")) {
		auto animation = Sprite::create("player_die.png");
		Vec2 pos = this->getPosition();
		Sequence *seq = Sequence::create(
			Spawn::create(
				MoveTo::create(0.1f, Vec2(pos.x - 10, pos.y + 80)),
				FadeOut::create(0.1f)),
			RemoveSelf::create(),
			nullptr
		);
		animation->runAction(seq);
		this->addChild(animation, 1, "animation");
	}
}

void RoleNode::setHealth(size_t health)
{
	this->_health = health;
	this->_isDeath = this->_health <= 0;
	CCLOG("health = %d", health);
	if (this->_isDeath)
		this->roleDeath();
}

void RoleNode::setRoleType(int type)
{
	_roleType = type;
}

Vec2 RoleNode::getColAndRow(Vec2 colRow)
{
	auto col = colRow.x;
	auto row = colRow.y;
	switch (this->getDirection())
	{
	case Direction::RIGHT:
		col = col < MAP_COLUMN_NUMBER - 1 ? col + 1 : col;
		row = round(row);
		break;
	case Direction::LEFT:
		col = col > 0 ? col - 1 : col;
		row = round(row);
		break;
	case Direction::BOTOOM:
		row = row > 0 ? row - 1 : row;
		col = round(col);
		break;
	case Direction::TOP:
		row = row < MAP_ROW_NUMBER - 1 ? row + 1 : row;
		col = round(col);
		break;
	}
	return Vec2(col, row);
}

void RoleNode::startMove()
{
	if (!this->isScheduled(CC_SCHEDULE_SELECTOR(RoleNode::updateMovePos)))
	{
		this->schedule(CC_SCHEDULE_SELECTOR(RoleNode::updateMovePos), 0.1f);
	}
}

void RoleNode::stopMove()
{
	if (this->isScheduled(CC_SCHEDULE_SELECTOR(RoleNode::updateMovePos)))
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(RoleNode::updateMovePos));
	}
}

bool RoleNode::isMove(Vec2 pos)
{
	_isMove = false;
	auto manager = GameManage::getIns();
	auto items = manager->getMapItems();
	auto row = pos.y / MAP_UTILE;
	auto col = pos.x / MAP_UTILE;
	_rowAndCol = Vec2(col, row);
	if ((size_t)row < 0 || (size_t)col < 0 || (size_t)row >= MAP_ROW_NUMBER || (size_t)col >= MAP_COLUMN_NUMBER)
	{
		_isMove = false;
	}
	else
	{
		Vec2 vec2 = this->getColAndRow(_rowAndCol);
		row = (size_t)vec2.y;
		col = (size_t)vec2.x;
		
		auto item = items[row][col];
		_isMove = manager->isEmptyFloor(item->getMapType(), row,col);
		_isBox = manager->isBox(item->getMapType()) || (item->getMapType() == MAP_TYPE::PROPS && item->getChild());
		_isPlayer = manager->isPlayer(col,row);
		manager->collectProps(item, col, row);
		CCLOG("<Player::isMove>row = %d  col = %d", (size_t)row, (size_t)col);
	}
	return _isMove;
}

void RoleNode::updateMovePos(float dt)
{
	Vec2 pos = this->getPosition();
	Vec2 movePos = Vec2(pos.x + _moveX + _roleBiasPos.x, pos.y + _moveY + _roleBiasPos.y);
	if (this->isMove(movePos)) {
		this->setPosition(movePos.x - _roleBiasPos.x, movePos.y - _roleBiasPos.y);
		if (this->_moveFunc)
			this->_moveFunc(_rowAndCol);
	}
	else {
		this->stopMove();
		if (this->_moveFunc)
			this->_moveFunc(_rowAndCol);
	}
}

void RoleNode::setTotalHealth(size_t health)
{
	this->_TotalHealth = health;
}
