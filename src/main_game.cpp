//24-780 Engineering Computation - Prisoners' Dilemma
//file by Siri Maley (smaley)

#include <stdio.h>
#include <stdlib.h>

#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "yspng.h"

#include "Player.h"
#include "Mirror.h"
#include "Laser.hpp"

int screenW_px = 961;
int screenH_px = 721;
int sleep_millisec = 1;

/////MAIN/////
int main(void)
{
	Input input[2];
	int lb, mb, rb, mx, my;
	auto evt = FsGetMouseEvent(lb, mb, rb, mx, my);

////Laser
	LaserBeam beam(20);

	//Mirrors
	MirrorAll mirrors = MirrorAll();
	mirrors.AddMirror(60, 100); //hardcoded, replace with mouse polling inputs
	mirrors.AddMirror(100, 300);
	mirrors.AddMirror(600, 400);

	//Player
	Player shooters[2];
	shooters[0].SetPlayerVal(1);
	shooters[1].SetPlayerVal(2);

	//Pngs
	YsRawPngDecoder pic_bkg, pic_start, pic_rules, png4;
	pic_bkg.Decode("pd_bkg.png");
	pic_bkg.Flip();

	pic_start.Decode("pd_start.png");
	pic_start.Flip();

	pic_rules.Decode("pd_rules.png");
	pic_rules.Flip();

	//GRAPHIC LOOP
	FsOpenWindow(16, 16, screenW_px, screenH_px, 1);
	int terminate = 0;
	while (0 == terminate)
	{
		FsPollDevice();
		auto key = FsInkey();
		//Laser
		switch(key)
		{
      	case FSKEY_ESC:
			terminate=1;
            break;
		case FSKEY_SPACE:
			beam.Reset();
	  		input[0].shoot = true;
			break;
      }

		//Player
		evt = FsGetMouseEvent(lb, mb, rb, mx, my);
		input[0].mouse_x = mx;
		input[0].mouse_y = my;
		input[0].mouse_event = evt;

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glRasterPos2d(0, pic_bkg.hei);
		glDrawPixels(pic_bkg.wid, pic_bkg.hei, GL_RGBA, GL_UNSIGNED_BYTE, pic_bkg.rgba);

		beam.Move();
		beam.CheckHit();
		beam.CheckExist();
		beam.Draw();
		shooters[0].DrawPlayer();
		shooters[1].DrawPlayer();
		mirrors.Draw(); //replace parameters with laser coordinates
		bool mirrorHit = mirrors.AnyHit(5, 5);

		FsSwapBuffers();
		FsSleep(sleep_millisec);
	}

	return 0;
}
