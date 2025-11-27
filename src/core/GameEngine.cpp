#include "Core/GameEngine.h" 
#include <iostream> 
#include <sstream> 
namespace Ecosystem { 
namespace Core { 
//  CONSTRUCTEUR 
GameEngine::GameEngine(const std::string& title, float width, float height) 
    : mWindow(title, width, height),  
      mEcosystem(width, height, 500), 
      mIsRunning(false),  
      mIsPaused(false), 
      mTimeScale(1.0f), 
      mAccumulatedTime(0.0f) {} 
// INITIALISATION 
bool GameEngine::Initialize() { 
    if (!mWindow.Initialize()) { 
        return false; 
    }
    mEcosystem.Initialize(20, 5, 30);  // 20 herbivores, 5 carnivores, 30 plantes 
    mIsRunning = true; 
    mLastUpdateTime = std::chrono::high_resolution_clock::now(); 
    std::cout << "Moteur de jeu initialisé" << std::endl; 
    return true; 
} 
// BOUCLE PRINCIPALE 
void GameEngine::Run() { 
    std::cout << "Démarrage de la boucle de jeu..." << std::endl; 
    while (mIsRunning) { 
        auto currentTime = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<float> elapsed = currentTime - mLastUpdateTime; 
        mLastUpdateTime = currentTime; 
        float deltaTime = elapsed.count(); 
        HandleEvents(); 
        if (!mIsPaused) { 
            Update(deltaTime * mTimeScale);
            // Limitation à ~60 FPS 
            SDL_Delay(16);  
        } 
        Render(); 
    } 
}
// FERMETURE 
void GameEngine::Shutdown() { 
    mIsRunning = false; 
    std::cout << "Moteur de jeu arrêté" << std::endl; 
} 
// GESTION DES ÉVÉNEMENTS 
void GameEngine::HandleEvents() { 
    SDL_Event event; 
    while (SDL_PollEvent(&event)) { 
        switch (event.type) { 
            case SDL_EVENT_QUIT: 
                mIsRunning = false; 
                break; 
            case SDL_EVENT_KEY_DOWN: 
                HandleInput(event.key.key); 
                break; 
        } 
    }
 } 
// GESTION DES TOUCHES 
void GameEngine::HandleInput(SDL_Keycode key) { 
    switch (key) { 
        case SDLK_ESCAPE: 
            mIsRunning = false; 
            break; 
        case SDLK_SPACE: 
            mIsPaused = !mIsPaused; 
            if (mIsPaused)  std::cout <<"⏸Simulation en pause" ;
            else { 
                std::cout << " ▶ Simulation reprend" <<std::endl;
            }
            break; 
        case SDLK_R: 
            mEcosystem.Initialize(20, 5, 30); 
            std::cout << "Simulation réinitialisée" << std::endl; 
            break; 
        case SDLK_F: 
            mEcosystem.SpawnFood(10); 
            std::cout << "Nourriture ajoutée" << std::endl; 
            break; 
        case SDLK_UP: 
            mTimeScale *= 1.5f; 
            std::cout << "Vitesse: " << mTimeScale << "x" << std::endl; 
            break; 
        case SDLK_DOWN: 
            mTimeScale /= 1.5f; 
            std::cout << "Vitesse: " << mTimeScale << "x" << std::endl; 
            break; 
    }
 } 
// MISE À JOUR 
void GameEngine::Update(float deltaTime) { 
    mEcosystem.Update(deltaTime); 
    // Affichage occasionnel des statistiques 
    static float statsTimer = 0.0f; 
    statsTimer += deltaTime; 
    if (statsTimer >= 2.0f) { 
        auto stats = mEcosystem.GetStatistics(); 
        std::cout << "📊Stats - Herbivores: " << stats.totalHerbivores << ", Carnivores: " << stats.totalCarnivores << ", Plantes: " << stats.totalPlants << ", Naissances: " << stats.birthsToday << ", Morts: " << stats.deathsToday << std::endl; 
        statsTimer = 0.0f; 
    }
 } 
// RENDU 
void GameEngine::Render() { 
    mWindow.Clear(); 
    // Rendu de l'écosystème 
    mEcosystem.Render(mWindow.GetRenderer()); 
    // Ici on ajouterait l'interface utilisateur 
    RenderUI(); 
    mWindow.Present(); 
} 
// INTERFACE UTILISATEUR 
void GameEngine::RenderUI() { 
    // Pour l'instant, interface texte dans la console 
    // Une vraie interface graphique serait implémentée ici 
} 
} // namespace Core 
} // namespace Ecosystem