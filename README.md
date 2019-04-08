# Plaspaint  : programme d'édition graphique

**Plaspaint** est un programme d'édition graphique développé à l'aide du [**processeur Plasma** ](https://opencores.org/projects/plasma)implémenté sur **FPGA** (Nexys4 ou Nexys4DDR) dans le cadre du module EN211.  
Ce document montre comment l'utiliser et quelles sont les fonctions disponibles.

# Installation


La série d'instructions suivante permet de mettre en place les périphériques et programmes nécessaires à **Plaspaint** pour fonctionner.

* Compiler le boot-loader du projet : 
    `make boot_loader`
* Synthétiser le module plasma : 
    `make plasma`
*  Brancher une **souris** sur le port **USB** de la carte Nexys4.
 * Brancher un **clavier 16 touches** sur le port **JA** de la carte.
  * Brancher un **écran OLED RGB** sur le port **JB** de la carte.
 * Implémenter le fichier **plasma.bit** sur la carte Nexys4 à l'aide de Vivado Hardware Manager.
  * Compiler le programme Plaspaint :
`make project CONFIG_PROJECT=Plaspaint`
  * Charger le programme Plaspaint sur la carte :
   ` make send CONFIG_PROJECT=Plaspaint`

Si tout se passe bien, le **logo du projet Plaspaint** devrait s'afficher. 
> ![](https://i.imgur.com/PmWJoYY.png) Logo de Plaspaint
>
Pour **commencer** à utiliser le programme, appuyer sur le **bouton gauche de la souris**, un écran blanc et un curseur devraient s'afficher.


> **Note** : Dans le cas de l'utilisation d'une Nexys4DDR, le fichier de contrainte est à modifier dans le fichier Makefile ligne 234, en modifiant `nexys4` par `nexys4-ddr`.

\* : Attention, une souris classique 2 touches avec molette est necessaire. Une souris avec plus de trois touches n'est très probablement pas supportée par le module VHDL de gestion de la souris.

# Utilisation de Plaspaint

Le programme se contrôle à l'aide du **clavier** et de la **souris** et l'affichage se fait via l'**écran OLED**. La souris permet de contrôler le curseur et d'utiliser les outils alors que le clavier permet de changer les outils et leurs paramètres.

## Sélection des outils
Le choix des outils se fait à l'aide du clavier selon l'assignation suivante :
* **Touche 1** : Pinceau
* **Touche 2** : Gomme
* **Touche 3** : Pipette

> **Note** : Un rappel des assignations est donné avec l'affichage de la palette qui est quant à lui assigné à la molette de la souris.

## Utiliser les outils
### Pinceau
* **Clic gauche** : Utiliser  le pinceau.
* **Touche A** : Augmenter la taille du pinceau
* **Touche B** : Diminuer la taille du pinceau
* **Touche C** : Changer la forme du pinceau parmi les 4 proposées (carré, point, trait, croix).

### Gomme
* **Clic gauche** : Utiliser  la gomme.
### Pipette
* **Clic gauche** : Utiliser  la pipette.

## Changer la couleur

Pour changer la couleur, appuyer sur le **bouton de la molette**, et tout en restant appuyé, selectionner la couleur voulue sur la palette affiché à l'écran.
Le relachement du bouton molette enregistre la couleur sur laquelle le curseur était positionné.

> ![](https://i.imgur.com/OIlOSE6.png) Palette des couleurs


## Nettoyer l'écran
Il est possible de nettoyer rapidement l'écran avec les touche suivantes : 
* **Touche D** : Nettoyage de l'écran en noir.
* **Touche E** : Nettoyage de l'écran en blanc.

# Axes d'amélioration
 * Redéfinir dynamiquement la taille des curseurs en fonction de celle des outils.
 * Compléter la palette avec les dernières couleurs utilisées.
 * Faire un retour Serial du dessin une fois terminé pour une sauvegarde sur ordinateur.
 * Optimiser le programme pour gagner en mémoire avec codage des couleurs sur 8 bits (actuellement 64kB).



