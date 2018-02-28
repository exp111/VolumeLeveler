/*
* TeamSpeak 3 demo plugin
*
* Copyright (c) 2008-2017 TeamSpeak Systems GmbH
*/

#ifdef _WIN32
#pragma warning (disable : 4100)  /* Disable Unreferenced parameter warning */
#include <Windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "teamspeak/public_errors.h"
#include "teamspeak/public_errors_rare.h"
#include "teamspeak/public_definitions.h"
#include "teamspeak/public_rare_definitions.h"
#include "teamspeak/clientlib_publicdefinitions.h"
#include "ts3_functions.h"
#include "plugin.h"
#include <iostream>
#include <string>
#include <fstream>
//#include "config.h"
#include "QtConfig.h"
#include "config.h"
#include "db.h"

static struct TS3Functions ts3Functions;

#ifdef _WIN32
#define _strcpy(dest, destSize, src) strcpy_s(dest, destSize, src)
#define snprintf sprintf_s
#else
#define _strcpy(dest, destSize, src) { strncpy(dest, src, destSize-1); (dest)[destSize-1] = '\0'; }
#endif

#define PLUGIN_API_VERSION 22

#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

//Global Variables
static char* pluginID = NULL;
std::string configFile;

#ifdef _WIN32
/* Helper function to convert wchar_T to Utf-8 encoded strings on Windows */
static int wcharToUtf8(const wchar_t* str, char** result) {
	int outlen = WideCharToMultiByte(CP_UTF8, 0, str, -1, 0, 0, 0, 0);
	*result = (char*)malloc(outlen);
	if (WideCharToMultiByte(CP_UTF8, 0, str, -1, *result, outlen, 0, 0) == 0) {
		*result = NULL;
		return -1;
	}
	return 0;
}
#endif

/*********************************** Required functions ************************************/


const char* ts3plugin_name() {
#ifdef _WIN32
	static char* result = NULL;  /* Static variable so it's allocated only once */
	if (!result) {
		const wchar_t* name = L"Volume Leveler";
		if (wcharToUtf8(name, &result) == -1) {  /* Convert name into UTF-8 encoded result */
			result = "Volume Leveler";  /* Conversion failed, fallback here */
		}
	}
	return result;
#else
	return "Volume Leveler";
#endif
}

const char* ts3plugin_version() {
	return "1.0";
}

int ts3plugin_apiVersion() {
	return PLUGIN_API_VERSION;
}

const char* ts3plugin_author() {
	return "Exp";
}

const char* ts3plugin_description() {
	return "Know that one guy who screams in his microphone? Yea, now it lowers his volume if he does it again.";
}

void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
	ts3Functions = funcs;
}

bool file_exists(const LPCSTR file_name)
{
	std::ifstream file(file_name);
	return file.good();
}

void create_config(const LPCSTR file_name)
{
	WritePrivateProfileString("Config", "enabled", "1", file_name);
	WritePrivateProfileString("Config", "limit", "6000", file_name);
}

void loadConfig()
{
	char enabled[128];
	char limit[128];
	GetPrivateProfileString("Config", "enabled", "1", enabled, 128, configFile.c_str());
	GetPrivateProfileString("Config", "limit", "6000", limit, 128, configFile.c_str());

	config->enabled = std::stoi(enabled);
	config->limit = std::stoi(limit);
}

void saveConfig()
{
	if (!file_exists(configFile.c_str()))
		create_config(configFile.c_str());

	WritePrivateProfileString("Config", "enabled", std::to_string(config->enabled).c_str(), configFile.c_str());
	WritePrivateProfileString("Config", "limit", std::to_string(config->limit).c_str(), configFile.c_str());
}

int ts3plugin_init() {
	char appPath[PATH_BUFSIZE];
	char resourcesPath[PATH_BUFSIZE];
	char configPath[PATH_BUFSIZE];
	char pluginPath[PATH_BUFSIZE];

	ts3Functions.getAppPath(appPath, PATH_BUFSIZE);
	ts3Functions.getResourcesPath(resourcesPath, PATH_BUFSIZE);
	ts3Functions.getConfigPath(configPath, PATH_BUFSIZE);
	ts3Functions.getPluginPath(pluginPath, PATH_BUFSIZE, pluginID);

	configFile = std::string(configPath) + "plugins/VolumeLeveler/config.ini";
	loadConfig();
	return 0;
}

void ts3plugin_shutdown() {
	saveConfig();

	if (pluginID) {
		free(pluginID);
		pluginID = NULL;
	}
}

int ts3plugin_offersConfigure() {
	return PLUGIN_OFFERS_CONFIGURE_QT_THREAD;
}

void openConfig(void* qParentWidget = nullptr)
{
	QtConfig* cfg = new QtConfig((QWidget*)qParentWidget);
	cfg->setAttribute(Qt::WA_DeleteOnClose);
	cfg->show();
}

