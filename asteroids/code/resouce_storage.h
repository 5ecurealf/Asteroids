#pragma once

#include <memory>
#include <unordered_map>

#include <SDL.h>

class ResourceStorage final
{
public:
    using SurfacePtr = std::shared_ptr<SDL_Surface>;

    SurfacePtr GetOrLoadImage(const std::string &);

private:
    std::unordered_map<std::string, SurfacePtr> m_images;
};