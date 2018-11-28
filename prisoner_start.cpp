//24-780 Engineering Computation - Prisoners' Dilemma
//file by Siri Maley (smaley)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>

#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "yspng.h"

#include "Sounds.hpp"
#include "Laser.hpp"
#include "Player.h"
#include "Mirror.h"

int screenW_px = 961;
int screenH_px = 721;


//the render function to keep compatibility with mac
void Render1(void *incoming)
{
	Player *test = (Player *)incoming;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	test[0].DrawPlayer();
	test[1].DrawPlayer();
	FsSwapBuffers();
}

/////MAIN/////
int main(void)
{
	//Input input[2];
//int lb, mb, rb, mx, my;
//auto evt = FsGetMouseEvent(lb, mb, rb, mx, my);

////Laser
//LaserBeam beam(20);

////Mirrors
//MirrorAll mirrors = MirrorAll();

////hardcoded, replace with mouse polling inputs
//mirrors.AddMirror(60, 100);
//mirrors.AddMirror(100, 300);
//mirrors.AddMirror(600, 400);

////Player
//Player test[2];
//test[0].SetPlayerVal(1);
//test[1].SetPlayerVal(2);
//FsRegisterOnPaintCallBack(Render1, &test);

	//Pngs
	YsRawPngDecoder pic_bkg, pic_start, pic_rules, png4;
	pic_bkg.Decode("pd_bkg.png");
	pic_bkg.Flip();

	pic_start.Decode("pd_start.png");
	pic_start.Flip();

	pic_rules.Decode("pd_rules.png");
	pic_rules.Flip();

	//GRAPHIC LOOP
	FsOpenWindow(16, 16, 961, 721, 1);
	int terminate = 0;
	while (0 == terminate)
	{
		////Laser
//      switch(key)
//      {
//      	case FSKEY_ESC:
//              term=1;
//              break;
//          
//          case FSKEY_SPACE:
//              beam.Reset();
	  //		input[0].shoot = true;
//              break;
//      }

	  ////Player
	  //evt = FsGetMouseEvent(lb, mb, rb, mx, my);
	  //input[0].mouse_x = mx;
	  //input[0].mouse_y = my;
	  //input[0].mouse_event = evt;

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glRasterPos2d(0, pic_bkg.hei);
		glDrawPixels(pic_bkg.wid, pic_bkg.hei, GL_RGBA, GL_UNSIGNED_BYTE, pic_bkg.rgba);

		//      beam.Move();
//      beam.CheckHit();
//      beam.CheckExist();
//      beam.Draw();

	  //mirrors.Draw();
	  //replace parameters with laser coordinates
	  //bool mirrorHit = mirrors.AnyHit(5, 5);

	  //FsPushOnPaintEvent(); //Player

		FsSwapBuffers();
		FsSleep(1000);
	}

    return 0;
}
