
#pragma once

#include "resouce_storage.h"

struct SDL_Window;
struct SDL_Renderer;

class Drawer
{
public:
    Drawer(std::shared_ptr<SDL_Window> window, std::shared_ptr<SDL_Renderer> renderer);

    void DrawImage(const char *imagePath, int posX = 0, int posY = 0, double angle = 0.0f, int centerX = 0, int centerY = 0);
    bool DrawText(const char *font, const char *text, float size, int posX, int posY);

private:
    ResourceStorage m_resources;
    std::shared_ptr<SDL_Window> m_window;
    std::shared_ptr<SDL_Renderer> m_renderer;
};