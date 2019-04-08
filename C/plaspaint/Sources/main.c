#include "../Includes/plaspaint.h"

/**
 * Processus principale (initialisation + loop )
 */
int mouse[6] = {0, 0, 0, 0, 0, 0};
int keyb[6] = {0, 0, 0, 0, 0, 0};
int displayMode = 0;

void getMouse();
void getKeyb();

int main(int argc, char **argv) {

	// Initialisation du programme
	initOledBitmap();
	initSketch();
	clearSketch(WHITE);
	updateCursorMatrix(SQUARE); // Une première fois pour initialiser la matrix.

	int size_pencil = 1;
	int size_eraser = 1;
	int pressed = 0;
	int size = 1;

	//Boucle infinie
	do {
		// Mis à jour des valeurs de la souris et du clavier
		getMouse();
		getKeyb();

		/**
		 * MODE HOME SCREEN
		 */
		if (displayMode == MODE_HOMESCREEN) {
			homeScreen();

			if (mouse[L_CLICK] == 1) {
				setCurrentTool(PENCIL);
				setShape(SQUARE);
				displayMode = MODE_NORMAL;
			}
		}


		/**
		 * MODE DESSIN DE BASE
		 */
		if (displayMode == MODE_NORMAL) {

			// Mis à jour du curseur, obligatoire avant toutes les fonctions de dessins !!!
			updateCursor(mouse[X_POS], mouse[Y_POS]);

			// Pinceau : Outil de base
			if (mouse[L_CLICK]) {
				if (getCurrentTool() == PENCIL)
					pencil(size_pencil, getShape());

				if(getCurrentTool() == ERASER)
					eraser(size_eraser);

				if (getCurrentTool() == EYEDROPPER)
					getColor();
			}

			// DEBUG : Test du clavier
			if (keyb[TOUCHE] == D) {
				if (keyb[APPUI] == 0) {
					paintAllBackground(BLACK);
				}
			}

			// Sélection outil
			if ((keyb[TOUCHE] == 1) && (!keyb[APPUI])) {
				setCurrentTool(PENCIL);
				size = size_pencil;
			}
			if ((keyb[TOUCHE] == 2) && (!keyb[APPUI])) {
				setCurrentTool(ERASER);
				size = size_eraser;
			}
			if ((keyb[TOUCHE] == 3) && (!keyb[APPUI])) {
				setCurrentTool(EYEDROPPER);
			}


			// Change la forme
			if ((getCurrentTool() == PENCIL) && (keyb[TOUCHE] == C)) {
				if (!keyb[APPUI] && (pressed == 0)) {
					pressed = 1;
				}
				if (keyb[APPUI]) {
					pressed = 0;
				}
				if (pressed == 1) {
					if ((getShape() != 23))
						setShape(getShape() + 1);
					else
						setShape(20);
					pressed = 2;
				}
			}

			// Taille curseur +
			if (keyb[TOUCHE] == A) {

				if (!keyb[APPUI] && (pressed == 0)) {
					pressed = 1;
				}
				if (keyb[APPUI]) {
					pressed = 0;
				}
				if (pressed == 1) {
					(size > 15) ? (size = 1) : size++;
					pressed = 2;
				}

			}

			// Taille curseur -
			if (keyb[TOUCHE] == B) {
				// Appui du bouton
				if (!keyb[APPUI] && (pressed == 0)) {
					pressed = 1;
				}
				// Bouton relaché
				if (keyb[APPUI]) {
					pressed = 0;
				}
				// Change la taille
				if (pressed == 1) {
					(size == 1) ? (size = 1) : size--;
					pressed = 2;
				}
			}

			if (getCurrentTool() == PENCIL)
				size_pencil = size;
			if (getCurrentTool() == ERASER)
				size_eraser = size;

			// Si appuie sur E, on efface le tableau de travail (sketch)
			if (keyb[TOUCHE] == E) {
				clearSketch(WHITE);
			}

			// Affichage du skecth sur lequel on travail
			displaySketch();

			if (mouse[MID_CLICK] == 1) {
				displayMode = MODE_CHROMATIC;
				updateCursorMatrix(COLOR_SELECTOR);
				setCurrentColor(WHITE);
			}
		}


		/**
		 *  Mode chromatic, choix de la couleur
		 */
		if (displayMode == MODE_CHROMATIC) {

			// Mis à jour du curseur
			updateCursor(mouse[X_POS], mouse[Y_POS]);

			// Affichage de la palette de couleurs
			displayChromaticScaleColors();

			// Si l'utilisateur relache le bouton du milieu, on valide la sélection de la couleur
			if (mouse[MID_CLICK] == 0) {
				updateColor();
				setCurrentTool(getCurrentTool());
				displayMode = MODE_NORMAL;
			}
		}


	} while (1);
}

void getMouse() {
	mouse[X_POS] = MemoryRead(MOUSE_X);
	mouse[Y_POS] = MemoryRead(MOUSE_Y);
	mouse[Z_POS] = MemoryRead(MOUSE_Z);
	mouse[L_CLICK] = MemoryRead(MOUSE_BUTTONS) & 0x00000001;
	mouse[MID_CLICK] = (MemoryRead(MOUSE_BUTTONS) >> 1) & 0x00000001;
	mouse[R_CLICK] = (MemoryRead(MOUSE_BUTTONS) >> 2) & 0x00000001;
}

void getKeyb() {
	keyb[APPUI] = (MemoryRead(KEYS_DECODE) >> 8) & 0x00000001;
	keyb[TOUCHE] = MemoryRead(KEYS_DECODE) & 0x0000000F;
}
