//make a class header for the player functions
//then populate the draw player funcion myself.
//just set everything up so that it's not that hard to incorporate everything together for the player class

//don't forget to try to find some sounds that would be good to use for this

#include "Player.h"

#define PI 3.14159265

//the default values are there to allow the user to either only choose the player number and use those defaults or to be able to set their own position as wanted.
void Player::SetPlayerVal(int player_number, int x, int y, int angle, int screenW_px, int screenH_px) {

    if(x==0 && y==0 && angle==0 && player_number!=0)
    {
        switch(player_number)
        {
            case 1:
                p_x = 50;
                p_y = screenH_px - 50;
                p_theta = -45*PI/180;
                p_num = player_number;
                break;
            case 2:
                p_x = screenW_px - 50;
                p_y = screenH_px - 50;
                p_theta = -135*PI/180;
                p_num = player_number;
                break;
        }
    }
    else
    {
        p_x = x;
        p_y = y;
        p_theta = angle;
        p_num = player_number;
    }

}

void Player::DrawPlayer() {
    //set the color of the player 1 is green, 2 is blue and the default is black
    switch(p_num)
    {
        case 1:
            r = 0;
            g = 128;
            b = 0;
            break;
        case 2:
            r = 0;
            g = 0;
            b = 128;
            break;
        default:
            r = 0;
            g = 0;
            b = 0;
    }
    //drawing all the quads that make up the character
    glBegin(GL_QUADS);
    glColor3ub(r,g,b);
    //body
    glVertex2d(p_x-body_w/2, p_y+body_l/2);
    glVertex2d(p_x+body_w/2, p_y+body_l/2);
    glVertex2d(p_x+body_w/2, p_y-body_l/2);
    glVertex2d(p_x-body_w/2, p_y-body_l/2);
    //head
    glVertex2d(p_x-head_w/2, p_y-body_l/2);
    glVertex2d(p_x+head_w/2, p_y-body_l/2);
    glVertex2d(p_x+head_w/2, p_y-(body_l/2+head_l));
    glVertex2d(p_x-head_w/2, p_y-(body_l/2+head_l));
    //legs
    glVertex2d(p_x-leg_w/2, p_y+body_l/2);
    glVertex2d(p_x+leg_w/2, p_y+body_l/2);
    glVertex2d(p_x+leg_w/2, p_y+(body_l/2+leg_l));
    glVertex2d(p_x-leg_w/2, p_y+(body_l/2+leg_l));
    glEnd();
    //arm
    glLineWidth((GLfloat)10);
    glEnable(GL_LINE_SMOOTH);
    glBegin(GL_LINES);
    glVertex2d(p_x,p_y);
    glVertex2d(p_x+arm_l*cos(p_theta),p_y+arm_l*sin(p_theta));

    glEnd();
}