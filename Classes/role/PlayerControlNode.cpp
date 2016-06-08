#include "PlayerControlNode.h"
#include "utils\DisplayTools.h"
#include "utils\VisibleRect.h"
#include "manage\EventManager.h"
#include "config\GmaeConfig.h"
PlayerControlNode::PlayerControlNode()
{
}

PlayerControlNode::~PlayerControlNode()
{
}

bool PlayerControlNode::init()
{
	if (!Node::init()) {
		return false;
	}
	
	auto bg = Sprite::create("control.png");
	this->addChild(bg);
	float scale = 0.6f;
	float imgw = 128 * 0.9f;
	auto menuItemLeft = DisplayTools::createMenuItemSprite(DisplayTools::createSprite("resume.png"), nullptr, nullptr, CC_CALLBACK_1(PlayerControlNode::toLeft, this), [this]() {this->toLeftKeybod(); }, [this]() {this->toStop(); });
	menuItemLeft->setPosition(Vec2(-imgw, 0));
	menuItemLeft->setRotation(180);

	auto menuItemRight = DisplayTools::createMenuItemSprite(DisplayTools::createSprite("resume.png"), nullptr, nullptr, CC_CALLBACK_1(PlayerControlNode::toRight, this), [this]() {this->toRightKeybod(); }, [this]() {toStop(); });
	menuItemRight->setPosition(Vec2(imgw, 0));
	
	auto menuItemTop = DisplayTools::createMenuItemSprite(DisplayTools::createSprite("resume.png"), nullptr, nullptr, CC_CALLBACK_1(PlayerControlNode::toTop, this), [this]() {this->toTopKeybod(); }, [this]() {this->toStop(); });
	menuItemTop->setPosition(Vec2(0, imgw ));
	menuItemTop->setRotation(270);

	auto menuItemBottom = DisplayTools::createMenuItemSprite(DisplayTools::createSprite("resume.png"), nullptr, nullptr, CC_CALLBACK_1(PlayerControlNode::toBottom, this), [this]() {this->toBottomKeybod(); }, [this]() {this->toStop(); });
	menuItemBottom->setPosition(Vec2(0, -imgw));
	menuItemBottom->setRotation(90);

	auto menuItemPutbomb = DisplayTools::createMenuItemSprite(DisplayTools::createSprite("levelSelect.png"), nullptr, nullptr, CC_CALLBACK_1(PlayerControlNode::putBomb, this),nullptr,nullptr);
	auto menu = Menu::create(menuItemLeft, menuItemRight, menuItemTop, menuItemBottom, menuItemPutbomb, nullptr);
	menu->setPosition(Vec2(-390.0f * 0.5, -260.0f * 0.5));
	menu->setScale(scale);
	this->addChild(menu);
	this->initListener();
	this->setContentSize(Size(260.0f, 260.0f));
	CCLOG("width = %f height = %f",this->getBoundingBox().size.width, this->getContentSize().height);
	return true;
}

void PlayerControlNode::initListener()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayerControlNode::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayerControlNode::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void PlayerControlNode::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		this->toLeftKeybod();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		this->toRightKeybod();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		this->toTopKeybod();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		this->toBottomKeybod();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		this->putBombKeybod();
		break;
	default:
		break;
	}
	//CCLOG("pressed keyCode = %d", keyCode);
}

void PlayerControlNode::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		this->toStop();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		this->toStop();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		this->toStop();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		this->toStop();
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		this->toStop();
		break;
	default:
		break;
	}
	//CCLOG("released keyCode = %d", keyCode);
}

void PlayerControlNode::toLeftKeybod()
{
	int left = static_cast<int>(Direction::LEFT);
	EventManager::getIns()->dispatchEvent(EVENT_PLAYER_MOVE, &left);
}

void PlayerControlNode::toRightKeybod()
{
	int right = static_cast<int>(Direction::RIGHT);
	EventManager::getIns()->dispatchEvent(EVENT_PLAYER_MOVE, &right);
}

void PlayerControlNode::toTopKeybod()
{
	int top = static_cast<int>(Direction::TOP);
	EventManager::getIns()->dispatchEvent(EVENT_PLAYER_MOVE, &top);
}

void PlayerControlNode::toBottomKeybod()
{
	int botoom = static_cast<int>(Direction::BOTOOM);
	EventManager::getIns()->dispatchEvent(EVENT_PLAYER_MOVE, &botoom);
}

void PlayerControlNode::putBombKeybod()
{
	EventManager::getIns()->dispatchEvent(EVENT_PLAYER_PUT_BOMB, nullptr);
}

void PlayerControlNode::toLeft(Ref * sender)
{
	//this->toLeftKeybod();
}

void PlayerControlNode::toRight(Ref * sender)
{
	//this->toRightKeybod();
}

void PlayerControlNode::toTop(Ref * sender)
{
	//this->toTopKeybod();
}

void PlayerControlNode::toBottom(Ref * sender)
{
	//this->toBottomKeybod();
}

void PlayerControlNode::putBomb(Ref * sender)
{
	this->putBombKeybod();
}

void PlayerControlNode::toStop()
{
	int stop = static_cast<int>(Direction::STOP);
	EventManager::getIns()->dispatchEvent(EVENT_PLAYER_MOVE, &stop);
}
