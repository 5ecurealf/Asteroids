#include "resouce_storage.h"

#include <stdexcept>
#include <SDL.h>
#include <stb_image.h>

static ResourceStorage::SurfacePtr CreateImageSurface(const std::string &img)
{
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;
    unsigned char *data = stbi_load(img.c_str(), &width, &height, &orig_format, req_format);
    if (data == nullptr)
    {
        SDL_Log("Loading image %s failed: %s", img.c_str(), stbi_failure_reason());
        throw std::runtime_error(stbi_failure_reason());
    }

    int depth, pitch;
    Uint32 pixel_format;
    if (req_format == STBI_rgb_alpha)
    {
        depth = 32;
        pitch = 4 * width;
        pixel_format = SDL_PIXELFORMAT_RGBA32;
    }

    ResourceStorage::SurfacePtr surface(SDL_CreateRGBSurfaceWithFormatFrom((void *)data, width, height,
                                                                           depth, pitch, pixel_format),
                                        [data](SDL_Surface *surface) -> void {
                                            SDL_FreeSurface(surface);
                                            free(data);
                                        });

    if (surface == nullptr)
    {
        SDL_Log("Creating surface failed: %s", SDL_GetError());
        throw std::runtime_error(stbi_failure_reason());
    }

    return surface;
}

ResourceStorage::SurfacePtr ResourceStorage::GetOrLoadImage(const std::string &img)
{
    auto it = m_images.find(img);
    if (it == m_images.end())
    {
        return m_images[img] = CreateImageSurface(img);
    }
    return it->second;
}
