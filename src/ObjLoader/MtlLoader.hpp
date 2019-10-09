#pragma once
#include <istream>
#include <map>
#include <memory>
#include <vector>
#include <SDL2/SDL_image.h>
#include "Material.hpp"
#include <GL/gl.h>

class MTL {
public:
    /**
     * Loads a material file, so long as it mostly adheres to the standard.
     * @brief Load an MTL material file
     * @param filepath The path of the material file to load
     * @return A mapping of material names to material data.
     */
    static auto Load(const std::string &filepath) -> std::map<std::string, Material>;

    // Stolen from TexturedPolygons.hpp
    using Image = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
    /**
     * Storage of loaded textures
     */
    static std::vector<Image> Images;
    static std::vector<GLuint> Textures;
    /**
     * Mapping of filename to texture id
     */
    static std::map<std::string, int> ImageNames;
};
