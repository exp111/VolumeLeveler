#pragma once
#include <string>

class Config
{
public:
	Config() { };
	~Config() { };

	bool enabled = true;
	int limit = 6000;

	enum ACTIONS
	{
		NONE = 0,
		MUTE = 1,
		KICK_CHANNEL,
		KICK_SERVER,
		BAN,
	};
	int actionOnLevelExceeded = -1;
	//0 for permanent; else temporary
	int banDuration = 10;
	std::string actionReason = "Your loudest sample was at {level} while the treshold is at {limit}!";
};

extern Config* config;