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
#define CURSOR_DEFAULT_COLOR  BLACK
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

#define MAX_CURSOR_MATRIX 15
#define CURSOR_CENTER (MAX_CURSOR_MATRIX/2)

// Outils :
#define PENCIL_SQUARE 0
#define PENCIL_CIRCLE 1
#define PENCIL_POINT  2
#define PENCIL_DIAGONAL  3
#define EYEDROPPER 10
#define ERASER 11

// Curseurs
#define SQUARE  0
#define CIRCLE	1
#define POINT	2
#define DIAGONAL 3

#define COLOR_SELECTOR 10


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
void updateCursorMatrix(int tool);
void clearCursorMatrix();
void displayChromaticScaleColors();
void setColorAndTool();
void setCurrentColor(int color);

#endif
