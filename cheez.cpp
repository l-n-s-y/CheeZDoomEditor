#pragma once

#include <Windows.h>
#include <stdio.h>

#ifdef _WIN32
#include <direct.h>
#endif

#include <math.h>
#include <assert.h>

#include "events.h"
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


void Chz_PrintError(const char* msg);
void Chz_PrintError(const char* msg, const char* details);
void Chz_Print(const char* msg);

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

float Cheez_DesiredFOV = 0;
float Cheez_FOV = 0;
double Cheez_viewz = 0;
double Cheez_viewheight = 0;
double Cheez_deltaviewheight = 0;
double Cheez_bob = 0;

DVector2 Cheez_Vel = { 0,0 };

bool Cheez_centering = false;
uint8_t Cheez_turnticks = 0;

bool Cheez_attackdown = false;
bool Cheez_usedown = false;
uint32_t Cheez_oldbuttons = false;
int Cheez_health = 0;

int Cheez_inventorytics = 0;
uint8_t Cheez_CurrentPlayerClass = 0;

int Cheez_frags[MAXPLAYERS] = {};
int Cheez_fragcount = 0;
int Cheez_lastkilltime = 0;
uint8_t Cheez_multicount = 0;
uint8_t Cheez_spreecount = 0;
uint16_t Cheez_WeaponState = 0;

AActor* Cheez_ReadyWeapon = nullptr;
AActor* Cheez_PendingWeapon = nullptr;
TObjPtr<DPSprite*> Cheez_psprites = MakeObjPtr<DPSprite*>(nullptr);

int Cheez_cheats = 0;
int Cheez_timefreezer = 0;
short Cheez_refire = 0;
short Cheez_inconsistant = 0;
bool Cheez_waiting = 0;
int Cheez_killcount = 0;
int Cheez_itemcount = 0;
int Cheez_secretcount = 0;
uint32_t Cheez_damagecount = 0;
uint32_t Cheez_bonuscount = 0;
int Cheez_hazardcount = 0;
int Cheez_hazardinterval = 0;
FName Cheez_hazardtype = NAME_None;
int Cheez_poisoncount = 0;
FName Cheez_poisontype = NAME_None;
FName Cheez_poisonpaintype = NAME_None;
TObjPtr<AActor*> Cheez_poisoner = MakeObjPtr<AActor*>(nullptr);
TObjPtr<AActor*> Cheez_attacker = MakeObjPtr<AActor*>(nullptr);
int Cheez_extralight = 0;
short Cheez_fixedcolormap = 0;
short Cheez_fixedlightlevel = 0;
int Cheez_morphTics = 0;
PClassActor* Cheez_MorphedPlayerClass = nullptr;
int Cheez_MorphStyle = 0;
PClassActor* Cheez_MorphExitFlash = nullptr;
TObjPtr<AActor*> Cheez_PremorphWeapon = MakeObjPtr<AActor*>(nullptr);
int Cheez_chickenPeck = 0;
int Cheez_jumpTics = 0;
bool Cheez_onground = 0;
bool Cheez_crossingPortal = 0;

int Cheez_respawn_time = 0;
TObjPtr<AActor*> Cheez_camera = MakeObjPtr<AActor*>(nullptr);

int Cheez_air_finished = 0;

FName Cheez_LastDamageType = NAME_None;

TObjPtr<AActor*> Cheez_MUSINFOactor = MakeObjPtr<AActor*>(nullptr);
int8_t Cheez_MUSINFOtics = 0;

bool Cheez_settings_controller = false;
int8_t Cheez_crouching = 0;
int8_t Cheez_crouchdir = 0;


TObjPtr<DBot*> Cheez_Bot = MakeObjPtr<DBot*>(nullptr);

float Cheez_BlendR = 0;
float Cheez_BlendG = 0;
float Cheez_BlendB = 0;
float Cheez_BlendA = 0;

FString Cheez_SoundClass;
FString Cheez_LogText;
FString Cheez_SubtitleText;
int Cheez_SubtitleCounter;

DAngle Cheez_MinPitch = nullAngle;
DAngle Cheez_MaxPitch = nullAngle;

double Cheez_crouchfactor = 0;
double Cheez_crouchoffset = 0;
double Cheez_crouchviewdelta = 0;

