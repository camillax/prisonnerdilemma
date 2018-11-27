//
// Created by smaley on 11/25/2018.
//

#ifndef HW_MIRROR_H
#define HW_MIRROR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "fssimplewindow.h"

class Mirror
{
public:
private:
	double wid, hei;
	double x, y; //center of mirror
public:
	Mirror(); //constructor sets x, y to -1

	void SetX(int mx);
	void SetY(int my);
	double GetX(void) const;
	double GetY(void) const;


	void Place(int mx, int my);
	bool Hit(int lx, int ly) const;
	void DrawMirror(void) const;
};

class MirrorAll
{
private:
	int ind;
	Mirror *mirrArray;

public:
	MirrorAll();
	~MirrorAll();

	void CleanUp(void);
	void AddMirror(int mx, int my); //can change to take doubles as well
	void Draw(void) const;
	bool AnyHit(int lx, int ly) const;
};

#endif //HW_MIRROR_H
