//24-780 Engineering Computation - Prisoners' Dilemma
//file by Siri Maley (smaley)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "yspng.h"
#include "ysglfontdata.h"

#include "Player.h"
#include "Mirror.h"
#include "Block.h"
#include "Laser.hpp"


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
	bool winner[2] = { false, false };

    //Laser
    LaserBeam beam(20);

    //Mirrors
    MirrorAll mirrors;
//    mirrors.AddMirror(60, 100); //hardcoded, replace with mouse polling inputs
//    mirrors.AddMirror(100, 300);
//    mirrors.AddMirror(600, 400);

    //Player
    Player shooters[2];
    int p1_x = 50, p1_y = screenH_px-50, p2_x = screenW_px-50, p2_y = screenH_px-50;
    shooters[0].SetPlayerVal(1, p1_x, p1_y);
    shooters[1].SetPlayerVal(2, p2_x, p2_y);

    //Pngs
	YsRawPngDecoder pic_bkg, pic_start, pic_rules, pic_winA, pic_winB;
    pic_bkg.Decode("images/pd_blocked.png");
    pic_bkg.Flip();

    pic_start.Decode("images/pd_start.png");
    pic_start.Flip();

    pic_rules.Decode("images/pd_rules.png");
    pic_rules.Flip();

	pic_winA.Decode("images/pd_winA.png");
	pic_winA.Flip();

	pic_winB.Decode("images/pd_winB.png");
	pic_winB.Flip();

    ////GRAPHIC LOOP////
    FsOpenWindow(16, 16, screenW_px+1, screenH_px+1, 1);
    int terminate = 0;
    auto start_tstamp = time(nullptr);

    //because keitaro is terrible at coding, more global parameters!!:)
    int dt_theta=0, dtt_1=0, dtt_2=0;
    int player_id = 0;
    int p_x, p_y, mirror_x, mirror_y;
    bool fire_flag = false, mirror_place_flag = false;
    bool shooting_init_flag = false, mirror_init_flag=false;




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
                if(shooting_init_flag)
                {
                    if(player_id==1)
                    {
                        p_x = p1_x;
                        p_y = p1_y;
                        dt_theta = 45+dtt_1;
                    }
                    else if(player_id==2)
                    {
                        p_x = p2_x;
                        p_y = p2_y;
                        dt_theta = 135+dtt_2;
                    }
                    beam.Init(p_x,p_y,dt_theta);
                    beam.Reset();
                    fire_flag = true;
                    shooting_init_flag=false;
                    mirror_place_flag=false;
                }
                if(mirror_init_flag)
                {
                    mirrors.AddMirror(mirror_x, mirror_y);
                    mirror_init_flag=false;
                    mirror_place_flag=true;
                }
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
            case FSKEY_S:
                if(!shooting_init_flag)
                {
                    shooting_init_flag = true;
                    switch(player_id)
                    {
                        case 0:
                            player_id=1;
                            break;
                        case 1:
                            player_id=2;
                            break;
                        case 2:
                            player_id=1;
                            break;
                    }
                }
                break;
            case FSKEY_M:
                if(!mirror_init_flag && !mirror_place_flag)
                {
                    mirror_init_flag=true;
                    switch(player_id)
                    {
                        case 0:
                            mirror_x = p1_x;
                            mirror_y = p1_y-100;
                            break;
                        case 1:
                            mirror_x = p2_x;
                            mirror_y = p2_y-100;
                            break;
                        case 2:
                            mirror_x = p1_x;
                            mirror_y = p1_y-100;
                            break;
                    }
                }
                break;
            case FSKEY_UP:
                if(shooting_init_flag)
                {
                    if(player_id==1)
                    {
                        dtt_1+=5;
                        shooters[0].ChangePlayerVal(-5);
                    }
                    else if(player_id==2)
                    {
                        dtt_2-=5;
                        shooters[1].ChangePlayerVal(5);
                    }
                }
                if(mirror_init_flag)
                {
                    mirror_y-=5;
                }
                break;
            case FSKEY_DOWN:
                if(shooting_init_flag)
                {
                    if(player_id==1)
                    {
                        dtt_1-=5;
                        shooters[0].ChangePlayerVal(5);
                    }
                    else if(player_id==2)
                    {
                        dtt_2+=5;
                        shooters[1].ChangePlayerVal(-5);
                    }
                }
                if(mirror_init_flag)
                {
                    mirror_y+=5;
                }
                break;
            case FSKEY_LEFT:
                if(mirror_init_flag)
                {
                    mirror_x-=5;
                }
                break;
            case FSKEY_RIGHT:
                if(mirror_init_flag)
                {
                    mirror_x+=5;
                }
                break;
        }
        //std::cout << dt_theta << endl;

        //Get Mouse Input
//        evt = FsGetMouseEvent(lb, mb, rb, mx, my);
//        input[0].mouse_x = mx;
//        input[0].mouse_y = my;
//        input[0].mouse_event = evt;

        ////Get Mode
        if ((time(nullptr) - start_tstamp > start_sec) && (mode == 0)) //move out of start mode
        {
            mode = 1;
        }
        else if ((mode == 1) && (rules_ready[0] == true) && (rules_ready[1] == true)) // move out of rules mode
        {
            mode = 2;
        }
		else if ((mode == 2) && winner[0] == true) // Player A won
		{
			mode = 3;
		}
		else if ((mode == 2) && winner[1] == true) // Player B won
		{
			mode = 4;
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
                if(fire_flag)
                {
                    beam.Move();
                    beam.CheckHit(mirrors);
		    if(player_id==1)
                    {
                        if(beam.CheckHit(shooters[1]))
                        {
                            winner[0] = true;
                        }
                    }
                    if(player_id==2)
                    {
                        if(beam.CheckHit(shooters[0]))
                        {
                            winner[1] = true;
                        }
                    }
                    beam.CheckExist();
                    beam.Draw();
                }

                //Shooters
                shooters[0].DrawPlayer();
                shooters[1].DrawPlayer();

                //Mirrors
                if(mirror_init_flag)
                {
                    Mirror mirror;
                    mirror.Place(mirror_x,mirror_y);
                    mirror.DrawMirror();
                }
                mirrors.Draw(); //replace parameters with laser coordinates
                //bool mirrorHit = mirrors.AnyHit(5, 5);

                break;
			case 3: 
				glRasterPos2d(0, pic_winA.hei);
				glDrawPixels(pic_winA.wid, pic_winA.hei, GL_RGBA, GL_UNSIGNED_BYTE, pic_winA.rgba);
				break;
			
			case 4:
				glRasterPos2d(0, pic_winB.hei);
				glDrawPixels(pic_winB.wid, pic_winB.hei, GL_RGBA, GL_UNSIGNED_BYTE, pic_winB.rgba);
				break;
        }

        FsSwapBuffers();
        FsSleep(sleep_millisec);
    }

    return 0;
}