FWeaponSlots Cheez_weapons;

TObjPtr<AActor*> Cheez_ConversationNPC = MakeObjPtr<AActor*>(nullptr);
TObjPtr<AActor*> Cheez_ConversationPC = MakeObjPtr<AActor*>(nullptr);
DAngle Cheez_ConversationNPCAngle = nullAngle;
bool Cheez_ConversationFaceTalker = false;

usercmd_t Cheez_original_cmd;
uint32_t Cheez_original_oldbuttons;

inline const char* mapName = "MAP01";

//TArray<UserInfoCVarNamePlayer> LoadGameUserInfoCVars;
void Cheez_LevelSerialize(FSerializer& arc, bool hubload)
{
	int i = 100;
	uint8_t md5[16];
	TArray<line_t> lines;
	TArray<side_t> sides;
	TArray<sector_t> sectors;
	TArray<FPolyObj> Polyobjects;

	FThinkerCollection Thinkers;
	FInterpolator interpolator;

	if (arc.isWriting())
	{
		arc.Array("checksum", md5, 16);
	}
	else
	{
		// prevent bad things from happening by doing a check on the size of level arrays and the map's entire checksum.
		// The old code happily tried to load savegames with any mismatch here, often causing meaningless errors
		// deep down in the deserializer or just a crash if the few insufficient safeguards were not triggered.
		uint8_t chk[16] = { 0 };
		arc.Array("checksum", chk, 16);
		if (arc.GetSize("linedefs") != lines.Size() ||
			arc.GetSize("sidedefs") != sides.Size() ||
			arc.GetSize("sectors") != sectors.Size() ||
			arc.GetSize("polyobjs") != Polyobjects.Size() ||
			memcmp(chk, md5, 16))
		{
			I_Error("Savegame is from a different level");
		}
	}
	arc("saveversion", SaveVersion);

	// this sets up some static data needed further down which means it must be done first.
	StaticSerializeTranslations(arc);

	if (arc.isReading())
	{
		Thinkers.DestroyAllThinkers();
		interpolator.ClearInterpolations();
		arc.ReadObjects(hubload);
		// If there have been object deserialization errors we must absolutely not continue here because scripted objects can do unpredictable things.
		if (arc.mObjectErrors) I_Error("Failed to load savegame");
	}

	bool multiplayer = false;
	arc("multiplayer", multiplayer);

	uint32_t		flags;
	uint32_t		flags2;
	uint32_t		flags3;

	uint32_t		fadeto;
	int			total_secrets;
	int			found_secrets;
	int			total_items;
	int			found_items;

	int			total_monsters;
	int			killed_monsters;

	double		gravity;
	double		aircontrol;

	int			maptime;			// time in the map
	FTextureID	skytexture1;
	FTextureID	skytexture2;

	int fogdensity;
	int outsidefogdensity;
	int skyfog;

	FName		deathsequence;
	
	int bodyqueslot;
	uint32_t	spawnindex;

	static const int BODYQUESIZE = 32;
	TObjPtr<AActor*> bodyque[BODYQUESIZE];
	TObjPtr<DAutomapBase*> automap = MakeObjPtr<DAutomapBase*>(nullptr);

	TArray<TObjPtr<AActor*>> CorpseQueue;
	TObjPtr<DFraggleThinker*> FraggleScriptThinker = MakeObjPtr<DFraggleThinker*>(nullptr);
	TObjPtr<DACSThinker*> ACSThinker = MakeObjPtr<DACSThinker*>(nullptr);
	int		frozenstate;
	TObjPtr<DSpotState*> SpotState = MakeObjPtr<DSpotState*>(nullptr);


	TArray<DVector2>	Scrolls;

	arc("flags", flags)
		("flags2", flags2)
		("flags3", flags3)
		("fadeto", fadeto)
		("found_secrets", found_secrets)
		("found_items", found_items)
		("killed_monsters", killed_monsters)
		("total_secrets", total_secrets)
		("total_items", total_items)
		("total_monsters", total_monsters)
		("gravity", gravity)
		("aircontrol", aircontrol)
		("teamdamage", teamdamage)
		("maptime", maptime)
		("totaltime", i)
		("skytexture1", skytexture1)
		("skytexture2", skytexture2)
		("fogdensity", fogdensity)
		("outsidefogdensity", outsidefogdensity)
		("skyfog", skyfog)
		("deathsequence", deathsequence)
		("bodyqueslot", bodyqueslot)
		("spawnindex", spawnindex)
		.Array("bodyque", bodyque, BODYQUESIZE)
		("corpsequeue", CorpseQueue)
		("spotstate", SpotState)
		("fragglethinker", FraggleScriptThinker)
		("acsthinker", ACSThinker)
		("scrolls", Scrolls)
		("automap", automap)
		("interpolator", interpolator)
		("frozenstate", frozenstate);


	// Hub transitions must keep the current total time
	if (!hubload)
		int totaltime = i;

	/*if (arc.isReading())
	{
		InitSkyMap(this);
		AirControlChanged();
	}*/

	TArray<sector_t>	loadsectors;
	TArray<line_t>	loadlines;
	TArray<side_t>	loadsides;

	TArray<zone_t>	Zones;

	TArray<FSectorPortal> sectorPortals;
	TArray<FLinePortal> linePortals;

	//Behaviors.SerializeModuleStates(arc);
	// The order here is important: First world state, then portal state, then thinkers, and last polyobjects.
	//SetCompatLineOnSide(false);	// This flag should not be saved. It solely depends on current compatibility state.
	arc("linedefs", lines, loadlines);
	//SetCompatLineOnSide(true);
	arc("sidedefs", sides, loadsides);
	arc("sectors", sectors, loadsectors);
	arc("zones", Zones);
	arc("lineportals", linePortals);
	arc("sectorportals", sectorPortals);
	/*if (arc.isReading())
	{
		FinalizePortals();
	}*/

	// [ZZ] serialize health groups
	//P_SerializeHealthGroups(this, arc);
	// [ZZ] serialize events

	EventManager* localEventManager = nullptr;
	FCanvasTextureInfo canvasTextureInfo;

	arc("firstevent", localEventManager->FirstEventHandler)
		("lastevent", localEventManager->LastEventHandler);
	if (arc.isReading()) localEventManager->CallOnRegister();
	Thinkers.SerializeThinkers(arc, hubload);
	arc("polyobjs", Polyobjects);
	//SerializeSubsectors(arc, "subsectors");
	StatusBar->SerializeMessages(arc);
	canvasTextureInfo.Serialize(arc);
	//SerializePlayers(arc, hubload);
	//SerializeSounds(arc);
	//arc("sndseqlisthead", SequenceListHead);


	// Regenerate some data that wasn't saved
	//if (arc.isReading())
	//{
	//	for (auto& sec : sectors)
	//	{
	//		P_Recalculate3DFloors(&sec);
	//	}
	//	for (int i = 0; i < MAXPLAYERS; ++i)
	//	{
	//		if (PlayerInGame(i) && Players[i]->mo != nullptr)
	//		{
	//			FWeaponSlots::SetupWeaponSlots(Players[i]->mo);
	//		}
	//	}
	//	localEventManager->SetOwnerForHandlers();	// This cannot be automated.
	//	RecreateAllAttachedLights();
	//	InitPortalGroups(this);

	//	auto it = GetThinkerIterator<DImpactDecal>(NAME_None, STAT_AUTODECAL);
	//	ImpactDecalCount = 0;
	//	while (it.Next()) ImpactDecalCount++;

	//	automap->UpdateShowAllLines();

	//}
	// clean up the static data we allocated
	StaticClearSerializeTranslationsData();

}



