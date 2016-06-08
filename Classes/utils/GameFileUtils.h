#pragma once
#ifndef __GAME_FILE_UTILS__H_
#define __GAME_FILE_UTILS__H_
#include "cocos2d.h"
USING_NS_CC;
class GameFileUtils
{
public:
	GameFileUtils();
	~GameFileUtils();
	static GameFileUtils* getIns();
	void initCacheData();
	ValueMap getCacheData();
	Value getCacheData(std::string k);
	void setCacheData(std::string k,Value v);
	std::string getGameCachePath() const { return _gameCachePath; };
private:
	std::string _gameCachePath;
	static GameFileUtils* _ins;
	FileUtils* _fileUtils;
	ValueMap _vMap;
};



#endif // !__GAME_FILE_UTILS__H_