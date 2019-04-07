#include "../Includes/plaspaint.h"

/**
 * Processus principale (initialisation + loop )
 */
int mouse[6] = {0, 0, 0, 0, 0, 0};
int keyb[6] = {0, 0, 0, 0, 0, 0};
int displayMode = 0;

int main(int argc, char **argv) {

	// Initialisation du programme
	initOledBitmap();
	initSketch();
	clearSketch(WHITE);
	updateCursorMatrix(SQUARE); // Une première fois pour initialiser la matrix.

	int size_pencil = 1;
	int size_eraser = 1;
	int pressed = 0;
	int currentTool = PENCIL;
	int shape = SQUARE;
	int size = 1;

	//Boucle infinie
	do {
		// Mis à jour des valeurs de la souris et du clavier
		getMouse(mouse);
		getKeyb(keyb);


		// MODE HOME SCREEN
		if (displayMode == MODE_HOMESCREEN) {
			homeScreen();
			if (mouse[L_CLICK] == 1) {
				displayMode = MODE_NORMAL;
			}
		}


		// MODE DESSIN DE BASE
		if (displayMode == MODE_NORMAL) {

			// Mis à jour du curseur, obligatoire avant toutes les fonctions de dessins !!!
			updateCursor(mouse[X_POS], mouse[Y_POS]);

			// Pinceau : Outil de base
			if (mouse[L_CLICK]) {
				if(currentTool == PENCIL)
					pencil(size_pencil, shape);
				/*
				if(currentTool == ERASER)
					eraser()

				if(currentTool == ERASER)
					//EYEDROPPER
				*/
			}

			// DEBUG : Test du clavier
			if (keyb[TOUCHE] == D) {
				if (keyb[APPUI] == 0) {
					paintAllBackground(BLACK);
				}
			}


			// Sélection outil
			if ( (keyb[TOUCHE]==1) && (!keyb[APPUI]) ) {
				currentTool = PENCIL;
				size = size_pencil;
			}
			if ( (keyb[TOUCHE]==2) && (!keyb[APPUI]) ) {
				currentTool = ERASER;
				size = size_eraser;
			}
			if ( (keyb[TOUCHE]==3) && (!keyb[APPUI]) ) {
				currentTool = EYEDROPPER;
			}

			// Change la forme
			if((currentTool == PENCIL) && (keyb[TOUCHE] == C)){
				if(!keyb[APPUI] && (pressed==0)){
					pressed = 1;
				}
				if(keyb[APPUI]){
					pressed = 0;
				}
				if(pressed == 1){
					(shape==3)?(shape=0):shape++;
					pressed = 2;
				}
			}

			// Taille curseur +
			if (keyb[TOUCHE] == A) {

				if(!keyb[APPUI] && (pressed==0)){
					pressed = 1;
				}
				if(keyb[APPUI]){
					pressed = 0;
				}
				if(pressed == 1){
					(size>15)?(size=1):size++;
					pressed = 2;
				}

			}

			// Taille curseur -
			if (keyb[TOUCHE] == B) {
				// Appui du bouton
				if(!keyb[APPUI] && (pressed==0)){
					pressed = 1;
				}
				// Bouton relaché
				if(keyb[APPUI]){
					pressed = 0;
				}
				// Change la taille
				if(pressed == 1){
					(size==1)?(size=1):size--;
					pressed = 2;
				}
			}

			if(currentTool == PENCIL)
				size_pencil = size;
			if(currentTool == ERASER)
				size_eraser = size;

			// Si clique droite, on efface le tableau de travail (sketch)
			if (mouse[R_CLICK] == 1) {
				clearSketch(WHITE);
			}

			// Affichage du skecth sur lequel on travail
			displaySketch();

			if (mouse[MID_CLICK] == 1){
				displayMode = MODE_CHROMATIC;
				updateCursorMatrix(COLOR_SELECTOR);
				setCurrentColor(WHITE);
			}
		}

		// Mode chromatic, choix de la couleur
		if (displayMode == MODE_CHROMATIC){

			// Mis à jour du curseur
			updateCursor(mouse[X_POS], mouse[Y_POS]);

			// Affichage de la palette de couleurs
			displayChromaticScaleColors();

			// Si l'utilisateur relache le bouton du milieu, on valide la sélection de la couleur
			if (mouse[MID_CLICK] == 0){
				setColorAndTool();
				displayMode = MODE_NORMAL;
			}
		}


	} while (1);
}


