#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "Sounds.hpp"
#include "Laser.hpp"


int main4(){
    int term = 0;
    FsOpenWindow(0,0,winX,winY,1);
    LaserBeam beam(20);
    //Laser beam;
    while(term==0){
        FsPollDevice();
        int key = FsInkey();

        switch(key)
        {
        	case FSKEY_ESC:
                term=1;
                break;
            
            case FSKEY_SPACE:
                beam.Reset();
                break;
        }

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        beam.Move();
        beam.CheckHit();
        beam.CheckExist();
        beam.Draw();
        FsPushOnPaintEvent();
        FsSwapBuffers();
        FsSleep(1);

    }      
    return 0;
}