void Cheez_InitCVars()
{
	AutoSegs::CVarDecl.ForEach([](FCVarDecl* cvInfo)
		{
			FBaseCVar* newcvar;
			switch (cvInfo->type)
			{
			default:
				return;

			case CVAR_Int:
			{
				using callbacktype = void (*)(FIntCVar&);
				newcvar = new FIntCVar(cvInfo->name, cvInfo->defaultval.Int, cvInfo->flags, reinterpret_cast<callbacktype>(cvInfo->callbackp), cvInfo->description);
				break;
			}
			case CVAR_Bool:
			{
				using callbacktype = void (*)(FBoolCVar&);
				newcvar = new FBoolCVar(cvInfo->name, cvInfo->defaultval.Bool, cvInfo->flags, reinterpret_cast<callbacktype>(cvInfo->callbackp), cvInfo->description);
				break;
			}
			case CVAR_Float:
			{
				using callbacktype = void (*)(FFloatCVar&);
				newcvar = new FFloatCVar(cvInfo->name, cvInfo->defaultval.Float, cvInfo->flags, reinterpret_cast<callbacktype>(cvInfo->callbackp), cvInfo->description);
				break;
			}
			case CVAR_String:
			{
				using callbacktype = void (*)(FStringCVar&);
				newcvar = new FStringCVar(cvInfo->name, cvInfo->defaultval.String, cvInfo->flags, reinterpret_cast<callbacktype>(cvInfo->callbackp), cvInfo->description);
				break;
			}
			case CVAR_Color:
			{
				using callbacktype = void (*)(FColorCVar&);
				newcvar = new FColorCVar(cvInfo->name, cvInfo->defaultval.Int, cvInfo->flags, reinterpret_cast<callbacktype>(cvInfo->callbackp), cvInfo->description);
				break;
			}

			}
			*(void**)cvInfo->refAddr = newcvar;
		});
	AutoSegs::CVarDecl.ForEach([](FCVarDecl* cvInfo)
		{
			FBaseCVar* newcvar;
			switch (cvInfo->type)
			{
			default:
				return;

			case CVAR_Flag:
			{
				newcvar = new FFlagCVar(cvInfo->name, *cvInfo->defaultval.Pointer->get(), cvInfo->flags, cvInfo->description);
				break;
			}
			case CVAR_Mask:
			{
				newcvar = new FMaskCVar(cvInfo->name, *cvInfo->defaultval.Pointer->get(), cvInfo->flags, cvInfo->description);
				break;
			}

			}
			*(void**)cvInfo->refAddr = newcvar;
		});
}


