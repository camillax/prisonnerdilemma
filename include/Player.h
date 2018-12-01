//
// Created by keimu on 11/15/2018.
//

#ifndef HW_PLAYER_H
#define HW_PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "fssimplewindow.h"

struct Input
{
    int theta;
    int x;
    int y;
    bool shoot;
    double mouse_x;
    double mouse_y;
    int mouse_event;
};

class Player
{
private:
    int p_x;
    int p_y;
    double p_theta;
    int p_num;
    //variables for the sizes of the player
    int body_w = 20;
    int body_l = 40;
    int head_w = 30;
    int head_l = 30;
    int leg_w = 10;
    int leg_l = 30;
    int arm_w = 10;
    int arm_l = 40;
    //color variables
    int r;
    int g;
    int b;

public:
    void SetPlayerVal(int player_number=0, int x=0, int y=0, int angle=0);
    void ChangePlayerVal(int angle=0, int x=0, int y=0);
    void DrawPlayer(void);
};

#endif //HW_PLAYER_H
