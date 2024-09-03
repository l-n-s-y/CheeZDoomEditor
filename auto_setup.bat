@echo off


if exist zmusic goto SKIP_ZMUSIC
git clone https://github.com/zdoom/zmusic
mkdir zmusic\build
cd zmusic\build
cmake ..
cd ..\..
:SKIP_ZMUSIC

if not exist gzdoom git clone https://github.com/zdoom/gzdoom
xcopy /Y i_main.cpp gzdoom\src\common\platform\win32\i_main.cpp
xcopy /Y g_game.h gzdoom\src\g_game.h
if exist gzdoom\build goto NO_CMAKE
mkdir gzdoom\build
cd gzdoom\build
cmake ..
goto CONTINUE
:NO_CMAKE
cd gzdoom\build
:CONTINUE
xcopy /Y ..\..\cheez* src\
python3 ..\..\vcx_inject.py
start GZDoom.sln
cd ..\..
echo CheeZ project has been constructed
echo
echo You'll need to build ZMUSIC.DLL too
echo
echo Now go find a DOOM.wad
