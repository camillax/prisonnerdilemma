#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fssimplewindow.h"
#include "Sounds.hpp"
#define Pi 3.14159

int winX = 800, winY = 600; // window size 
int x_init = 100, y_init = winY-100; // laser beam initial position

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
    int ExistState = 1, hitCount = 0;
    double x = (double)x_init, y = (double)y_init, theta=45.0, v=5.0;
    Laser();
    ~Laser();
    void Set(double nx, double ny); // Set the x y coordinates
    void Move(void); // Move the object 
    void CheckHit(void); // Check whether the laser object contacted obstacles
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

void Laser::CheckHit(void){   
    if(x>=winX || x<=0)
    {
        double alpha = 90.0;
        theta = 2.0*alpha - theta;
        hitCount++; 
    }
    if(y>=winY || y<=0)
    {
        double alpha = 180.0;
        theta = 2.0*alpha - theta;
        hitCount++;
    }


}

void Laser::Draw(void) {
    if(ExistState==1){
        glColor3ub(0,255,0);
        DrawCircle(x, y, 5);
    }
    
}

void Laser::CheckExist(void){
    if (hitCount >= 5){
        ExistState = 0;
    }    
}

void Laser::Reset(void){
    x = x_init;
    y = y_init;
    theta = 45.0;
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
    void CheckHit(void);
    void Draw(void);
    void Reset(void);
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

void LaserBeam::CheckHit(void){
    for(int i=0; i<n; i++){
        laser[i].CheckHit();
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
