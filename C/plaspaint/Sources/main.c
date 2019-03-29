#include "../Includes/plaspaint.h"

/**
 * Processus principale (initialisation + loop )
 */

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

	// if (keyb[TOUCHE] == 1) {
		pencil(mouse[L_CLICK], mouse[X_POS], mouse[Y_POS], RED, 10, SQUARE);
		if ( keyb[APPUI]== 0) {
			paint_background(BLACK);
		}
	// }

	if (mouse[R_CLICK] == 1) {
		refresh();
	}

	}while(1);

}
