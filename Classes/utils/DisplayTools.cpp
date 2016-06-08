#include "DisplayTools.h"
#include "config\GmaeConfig.h"

DisplayTools::DisplayTools()
{
}

DisplayTools::~DisplayTools()
{
}

Label * DisplayTools::createLabel(const char * str, int fontSize, Vec2 pos, Vec2 apos, Color3B color, TextVAlignment va, TextHAlignment ha)
{
	auto label = Label::createWithSystemFont(str, GAME_FONE_NAME, fontSize, Size::ZERO);
	label->setColor(color);
	label->setPosition(pos);
	label->setAnchorPoint(apos);
	label->setVerticalAlignment(va);
	label->setHorizontalAlignment(ha);
	return label;
}

Node * DisplayTools::createNode(Vec2 pos, Vec2 apos)
{
	auto node = Node::create();
	node->setPosition(pos);
	node->setAnchorPoint(apos);
	return node;
}

Sprite * DisplayTools::createSprite(string textureName, size_t angle, float scale, bool isFlippedX, bool isFlippedY)
{
	auto sprite = Sprite::create(textureName);
	sprite->setFlippedX(isFlippedX);
	sprite->setFlippedY(isFlippedY);
	sprite->setRotation(angle);
	sprite->setScale(scale);
	return sprite;
}

MenuItemSprite * DisplayTools::createMenuItemSprite(string normal, string selected, string disabled, ccMenuCallback selector)
{
	auto normals = DisplayTools::createSprite(normal);
	auto selecteds = DisplayTools::createSprite(selected);
	auto disableds = DisplayTools::createSprite(disabled);
	auto itemSprite = MenuItemSprite::create(normals, selecteds, disableds, selector);
	return itemSprite;
}

MenuItemSprite * DisplayTools::createMenuItemSprite(Sprite * normal, Sprite * selected, Sprite * disabled, ccMenuCallback selector, std::function<void()> selectedFunc, std::function<void()> unselectedFunc)
{
	MenuItemSprite* itemSprite = nullptr;
	if (nullptr == selectedFunc)
	{
		itemSprite = DisplayTools::createMenuItemSprite(normal, selected, disabled, selector);
	}
	else
	{
		itemSprite = MenuItemSpriteLib::createMenuItemSpriteLib(normal, selected, disabled, selector, selectedFunc, unselectedFunc);
	}
	return itemSprite;
}

MenuItemSprite * DisplayTools::createMenuItemSprite(Sprite * normal, Sprite * selected, Sprite * disabled, ccMenuCallback selector)
{
	if (normal && nullptr == selected)
	{
		selected = Sprite::create(normal->getResourceName());
		selected->setScale(normal->getScale() - 0.1);
	}
	auto itemSprite = MenuItemSprite::create(normal, selected, disabled, selector);
	return itemSprite;
}


