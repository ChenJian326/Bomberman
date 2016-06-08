#pragma once
#ifndef __GAME_CONFIG__H_
#define __GAME_CONFIG__H_
#include <string>
#include <vector>
#include "cocos2d.h"
enum GameStatus
{
	START = 1,
	CONDUCT,
	CONTINUE,
	END
};
enum class Direction {
	LEFT,
	RIGHT,
	BOTOOM,
	TOP,
	STOP,
};

enum RoleType {
	Player,
	EnemyA,
	EnemyB,
	EnemyC,
};
enum PropType {
	PROP_SLDAN,
	PROP_XIE,
	PROP_XIE_Z_DAN,
	PROP_Z_DAN_1,
	PROP_Z_DAN_2,
	PROP_Z_DAN_3
};
typedef std::vector<std::vector<std::string>> animation_names;
std::vector<animation_names> const g_animationNames = {
	{
		{ "player_left1.png","player_left2.png", "player_left3.png" },
		{ "player_bottom1.png","player_bottom2.png", "player_bottom3.png" },
		{ "player_top1.png","player_top2.png", "player_top3.png" }
	},
	{
		{ "enemy_green_left1.png","enemy_green_left2.png", "enemy_green_left3.png" },
		{ "enemy_green_bottom1.png","enemy_green_bottom2.png", "enemy_green_bottom3.png" },
		{ "enemy_green_top1.png","enemy_green_top2.png", "enemy_green_top2.png" }
	},
	{
		{ "enemy_purple_left1.png","enemy_purple_left2.png", "enemy_purple_left3.png" },
		{ "enemy_purple_bottom1.png","enemy_purple_bottom2.png", "enemy_purple_bottom3.png" },
		{ "enemy_purple_top1.png","enemy_purple_top2.png", "enemy_purple_top3.png" }
	},
	{
		{ "enemy_red_left1.png","enemy_red_left2.png", "enemy_red_left3.png" },
		{ "enemy_red_bottom1.png","enemy_red_bottom2.png", "enemy_red_bottom3.png" },
		{ "enemy_red_top1.png","enemy_red_top2.png", "enemy_red_top3.png" }
	}
};

animation_names const PROP_Z_DAN = {
	{ "zdan_blue1.png","zdan_blue2.png", "zdan_blue3.png" , "zdan_blue4.png" },
	{ "zdan_purple1.png","zdan_purple2.png", "zdan_purple3.png" , "zdan_purple4.png" },
	{ "zdan_red1.png","zdan_red2.png", "zdan_red3.png" , "zdan_red4.png" },
};

std::vector<std::string> const PROP_NAMES = {
		"sldan.png",
		"xie.png",
		"zdan2.png",
		"zdan_blue4.png",
		"zdan_purple4.png",
		"zdan_red4.png"
};

std::string const Cache_Current_Level = "currentLevel";
std::string const EVENT_GAME_STATUS_CHANGE = "EVENT_GAME_STATUS_CHANGE";
std::string const EVENT_PLAYER_MOVE = "EVENT_PLAYER_MOVE";
std::string const EVENT_PLAYER_PUT_BOMB = "EVENT_PLAYER_PUT_BOMB";
std::string const GAME_FONE_NAME = "";

cocos2d::Size const ROLE_SIZE = cocos2d::Size(32, 32);

size_t const ANIMMATION_PLAY_TIME = 8;
size_t const PLAYER_NORMAL_SPEED = 5;
size_t const ENEMY_NORMAL_SPEED = 5;
#endif // !__GAME_CONFIG__H_
