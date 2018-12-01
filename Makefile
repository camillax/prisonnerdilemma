# makefile for prisoner's dilemma code to simplify building the code and clean up the repository. Also I have using VS IDE so this way you can work on the code from temrinal
# To build run 'nmake' from the parent directory where this makefile is.

TARGET = prisoners_dilemma.exe

SOURCE =\
	src/main_game.cpp\
	src/blockWall.cpp\
	src/fssimplewindow.cpp\
	src/mirror.cpp\
	src/Player.cpp\
	src/ysglfontdata.c\
	src/yspng.cpp\
	src/yssimplesound.cpp\
	src/yssimplesound_dsound.cpp
	#src/prisoners_dilemma.cpp\

$(TARGET):$(SOURCE)
	cl /I include /I images /I sounds /Fo".\build/" /Feprisoners_dilemma $(SOURCE)  