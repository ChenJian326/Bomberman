#ifndef __DISPLAY_TOOLS_H__
#define __DISPLAY_TOOLS_H__
#include "cocos2d.h"
#include "lib\MenuItemSpriteLib.h"
USING_NS_CC;
using namespace std;
class DisplayTools
{
public:
	DisplayTools();
	~DisplayTools();
	//创建一个系统字体Label
	static Label* createLabel(const char* str, int fontSize = 18,Vec2 pos = Vec2::ZERO,Vec2 apos = Vec2(0.5,0.5), Color3B color = Color3B::WHITE, TextVAlignment va = TextVAlignment::CENTER, TextHAlignment ha = TextHAlignment::LEFT);
	static Node* createNode(Vec2 pos = Vec2::ZERO,Vec2 apos = Vec2::ANCHOR_MIDDLE);
	static Sprite* createSprite(string textureName,size_t angle = 0, float scale = 1, bool isFlippedX = false, bool isFlippedY = false);
	static MenuItemSprite* createMenuItemSprite(string normal,string selected,string disabled, ccMenuCallback selector);
	static MenuItemSprite* createMenuItemSprite(Sprite* normal, Sprite* selected, Sprite* disabled, ccMenuCallback selector);
	static MenuItemSprite* createMenuItemSprite(Sprite* normal, Sprite* selected, Sprite* disabled, ccMenuCallback selector,std::function<void()> selectedFunc, std::function<void()> unselectedFunc);
private:

};

#endif // !__DISPLAY_TOOLS_H__
