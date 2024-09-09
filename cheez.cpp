#pragma once

#include <Windows.h>
#include <stdio.h>

#ifdef _WIN32
#include <direct.h>
#endif

#include <math.h>
#include <assert.h>


#include "version.h"
#include "doomdef.h" 
#include "doomstat.h"
#include "d_protocol.h"
#include "d_netinf.h"
#include "intermission/intermission.h"
#include "m_argv.h"
#include "m_misc.h"
#include "menu.h"
#include "m_crc32.h"
#include "p_saveg.h"
#include "p_tick.h"
#include "d_main.h"
#include "wi_stuff.h"
#include "hu_stuff.h"
#include "st_stuff.h"
#include "am_map.h"
#include "c_console.h"
#include "c_bind.h"
#include "c_dispatch.h"
#include "filesystem.h"
#include "p_local.h" 
#include "gstrings.h"
#include "r_sky.h"
#include "g_game.h"
#include "sbar.h"
#include "m_png.h"
#include "a_keys.h"
#include "cmdlib.h"
#include "d_net.h"
#include "d_event.h"
#include "p_acs.h"
#include "p_effect.h"
#include "m_joy.h"
#include "r_utility.h"
#include "a_morph.h"
#include "p_spec.h"
#include "serializer_doom.h"
#include "vm.h"
#include "dobjgc.h"
#include "gi.h"
#include "a_dynlight.h"
#include "i_system.h"
#include "p_conversation.h"
#include "v_palette.h"
#include "s_music.h"
#include "p_setup.h"
#include "d_event.h"
#include "model.h"

#include "g_hub.h"

#include <stdint.h>
#include <type_traits>
#include "p_setup.h"
#include "c_cvars.h"


void ChZ_PrintError(const char* msg);
void ChZ_PrintError(const char* msg, const char* details);
void ChZ_Print(const char* msg);


