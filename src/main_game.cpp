//24-780 Engineering Computation - Prisoners' Dilemma
//file by Siri Maley (smaley)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"

#include "Player.h"
#include "Mirror.h"
#include "Block.h"
#include "Laser.h"


int screenW_px = 800;
int screenH_px = 600;
int sleep_millisec = 1;

/////MAIN/////
int main(void)
{
	//Initalize Inputs
	Input input[2];
	int lb, mb, rb, mx, my;
	auto evt = FsGetMouseEvent(lb, mb, rb, mx, my);

	//Initialize Modes
	bool rules_ready[2] = { false, false }; //each player
	int mode = 0;
	int start_sec = 1; //duration of start image (seconds)

	//Laser
	LaserBeam beam(20);

	//Mirrors
	MirrorAll mirrors = MirrorAll();
	mirrors.AddMirror(60, 100); //hardcoded, replace with mouse polling inputs
	mirrors.AddMirror(100, 300);
	mirrors.AddMirror(600, 400);

	//Player
	Player shooters[2];
	shooters[0].SetPlayerVal(1, 0, 0, 0, screenW_px, screenH_px);
	shooters[1].SetPlayerVal(2, 0, 0, 0, screenW_px, screenH_px);

	//Pngs
	YsRawPngDecoder pic_bkg, pic_start, pic_rules;
	pic_bkg.Decode("images/pd_blocked.png");
	pic_bkg.Flip();

	pic_start.Decode("images/pd_start.png");
	pic_start.Flip();

	pic_rules.Decode("images/pd_rules.png");
	pic_rules.Flip();

	////GRAPHIC LOOP////
	FsOpenWindow(16, 16, screenW_px+1, screenH_px+1, 1);
	int terminate = 0;
	auto start_tstamp = time(nullptr);
	while (0 == terminate)
	{
		FsPollDevice();
		auto key = FsInkey();
		
		//Get Keyboard Input
		switch(key)
		{
      	case FSKEY_ESC:
			terminate=1;
            break;
		case FSKEY_SPACE:
			beam.Reset();
	  		input[0].shoot = true;
			break;
		case FSKEY_A:
			if (mode = 1)
			{
				rules_ready[0] = true;
			}
			break;
		case FSKEY_L:
			if (mode = 1)
			{
				rules_ready[1] = true;
			}
			break;
      }

		//Get Mouse Input
		evt = FsGetMouseEvent(lb, mb, rb, mx, my);
		input[0].mouse_x = mx;
		input[0].mouse_y = my;
		input[0].mouse_event = evt;

		////Get Mode
		if ((time(nullptr) - start_tstamp > start_sec) && (mode == 0)) //move out of start mode
		{
			mode = 1;
		}
		else if ((mode == 1) && (rules_ready[0] == true) && (rules_ready[1] == true)) // move out of rules mode
		{
			mode = 2;
		}

		////DRAW////
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		//Image Switching
		switch (mode)
		{
		case 0: //mode
			glRasterPos2d(0, pic_start.hei);
			glDrawPixels(pic_start.wid, pic_start.hei, GL_RGBA, GL_UNSIGNED_BYTE, pic_start.rgba);
			break;

		case 1: //rules
			glRasterPos2d(0, pic_rules.hei);
			glDrawPixels(pic_rules.wid, pic_rules.hei, GL_RGBA, GL_UNSIGNED_BYTE, pic_rules.rgba);
			break;

		case 2: //play
			//Bkg Image
			glRasterPos2d(0, pic_bkg.hei);
			glDrawPixels(pic_bkg.wid, pic_bkg.hei, GL_RGBA, GL_UNSIGNED_BYTE, pic_bkg.rgba);
			//DrawBlock(screenW_px, screenH_px);

			//Laser
			beam.Move();
			beam.CheckHit();
			beam.CheckExist();
			beam.Draw();

			//Shooters
			shooters[0].DrawPlayer();
			shooters[1].DrawPlayer();

			//Mirrors
			mirrors.Draw(); //replace parameters with laser coordinates
			bool mirrorHit = mirrors.AnyHit(5, 5);

			break;
		}

		FsSwapBuffers();
		FsSleep(sleep_millisec);
	}

	return 0;
}
