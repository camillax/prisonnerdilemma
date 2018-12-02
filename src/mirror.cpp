#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "fssimplewindow.h"

#define winWid 800 //can change depending on final code
#define winHei 600 //can change depending on final code
#define mirrPI 3.14159265359


/*Mirror Class:
A single mirror object
Key functions: Place(x, y)--will set the mirror location as x, y (center)
Draw()--will draw the mirror
Hit(lx, ly)--given laser location lx, ly, will check
if it has been hit*/

bool distEqual(double a, double b) {
	return (fabs(a - b) < 1);
}

class Mirror {
public:
private:
	double wid, hei;
	double x, y; //center of mirror
	double angle;
public:
	Mirror(); //constructor sets x, y to -1

	void SetX(int mx);
	void SetY(int my);
	void SetAngle(double theta);
	double GetX(void) const;
	double GetY(void) const;
	double GetAngle(void) const;

	void Place(int mx, int my, double theta);
	bool Hit(int lx, int ly) const;
	void DrawMirror(void) const;
};

Mirror::Mirror(void) {
	x = -1.;
	y = -1.;
	wid = 80.;
	hei = 4.;
}

void Mirror::SetX(int mx) {
	x = (double)mx;
}

void Mirror::SetY(int my) {
	y = (double)my;
}

void Mirror::SetAngle(double theta) {
	angle = theta;
}

double Mirror::GetX(void) const {
	return x;
}

double Mirror::GetY(void) const {
	return y;
}

//returns in radians!!
double Mirror::GetAngle(void) const {
	return angle;
}

void Mirror::Place(int mx, int my, double theta) {
	//insert other restrictions as necessary
	//return if placement not valid
	//for x wrt window
	if ((winWid - (double)mx) <= wid / 2. || (double)mx <= wid / 2.) {
		return; //can also insert error before return
	}
	//for y wrt window
	if ((winHei - (double)my) <= hei / 2. || (double)my <= hei / 2.) {
		return; //can also insert error before return
	}
	SetX(mx);
	SetY(my);
	SetAngle(theta*mirrPI/180.);
}

void Mirror::DrawMirror(void) const {
	glBegin(GL_QUADS);

	double xc = (double)x + (hei/2.)*sin(angle);
	double yc = (double)y + (hei/2.)*cos(angle);

	double x1 = xc + (wid/2)*cos(angle);
	double y1 = yc - (wid/2)*sin(angle);
	double x2 = x1 - hei*sin(angle);
	double y2 = y1 - hei*cos(angle);
	double x3 = x2 - wid*cos(angle);
	double y3 = y2 + wid*sin(angle);
	double x4 = x1 - wid*cos(angle);
	double y4 = y1 + wid*sin(angle);


	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glVertex2i(x4, y4);
	glEnd();
}

bool Mirror::Hit(int lx, int ly) const {
	double xc = (double)x + (hei / 2.)*sin(angle);
	double yc = (double)y + (hei / 2.)*cos(angle);

	double x1 = xc + (wid / 2)*cos(angle);
	double y1 = yc - (wid / 2)*sin(angle);
	double x2 = x1 - hei*sin(angle);
	double y2 = y1 - hei*cos(angle);
	double x3 = x2 - wid*cos(angle);
	double y3 = y2 + wid*sin(angle);
	double x4 = x1 - wid*cos(angle);
	double y4 = y1 + wid*sin(angle);

	double d1 = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	double d1a = sqrt(pow(lx - x1, 2) + pow(ly - y1, 2));
	double d1b = sqrt(pow(lx - x2, 2) + pow(ly - y2, 2));

	double d2 = sqrt(pow(x2 - x3, 2) + pow(y2 - y3, 2));
	double d2a = sqrt(pow(lx - x2, 2) + pow(ly - y2, 2));
	double d2b = sqrt(pow(lx - x3, 2) + pow(ly - y3, 2));

	double d3 = sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2));
	double d3a = sqrt(pow(lx - x3, 2) + pow(ly - y3, 2));
	double d3b = sqrt(pow(lx - x4, 2) + pow(ly - y4, 2));

	double d4 = sqrt(pow(x4 - x1, 2) + pow(y4 - y1, 2));
	double d4a = sqrt(pow(lx - x4, 2) + pow(ly - y4, 2));
	double d4b = sqrt(pow(lx - x1, 2) + pow(ly - y1, 2));

	if (distEqual(d1a + d1b, d1) ||
		distEqual(d2a + d2b, d2) ||
		distEqual(d3a + d3b, d3) ||
		distEqual(d4a + d4b, d4)) {
		return true;
	}

	// if (lx >= x - wid / 2. && lx <= x + wid / 2. &&
	// 	ly >= y - hei / 2. && ly <= y + hei / 2.) {
	// 	return true;
	// }


	return false;
}

