#pragma once
#include <math.h>

#define ASSET_PATH "assets\\"
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define CANVAS_WIDTH 1000
#define CANVAS_HEIGHT 500

#define CARD_WIDTH 80
#define CARD_HEIGHT 120
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define RANDMAX 13

#define SETCOLOR(c,r,g,b) {c[0]=r; c[1]=g; c[2]=b;}



inline float distance(float x1, float y1, float x2, float y2) {
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}