#pragma once
#include "heightmap.hpp"
#include "normalmap.hpp"
#include "tga/tga_math.hpp"
#include "glm/glm.hpp"
#include "tga/tga_utils.hpp"

using namespace tga;


class SplatMap
{
    public:

        /**
        * @brief creates a splatmap using a heightmap and a normalmap
        *
        * @param heightMap the heightmap
        * @param normalMap the normalmap
        * @param size the size
        */
        SplatMap(Heightmap& heightMap, Normalmap& normalMap, int size);
        /**
        * @brief Save access with wrapping behavior
        *
        * @param x x-cooordinate
        * @param y y-coordinate
        * @return float&, reference to the value, allowing read and write with one function
        */
        glm::vec4& atData(int x, int y);

        glm::vec3& atImage(int x, int y);

        std::vector<glm::vec4>& getSplatMap();

    private:

        void generateSplatMap(Heightmap&, Normalmap&);

        void mergeTextures(Heightmap&, Normalmap&);

        float getMaxHeight(Heightmap&);

        double getMaxSlope(Normalmap&);

        std::vector<glm::vec4> data;
        
        std::vector<glm::vec3> image;

        int mSize;

        //Texture text = loadTexture("../../../../external/textures/gras15.jpg");
        Image lowFlatImage = loadImage("../../../../external/textures/gras15.jpg");
        Image lowSteepImage = loadImage("../../../../external/textures/mud02.jpg");
        Image highFlatImage = loadImage("../../../../external/textures/concretefloor012a.png");
        Image highSteepImage = loadImage("../../../../external/textures/rock4.jpg");
};