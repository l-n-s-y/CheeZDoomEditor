#include <Windows.h>

#ifdef _WIN32
#include <direct.h>
#endif

#include <math.h>
#include <assert.h>

#include "engineerrors.h"

#include "g_mapinfo.h"
//#include "i_time.h"
//#include "d_gui.h"
#include "m_random.h"
//#include "doomdef.h"
//#include "doomstat.h"
//#include "gstrings.h"
//#include "filesystem.h"
//#include "s_sound.h"
//#include "v_video.h"
//#include "intermission/intermission.h"
//#include "wipe.h"
//#include "m_argv.h"
//#include "m_misc.h"
//#include "menu.h"
//#include "doommenu.h"
//#include "c_console.h"
//#include "c_dispatch.h"
//#include "i_sound.h"
//#include "i_video.h"
//#include "g_game.h"
//#include "hu_stuff.h"
//#include "wi_stuff.h"
//#include "st_stuff.h"
//#include "am_map.h"
//#include "p_setup.h"
//#include "r_utility.h"
//#include "r_sky.h"
//#include "d_main.h"
//#include "d_dehacked.h"
//#include "cmdlib.h"
//#include "v_text.h"
//#include "gi.h"
//#include "a_dynlight.h"
//#include "gameconfigfile.h"
//#include "sbar.h"
//#include "decallib.h"
//#include "version.h"
//#include "st_start.h"
//#include "teaminfo.h"
//#include "hardware.h"
//#include "sbarinfo.h"
//#include "d_net.h"
//#include "d_event.h"
//#include "d_netinf.h"
//#include "m_cheat.h"
//#include "m_joy.h"
//#include "v_draw.h"
//#include "po_man.h"
//#include "p_local.h"
//#include "autosegs.h"
//#include "fragglescript/t_fs.h"
//#include "g_levellocals.h"
//#include "events.h"
//#include "vm.h"
//#include "types.h"
//#include "i_system.h"
//#include "g_cvars.h"
//#include "r_data/r_vanillatrans.h"
//#include "s_music.h"
//#include "swrenderer/r_swcolormaps.h"
//#include "findfile.h"
//#include "md5.h"
//#include "c_buttons.h"
//#include "d_buttons.h"
//#include "i_interface.h"
//#include "animations.h"
//#include "texturemanager.h"
//#include "formats/multipatchtexture.h"
//#include "scriptutil.h"
//#include "v_palette.h"
//#include "texturemanager.h"
//#include "hw_clock.h"
//#include "hwrenderer/scene/hw_drawinfo.h"
//#include "doomfont.h"
//#include "screenjob.h"
//#include "startscreen.h"
//#include "shiftstate.h"
//
//#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <stddef.h>
//#include <memory>
//
//#include "i_time.h"
//
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

#include "v_video.h"
#include "g_hub.h"
#include "g_levellocals.h"
#include "events.h"
#include "c_buttons.h"
#include "d_buttons.h"
#include "hwrenderer/scene/hw_drawinfo.h"
#include "doommenu.h"
#include "screenjob.h"
#include "i_interface.h"
#include "fs_findfile.h"

#include "g_game.h"

#include <stdint.h>
#include <type_traits>

struct Fuck {
public:
	int idx=20;
};

inline const char* mapName = "MAP01";


int CheezMain(HINSTANCE hInstance) {
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
					("index",rngg.idx)
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

	FString filename("custom_save.zds");
	

	//// G_WriteSnapshots()
	////unsigned int i;
	////FString filename;

	
	//for (i = 0; i < wadlevelinfos.Size(); i++)
	//{
		//continue; // skip entire loop
		//if (wadlevelinfos[i].Snapshot.mCompressedSize > 0)
		//{
	//FString filename2("C:\\Users\\melti\\OneDrive\\Desktop\\",filename);
	filename = NicePath(filename.GetChars());
	filename.Substitute("\\", "/");
	
	FString fname;
	//FString fname(mapName,".map.json");
	//fname.Format("%s/%s", filename, fname);
	fname.Format("%s.map.json", mapName);
	fname.ToLower();
	savegame_filenames.Push(fname);
	
	level_info_t l;
	//FCompressedBuffer snapshotBuf;
	//savegame_content.Push(snapshotBuf);
	savegame_content.Push(l.Snapshot);
		//}
	//}


	for (unsigned i = 0; i < savegame_content.Size(); i++)
		savegame_content[i].filename = savegame_filenames[i].GetChars();

	bool succeeded = false;

	if (WriteZip(filename.GetChars(), savegame_content.Data(), savegame_content.Size()))
	{
		// Check whether the file is ok by trying to open it.
		FResourceFile* test = FResourceFile::OpenResourceFile(filename.GetChars(), true);
		if (test != nullptr)
		{
			delete test;
			succeeded = true;
		}
	}

	savegame_content[1].Clean();
	savegame_content[2].Clean();

	///*FResourceFile* testFile = FResourceFile::OpenResourceFile("test.zds");

	//auto info = testFile->FindEntry("info.json");
	//auto infoData = testFile->Read(info);

	//FSerializer arc;
	//if (!arc.OpenReader(infoData.string(), infoData.size())) {
	//	return -1;
	//}
	//FCompressedBuffer buff;
	//WriteZip("test.zds",&buff,(size_t)10);*/


	return 69;
}
