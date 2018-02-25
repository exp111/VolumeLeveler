#pragma once

class Config
{
public:
	Config() { };
	~Config() { };

	bool enabled = true;
	int limit = 6000;
};

extern Config* config;