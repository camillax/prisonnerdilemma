#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fssimplewindow.h"
#include "Sounds.hpp"


#define Pi 3.14159

int winX = 800, winY = 600; // window size 
int x_init = 100, y_init = winY-100,  theta_init = 45.0; // laser beam initial position

//===helper function to draw laser======================================================
void DrawCircle(double x,double y,int rad)
{
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0; i<360; i+=60)
	{
		double a=(double)i*Pi/180.0;
		double s=sin(a);
		double c=cos(a);

		double xx=(double)x+c*(double)rad;
		double yy=(double)y+s*(double)rad;
		glVertex2d(xx,yy);
	}
	glEnd();
}

//========================================================================================
//the laserbeam is consisted of an array of Laser object, this class is the laser object
//Varaibles:
//  hitCount: to count how many times the laser beam contacted obstacles
//  ExistState: if hitCount >= maximum hit the ExistState==0 which won't draw
//  x: x coordinate 
//  y: y coordinate
//  theta: angle in degrees 
//  v: moving velocity
//========================================================================================
class Laser{
public:
    int ExistState = 1, hitCount = 0, hitMax = 10;
    double x = (double)x_init, y = (double)y_init, theta=(double)theta_init, v=5.0;
    Laser();
    ~Laser();
    void Set(double nx, double ny); // Set the x y coordinates
    void Move(void); // Move the object 
    bool CheckHit(MirrorAll &mirrors); // Check whether the laser object contacted obstacles
    bool CheckHit(Player &player); //check whether the laser object contacted players
    void Draw(void); // Draw the laser object
    void CheckExist(void); // Check whether the laser object exist
    void Reset(void); // to 
};


Laser::Laser(){}
Laser::~Laser(){}

void Laser::Set(double nx, double ny){
    x = nx;
    y = ny;
}

void Laser::Move(void){
    x = x + v*cos(theta*Pi/180.0);
    y = y - v*sin(theta*Pi/180.0);
}

bool Laser::CheckHit(MirrorAll &mirrors){   
    if(x>=winX || x<=0){
        double alpha = 90.0;
        theta = 2.0*alpha - theta;
        hitCount++; 
    }
    if(y>=winY || y<=0){
        double alpha = 180.0;
        theta = 2.0*alpha - theta;
        hitCount++;
    }
    //if(BlockCheckHit(x, y) == true){
    //    hitCount = hitMax;
    //}

    if(mirrors.AnyHit(x, y) == false){
        double alpha = 180.0;
        theta = 2.0*alpha - theta;
        hitCount++;
        return true; 
    }

    return false;
}

bool Laser::CheckHit(Player &player)
{
    if(player.hit(x,y)&&ExistState==1)
    {
        return true;
    }
    return false;
}


void Laser::Draw(void) {
    if(ExistState==1){
        glColor3ub(0,255,0);
        DrawCircle(x, y, 5);
    }
    
}

void Laser::CheckExist(void){
    if (hitCount >= hitMax){
        ExistState = 0;
    }    
}

void Laser::Reset(void){
    x = x_init;
    y = y_init;
    theta = theta_init;
    hitCount = 0;
    ExistState = 1;
}
//=================================================================================
//This class is to create laser beam(an array of previous laser objects)
//  LaserBeam(int nl): construct an array with nl laser objects and set their coordinates with offsets so that they form a line
//  CheckHit(void): loop through each object to see whether they hit obstacles, if the first object hits play rebound sound
//=================================================================================
class LaserBeam{
public:
    int n=0;
    Laser *laser = NULL;

    LaserBeam();
    LaserBeam(int nl);
    ~LaserBeam();
    void Move(void);
    void CheckExist(void);
    void CheckHit(MirrorAll &mirrors);
    bool CheckHit(Player player);
    void Draw(void);
    void Reset(void);
    void Init(int x, int y, int theta);
};

LaserBeam::LaserBeam(){
}

LaserBeam::LaserBeam(int nl){
    n = nl;
    laser = new Laser[n];
    for(int i=0; i<n; i++){
        int a = laser[i].theta;
        double nextX = laser[i].x + (double)i*5.0*cos(a*Pi/180.0);
        double nextY = laser[i].y - (double)i*5.0*sin(a*Pi/180.0);
        laser[i].Set(nextX, nextY);
    }
}

LaserBeam::~LaserBeam(){
    delete [] laser;
}

void LaserBeam::Move(void){
    for(int i=0; i<n; i++){
        laser[i].Move();
    }
}

void LaserBeam::CheckExist(void){
    for(int i=0; i<n; i++){
        laser[i].CheckExist();
    }
}

void LaserBeam::CheckHit(MirrorAll &mirrors){
    for(int i=0; i<n; i++){
        if (laser[i].CheckHit(mirrors) == true && i==0){
            sound.PlayRebound();
        }
    }
    if((laser[0].x>=winX || laser[0].x<=0) && laser[0].ExistState==1)
    {
        sound.PlayRebound();
    }
    if((laser[0].y>=winY || laser[0].y<=0) && laser[0].ExistState==1)
    {
        sound.PlayRebound();
    }

}

bool LaserBeam::CheckHit(Player player) {
    if(laser[0].CheckHit(player))
    {
        return true;
    }
    return false;
}

void LaserBeam::Draw(void){
    for(int i=0; i<n; i++){
        laser[i].Draw();
    }
}

void LaserBeam::Reset(void){
    for(int i=0; i<n; i++){
        laser[i].Reset();
    }
    for(int i=0; i<n; i++){
        int a = laser[i].theta;
        double nextX = laser[i].x + (double)i*5.0*cos(a*Pi/180.0);
        double nextY = laser[i].y - (double)i*5.0*sin(a*Pi/180.0);
        laser[i].Set(nextX, nextY);
    }
}

void LaserBeam::Init(int x, int y, int theta) {
    x_init = x;
    y_init = y;
    theta_init = theta;
}
