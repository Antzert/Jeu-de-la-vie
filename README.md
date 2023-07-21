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

## Fonctionnalités

Le Jeu de la Vie propose les fonctionnalités suivantes :

- Créer une zone aléatoire avec la touche **a**.
- Réinitialiser la zone avec la touche **r**.
- Réinitialiser le compteur de génération avec la touche **g**.
- Mettre en pause avec la touche **espace** ou la touche **p**.
- Changer la vitesse avec les touches du pavé numérique, de **0** pour la vitesse la plus basse à **9** pour la plus rapide.
- Activation ou désactivation de la grille avec la touche **entrée**.
- Aller à la zone suivante avec la touche flèche de droite **->**.
