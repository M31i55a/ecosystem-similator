#pragma once
#include<SDL3/SDL.h>
#include<string>
#include"../core/Strusts.h"
 namespace Ecosystem{
    namespace Graphics{
        class Window{
            private:
            //ressources sdl
            SDL_Window*mWindow;
            SDL_renderer*mRenderer;
            float mWidth;
            float mHeight;
            bool mIsInitialized;
            std::string mTitle;
            public:
            //constructeur/destructeur
            Window(const std::string& title,float width, float height);
            Window();
            // initialisation
            bool Initialize();
            void Shutdown();
            //rendu
            void Clear(const Core::Color& color=core::color(30,30,30));
            void Present();
            //getters
            SDL_Renderer* GetRenderer()const{
                return mRenderer;
            }
            bool IsInitialized() const{
                return mIsInitialized;
            }
            float GetWidth() const{
                return GetWidth;
            }
            float GetHeight() const {
                return GetHeight;
            }
            std::string GetTitle() const{
                return GetTitle;
            }
        };
    }//namespace Graphics
 }//namespace Ecosystem