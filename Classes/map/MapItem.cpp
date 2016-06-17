#include "MapItem.h"
#include "config\MapConfig.h"
#include "props\GameProps.h"
#include "role\RoleNode.h"
#include <new>
MapItem::MapItem()
	:_child(nullptr),
	_props(nullptr)
{
}

MapItem::~MapItem()
{
	removeChild();
}

MapItem * MapItem::createMapItem(Node * child, size_t mapType)
{
	auto item = new(std::nothrow) MapItem();
	item->_child = child;
	item->_mapType = mapType;
	return item;
}

Node * MapItem::getChild()
{
	return this->_child;
}

Node * MapItem::getProps()
{
	return this->_props;
}

void MapItem::clear()
{
	this->removeChild();
	this->removeProps();
	_mapType = MAP_TYPE::EMPTY;
}

void MapItem::removeChild()
{
	if (this->_child)
	{
		this->_child->removeFromParent();
	}
	this->_child = nullptr;
}

//请在remove之前添加
void MapItem::addProp(size_t propType)
{
	if (this->_child)
	{
		_mapType = MAP_TYPE::PROPS;
		_props = GameProps::createProps(propType);
		_props->setPosition(this->_child->getPosition());
		this->_child->getParent()->addChild(_props);
	}
}
//请在remove之前添加
void MapItem::removeProps()
{
	if (this->_props)
	{
		_props->removeFromParent();
		_props = nullptr;
	}
}

bool MapItem::isDeath()
{
	auto item = dynamic_cast<RoleNode*>(this->getChild());
	if (item)
	{
		return item->isDeath();
	}
	return false;
}

void MapItem::InjuryRole(int value)
{
	auto item = dynamic_cast<RoleNode*>(this->getChild());
	if (item)
	{
		int health = item->getTotalHealth() - value;
		item->setHealth(size_t(health));
	}
}
