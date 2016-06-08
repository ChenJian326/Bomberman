#include "MenuItemSpriteLib.h"

MenuItemSpriteLib::MenuItemSpriteLib()
{
}

MenuItemSpriteLib::~MenuItemSpriteLib()
{
}

MenuItemSpriteLib * MenuItemSpriteLib::createMenuItemSpriteLib(Sprite * normal, Sprite * selected, Sprite * disabled, ccMenuCallback selector, std::function<void()> selectedFunc, std::function<void()> unselectedFunc)
{
	auto itemSprite = MenuItemSpriteLib::create();
	itemSprite->setNormalImage(normal);
	itemSprite->setSelectedImage(selected);
	itemSprite->setDisabledImage(disabled);
	itemSprite->initWithCallback(selector);
	itemSprite->_selectedFunc = selectedFunc;
	itemSprite->_unselectedFunc = unselectedFunc;
	return itemSprite;
}

bool MenuItemSpriteLib::init()
{
	if (!MenuItemSprite::init())
		return false;
	return true;
}

void MenuItemSpriteLib::selected()
{
	MenuItemSprite::selected();
	this->_selectedFunc();
}

void MenuItemSpriteLib::unselected()
{
	MenuItemSprite::unselected();
	this->_unselectedFunc();
}