struct Fuck {
public:
	int idx=20;
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

inline const char* mapName = "MAP01";

//TArray<UserInfoCVarNamePlayer> LoadGameUserInfoCVars;

void Cheez_ReadSnapshots(FResourceFile* resf) // Loads all map data!!
{
	FString MapName;
	level_info_t* i;
	level_info_t TheDefaultLevelInfo;

	G_ClearSnapshots();

	for (unsigned j = 0; j < resf->EntryCount(); j++)
	{
		auto name = resf->getName(j);
		auto ptr = strstr(name, ".map.json");
		if (ptr != nullptr)
		{
			ptrdiff_t maplen = ptr - name;
			FString mapname(name, (size_t)maplen);
			i = FindLevelInfo(mapname.GetChars()); // Grabs the map's wadlevelinfos[] ptr
			if (i != nullptr)
			{
				i->Snapshot = resf->GetRawData(j); // Sets wadlevel's current state to be from *.map.json
			}
		}
		else
		{
			auto ptr = strstr(name, ".mapd.json");
			if (ptr != nullptr)
			{
				ptrdiff_t maplen = ptr - name;
				FString mapname(name, (size_t)maplen);
				TheDefaultLevelInfo.Snapshot = resf->GetRawData(j);
			}
		}
	}
}

TArray<FCompressedBuffer> CheezWrite(FString* filename_p, bool doReturn) {//FSerializer* arc_p) {
	FString filename = *filename_p;
	//FSerializer arc = *arc_p;
	//( (resf.reset(FResourceFile::OpenResourceFile(node->Filename.GetChars(), true))), resf != nullptr))

	BufferWriter savepic;
	FSerializer savegameinfo;
	FSerializer savegameglobals;

	savegameinfo.OpenWriter(true);
	savegameglobals.OpenWriter(false);

	SaveVersion = SAVEVER;
	//WriteSavePic(&players[0],&savepic,0,0);
	M_CreateDummyPNG(&savepic);

	char buf[100];
	mysnprintf(buf, countof(buf), GAMENAME" %s", GetVersionString());

	M_AppendPNGText(&savepic, "Software", buf);
	M_AppendPNGText(&savepic, "Title", "this is a test");
	M_AppendPNGText(&savepic, "Current Map", mapName);
	M_FinishPNG(&savepic);

	//int ver = SAVEVER;
	int ver = MINSAVEVER; // Let every version of GZ run these. DEBUG ONLY
	savegameinfo.AddString("Software", buf)
		.AddString("Engine", GAMESIG)
		("Save Version", ver)
		.AddString("Title", "this is a test")
		.AddString("Current Map", mapName);

	//PutSaveWads
	savegameinfo.AddString("Game WAD", "DOOM2.WAD");
	savegameinfo.AddString("Map WAD", "DOOM2.WAD");

	//Cheez_PutSaveComment(savegameinfo);
	FString comment = myasctime();
	savegameinfo.AddString("Creation Time", comment.GetChars());
	savegameinfo.AddString("Comment", "MAP01 - Entryway\nTime: 00:00:03");

	//// TODO: G_SerializeHub()
	//// TODO: C_SerializeCVars()
	Fuck level;
	int ticrate = TICRATE;
	savegameglobals("ticrate", ticrate);
	savegameglobals("leveltime", level.idx);

	//// TODO: STAT_Serialize()


	//// FRandom::StaticWriteRNGState()
	savegameglobals("rngseed", rngseed);

	if (savegameglobals.BeginArray("rngs"))
	{
		//for (rng = FRandom::RNGList; rng != NULL; rng = rng->Next)
		int rngs[] = { 1073149939,
				1581304684,
				349594625,
				809580056,
				2342931053,
				936943241,
				1216293532,
				1017964057,
				1724529788,
				263778991,
				2340340511,
				2846406287,
				1830544738,
				801704492,
				1783593764,
				3924695953,
				103561156,
				1638460198,
				967387793,
				1085631963 };
		int rng_size = sizeof(rngs) / sizeof(int);
		for (auto i = 0; i <= rng_size; i++)
		{
			int rng = rngs[i];
			// Only write those RNGs that have names
			if (savegameglobals.BeginObject(nullptr))
			{
				//FRandom* rngg;
				Fuck rngg;
				savegameglobals("crc", rng)
					("index", rngg.idx)
					.Array("u", rngs, rng_size)
					.EndObject();
			}
		}
		savegameglobals.EndArray();
	}

	int NextSkill = 1;
	savegameglobals("nextskill", NextSkill);

	auto picdata = savepic.GetBuffer();
	FCompressedBuffer bufpng = { picdata->size(), picdata->size(), FileSys::METHOD_STORED, static_cast<unsigned int>(crc32(0, &(*picdata)[0], picdata->size())), (char*)&(*picdata)[0] };

	TArray<FCompressedBuffer> savegame_content;
	TArray<FString> savegame_filenames;

	savegame_content.Push(bufpng);
	savegame_filenames.Push("savepic.png");
	savegame_content.Push(savegameinfo.GetCompressedOutput());
	savegame_filenames.Push("info.json");
	savegame_content.Push(savegameglobals.GetCompressedOutput());
	savegame_filenames.Push("globals.json");

	//FString filename3("custom_save.zds");


	//// G_WriteSnapshots()
	////unsigned int i;
	////FString filename;


	//for (i = 0; i < wadlevelinfos.Size(); i++)
	//{
		//continue; // skip entire loop
		//if (wadlevelinfos[i].Snapshot.mCompressedSize > 0)
		//{
	/*FString filename2;
	filename2.Format("C:\\Users\\me\\Saved Games\\GZDoom\doom.id.doom2.commercial\\%s",filename3);
	filename2 = NicePath(filename2.GetChars());
	filename2.Substitute("\\", "/");*/

	FString fname;
	//FString fname(mapName,".map.json");
	//fname.Format("%s/%s", filename, fname);
	fname.Format("%s.map.json", mapName);
	fname.ToLower();
	savegame_filenames.Push(fname);

	level_info_t l;
	savegame_content.Push(l.Snapshot);



	for (unsigned i = 0; i < savegame_content.Size(); i++)
		savegame_content[i].filename = savegame_filenames[i].GetChars();

	bool succeeded = false;

	if (doReturn)
		return savegame_content;

	//savegame_content.Clear();
	//savegame_content.Push(compbuf);
	//FString writePath("C:\\Users\\me\\Saved Games\\GZDoom\\doom.id.doom2.commercial\\save123.zds");
	MessageBoxA(HWND_DESKTOP, filename.GetChars(), NULL, MB_OK);
	if (WriteZip(filename.GetChars(), savegame_content.Data(), savegame_content.Size()))
	{
		// Check whether the file is ok by trying to open it.
		FResourceFile* test = FResourceFile::OpenResourceFile(filename.GetChars(), true);
		if (test != nullptr)
		{
			delete test;
			succeeded = true;
			MessageBoxA(HWND_DESKTOP, "CheezWrite() WROTE ZDS", NULL, MB_OK);
		}
	}
	else {
		MessageBoxA(HWND_DESKTOP, "CheezWrite() FAILED", NULL, MB_ICONERROR | MB_OK);
	}

	savegame_content[1].Clean();
	savegame_content[2].Clean();

	TArray<FCompressedBuffer> bufff;
	return bufff;
	
}

// TODO: template
void ChZ_PrintError(const char* msg) {
	//printf("[ERROR][%s]\n", msg);
	MessageBoxA(HWND_DESKTOP, msg, NULL, MB_ICONERROR|MB_OK);
}

void ChZ_PrintError(const char* msg, const char* details) {
	//printf("[ERROR][%s] %s\n", msg, details);
	char buf[99];
	sprintf_s(buf, "%s: %s", msg, details);
	MessageBoxA(HWND_DESKTOP, buf, NULL, MB_ICONERROR | MB_OK);
}

void ChZ_Print(const char* msg) {
	MessageBoxA(HWND_DESKTOP, msg, NULL, MB_OK);
}

player_t chz_player;
/*void Cheez_Serialize(FSerializer& arc)
{
	FString skinname;

	arc("class", cls)
		("mo", mo)
		("camera", camera)
		("playerstate", playerstate)
		("cmd", cmd);

	if (arc.isReading())
	{
		userinfo.Reset(mo->Level->PlayerNum(this));
		ReadUserInfo(arc, userinfo, skinname);
	}
	else
	{
		WriteUserInfo(arc, userinfo);
	}

	arc("desiredfov", DesiredFOV)
		("fov", FOV)
		("viewz", viewz)
		("viewheight", viewheight)
		("deltaviewheight", deltaviewheight)
		("bob", bob)
		("vel", Vel)
		("centering", centering)
		("health", health)
		("inventorytics", inventorytics)
		("fragcount", fragcount)
		("spreecount", spreecount)
		("multicount", multicount)
		("lastkilltime", lastkilltime)
		("readyweapon", ReadyWeapon)
		("pendingweapon", PendingWeapon)
		("cheats", cheats)
		("refire", refire)
		("inconsistant", inconsistant)
		("killcount", killcount)
		("itemcount", itemcount)
		("secretcount", secretcount)
		("damagecount", damagecount)
		("bonuscount", bonuscount)
		("hazardcount", hazardcount)
		("poisoncount", poisoncount)
		("poisoner", poisoner)
		("attacker", attacker)
		("extralight", extralight)
		("fixedcolormap", fixedcolormap)
		("fixedlightlevel", fixedlightlevel)
		("morphTics", morphTics)
		("morphedplayerclass", MorphedPlayerClass)
		("morphstyle", MorphStyle)
		("morphexitflash", MorphExitFlash)
		("premorphweapon", PremorphWeapon)
		("chickenpeck", chickenPeck)
		("jumptics", jumpTics)
		("respawntime", respawn_time)
		("airfinished", air_finished)
		("turnticks", turnticks)
		("oldbuttons", oldbuttons)
		("hazardtype", hazardtype)
		("hazardinterval", hazardinterval)
		("bot", Bot)
		("blendr", BlendR)
		("blendg", BlendG)
		("blendb", BlendB)
		("blenda", BlendA)
		("weaponstate", WeaponState)
		("logtext", LogText)
		("subtitletext", SubtitleText)
		("subtitlecounter", SubtitleCounter)
		("conversionnpc", ConversationNPC)
		("conversionpc", ConversationPC)
		("conversionnpcangle", ConversationNPCAngle)
		("conversionfacetalker", ConversationFaceTalker)
		.Array("frags", frags, MAXPLAYERS)
		("psprites", psprites)
		("currentplayerclass", CurrentPlayerClass)
		("crouchfactor", crouchfactor)
		("crouching", crouching)
		("crouchdir", crouchdir)
		("crouchviewdelta", crouchviewdelta)
		("original_cmd", original_cmd)
		("original_oldbuttons", original_oldbuttons)
		("poisontype", poisontype)
		("poisonpaintype", poisonpaintype)
		("timefreezer", timefreezer)
		("settings_controller", settings_controller)
		("onground", onground)
		("musinfoactor", MUSINFOactor)
		("musinfotics", MUSINFOtics)
		("soundclass", SoundClass);

	if (arc.isWriting())
	{
		// If the player reloaded because they pressed +use after dying, we
		// don't want +use to still be down after the game is loaded.
		oldbuttons = ~0;
		original_oldbuttons = ~0;
	}
	if (skinname.IsNotEmpty())
	{
		userinfo.SkinChanged(skinname.GetChars(), CurrentPlayerClass);
	}
}*/

void Cheez_ReadCVars(uint8_t** demo_p)
{
	char* ptr = *((char**)demo_p);
	char* breakpt;

	if (*ptr++ != '\\')
		return;

	if (*ptr == '\\')
	{       // compact mode
		TArray<FBaseCVar*> cvars;
		FBaseCVar* cvar;
		uint32_t filter;

		ptr++;
		breakpt = strchr(ptr, '\\');
		*breakpt = 0;
		filter = strtoul(ptr, NULL, 16);
		*breakpt = '\\';
		ptr = breakpt + 1;

		FilterCompactCVars(cvars, filter);

		while (cvars.Pop(cvar))
		{
			UCVarValue val;
			breakpt = strchr(ptr, '\\');
			if (breakpt)
				*breakpt = 0;
			val.String = ptr;
			cvar->ForceSet(val, CVAR_String);
			if (breakpt)
			{
				*breakpt = '\\';
				ptr = breakpt + 1;
			}
			else
				break;
		}
	}
	else
	{
		char* value;

		while ((breakpt = strchr(ptr, '\\')))
		{
			*breakpt = 0;
			value = breakpt + 1;
			if ((breakpt = strchr(value, '\\')))
				*breakpt = 0;

			cvar_set(ptr, value);

			*(value - 1) = '\\';
			if (breakpt)
			{
				*breakpt = '\\';
				ptr = breakpt + 1;
			}
			else
			{
				break;
			}
		}
	}
	*demo_p += strlen(*((char**)demo_p)) + 1;
}


void Cheez_SerializeCVars(FSerializer& arc, const char* label, uint32_t filter)
{
	FString dump;
	if (arc.BeginObject(label))
	{
		if (arc.isWriting())
		{
			ChZ_Print("Cheez_SerializeCVars() writing");
			decltype(cvarMap)::Iterator it(cvarMap);
			decltype(cvarMap)::Pair* pair;
			while (it.NextPair(pair))
			{
				auto cvar = pair->Value;

				uint32_t flags = cvar->GetFlags();
				if ((flags & filter) && !(flags & (CVAR_NOSAVE | CVAR_IGNORE | CVAR_CONFIG_ONLY)))
				{
					UCVarValue val = cvar->GetGenericRep(CVAR_String);
					char* c = const_cast<char*>(val.String);
					arc(cvar->GetName(), c);
				}
			}
		}
		else
		{
			ChZ_Print("Cheez_SerializeCVars() reading");
			decltype(cvarMap)::Iterator it(cvarMap);
			decltype(cvarMap)::Pair* pair;
			while (it.NextPair(pair))
			{
				auto cvar = pair->Value;
				uint32_t flags = cvar->GetFlags();
				if ((flags & filter) && !(flags & (CVAR_NOSAVE | CVAR_IGNORE | CVAR_CONFIG_ONLY)))
				{
					UCVarValue val;
					char* c = nullptr;
					arc(cvar->GetName(), c);
					if (c != nullptr)
					{
						val.String = c;
						cvar->SetGenericRep(val, CVAR_String);
						delete[] c;
					}
				}
			}
		}
		arc.EndObject();
	}
}

TArray<UserInfoCVarNamePlayer> ChZ_LoadGameUserInfoCVars;
void Cheez_SetupLoadingCVars()
{
	ChZ_LoadGameUserInfoCVars.Clear();
}

void Cheez_FinishLoadingCVars()
{
	for (UserInfoCVarNamePlayer& cvar : ChZ_LoadGameUserInfoCVars)
	{
		(*cvar.addr) = GetCVar(cvar.pnum, cvar.name.GetChars());
	}
}

static FEpisode* StartEpisode;
static TArray<OneLevel> LevelData;
void Cheez_STAT_Serialize(FSerializer& arc)
{
	FString startlevel;
	int i = LevelData.Size();

	if (arc.BeginObject("statistics"))
	{
		if (arc.isReading())
		{
			arc("startlevel", startlevel);
			StartEpisode = NULL;
			for (unsigned int j = 0; j < AllEpisodes.Size(); j++)
			{
				if (!AllEpisodes[j].mEpisodeMap.CompareNoCase(startlevel))
				{
					StartEpisode = &AllEpisodes[j];
					break;
				}
			}
			LevelData.Resize(i);
		}
		else
		{
			if (StartEpisode != NULL) startlevel = StartEpisode->mEpisodeMap;
			arc("startlevel", startlevel);
		}
		//arc("levels", LevelData);
		arc.EndObject();
	}
}

int Cheez_DoLoadGame(FString savename, FSerializer* arc_p) {
	FSerializer arc = *arc_p;
	Cheez_SetupLoadingCVars();
	bool hidecon;

	if (gameaction != ga_autoloadgame)
	{
		demoplayback = false;
	}
	hidecon = gameaction == ga_loadgamehidecon;
	gameaction = ga_nothing;

	ChZ_Print(savename.GetChars());
	std::unique_ptr<FResourceFile> resfile(FResourceFile::OpenResourceFile(savename.GetChars(), true));
	if (resfile == nullptr)
	{
		ChZ_PrintError("TXT_COULDNOTREAD");
		return 1;
	}


	auto info = resfile->FindEntry("info.json");
	if (info < 0)
	{
		ChZ_PrintError("TXT_NOINFOJSON");
		return 2;
	}

	SaveVersion = 0;

	auto data = resfile->Read(info);
	//FSerializer arc;
	if (!arc.OpenReader(data.string(), data.size()))
	{
		ChZ_PrintError("TXT_FAILEDTOREADSG");
		return 3;
	}

	// Check whether this savegame actually has been created by a compatible engine.
	// Since there are ZDoom derivates using the exact same savegame format but
	// with mutual incompatibilities this check simplifies things significantly.
	FString savever, engine, map;
	arc("Save Version", SaveVersion);
	arc("Engine", engine);
	arc("Current Map", map);

	if (engine.CompareNoCase(GAMESIG) != 0)
	{
		// Make a special case for the message printed for old savegames that don't
		// have this information.
		if (engine.IsEmpty())
		{
			ChZ_PrintError("TXT_INCOMPATIBLESG");
		}
		else
		{
			ChZ_PrintError("TXT_OTHERENGINESG", engine.GetChars());
		}
		return 4;
	}

	if (SaveVersion < MINSAVEVER || SaveVersion > SAVEVER)
	{
		FString message;
		if (SaveVersion < MINSAVEVER)
		{
			message = GStrings.GetString("TXT_TOOOLDSG");
			message.Substitute("%e", FStringf("%d", MINSAVEVER));
		}
		else
		{
			message = GStrings.GetString("TXT_TOONEWSG");
			message.Substitute("%e", FStringf("%d", SAVEVER));
		}
		message.Substitute("%d", FStringf("%d", SaveVersion));
		ChZ_PrintError(message.GetChars());
		return 5;
	}

	if (!G_CheckSaveGameWads(arc, true))
	{
		//MessageBoxA(HWND_DESKTOP, "NOT ALL WADS LOADED", NULL, MB_ICONEXCLAMATION | MB_OK);
		ChZ_PrintError("NOT ALL WADS LOADED");
		//return 6;
	}

	if (map.IsEmpty())
	{
		ChZ_PrintError("TXT_NOMAPSG");
		return 7;
	}

	// Now that it looks like we can load this save, hide the fullscreen console if it was up
	// when the game was selected from the menu.
	if (hidecon && gamestate == GS_FULLCONSOLE)
	{
		gamestate = GS_HIDECONSOLE;
	}
	// we are done with info.json.
	arc.Close();

	info = resfile->FindEntry("globals.json");
	if (info < 0)
	{
		ChZ_PrintError("TXT_NOGLOBALSJSON");
		return 8;
	}


	data = resfile->Read(info);
	if (!arc.OpenReader(data.string(),data.size()))
	{
		ChZ_PrintError("TXT_SGINFOERR");
		return 9;
	}


	// Read intermission data for hubs
	G_SerializeHub(arc);

	primaryLevel->BotInfo.RemoveAllBots(primaryLevel, true);

	savegamerestore = true;		// Use the player actors in the savegame

	FString cvar;
	arc("importantcvars", cvar);
	if (!cvar.IsEmpty())
	{
		uint8_t* vars_p = (uint8_t*)cvar.GetChars();
		Cheez_ReadCVars(&vars_p);
		
	}
	else
	{
		Cheez_SerializeCVars(arc, "servercvars", CVAR_SERVERINFO);
	}

	uint32_t time[2] = { 1,0 };

	uint32_t globalfreeze = 0;
	arc("ticrate", time[0])
		("leveltime", time[1])
		("globalfreeze", globalfreeze);
	// dearchive all the modifications
	level.time = Scale(time[1], TICRATE, time[0]);

	Cheez_ReadSnapshots(resfile.get()); // Read map level snapshot (*.map.json)
	//resfile.reset(nullptr);	// we no longer need the resource file below this point
	G_ReadVisited(arc); // Load players[] classes and "visited"

	// load a base level
	bool demoplaybacksave = demoplayback;
	/*try {
		G_InitNew(map.GetChars(), false);
	}
	catch (...) {
		MessageBoxA(HWND_DESKTOP, "InitNew failed", NULL, MB_OK);
	}*/
	Cheez_FinishLoadingCVars();
	demoplayback = demoplaybacksave;
	savegamerestore = false;

	Cheez_STAT_Serialize(arc); // Load startlevel
	FRandom::StaticReadRNGState(arc);
	P_ReadACSDefereds(arc); // Deferreds 
	P_ReadACSVars(arc); // ACS stuff

	NextSkill = -1;
	arc("nextskill", NextSkill);

	if (level.info != nullptr) {
		level.info->Snapshot.Clean();
	}

	// At this point, the GC threshold is likely a lot higher than the
	// amount of memory in use, so bring it down now by starting a
	// collection.
	GC::StartCollection();



	auto mapEnt = resfile->FindEntry("map01.map.json");
	if (mapEnt < 0) {
		ChZ_PrintError("NO MAP");
	}
	arc.Close();
	auto mapData = resfile->Read(mapEnt);
	//FSerializer mapArc;
	if (!arc.OpenReader(mapData.string(), mapData.size())) {
		ChZ_PrintError("FAILED TO READ MAP");
		return 20;
	}

	//mapArc("health", health);
	char* key;
	/*for (int i = 0; i < 26; i++) {
		key = (char*)mapArc.GetKey();
	}*/

	// Enter 'players' array
	if (!arc.BeginArray("players")) {
		ChZ_PrintError("Error entering player array");
		return 21;
	}

	// Enter 'players' object
	arc.BeginObject("players");

	// Gets key ("health")
	for (int i = 0; i < 15; i++) {
		key = (char*)arc.GetKey();
	}

	int health = 69;
	char hp[50];

	arc("health", health);

	sprintf_s(hp, "%d", health);
	MessageBoxA(HWND_DESKTOP, hp, NULL, MB_OK);

	TArray<FCompressedBuffer> savegame_content;
	/*arc.Close();
	arc.OpenWriter();*/ 
	savegame_content = CheezWrite(&savename,true);

	FCompressedBuffer buff = arc.GetCompressedOutput();
	//savegame_content.Push(buff);

	FString filename = NicePath(savename.GetChars());
	filename.Substitute("\\", "/");
	filename.ReplaceChars('0','x');
	resfile.reset(nullptr); // we no longer need the resource file below this point
	 


	MessageBoxA(HWND_DESKTOP, filename.GetChars(), NULL, MB_OK);
	if (WriteZip(filename.GetChars(), savegame_content.Data(), savegame_content.Size()))
	{
		// Check whether the file is ok by trying to open it.
		//FResourceFile* test = FResourceFile::OpenResourceFile(filename.GetChars(), true);
		//if (test != nullptr)
		//{
		//	delete test;
		//	//succeeded = true;
		//}
		ChZ_Print("Wrote ZDS");
		return 128;
	}
	else {
		ChZ_PrintError("Write failed");
	}


	return 420;
}

// TODO: Pass argv from main
int CheezMain(HINSTANCE hInstance) {
	// Load save file
	//void G_DoLoadGame()
	const char* path = "C:\\Users\\me\\Saved Games\\GZDoom\\doom.id.doom2.commercial\\";
	FString savename("save01.zds");
	FSerializer arc;
	savename.Format("%s%s", path, savename.GetChars());
	savename = NicePath(savename.GetChars());
	savename.Substitute("\\", "/");
	int code = 69;
	try {
		code = Cheez_DoLoadGame(savename,&arc);
	}
	catch (...) {
		//code = GetLastError();
		ChZ_PrintError("DoLoadGame() failed");
		return 80085;
	}

	//arc.GetCompressedOutput();
	// Read and edit
	

	// Write back
	
	savename.Substitute('1', 'y');
	//CheezWrite(&savename,false);


	return code;
}
