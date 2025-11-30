#include "Core/Entity.h" 
#include <cmath> 
#include <iostream> 
#include <algorithm> 
namespace Ecosystem { 
namespace Core { 
//  CONSTRUCTEUR PRINCIPAL 
Entity::Entity(EntityType type, Vector2D pos, std::string entityName) 
    : mType(type), position(pos), name(entityName),  
      mRandomGenerator(std::random_device{}())  // Initialisation du générateur alé
 { 
    //INITIALISATION SELON LE TYPE 
    switch(mType) { 
        case EntityType::HERBIVORE: 
            mEnergy = 80.0f; 
            mMaxEnergy = 150.0f; 
            mMaxAge = 200; 
            color = Color::Blue(); 
            size = 8.0f; 
            break; 
        case EntityType::CARNIVORE: 
            mEnergy = 100.0f; 
            mMaxEnergy = 200.0f; 
            mMaxAge = 150; 
            color = Color::Red(); 
            size = 12.0f; 
            break; 
        case EntityType::PLANT: 
            mEnergy = 50.0f; 
            mMaxEnergy = 100.0f; 
            mMaxAge = 300; 
            color = Color::Green(); 
            size = 6.0f; 
            break; 
    }
    mAge = 0; 
    mIsAlive = true; 
    mVelocity = GenerateRandomDirection(); 
    std::cout << " Entité créée: " << name << " à (" << position.x << ", " << position.y << ")";
 } 

//  CONSTRUCTEUR DE COPIE 
Entity::Entity(const Entity& other) 
    : mType(other.mType), position(other.position), name(other.name + "_copy"), 
      mEnergy(other.mEnergy * 0.7f),  // Enfant a moins d'énergie 
      mMaxEnergy(other.mMaxEnergy), 
      mAge(0),  // Nouvelle entité, âge remis à 0 
      mMaxAge(other.mMaxAge), 
      mIsAlive(true), 
      mVelocity(other.mVelocity), 
      color(other.color), 
      size(other.size * 0.8f),  // Enfant plus petit 
      mRandomGenerator(std::random_device{}()) 
{ 
 
    std::cout << "  Copie d'entité créée: " << name << std::endl; 
}
//  DESTRUCTEUR 
Entity::~Entity() { 
    std::cout << "Entité détruite: " << name << " (Âge: " << mAge << ")" << std::endl;
 } 

 //MISE À JOUR PRINCIPALE 
void Entity::Update(float deltaTime) { 
    if (!mIsAlive) return; 
    
    //PROCESSUS DE VIE 
    ConsumeEnergy(deltaTime); 
    Age(deltaTime); 
    Move(deltaTime); 
    CheckVitality(); 
} 
//MOUVEMENT 
Vector2D SeekFood();
Vector2D AvoidPredators();
Vector2D StayInBounds();
void ApplyForce();
void Entity::Move(float deltaTime) { 
    if (mType == EntityType::PLANT) return;  // Les plantes ne bougent pas 
    
    //Comportement aléatoire occasionnel 
    std::uniform_real_distribution<float> chance(0.0f, 1.0f); 
    if (chance(mRandomGenerator) < 0.02f) { 
        mVelocity = GenerateRandomDirection(); 
    }
    //Application du mouvement 
    position = position + mVelocity * deltaTime * 20.0f; 
    
    // Consommation d'énergie due au mouvement 
    mEnergy -= mVelocity.Distance(Vector2D(0, 0)) * deltaTime * 0.1f; 
} 
//  MANGER
 void Entity::Eat(float energy) { 
    mEnergy += energy; 
    if (mEnergy > mMaxEnergy) { 
        mEnergy = mMaxEnergy; 
    } 
        std::cout << "🍽 " << name << " mange et gagne " << energy << " énergie" << std::endl;
    }
 
    //CONSOMMATION D'ÉNERGIE 
void Entity::ConsumeEnergy(float deltaTime) { 
    float baseConsumption = 0.0f; 
    switch(mType) { 
        case EntityType::HERBIVORE: 
            baseConsumption = 1.5f; 
            break; 
        case EntityType::CARNIVORE: 
            baseConsumption = 2.0f; 
            break; 
        case EntityType::PLANT: 
            baseConsumption = -0.5f;  // Les plantes génèrent de l'énergie ! 
            break; 
    }
    mEnergy -= baseConsumption * deltaTime; 
} 

// VIEILLISSEMENT 
void Entity::Age(float deltaTime) { 
    mAge += static_cast<int>(deltaTime * 10.0f);  // Accéléré pour la simulation 
} 

// VÉRIFICATION DE LA SANTÉ 
void Entity::CheckVitality() { 
    if (mEnergy <= 0.0f || mAge >= mMaxAge) { 
        mIsAlive = false; 
        std::cout << "💀 " << name << " meurt - "; 
        if (mEnergy <= 0) std::cout << "Faim"; 
        else std::cout << "Vieillesse"; 
        std::cout << std::endl; 
    }
 } 