/*MirrorAll Class:
Puts all mirrors in a 2D list for easier management
Key functions: AddMirror(x, y)--will add a mirror at location x, y
Draw()--will draw all the mirrors
AnyHit(lx, ly)--given laser location lx, ly, will check
if any of the mirrors have been hit*/

class MirrorAll {
private:
	int ind;
	Mirror *mirrArray;
	double hitAngle;

public:
	MirrorAll();
	~MirrorAll();

	void CleanUp(void);
	void AddMirror(int mx, int my, double theta); //can change to take doubles as well
	void SetHitAngle(int ind);
	double GetHitAngle(void) const;
	void Draw(void) const;
	bool AnyHit(int lx, int ly);
};

//Constructor. Initializes array as NULL and index as 0
MirrorAll::MirrorAll(void) {
	mirrArray = NULL;
	ind = 0;
	hitAngle = -1;
}

//Destructor
MirrorAll::~MirrorAll(void) {
	CleanUp();
}

//Cleanup function to prevent memory leaks
void MirrorAll::CleanUp(void) {
	delete[] mirrArray;
	mirrArray = NULL;
}

//Adds a mirror
void MirrorAll::AddMirror(int mx, int my, double theta) {
	//If array is uninitialized, initializes it
	if (mirrArray == NULL) {
		//hopefully 1000 is plenty...don't want to deal with ubas
		mirrArray = new Mirror[100];
		ind = 0;
		hitAngle = -1;
	}

	//add to array, increase index
	Mirror newMirr = Mirror();
	newMirr.Place(mx, my, theta);
	mirrArray[ind] = newMirr;
	ind++;
}

void MirrorAll::SetHitAngle(int hitInd) {
	if (mirrArray != NULL) {
		hitAngle = mirrArray[hitInd].GetAngle();
	}
}

//returns in radians!
double MirrorAll::GetHitAngle(void) const {
	return hitAngle;
}

//Draws all the mirrors
void MirrorAll::Draw(void) const {
	glColor3ub(138, 219, 255);
	for (int i = 0; i < ind; i++) {
		mirrArray[i].DrawMirror();
	}
}

//Checks if any of the mirrors have been hit
bool MirrorAll::AnyHit(int lx, int ly) {
	for (int i = 0; i < ind; i++) {
		if (mirrArray[i].Hit(lx, ly)) {
			SetHitAngle(i);
			return false;
		}
	}
	return true;
}

//int main(void) {
//	int term = 0;
//	MirrorAll mirrors = MirrorAll();
//
//	//hardcoded, replace with mouse polling inputs
//	mirrors.AddMirror(60, 100, 20);
//	mirrors.AddMirror(100, 300, 45);
//	mirrors.AddMirror(600, 400, 90);
//
//	FsOpenWindow(16, 16, winWid, winHei, 1);
//	while (term == 0) {
//		FsPollDevice();
//		int key = FsInkey();
//
//		if (key == FSKEY_ESC)
//		{
//			term = 1;
//		}
//
//		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//		mirrors.Draw();
//		//replace parameters with laser coordinates
//		//bool mirrorHit = mirrors.AnyHit(5, 5);
//
//		FsSwapBuffers();
//		FsSleep(1000);
//	}
//
//	return 0;
//}
