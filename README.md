# Le jeu de la vie

Ce programme permet de jouer au jeu de la vie grâce à un programme en langage C et en SDL.

## Installation

Pour installer le Jeu de la Vie, suivez ces étapes :

1. Clonez le dépôt avec Git :

```
git clone https://github.com/Antzert/Jeu-de-la-vie
```

2. Installez les dépendances nécessaires (SDL2 et SDL2_ttf) en utilisant apt :

```
sudo apt install libsdl2-dev libsdl2-ttf-dev
```

3. Accédez au répertoire du jeu :

```
cd Jeu-de-la-vie
```

4. Compilez le code à l'aide du compilateur GCC :

```
gcc *.c -o Jeu-de-la-vie -lSDL2 -lSDL2_ttf
```
## Utilisation

Pour utiliser l'exécutable, suivez les instructions ci-dessous:

Exécutez la commande suivante dans votre terminal :

```
./Jeu-de-la-vie
```

Cela ouvrira une fenêtre avec une largeur de 1920 pixels et une hauteur de 1080 pixels, avec une taille de pixel de 10 et en mode plein écran.

Si vous souhaitez modifier les paramètres, executer la commande avec ces paramètes `[Largeur]`, `[Hauteur]`, `[Taille des pixels]`, `[Plein écran]` dans la commande ci-dessus et exécutez-la. Par exemple :

`[Largeur]` la largeur en pixels de la fenêtre   
`[Hauteur]` la hauteur en pixels de la fenêtre   
`[Taille des pixels]` la taille des pixels   
`[Plein écran]` mode plein ecran 0 pour le désactiver et 1 pour l'activer   
```
./Jeu-de-la-vie 1280 720 5 0
```

Cela lancera le jeu avec une résolution de 1280x720 pixels, une taille de pixel de 5, et en mode fenêtré (non plein écran).

## Fonctionnalités

Le Jeu de la Vie propose les fonctionnalités suivantes :

- Créer une zone aléatoire avec la touche **a**.
- Réinitialiser la zone avec la touche **r**.
- Réinitialiser le compteur de génération avec la touche **g**.
- Mettre en pause avec la touche **espace** ou la touche **p**.
- Changer la vitesse avec les touches du pavé numérique, de **0** pour la vitesse la plus basse à **9** pour la plus rapide.
- Activation ou désactivation de la grille avec la touche **entrée**.
- Aller à la zone suivante avec la touche flèche de droite **->**.
