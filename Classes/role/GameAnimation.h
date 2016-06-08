#pragma once
#ifndef __ROLE_ANIMATION__H_
#define __ROLE_ANIMATION__H_
#include "cocos2d.h"
USING_NS_CC;
class GameAnimation : public Node
{
public:
	GameAnimation();
	~GameAnimation();
	virtual bool init();
	static GameAnimation* creatAnimation(std::vector<std::string> names);
	static GameAnimation* creatAnimation(std::vector<std::vector<std::string>> names);
	void play(float duration, int loop,size_t playId);//duration秒为单位  循环次数-1表示无限循环
	void play(float duration,int loop);//duration秒为单位  循环次数-1表示无限循环
	void play();
	void stop();
	void gotoAndStop(size_t frame);
	void gotoAndPlay(size_t frame);
	void setFlippedX(bool flippedX);
	void setFlippedY(bool flippedY);
	void setFinishFunc(std::function<void()> finishCallBackFunc);
	bool getFlippedX() const { return _flippedX; };
	bool getFlippedY() const { return _flippedY; };
	size_t getCurrentFrame() const {return _currentFrame; };
	size_t getTotalFrame() const { return _totalFrame; };
	bool isPlay() const { return _isPlay; };
	// implement the "static create()" method manually
	CREATE_FUNC(GameAnimation);
private:
	std::vector<std::string> _animationNames;
	std::vector<std::vector<std::string>> _animationNameVers;
	std::function<void()> _finishCallBackFunc;
	void setAnimationNames(std::vector<std::string> names);
	void setAnimationNames(std::vector<std::vector<std::string>> names);
	void setCurrentFrame(size_t frame);
	void setTotalFrame(size_t frame);
	void updateFrame(float dt);
	void runFinishCallBackFunc();
	size_t _currentFrame;
	size_t _totalFrame;
	Sprite* _animation;
	float _duration;
	int _loop;
	bool _flippedX;
	bool _flippedY;
	bool _isPlay;
};

#endif // !__ROLE_ANIMATION__H_