#pragma once
#include <string>
#include <vector>
using namespace std;

class Config
{
public:
	Config() { };
	~Config() { };

	bool enabled = true;
	int limit = 6000;

	bool enableLog = true;

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
	string actionReason = "Your loudest sample was at {level} while the treshold is at {limit}!";

	vector<unsigned> whitelist;
};

extern Config* config;