#include "GameFileUtils.h"
#include <new>
#include "config\GmaeConfig.h"
#include "manage\GameManage.h"
GameFileUtils* GameFileUtils::_ins = nullptr;

GameFileUtils::GameFileUtils()
	:_fileUtils(FileUtils::getInstance())
{
}

GameFileUtils::~GameFileUtils()
{
}
GameFileUtils * GameFileUtils::getIns()
{
	if (nullptr == _ins)
	{
		_ins = new(std::nothrow) GameFileUtils();
	}
	return _ins;
}
void GameFileUtils::initCacheData()
{
	if (_gameCachePath.empty())
	{
		_gameCachePath = _fileUtils->getWritablePath().append("/gameCache.data");
	}
	this->getCacheData();
}

ValueMap GameFileUtils::getCacheData()
{
	_vMap =	_fileUtils->getValueMapFromFile(_gameCachePath);
	if (_vMap.empty())
	{
		GameManage::getIns()->setCurrentLevel(1);
	}
	else
	{
		GameManage::getIns()->setCurrentLevel(_vMap[Cache_Current_Level].asInt());
	}
	return _vMap;
}

Value GameFileUtils::getCacheData(std::string k)
{
	Value data = _vMap[k];
	if (data == Value::Null)
	{
		data = -1;
	}
	return data;
}

void GameFileUtils::setCacheData(std::string k, Value v)
{
	_vMap[k] = v;
	_fileUtils->writeValueMapToFile(_vMap, _gameCachePath);
}
