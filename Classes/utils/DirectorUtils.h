#pragma once
#ifndef __DIRECTOR_UTILS__H_
#define __DIRECTOR_UTILS__H_
#include "cocos2d.h"
USING_NS_CC;

class DirectorUtils
{
public:
	DirectorUtils();
	~DirectorUtils();
	static Size getVisibleSize();
	static void runScene(Scene* scene);
	template <class T>
	static void runScene(T clas);
	static Scene* getRunningScene();
	static float getAnimationInterval();
	static TextureCache* getTextureCache();
private:
	static Director* _director;
};
#endif // !__DIRECTOR_UTILS__H_