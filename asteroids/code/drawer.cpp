
#include "drawer.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBTTF_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_RECT_PACK_IMPLEMENTATION

#include <stb_image.h>
#include <stbttf.h>

#include <SDL.h>

Drawer::Drawer(std::shared_ptr<SDL_Window> window, std::shared_ptr<SDL_Renderer> renderer)
    : m_window{window}, m_renderer{renderer}
{
}

void Drawer::DrawImage(const char *img, int posX, int posY, double angle, int centerX, int centerY)
{
    auto surface = m_resources.GetOrLoadImage(img);
    SDL_Texture *optimizedSurface = SDL_CreateTextureFromSurface(m_renderer.get(), surface.get());

    SDL_Rect sizeRect;
    sizeRect.x = 0;
    sizeRect.y = 0;
    sizeRect.w = surface->w;
    sizeRect.h = surface->h;

    SDL_Rect posRect;
    posRect.x = posX;
    posRect.y = posY;
    posRect.w = sizeRect.w;
    posRect.h = sizeRect.h;


    //if we delcare an angle then flip the image, and if not continue the SDL_RenderCopy()
    if (angle)
    {
        SDL_Point center{centerX, centerY};
        SDL_RenderCopyEx(m_renderer.get(), optimizedSurface, &sizeRect, &posRect, angle, &center, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopy(m_renderer.get(), optimizedSurface, &sizeRect, &posRect);
    }
    SDL_DestroyTexture(optimizedSurface);
}

bool Drawer::DrawText(const char *font, const char *text, float size, int posX, int posY)
{
    STBTTF_Font *stbFont = STBTTF_OpenFont(m_renderer.get(), font, size);
    if (stbFont)
    {
        SDL_SetRenderDrawColor(m_renderer.get(), 255, 255, 255, 255);
        STBTTF_RenderText(m_renderer.get(), stbFont, posX, posY, text);
        STBTTF_CloseFont(stbFont);
        return true;
    }
    else
    {
        SDL_Log("Error loading font: %s", font);
        return false;
    }
}