void Cheez_WriteSnapshots(TArray<FString>& filenames, TArray<FCompressedBuffer>& buffers)
{
	unsigned int i;
	FString filename;

	for (i = 0; i < wadlevelinfos.Size(); i++)
	{
		if (wadlevelinfos[i].Snapshot.mCompressedSize > 0)
		{
			filename.Format("%s.map.json", wadlevelinfos[i].MapName.GetChars());
			filename.ToLower();
			filenames.Push(filename);
			buffers.Push(wadlevelinfos[i].Snapshot); // INJECT MODIFIED DATA INTO SNAPSHOT
		}
	}
	/*if (TheDefaultLevelInfo.Snapshot.mCompressedSize > 0)
	{
		filename.Format("%s.mapd.json", TheDefaultLevelInfo.MapName.GetChars());
		filename.ToLower();
		filenames.Push(filename);
		buffers.Push(TheDefaultLevelInfo.Snapshot);
	}*/
}

void Cheez_SerializeCVars(FSerializer& arc, const char* label, uint32_t filter)
{
	FString dump;

	if (arc.BeginObject(label))
	{
		if (arc.isWriting())
		{
			decltype(cvarMap)::Iterator it(cvarMap);
			decltype(cvarMap)::Pair* pair;
			while (it.NextPair(pair))
			{
				FBaseCVar* cvar = pair->Value;
				//if ((cvar->GetFlags() & filter) && !(cvar->GetFlags() & (CVAR_NOSAVE | CVAR_IGNORE | CVAR_CONFIG_ONLY)))
				{
					UCVarValue val = cvar->GetGenericRep(CVAR_String);
					char* c = const_cast<char*>(val.String);
					FString cvar_name = cvar->GetName();
					arc(cvar_name.GetChars(), c);

					if (cvar_name.Compare("health") == 0) { // Proves no playervars are being written
						FString out;
						out.Format("WRITE: %s - %x", cvar_name, c);
						Chz_Print(out.GetChars());
						
					}
				}
			}
		}
		else
		{
			decltype(cvarMap)::Iterator it(cvarMap);
			decltype(cvarMap)::Pair* pair;
			while (it.NextPair(pair))
			{
				auto cvar = pair->Value;
				if ((cvar->GetFlags() & filter) && !(cvar->GetFlags() & (CVAR_NOSAVE | CVAR_IGNORE | CVAR_CONFIG_ONLY)))
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
	if (savegameglobals.isReading()) {
		Chz_Print("GLOBALS READING");
	}
	else { Chz_Print("GLOBALS WRITING"); }
	Cheez_SerializeCVars(savegameglobals, "servercvars", CVAR_SERVERINFO);

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
	Cheez_WriteSnapshots(savegame_filenames, savegame_content);

	//FString filename3("custom_save.zds");


	/*FString fname;
	FString fname(mapName,".map.json");
	fname.Format("%s/%s", filename, fname);
	fname.Format("%s.map.json", mapName);
	fname.ToLower();
	savegame_filenames.Push(fname);

	level_info_t l;
	savegame_content.Push(l.Snapshot);*/



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
void Chz_PrintError(const char* msg) {
	//printf("[ERROR][%s]\n", msg);
	MessageBoxA(HWND_DESKTOP, msg, NULL, MB_ICONERROR|MB_OK);
}

void Chz_PrintError(const char* msg, const char* details) {
	//printf("[ERROR][%s] %s\n", msg, details);
	char buf[99];
	sprintf_s(buf, "%s: %s", msg, details);
	MessageBoxA(HWND_DESKTOP, buf, NULL, MB_ICONERROR | MB_OK);
}


void Chz_Print(const char* msg) {
	MessageBoxA(HWND_DESKTOP, msg, NULL, MB_OK);
}

player_t Chz_player;
userinfo_t userinfo;
void Cheez_Serialize(FSerializer& arc)
{
	FString skinname;

	/*arc("class", cls)
		("mo", mo)
		("camera", camera)
		("playerstate", playerstate)
		("cmd", cmd);*/

	if (arc.isReading())
	{
		//userinfo.Reset(mo->Level->PlayerNum(this));
		ReadUserInfo(arc, userinfo, skinname);
	}
	else
	{
		WriteUserInfo(arc, userinfo);
	}

	arc.BeginObject(nullptr);

	arc("desiredfov", Cheez_DesiredFOV);
	arc("fov", Cheez_FOV);
	arc("viewz", Cheez_viewz);
	arc("viewheight", Cheez_viewheight);
	arc("deltaviewheight", Cheez_deltaviewheight);
	arc("bob", Cheez_bob);
	arc("vel", Cheez_Vel);
	arc("centering", Cheez_centering);
	arc("health", Cheez_health);
	arc("inventorytics", Cheez_inventorytics);
	arc("fragcount", Cheez_fragcount);
	arc("spreecount", Cheez_spreecount);
	arc("multicount", Cheez_multicount);
	arc("lastkilltime", Cheez_lastkilltime);
	//arc("readyweapon", Cheez_ReadyWeapon);
	//arc("pendingweapon", Cheez_PendingWeapon);
	arc("cheats", Cheez_cheats);
	arc("refire", Cheez_refire);
	arc("inconsistant", Cheez_inconsistant);
	arc("killcount", Cheez_killcount);
	arc("itemcount", Cheez_itemcount);
	arc("secretcount", Cheez_secretcount);
	arc("damagecount", Cheez_damagecount);
	arc("bonuscount", Cheez_bonuscount);
	arc("hazardcount", Cheez_hazardcount);
	arc("poisoncount", Cheez_poisoncount);
	//arc("poisoner", Cheez_poisoner);
	//arc("attacker", Cheez_attacker);
	arc("extralight", Cheez_extralight);
	arc("fixedcolormap", Cheez_fixedcolormap);
	arc("fixedlightlevel", Cheez_fixedlightlevel);
	arc("morphTics", Cheez_morphTics);
	arc("morphedplayerclass", Cheez_MorphedPlayerClass);
	arc("morphstyle", Cheez_MorphStyle);
	arc("morphexitflash", Cheez_MorphExitFlash);
	//arc("premorphweapon", Cheez_PremorphWeapon);
	arc("chickenpeck", Cheez_chickenPeck);
	arc("jumptics", Cheez_jumpTics);
	arc("respawntime", Cheez_respawn_time);
	arc("airfinished", Cheez_air_finished);
	arc("turnticks", Cheez_turnticks);
	arc("oldbuttons", Cheez_oldbuttons);
	arc("hazardtype", Cheez_hazardtype);
	arc("hazardinterval", Cheez_hazardinterval);
	//arc("bot", Cheez_Bot);
	arc("blendr", Cheez_BlendR);
	arc("blendg", Cheez_BlendG);
	arc("blendb", Cheez_BlendB);
	arc("blenda", Cheez_BlendA);
	arc("weaponstate", Cheez_WeaponState);
	arc("logtext", Cheez_LogText);
	arc("subtitletext", Cheez_SubtitleText);
	arc("subtitlecounter", Cheez_SubtitleCounter);
	/*arc("conversionnpc", Cheez_ConversationNPC);
	arc("conversionpc", Cheez_ConversationPC);*/
	arc("conversionnpcangle", Cheez_ConversationNPCAngle);
	//arc("conversionfacetalker", Cheez_ConversationFaceTalker);
	arc.Array("frags", Cheez_frags, MAXPLAYERS);
	//arc("psprites", Cheez_psprites);
	arc("currentplayerclass", Cheez_CurrentPlayerClass);
	arc("crouchfactor", Cheez_crouchfactor);
	arc("crouching", Cheez_crouching);
	arc("crouchdir", Cheez_crouchdir);
	arc("crouchviewdelta", Cheez_crouchviewdelta);
	arc("original_cmd", Cheez_original_cmd);
	arc("original_oldbuttons", Cheez_original_oldbuttons);
	arc("poisontype", Cheez_poisontype);
	arc("poisonpaintype", Cheez_poisonpaintype);
	arc("timefreezer", Cheez_timefreezer);
	arc("settings_controller", Cheez_settings_controller);
	arc("onground", Cheez_onground);
	//arc("musinfoactor", Cheez_MUSINFOactor);
	arc("musinfotics", Cheez_MUSINFOtics);
	arc("soundclass", Cheez_SoundClass);

	if (arc.isWriting())
	{
		// If the player reloaded because they pressed +use after dying, we
		// don't want +use to still be down after the game is loaded.
		/*oldbuttons = ~0;
		original_oldbuttons = ~0;*/
	}
}

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


//void Cheez_SerializeCVars(FSerializer& arc, const char* label, uint32_t filter)
//{
//	FString dump;
//	if (arc.BeginObject(label))
//	{
//		if (arc.isWriting())
//		{
//			Chz_Print("Cheez_SerializeCVars() writing");
//			decltype(cvarMap)::Iterator it(cvarMap);
//			decltype(cvarMap)::Pair* pair;
//			while (it.NextPair(pair))
//			{
//				auto cvar = pair->Value;
//
//				uint32_t flags = cvar->GetFlags();
//				if ((flags & filter) && !(flags & (CVAR_NOSAVE | CVAR_IGNORE | CVAR_CONFIG_ONLY)))
//				{
//					UCVarValue val = cvar->GetGenericRep(CVAR_String);
//					char* c = const_cast<char*>(val.String);
//					arc(cvar->GetName(), c);
//				}
//			}
//		}
//		else
//		{
//			Chz_Print("Cheez_SerializeCVars() reading");
//			decltype(cvarMap)::Iterator it(cvarMap);
//			decltype(cvarMap)::Pair* pair;
//			while (it.NextPair(pair))
//			{
//				auto cvar = pair->Value;
//				uint32_t flags = cvar->GetFlags();
//				if ((flags & filter) && !(flags & (CVAR_NOSAVE | CVAR_IGNORE | CVAR_CONFIG_ONLY)))
//				{
//					UCVarValue val;
//					char* c = nullptr;
//					arc(cvar->GetName(), c);
//					if (c != nullptr)
//					{
//						val.String = c;
//						cvar->SetGenericRep(val, CVAR_String);
//						delete[] c;
//					}
//				}
//			}
//		}
//		arc.EndObject();
//	}
//}

TArray<UserInfoCVarNamePlayer> Chz_LoadGameUserInfoCVars;
void Cheez_SetupLoadingCVars()
{
	Chz_LoadGameUserInfoCVars.Clear();
}

void Cheez_FinishLoadingCVars()
{
	for (UserInfoCVarNamePlayer& cvar : Chz_LoadGameUserInfoCVars)
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

	//Chz_Print(savename.GetChars());
	std::unique_ptr<FResourceFile> resfile(FResourceFile::OpenResourceFile(savename.GetChars(), true));
	if (resfile == nullptr)
	{
		Chz_PrintError("TXT_COULDNOTREAD");
		return 1;
	}


	auto info = resfile->FindEntry("info.json");
	if (info < 0)
	{
		Chz_PrintError("TXT_NOINFOJSON");
		return 2;
	}

	SaveVersion = 0;

	auto data = resfile->Read(info);
	//FSerializer arc;
	if (!arc.OpenReader(data.string(), data.size()))
	{
		Chz_PrintError("TXT_FAILEDTOREADSG");
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
			Chz_PrintError("TXT_INCOMPATIBLESG");
		}
		else
		{
			Chz_PrintError("TXT_OTHERENGINESG", engine.GetChars());
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
		Chz_PrintError(message.GetChars());
		return 5;
	}

	if (!G_CheckSaveGameWads(arc, true))
	{
		//MessageBoxA(HWND_DESKTOP, "NOT ALL WADS LOADED", NULL, MB_ICONEXCLAMATION | MB_OK);
		Chz_PrintError("NOT ALL WADS LOADED");
		//return 6;
	}

	if (map.IsEmpty())
	{
		Chz_PrintError("TXT_NOMAPSG");
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
		Chz_PrintError("TXT_NOGLOBALSJSON");
		return 8;
	}


	data = resfile->Read(info);
	if (!arc.OpenReader(data.string(),data.size()))
	{
		Chz_PrintError("TXT_SGINFOERR");
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
		Chz_PrintError("NO MAP");
	}
	arc.Close();
	auto mapData = resfile->Read(mapEnt);
	//FSerializer mapArc;
	if (!arc.OpenReader(mapData.string(), mapData.size())) {
		Chz_PrintError("FAILED TO READ MAP");
		return 20;
	}

	//mapArc("health", health);
	char* key;
	/*for (int i = 0; i < 26; i++) {
		key = (char*)mapArc.GetKey();
	}*/

	// Enter 'players' array
	if (!arc.BeginArray("players")) {
		Chz_PrintError("Error entering player array");
		return 21;
	}

	// Enter 'players' object
	arc.BeginObject("players");

	// Gets key ("health")
	for (int i = 0; i < 15; i++) {
		key = (char*)arc.GetKey();
	}

	//int health = 69;
	//char hp[50];

	//arc("health", health);

	/*sprintf_s(hp, "%d", health);
	MessageBoxA(HWND_DESKTOP, hp
	, NULL, MB_OK);*/

	TArray<FCompressedBuffer> savegame_content;
	/*arc.Close();
	arc.OpenWriter();*/ 
	//savegame_content = CheezWrite(&savename,true);

	Cheez_Serialize(arc);
	FString healthStr;
	healthStr.Format("Health: %d", Cheez_health);
	Chz_Print(healthStr.GetChars());

	FCompressedBuffer buff = arc.GetCompressedOutput();
	//savegame_content.Push(buff);

	FString filename = NicePath(savename.GetChars());
	filename.Substitute("\\", "/");
	filename.ReplaceChars('0','x');
	resfile.reset(nullptr); // we no longer need the resource file below this point
	 
	return 34;

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
		Chz_Print("Wrote ZDS");
		return 128;
	}
	else {
		Chz_PrintError("Write failed");
	}


	return 420;
}

// TODO: Pass argv from main
int CheezMain(HINSTANCE hInstance) {
	// Load save file
	//void G_DoLoadGame()
	Cheez_InitCVars();

	Chz_Print("G_DoGameLoad() -> FLevelLocals::SnapshotLevel() -> FLevelLocals::Serialize()");

	const char* path = "C:\\Users\\melti\\Saved Games\\GZDoom\\doom.id.doom2.commercial\\";
	FString savename("save02.zds");
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
		Chz_PrintError("DoLoadGame() failed");
		return 80085;
	}

	//arc.GetCompressedOutput();
	// Read and edit
	

	// Write back
	
	savename.Substitute("save", "fucked");
	CheezWrite(&savename,false);


	return code;
}
