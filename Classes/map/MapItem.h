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
	Node* getProps();
	void clear();
	void removeChild();
	void addProp(size_t propType);
	void removeProps();
	bool isDeath();
	void InjuryRole(int value);
private:
	size_t _mapType;
	Node* _child;
	Node* _props;
};
#endif // !__MAP_ITEM__H_
