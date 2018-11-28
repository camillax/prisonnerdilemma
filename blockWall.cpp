#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "yspng.h"
using namespace std;

/* 	
	Window size (600, 800)
	Blocks are in the middle
	Set to 300 first
*/
void DrawRedBlock(int x, int y) {
	// bottom left corner (x, y)
	// blockSize(40 ,40)
	YsRawPngDecoder redBrick;
	redBrick.Decode("rsz_red-brick-wall.png");
	redBrick.Flip();
	glRasterPos2d(x, y);  // bottom left
	glDrawPixels(redBrick.wid, redBrick.hei, GL_RGBA, GL_UNSIGNED_BYTE, redBrick.rgba);

}

void DrawGreyBlock(int x, int y) {
	YsRawPngDecoder greyBrick;
	greyBrick.Decode("rsz_brickblock.png");
	greyBrick.Flip();
	glRasterPos2d(x, y);  // bottom left
	glDrawPixels(greyBrick.wid, greyBrick.hei, GL_RGBA, GL_UNSIGNED_BYTE, greyBrick.rgba);
}

void DrawBlock(int screenW_px, int screenH_px) {
	//blockWall ()
	int layer = 11;
	int nums = 7;
	int base = screenH_px - 1;
	int incre;
	for(int i = 0; i < layer; i ++) {
		incre = screenW_px/4;
		base = (screenH_px-1) - i * 39;
		for (int j = 0; j < nums; j ++) {
			if (j % 2 == 0) {
				DrawRedBlock(incre, base);
				incre += 40;
			}
			else {
				DrawGreyBlock(incre, base);
				incre += 70;
			}
		}
	}
}

//int main() {
//	FsOpenWindow(16, 16, 800, 600, 1);
//	bool termFlag = false;
//	while (!termFlag) {
//		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//		DrawBlock();
//		FsSwapBuffers();
//		FsSleep(25);
//	}
//	return 0;
//}

