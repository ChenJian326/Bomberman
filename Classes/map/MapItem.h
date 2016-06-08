#pragma once
#ifndef __MAP_ITEM__H_
#define __MAP_ITEM__H_
#include "cocos2d.h"
USING_NS_CC;
class MapItem
{
public:
	MapItem();
	~MapItem();
	static MapItem* createMapItem(Node* child, size_t mapType);
	size_t getMapType() const { return _mapType; };
	Node* getChild();
	void removeChild();
	void addProp(size_t propType);
private:
	size_t _mapType;
	Node* _child;
};
#endif // !__MAP_ITEM__H_
