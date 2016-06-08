#pragma once
#ifndef __PLAYER_CONTROL_NODE__H_
#define __PLAYER_CONTROL_NODE__H_
#include "cocos2d.h"
USING_NS_CC;
class PlayerControlNode :public Node
{
public:
	PlayerControlNode();
	~PlayerControlNode();
	virtual bool init();
	CREATE_FUNC(PlayerControlNode);
private:
	void initListener();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void toLeftKeybod();
	void toRightKeybod();
	void toTopKeybod();
	void toBottomKeybod();
	void putBombKeybod();

	void toLeft(Ref* sender);
	void toRight(Ref* sender);
	void toTop(Ref* sender);
	void toBottom(Ref* sender);
	void putBomb(Ref* sender);
	void toStop();
};

#endif // !__PLAYER_CONTROL_NODE__H_
