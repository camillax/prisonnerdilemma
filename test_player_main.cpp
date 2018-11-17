#include "Player.h"

//the render function to keep compatibility with mac
void Render(void *incoming)
{
    Player *test=(Player *)incoming;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    test[0].DrawPlayer();
    test[1].DrawPlayer();
    FsSwapBuffers();
}

Input input[2];

int main(void)
{
    FsOpenWindow(0,0,800,600,1);
    Player test[2];

    test[0].SetPlayerVal(1);
    test[1].SetPlayerVal(2);
    FsRegisterOnPaintCallBack(Render,&test);
    for(;;)
    {
        FsPollDevice();
        auto key=FsInkey();
        if(FSKEY_ESC==key)
        {
            int lb,mb,rb,mx,my;
            auto evt=FsGetMouseEvent(lb,mb,rb,mx,my);
            input[0].mouse_x = mx;
            input[0].mouse_y = my;
            input[0].mouse_event = evt;

            if(key==FSKEY_SPACE)
            {
                input[0].shoot = true;
            }
            break;
        }

        FsPushOnPaintEvent();
        FsSleep(20);
    }
    return 0;
}
