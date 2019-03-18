#include "../../shared/plasma.h"
#include "../../shared/plasmaCoprocessors.h"
#include "../../shared/plasmaMyPrint.h"

#define MemoryRead(A)     (*(volatile unsigned int*)(A))
#define MemoryWrite(A,V) *(volatile unsigned int*)(A)=(V)

#define WHITE 		0xFFFF
#define BLACK			0x0000
#define MAX_X			96
#define MAX_Y			64
#define OLED_SIZE (96*64)
#define RED				0xF800
#define GREEN 		0x07C0
#define BLUE			0x001F

#define L_CLICK 		0
#define MID_CLICK		1
#define R_CLICK			2
#define X_POS				3
#define Y_POS 			4
#define Z_POS 			5

#define TOUCHE 0
#define APPUI  5
#define A	10
#define B	11
#define C	12
#define D	13
#define E	14
#define F	15

#define PENCIL	10
#define ERASER	11

#define SQUARE			0

//Function used to color a pixel at a given position (row, col)
void printPixel(char row, char col, int color)
{
	int buff = 0x00000000;

	buff = color;
	buff = (buff << 8) | row;
	buff = (buff << 8) | col;

	MemoryWrite(OLED_BITMAP_RW, buff);
}

void init_oled_bitmap(){
	MemoryWrite(OLED_MUX, OLED_MUX_BITMAP);
	MemoryWrite(OLED_BITMAP_RST, 1); // Reset the oled_rgb PMOD
}

void refresh(){
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			printPixel(i,j,WHITE);
		}
	}
}

int pix_on_screen(int x, int y){
	return( !((x<0) || (y<0) || (x>(MAX_X-1)) || (y>(MAX_Y-1))) );
}

void paint_background(int color){
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			printPixel(i,j,color);
		}
	}
}

void paint_area(int x, int y, int shape, int size, int color){
	int i = 0;
	int j = 0;
	int t_pos_x = x;
	int t_pos_y = y;

	if (shape==SQUARE) {
		for (i = 0; i < 2*size; i++) {
			for (j = 0; j < 2*size; j++) {
				t_pos_y = (y-size)+i;
				t_pos_x = (x-size)+j;
				if (pix_on_screen(t_pos_x, t_pos_y)) {
					printPixel(t_pos_y,t_pos_x, color);
				}
			}
		}
	}

}

void pencil(int mouse_left_click, int x, int y, int color, int size, int shape){
	if (mouse_left_click == 1)
	{
		paint_area(x, y, shape, size, color);
	}
}

void eraser(int mouse_left_click, int x, int y, int size){
	pencil(mouse_left_click, x, y, WHITE, size, SQUARE);
}

void get_mouse(int *mouse){
	mouse[X_POS]			= MemoryRead(MOUSE_X);
	mouse[Y_POS] 			= MemoryRead(MOUSE_Y);
	mouse[Z_POS] 			= MemoryRead(MOUSE_Z);
	mouse[L_CLICK]  	= MemoryRead(MOUSE_BUTTONS)&0x00000001;
	mouse[MID_CLICK]  = (MemoryRead(MOUSE_BUTTONS)>>1)&0x00000001;
	mouse[R_CLICK]  	= (MemoryRead(MOUSE_BUTTONS)>>2)&0x00000001;
}

void home_screen(){
/*
	int z = 0;
	for (int i = 0; i < MAX_Y; i++) {
		for (int j = 0; j < MAX_X; j++) {
			printPixel(i,j, plaspaint_home[z++]<<8);
		}
	}
*/

}
void get_keyb(int *keyb) {
	keyb[APPUI]  = (MemoryRead(KEYS_DECODE)>>8)&0x00000001;
	keyb[TOUCHE] = MemoryRead(KEYS_DECODE)&0x0000000F;
}


int main(int argc, char ** argv)
{
	int mouse[6]={0};
	int keyb[6] ={0};
	init_oled_bitmap();
	refresh();
	home_screen();

	do{
	get_mouse(mouse);
	get_keyb(keyb);

	if (keyb[TOUCHE] == 1) {
		pencil(mouse[L_CLICK], mouse[X_POS], mouse[Y_POS], RED, 10, SQUARE);
		if ( keyb[APPUI]== 0) {
			paint_background(BLACK);
		}
	}

	if (mouse[R_CLICK] == 1) {
		refresh();
	}

	}while(1);

}
