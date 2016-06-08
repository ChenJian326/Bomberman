#include "MapItem.h"
#include "config\MapConfig.h"
#include "props\GameProps.h"
#include <new>
MapItem::MapItem()
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

void MapItem::removeChild()
{
	if (this->_child)
	{
		this->_child->removeFromParent();
	}
	this->_mapType = MAP_TYPE::EMPTY;
	this->_child = nullptr;
}
//请在remove之前添加
void MapItem::addProp(size_t propType)
{
	if (this->_child)
	{
		auto prop = GameProps::createProps(propType);
		prop->setPosition(this->_child->getPosition());
		this->_child->getParent()->addChild(prop);
	}
}