 // REPRODUCTION 
bool Entity::CanReproduce() const { 
    return mIsAlive && mEnergy > mMaxEnergy * 0.8f && mAge > 20; 
} 
std::unique_ptr<Entity> Entity::Reproduce() { 
    if (!CanReproduce()) return nullptr; 
    
    // Chance de reproduction 
    std::uniform_real_distribution<float> chance(0.0f, 1.0f); 
    if (chance(mRandomGenerator) < 0.3f) { 
    }
        mEnergy *= 0.6f;  // Coût énergétique de la reproduction 
        return std::make_unique<Entity>(*this);  // Utilise le constructeur de copi
    return nullptr; 
} 

// GÉNÉRATION DE DIRECTION ALÉATOIRE 
Vector2D Entity::GenerateRandomDirection() { 
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f); 
    return Vector2D(dist(mRandomGenerator), dist(mRandomGenerator)); 
} 

// CALCUL DE LA COULEUR BASÉE SUR L'ÉTAT 
Color Entity::CalculateColorBasedOnState() const { 
    float energyRatio = GetEnergyPercentage(); 
    Color baseColor = color; 
    
    // Rouge si faible énergie 
    if (energyRatio < 0.3f) { 
        baseColor.r = 255; 
        baseColor.g = static_cast<uint8_t>(baseColor.g * energyRatio); 
        baseColor.b = static_cast<uint8_t>(baseColor.b * energyRatio); 
    }
    return baseColor; 
} 

// RENDU GRAPHIQUE 
void Entity::Render(SDL_Renderer* renderer) const { 
    if (!mIsAlive) return; 
    Color renderColor = CalculateColorBasedOnState(); 
    SDL_FRect rect = { 
        position.x - size / 2.0f, 
        position.y - size / 2.0f, 
        size, 
        size 
    }; 
    SDL_SetRenderDrawColor(renderer, renderColor.r, renderColor.g, renderColor.b, renderColor.a);
    SDL_RenderFillRect(renderer, &rect); 
    
    // Indicateur d'énergie (barre de vie) 
    if (mType != EntityType::PLANT) { 
        float energyBarWidth = size * GetEnergyPercentage(); 
        SDL_FRect energyBar = { 
            position.x - size / 2.0f, 
            position.y - size / 2.0f - 3.0f, 
            energyBarWidth, 
            2.0f 
        };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); 
        SDL_RenderFillRect(renderer, &energyBar); 
    }
 } 
  Vector2D SeekFood(const std::vector<Food> &foodSources) const
            {
             if (foodList.empty())
                 return Vector2D(0,0);
                const Vector2D* closest= nullptr;
                float minDist= std::numeric_limits<float>::max();
             //trouver la nourriture la plus proche
             for(const auto& food: foodList)
             {
                float d=(food-position).length();
                if (d<minDist)
                {
                    minDist=d;
                    closest=&food;
                }
             }
                                                                              // direction vers la nourriture
                Vector2D desired= (*closest-position).normalized()*maxSpeed;
                                                                              // steering=nouvelle direction-Vitesse actuelle
               Vector2D steering= desired-velocity;
              return steering;
            }
            Vector2D AvoidPredators(const std::vector<Entity> &predators) 
            {
                if(predators.empty())
                                                                                // parcours la liste de predateur
                    return{0,0}
                    const Vector2D* closest=nullptr;
                    float minDist=std::numeric_limits<float>::max();
                 for(const auto& pred: predators)
                 {
                    float d=(pred-position).length();
                    if(d<minDist)                                                  //verifi si le predateur actuel est plus proche que le precedent
                    {
                        minDist=d;
                        closest= &pred;                                            // on garde l'adresse du predateur le plus proche
                    }
                 }
                if(minDist>panicRadius)                                            // si le predateur est loin, no fuit pas
                return Vector2D(0,0);
             Vector2D desired=(position- *closest).normalized() * maxSpeed;        // sinon calcule une force de fuite
             return desired-velocity;
            }
            Vector2D StayInBounds(float worldWidth, float worldHeight,float margin)// garde les agents a l'interieur du monde
             {
                Vector2D desired(0,0);
                if(position.x<margin)                                            // si la position en x est inferieure a la distance de securite , alors fuit avec une vitesse maximale
                      desired.x=maxSpeed;
                 else if(position.x>worldWidth-margin)desired.x=-maxSpeed;      // si la position en x est hors du monde , revenir
               if(position.y<margin)                                            // si la position en y est inferieure a la distance de securite , alors fuit avec une vitesse maximale
                      desired.y=maxSpeed;
                 else if(position.y>worldHeight-margin)desired.y=-maxSpeed;    // si la position en y est hors du monde , revenir
               if(desired.x==0 && desired.y==0)                                //si l'agent est au centre du monde , ne rien faire
              return{0,0};
            return desired-velocity;
           // margin=distance de securite
           //maxSpeed=vitesse maximale
           //velocity=vitesse actuelle
           //desired = vitesse ou direction que l'agent veut atteindre
            }
            void ApplyForce(const Vector2D& force){
                acceleration+=force;
            }
} // namespace Core 
} // namespace Ecosystem