void ts3plugin_configure(void* handle, void* qParentWidget)
{
	Q_UNUSED(handle);
	openConfig(qParentWidget);
}

void ts3plugin_registerPluginID(const char* id) {
	const size_t sz = strlen(id) + 1;
	pluginID = (char*)malloc(sz * sizeof(char));
	_strcpy(pluginID, sz, id);
}

const char* ts3plugin_commandKeyword() {
	//return "test";
	return ""; //Command Suffix for chat; example: /test
}

const char* ts3plugin_infoTitle() {
	return "Volume Leveler";
}

void ts3plugin_freeMemory(void* data) {
	free(data);
}
int ts3plugin_requestAutoload() {
	return 0;
}

//Helper Functions

/* Helper function to create a menu item */
static struct PluginMenuItem* createMenuItem(enum PluginMenuType type, int id, const char* text, const char* icon) {
	struct PluginMenuItem* menuItem = (struct PluginMenuItem*)malloc(sizeof(struct PluginMenuItem));
	menuItem->type = type;
	menuItem->id = id;
	_strcpy(menuItem->text, PLUGIN_MENU_BUFSZ, text);
	_strcpy(menuItem->icon, PLUGIN_MENU_BUFSZ, icon);
	return menuItem;
}

/* Some makros to make the code to create menu items a bit more readable */
#define BEGIN_CREATE_MENUS(x) const size_t sz = x + 1; size_t n = 0; *menuItems = (struct PluginMenuItem**)malloc(sizeof(struct PluginMenuItem*) * sz);
#define CREATE_MENU_ITEM(a, b, c, d) (*menuItems)[n++] = createMenuItem(a, b, c, d);
#define END_CREATE_MENUS (*menuItems)[n++] = NULL; assert(n == sz);


enum {
	MENU_ID_GLOBAL_1 = 1,
	MENU_ID_GLOBAL_2 = 2,
	MENU_ID_MAX
};

void ts3plugin_initMenus(struct PluginMenuItem*** menuItems, char** menuIcon) {

	BEGIN_CREATE_MENUS(MENU_ID_MAX - 1); //Needs to be correct
	CREATE_MENU_ITEM(PLUGIN_MENU_TYPE_GLOBAL, MENU_ID_GLOBAL_1, "Enable/Disable", "");
	CREATE_MENU_ITEM(PLUGIN_MENU_TYPE_GLOBAL, MENU_ID_GLOBAL_2, "Change Limit", "");
	END_CREATE_MENUS;

	*menuIcon = (char*)malloc(PLUGIN_MENU_BUFSZ * sizeof(char));
	_strcpy(*menuIcon, PLUGIN_MENU_BUFSZ, ""); //PLUGIN MENU IMAGE
}

/************************** TeamSpeak callbacks ***************************/

void ts3plugin_onMenuItemEvent(uint64 serverConnectionHandlerID, enum PluginMenuType type, int menuItemID, uint64 selectedItemID) {
	switch (type) {
	case PLUGIN_MENU_TYPE_GLOBAL:
		/* Channel contextmenu item was triggered. selectedItemID is the channelID of the selected channel */
		switch (menuItemID) {
		case MENU_ID_GLOBAL_1:
			config->enabled = !config->enabled;
			if (config->enabled)
				ts3Functions.printMessageToCurrentTab("Enabled Volume Leveler.");
			else
				ts3Functions.printMessageToCurrentTab("Disabled Volume Leveler.");
			break;
		case MENU_ID_GLOBAL_2:
			openConfig();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void ts3plugin_onConnectStatusChangeEvent(uint64 serverConnectionHandlerID, int newStatus, unsigned int errorNumber)
{

}

const char* ts3plugin_keyDeviceName(const char* keyIdentifier) {
	return NULL;
}

const char* ts3plugin_displayKeyText(const char* keyIdentifier) {
	return NULL;
}

const char* ts3plugin_keyPrefix() {
	return NULL;
}

void ts3plugin_onEditPlaybackVoiceDataEvent(uint64 serverConnectionHandlerID, anyID clientID, short * samples, int sampleCount, int channels)
{
	if (!config->enabled)
		return;

	int count = sampleCount * channels;

	//scaling percentage
	//Get highest sample
	int highestSample = 0;
	for (int i = 0; i < count; i++)
	{
	if (abs(samples[i]) > highestSample)
	highestSample = abs(samples[i]);
	}

	//If we're not over the limit we don't need to change anything
	if (highestSample <= config->limit)
	return;

	//Get the difference between highest and limit for proper scaling
	double diff = ((double)highestSample / config->limit);

	//Clamp
	for (int i = 0; i < count; i++)
	{
		samples[i] /= diff;
	}

	//shitty compression
	/*for (int i = 0; i < count; i++)
	{
		if (samples[i] > config->limit)
		{
			samples[i] = config->limit;
		}
		else if (-samples[i] > config->limit)
		{
			samples[i] = -config->limit;
		}
	}*/
}