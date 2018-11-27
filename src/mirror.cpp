#include <stdlib.h>
#include <stdio.h>
#include "fssimplewindow.h"

#define winWid 800 //can change depending on final code
#define winHei 600 //can change depending on final code


/*Mirror Class:
A single mirror object
Key functions: Place(x, y)--will set the mirror location as x, y (center)
Draw()--will draw the mirror
Hit(lx, ly)--given laser location lx, ly, will check
if it has been hit*/

class Mirror {
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

Mirror::Mirror(void) {
	x = -1.;
	y = -1.;
	wid = 80.;
	hei = 4.;
}

void Mirror::SetX(int mx) {
	x = mx;
}

void Mirror::SetY(int my) {
	y = my;
}

double Mirror::GetX(void) const {
	return x;
}

double Mirror::GetY(void) const {
	return y;
}

void Mirror::Place(int mx, int my) {
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
}

void Mirror::DrawMirror(void) const {
	glBegin(GL_QUADS);
	glVertex2i(x - wid / 2., y - hei / 2.);
	glVertex2i(x + wid / 2., y - hei / 2.);
	glVertex2i(x + wid / 2., y + hei / 2.);
	glVertex2i(x - wid / 2., y + hei / 2.);
	glEnd();
}

bool Mirror::Hit(int lx, int ly) const {
	if (lx >= x - wid / 2. && lx <= x + wid / 2. &&
		ly >= y - hei / 2. && ly <= y + hei / 2.) {
		return true;
	}
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

public:
	MirrorAll();
	~MirrorAll();

	void CleanUp(void);
	void AddMirror(int mx, int my); //can change to take doubles as well
	void Draw(void) const;
	bool AnyHit(int lx, int ly) const;
};

//Constructor. Initializes array as NULL and index as 0
MirrorAll::MirrorAll(void) {
	mirrArray = NULL;
	ind = 0;
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
void MirrorAll::AddMirror(int mx, int my) {
	//If array is uninitialized, initializes it
	if (mirrArray == NULL) {
		//hopefully 1000 is plenty...don't want to deal with ubas
		mirrArray = new Mirror[1000];
		ind = 0;
	}

	//add to array, increase index
	Mirror newMirr = Mirror();
	newMirr.Place(mx, my);
	mirrArray[ind] = newMirr;
	ind++;
}

//Draws all the mirrors
void MirrorAll::Draw(void) const {
	glColor3ub(138, 219, 255);
	for (int i = 0; i < ind; i++) {
		mirrArray[i].DrawMirror();
	}
}

//Checks if any of the mirrors have been hit
bool MirrorAll::AnyHit(int lx, int ly) const {
	for (int i = 0; i < ind; i++) {
		if (mirrArray[i].Hit(lx, ly)) return false;
	}
	return true;
}

//int main(void) {
//	int term = 0;
//	MirrorAll mirrors = MirrorAll();
//
//	//hardcoded, replace with mouse polling inputs
//	mirrors.AddMirror(60, 100);
//	mirrors.AddMirror(100, 300);
//	mirrors.AddMirror(600, 400);
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