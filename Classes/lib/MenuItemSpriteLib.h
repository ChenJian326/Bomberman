#pragma once
#ifndef __MENU_ITEM_SPIRTE_LIB__H_
#define __MENU_ITEM_SPIRTE_LIB__H_
#include "cocos2d.h"
USING_NS_CC;
class MenuItemSpriteLib :public MenuItemSprite
{
public:
	MenuItemSpriteLib();
	~MenuItemSpriteLib();
	static MenuItemSpriteLib* createMenuItemSpriteLib(Sprite * normal, Sprite * selected, Sprite * disabled, ccMenuCallback selector, std::function<void()> selectedFunc, std::function<void()> unselectedFunc);
	virtual bool init();
	CREATE_FUNC(MenuItemSpriteLib);
private:
	virtual void selected() override;
	virtual void unselected() override;
	std::function<void()> _selectedFunc;
	std::function<void()> _unselectedFunc;
};


#endif // !__MENU_ITEM_SPIRTE_LIB__H_

