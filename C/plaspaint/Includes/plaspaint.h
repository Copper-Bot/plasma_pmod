#include "../../shared/plasma.h"
#include "../../shared/plasmaCoprocessors.h"

#ifndef PLASPAINT_H
#define PLASPAINT_H

#define MemoryRead(A)     (*(volatile unsigned int*)(A))
#define MemoryWrite(A, V) *(volatile unsigned int*)(A)=(V)

#define MODE_HOMESCREEN 0
#define MODE_NORMAL 1
#define MODE_CHROMATIC 2

#define WHITE        0xFFFF
#define BLACK            0x0000
#define CURSOR_COLOR            0x0000
#define MAX_X            96
#define MAX_Y            64
#define OLED_SIZE 6144
#define RED                0xF800
#define GREEN        0x07C0
#define BLUE            0x001F

#define L_CLICK        0
#define MID_CLICK    1
#define R_CLICK        2
#define X_POS            3
#define Y_POS            4
#define Z_POS            5

#define TOUCHE 0
#define APPUI  5
#define A    10
#define B    11
#define C    12
#define D    13
#define E    14
#define F    15

#define PENCIL    10
#define ERASER    11

#define SQUARE            0

void pencil(int size, int shape);
void stylo();
void getKeyb(int *keyb);
void homeScreen();
void getMouse(int *mouse);
void eraser(int size);
void paintSketchArea(int x, int y, int shape, int size, int color);
void paintAllBackground(int color);
int pix_on_screen(int x, int y);
int isXonScreen(int x);
int isYonScreen(int y);
void clearSketch(int color);
void initOledBitmap();
int isInCursorZone(char i, char j);
void printPixelAndCursor(char row, char col, int color);
void printPixel(char row, char col, int color);
void initSketch();
void displaySketch();
void updateCursor(int x, int y);
void displayChromaticScaleColors();
void setColorAndTool();

#endif
