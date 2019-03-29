#include "../Includes/plaspaint.h"

/**
 * Processus principale (initialisation + loop )
 */
int mouse[6] = {0, 0, 0, 0, 0, 0};
int keyb[6] = {0, 0, 0, 0, 0, 0};
int displayMode = 0;

int main(int argc, char **argv) {

	// Initialisation du programme
	init_oled_bitmap();
	initSketch();
	clearSketch(WHITE);

	//Boucle infinie
	do {
		// Mis à jour des valeurs de la souris et du clavier
		get_mouse(mouse);
		get_keyb(keyb);


		// MODE HOME SCREEN
		if (displayMode == 0) {
			home_screen();
			if (mouse[L_CLICK] == 1) {
				displayMode = 1;
			}
		}


		// MODE DESSIN DE BASE
		if (displayMode == 1) {

			// Mis à jour du curseur
			updateCursor(mouse[X_POS], mouse[Y_POS]);

			// Pinceau : Outil de base
			pencil(mouse[L_CLICK], mouse[X_POS], mouse[Y_POS], RED, 1, SQUARE);

			// Test du clavier
			if (keyb[TOUCHE] == 1) {
				if (keyb[APPUI] == 0) {
					paint_background(BLACK);
				}
			}

			// Si clique droite, on efface le tableau de travail (sketch)
			if (mouse[R_CLICK] == 1) {
				clearSketch(WHITE);
			}

			// Affichage du skecth sur lequel on travail
			displaySketch();
		}


	} while (1);
}


