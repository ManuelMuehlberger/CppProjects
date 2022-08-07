#include "splatmap.hpp"

SplatMap::SplatMap(Heightmap& heightMap, Normalmap& normalMap, int size) : mSize{size}, data(heightMap.data.size())
{
    // basic sanity-check
    assert(heightMap.data.size() == normalMap.size());

    SplatMap::generateSplatMap(heightMap, normalMap);

    SplatMap::mergeTextures(heightMap, normalMap);
}

glm::vec4& SplatMap::atData(int x, int y)
{
    // Wrap around for the coordinates
    x = (x + mSize) % mSize;
    y = (y + mSize) % mSize;
    return data.at(x + y * mSize);
}

glm::vec3& SplatMap::atImage(int x, int y)
{
    // Wrap around for the coordinates
    x = (x + mSize) % mSize;
    y = (y + mSize) % mSize;
    return image.at(x + y * mSize);
}

float getMaxHeight(Heightmap& heightMap)
{
    float maxF = -6e9;  // Immature Joke
    for (float v : heightMap.data) {
        if (v > maxF) maxF = v;
    }
    return maxF;
}

float getMaxSlope(Normalmap& normalMap)
{
    float minF = 4e20;  // Pretty high
    for (auto v : normalMap.data) {
        if (v.z < minF) minF = v.z;
    }
    return minF;
}

void SplatMap::generateSplatMap(Heightmap& heightMap, Normalmap& normalMap)
{
    // 1. die Maxima feststellen
    float maxHeight = getMaxHeight(heightMap);
    float maxSlope = getMaxSlope(normalMap);  // obwohl es maxSlope heißt, wird es wie ein Minimum behandelt, da der
                                              // kleinste z wert den größten Slope angibt

    // für jeden Punkt die Blending-Anteile ausrechnen
    for (size_t y = 0; y < mSize; y++) {
        for (size_t x = 0; x < mSize; x++) {
            // die 2 Werte an (x,y) samplen um daraus die weights der splatmap berechnen zu können
            float curHeight = heightMap.at(x, y);
            float curSlope = normalMap.at(x, y).z;

            // 1. Low-Height-Weight
            float lowHeightWeight = maxHeight - curHeight;
            // 2. High-Height-Weight
            float highHeightWeight = 1 - lowHeightWeight;
            // 3. Flat-Slope-Weight
            float flatSlopeWeight = curSlope - maxSlope;
            // 4. Steep-Slope-Weight
            float steepSlopeWeight = 1 - flatSlopeWeight;

            // das Weighting basierend auf den Werten ausrechnen
            // alph1 := LowFlat
            float alph1 = lowHeightWeight * flatSlopeWeight;
            // alph2 := LowSteep
            float alph2 = lowHeightWeight * steepSlopeWeight;
            // alp3 := HighFlat
            float alph3 = highHeightWeight * flatSlopeWeight;
            // alph4 := HighSteep
            float alph4 = highHeightWeight * steepSlopeWeight;

            // storing the result
            atData(x, y).x = alph1;
            atData(x, y).y = alph2;
            atData(x, y).z = alph3;
            atData(x, y).a = alph4;
        }
    }
}

void SplatMap::mergeTextures(Heightmap& heightMap, Normalmap& normalMap)
{
    for (size_t y = 0; y < mSize; y++) {
        for (size_t x = 0; x < mSize; x++) {
            Image lowFlatImage = loadImage("../../../../external/textures/gras15.jpg");
            Image lowSteepImage = loadImage("../../../../external/textures/mud02.jpg");
            Image highFlatImage = loadImage("../../../../external/textures/concretefloor012a.png");
            Image highSteepImage = loadImage("../../../../external/textures/rock4.jpg");

            // R
            atImage(x, y).x = atData(x, y).x * lowFlatImage.data.at(x / lowFlatImage.width + y / lowFlatImage.height) +
                              atData(x, y).y;

            // G
            atImage(x, y).y = atData(x, y).x * lowFlatImage.data.at(x / lowFlatImage.width + y / lowFlatImage.height) +
                              atData(x, y).y;

            // B
            atImage(x, y).z = atData(x, y).x * lowFlatImage.data.at(x / lowFlatImage.width + y / lowFlatImage.height) +
                              atData(x, y).y;
        }
    }
}