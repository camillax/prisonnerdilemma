//
// Created by smaley on 11/26/2018.
//

#ifndef HW_BLOCK_H
#define HW_BLOCK_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "fssimplewindow.h"
#include "yspng.h"
using namespace std;

void DrawRedBlock(int x, int y);
void DrawGreyBlock(int x, int y);
void DrawBlock(int screenW_px, int screenH_px);
bool BlockCheckHit(int x, int y);

#endif //HW_BLOCK_H
