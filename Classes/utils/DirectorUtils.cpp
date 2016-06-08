#include "DirectorUtils.h"
Director* DirectorUtils::_director = Director::getInstance();
DirectorUtils::DirectorUtils()
{
}

DirectorUtils::~DirectorUtils()
{
}

Size DirectorUtils::getVisibleSize()
{
	auto visibleSize = _director->getVisibleSize();
	return visibleSize;
}

void DirectorUtils::runScene(Scene * scene)
{
	if (_director->getRunningScene())
	{
		_director->replaceScene(scene);
	}
	else
	{
		_director->runWithScene(scene);
	}
}
template <class T>
void DirectorUtils::runScene(T clas)
{
	auto scene = clas::createScene();
	if (nullptr != scene)
	{
		DirectorUtils::runScene(scene);
	}
}

Scene * DirectorUtils::getRunningScene()
{
	return _director->getRunningScene();
}

float DirectorUtils::getAnimationInterval()
{
	return _director->getAnimationInterval();
}

TextureCache * DirectorUtils::getTextureCache()
{
	return _director->getTextureCache();
}