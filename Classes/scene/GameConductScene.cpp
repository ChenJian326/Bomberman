#include "GameConductScene.h"
#include "manage\GameManage.h"
#include "utils\VisibleRect.h"
#include "role\PlayerControlNode.h"
GameConductScene::GameConductScene()
{
}

GameConductScene::~GameConductScene()
{
}

Scene * GameConductScene::createScene()
{
	auto scene = Scene::create();
	auto node = GameConductScene::create();
	scene->setName("GameConductScene");
	scene->addChild(node);
	return scene;
}

bool GameConductScene::init()
{
	if (!Node::init()) {
		return false;
	}
	auto visibelSize = VisibleRect::getVisibleRect().size;
	auto bg = Sprite::create("gameScene.png");
	auto bg_x = VisibleRect::center().x + (visibelSize.width - bg->getContentSize().width) * 0.5;
	bg->setPosition(Vec2(bg_x, VisibleRect::center().y));

	_mapView = MapView::createMap(GameManage::getIns()->getCurrentLevel());
	_mapView->setPosition(Vec2(visibelSize.width - _mapView->getMapSize().width, visibelSize.height - _mapView->getMapSize().height));
	auto playerControl = PlayerControlNode::create();
	auto playerControlSize = playerControl->getContentSize();
	playerControl->setPosition(Vec2(playerControlSize.width * 0.5f, playerControlSize.height * 0.5f));
	this->addChild(bg);
	this->addChild(playerControl);
	this->addChild(_mapView);
	return true;
}

void GameConductScene::showMap(size_t level)
{
	GameManage* manage = GameManage::getIns();
	if (manage->getCurrentLevel() == level)
	{
		_mapView->showMap();
	}
	else
	{
		manage->setCurrentLevel(level);
		_mapView->setCurentLevel(level);
	}
}
