#include "GameAnimation.h"
#include "utils\DirectorUtils.h"
#include <new>

GameAnimation::GameAnimation()
	:_currentFrame(1),
	_totalFrame(1),
	_isPlay(false)
{
}

GameAnimation::~GameAnimation()
{
}
GameAnimation * GameAnimation::creatAnimation(std::vector<std::string> names)
{
	auto role = GameAnimation::create();
	role->setAnimationNames(names);
	return role;
}

GameAnimation * GameAnimation::creatAnimation(std::vector<std::vector<std::string>> names)
{
	auto role = GameAnimation::create();
	role->setAnimationNames(names);
	return role;
}

void GameAnimation::setAnimationNames(std::vector<std::string> names)
{
	_animationNames.clear();
	_animationNames.insert(_animationNames.end(), names.begin(), names.end());
	this->setTotalFrame(_animationNames.size());
}
void GameAnimation::setAnimationNames(std::vector<std::vector<std::string>> names)
{
	_animationNameVers.clear();
	_animationNameVers.insert(_animationNameVers.end(), names.begin(), names.end());
	if (_animationNameVers.size() > 0)
		this->setAnimationNames(_animationNameVers.at(0));
	this->gotoAndStop(1);
}


void GameAnimation::play(float duration, int loop, size_t playId)
{
	if (playId > _animationNameVers.size())
	{
		playId = _animationNameVers.size() > 0 ? _animationNameVers.size() - 1 : -1;
	}
	if (0 > playId) {
		CCLOG("not animation play id");
		return;
	}
	auto names = this->_animationNameVers.at(playId);
	this->setAnimationNames(names);
	this->play(duration, loop);
}

void GameAnimation::play()
{
	this->play(1, -1);
}
void GameAnimation::play(float duration, int loop)
{
	_duration = duration;
	_loop = loop;
	this->stop();
	this->gotoAndPlay(1);
	_isPlay = true;
}

void GameAnimation::stop()
{
	if (_isPlay)
		this->gotoAndStop(this->getCurrentFrame());
}

bool GameAnimation::init()
{
	if (!Node::init()) {
		return false;
	}
	_animation = Sprite::create("CloseNormal.png");
	this->setFlippedX(_animation->isFlippedX());
	this->setFlippedY(_animation->isFlippedY());
	this->addChild(_animation);
	return true;
}

void GameAnimation::gotoAndStop(size_t frame)
{
	if (0 >= frame || frame > this->getTotalFrame())
	{
		frame = this->getTotalFrame();
	}
	this->setCurrentFrame(frame);
	this->updateFrame(0.0);
	if (this->isScheduled(CC_SCHEDULE_SELECTOR(GameAnimation::updateFrame))) {
		this->unschedule(CC_SCHEDULE_SELECTOR(GameAnimation::updateFrame));
	}
	_isPlay = false;
}

void GameAnimation::gotoAndPlay(size_t frame)
{
	if (0 >= frame || frame > this->getTotalFrame())
	{
		frame = this->getTotalFrame();
	}
	this->setCurrentFrame(frame);
	float interval = _duration / 60;
	if (-1 == _loop) {
		this->schedule(CC_SCHEDULE_SELECTOR(GameAnimation::updateFrame), interval);
	}
	else {
		_loop = _loop * this->getTotalFrame() - 1;//这个选择器将会被执行的次数（repeat+1）,所以需要-1
		this->schedule(CC_SCHEDULE_SELECTOR(GameAnimation::updateFrame), interval, _loop, 0.0f);
	}
}

void GameAnimation::setFlippedX(bool flippedX)
{
	this->_flippedX = flippedX;
}

void GameAnimation::setFlippedY(bool flippedY)
{
	this->_flippedY = flippedY;
}

void GameAnimation::setFinishFunc(std::function<void()> finishCallBackFunc)
{
	this->_finishCallBackFunc = finishCallBackFunc;
}

void GameAnimation::setCurrentFrame(size_t frame)
{
	_currentFrame = frame;
}

void GameAnimation::setTotalFrame(size_t frame)
{
	_totalFrame = frame;
}

void GameAnimation::updateFrame(float dt)
{
	size_t frame;
	if (this->getCurrentFrame() > this->getTotalFrame()) {
		this->setCurrentFrame(1);
	}
	frame = this->getCurrentFrame() - 1;
	CCLOG("_currentFrame = %d", _currentFrame);
	auto texture = DirectorUtils::getTextureCache()->addImage(_animationNames[frame]);
	_animation->setTexture(texture);
	_animation->setFlippedX(this->getFlippedX());
	this->runFinishCallBackFunc();
	this->setCurrentFrame(_currentFrame + 1);//播放下一帧
}

void GameAnimation::runFinishCallBackFunc()
{
	bool isFinish = this->getCurrentFrame() == this->getTotalFrame();
	if (isFinish && this->_finishCallBackFunc) {
		this->_finishCallBackFunc();
	}
}

