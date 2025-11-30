SIMULATION D'UN ECOSYSTEME
#description
  ce projet a pour finalite de simuler un ecosysteme en c++ en se servant de la SDL3 et met en oeuvre la POO(programation oriente objet)
il consiste a developper un ecosysteme virtuel ou differentes entitees (animaux,plantes) interagissent selon les regles biologiques
simples. le but est d'observer l'evolution
#STRUCTURE
ecosystem_simulator/ 
├── include/ 
│   ├── Core/ 
│   │   ├── Structs.hpp 
│   │   ├── Entity.hpp 
│   │   └── Ecosystem.hpp 
│   └── Graphics/ 
│       ├── Window.hpp 
│       └── Renderer.hpp 
├── src/ 
│   ├── Core/ 
│   │   ├── Entity.cpp 
│   │   └── Ecosystem.cpp 
│   ├── Graphics/ 
│   │   ├── Window.cpp 
│   │   └── Renderer.cpp 
│   └── main.cpp 
├── assets/ 
│   └── (futures textures) 
└── README.md 
#OBJECTIF 
Créer un simulateur d'écosystème en C++ utilisant la POO, SDL3 pour la visualisation, et mettant en pratique :
- Les namespaces pour l'organisation du code
- Les structs pour les données simples
- Les classes pour les entités complexes
- L'encapsulation pour protéger les données
- Les constructeurs/destructeurs pour la gestion mémoire
- La gestion du cycle de vie des objets
#Prérequis
---------
- SDL3 installée sur le système
- Compilateur C++ compatible (g++, clang++, ou MSVC)
- Télécharger SDL3 (inclure les dossiers "lib" et "include", dans le fichier "src" de son projet
   et copier/coller le fichier SDL3.dll près du main.cpp)

#Compilation
-----------
1. Assurez-vous que les fichiers SDL3 (`SDL3/SDL.h` et bibliothèques) sont accessibles.
2. Compiler le programme :
commande
# Avec g++
 g++ -std=c++17 -Iinclude -o ecosystem src/*.cpp src/Core/*.cpp src/Graphics/*.cpp -o ecosystem.exe -lSDL3 
# Avec clang++ 
clang++ -std=c++17 -Iinclude -o ecosystem src/*.cpp src/Core/*.cpp src/Graphics/*.cpp -o ecosystem.exe -lSDL3
# INSTALLATIONS
-Créer mon ripository avec une licence MIT
-installer SDL3

 #Outils Recommandés
 Compilateur : g++ 9+ ou clang++ 10+
 Bibliothèque : SDL3
 IDE : VS Code, CLion, ou autre de votre choix

 je vous laisse l'occasion d'explorer ce projet majestueux . 
  par : NGAMALEU RUSSELLE
  sous la supervision de : MR TEGUIA
 
