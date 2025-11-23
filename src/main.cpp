#include "core/GameEngine.h"
#include <iostream>>
#include <cstdlib>>
#include <ctime>
int main(int argc, char *argv[])
{
    // initialisation de l'aleatoire
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::cout << "demarage du simulateur d'ecosysteme" << std::endl;
    std::cout << "============================================" << std::endl;
    // creation du moteur de jeu
    Ecosystem::core::GameEngine engine("simulateur d'EcosystemeIntelligent", 1200.0f, 800.0f);
    // iitialisation
    if (!engine.Initialisation())
    {
        std::cerr << "Erreur: Impossible d'initiaiser le moteur de jeu" << std::endl;
        return -1;
    }
    std::cout << "moteur initialise avec succes" << std::endl;
    std::cout << "lancement de la simulation..." << std::endl;
    std::cout << "====CONTROLES====" << std::endl;
    std::cout << "ESPACE:pause/reprise" << std::endl;
    std::cout << "R:Reset simulation" << std::endl;
    std::cout << "F:Ajouter nourriture" << std::endl;
    std::cout << "FLECHES:vitesse simulation" << std::endl;
    std::cout << "ECHAP:Quitter" << std::endl;
    // boucle principale
    engine.Run();
    // Arret propre
    engine.Shutdown();
    std::cout << "simulation terminee. Au revoir!" << std::endl;
}