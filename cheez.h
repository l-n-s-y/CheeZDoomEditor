#pragma once

#include <Windows.h>

struct Fuck {
public:
	int idx = 20;
};

struct OneLevel
{
	int totalkills, killcount;
	int totalitems, itemcount;
	int totalsecrets, secretcount;
	int leveltime;
	FString Levelname;
};

struct UserInfoCVarNamePlayer
{
	FBaseCVar** addr;
	FString name;
	int pnum;
};


int CheezMain(HINSTANCE hInstance);
