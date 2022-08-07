#include "heightmap.hpp"

#include "tga/tga_math.hpp"

const unsigned arrSize{10};
vector<float> heightmap(100);  //cache

std::default_random_engine randomness(static_cast<unsigned>(time(nullptr)));
std::normal_distribution<float> distribution(0.1f, 1.0f);

vector<float> mipMap(vector<float>& heightmap)
{
    fillArr(heightmap);

    // hoehe: 0,5size
    // breite: size
    vector<float> yHeightMap(heightmap.size() / 2);

    vector<float> newHeightMap(sqrt(heightmap.size()));

    // 1. hoehe halbieren: y
    for (size_t y = 0; y < arrSize; y += 2) {
        // durch x iterieren
        for (size_t x = 0; x < arrSize; x++) {
            float upperVal = getVal(x, y, arrSize);
            float lowerVal;
            // Sonderfall, falls die Dimension ungerade ist und wir die letzte Reihe anders machen muessen
            if (y == arrSize - 1) {
                lowerVal = getVal(x, y - 1, arrSize);
            } else {
                lowerVal = getVal(x, y + 1, arrSize);
            }
            setVal(x, y, (float)(upperVal + lowerVal) / 2, arrSize, yHeightMap);
        }
    }

    // 2. breite halbieren: x
    for (size_t x = 0; x < arrSize; x += 2) {
        // durch x iterieren
        for (size_t y = 0; y < arrSize / 2; y++) {
            float upperVal = getVal(x, y, arrSize);
            float lowerVal;
            // Sonderfall, falls die Dimension ungerade ist und wir die letzte Reihe anders machen muessen
            if (y == arrSize - 1) {
                lowerVal = getVal(x, y - 1, arrSize);
            } else {
                lowerVal = getVal(x, y + 1, arrSize);
            }
            setVal(x, y, (float)(upperVal + lowerVal) / 2, arrSize, newHeightMap);
        }
    }
    return newHeightMap;
}

void fillArr(std::vector<float>& heightMap)
{
    for (size_t i = 0; i < arrSize; i++) {
        for (size_t j = 0; j < arrSize; j++) {
            setVal(i, j, distribution(randomness), arrSize, heightMap);
        }
    }
}

void setVal(int x, int y, float val, int size, std::vector<float>& heightMap) { heightmap.at(x + y * size) = val; }

float getVal(int x, int y, int size) { return heightmap.at(x + y * size); }

/*Heightmap Function Implementations*/
float& Heightmap::at(int x, int y)
{
    // Wrap around for the coordinates
    x = (x + width) % width;
    y = (y + height) % height;
    return data[x + y * width];
}

void Heightmap::normalize()
{
    float minF = 4e20;  // Pretty high
    float maxF = -6e9;  // Immature Joke
    for (auto f : data) {
        minF = glm::min(minF, f);
        maxF = glm::max(maxF, f);
    }
    for (auto& f : data) f = glm::remap(f, minF, maxF, 0.f, 1.f);
}

/*RNG Function Implementations*/
RNG::RNG() : seed(rd()), generator(seed) {}

RNG::RNG(uint32_t seed) : seed(seed), generator(seed) {}

uint32_t RNG::getSeed() { return seed; }

void RNG::reSeed(uint32_t seed) { generator.seed(seed); }

float RNG::getFloat()
{
    // With a Sigma of .5, the values range roughly from -1.5 to 1.5
    auto dist = std::normal_distribution<float>{0, .5};
    float val = dist(generator);
    return val;
}

/*Diamond Square Function Implementations*/
DiamondSquare::DiamondSquare(int n, bool wrap, int featureSizeRatio, uint32_t seed)
{
    if (seed)
        rng.reSeed(seed);
    else {
        std::cout << "[Resource Generator] Diamond Square" << (wrap ? " Wrapped" : "")
                  << " using seed: " << rng.getSeed() << "\n";
    }
    if (wrap)
        generateWrapped(n, featureSizeRatio);
    else
        generate(n);
}

Heightmap& DiamondSquare::getHeightmap() { return heightmap; }

// Regular diamond step with no wrapping
void DiamondSquare::diamondStep(int x, int y, int step, double scale)
{
    // Could I just pass halfstep instead of step as parameter?
    int hs = step / 2;
    int total = 0;
    float value = 0;
    bool left = x - hs >= 0;
    bool right = x + hs < heightmap.width;
    bool up = y - hs >= 0;
    bool down = y + hs < heightmap.height;
    if (up && left) {
        total++;
        value += heightmap.at(x - hs, y - hs);
    }
    if (up && right) {
        total++;
        value += heightmap.at(x + hs, y - hs);
    }
    if (down && left) {
        total++;
        value += heightmap.at(x - hs, y + hs);
    }
    if (down && right) {
        total++;
        value += heightmap.at(x + hs, y + hs);
    }
    heightmap.at(x, y) = value / total + rng.getFloat() * scale;
}

// Regular square step with no wrapping
void DiamondSquare::squareStep(int x, int y, int step, double scale)
{
    int hs = step / 2;
    int total = 0;
    float value = 0;
    if (x - hs >= 0) {
        value += heightmap.at(x - hs, y);
        total++;
    }
    if (x + hs < heightmap.width) {
        value += heightmap.at(x + hs, y);
        total++;
    }
    if (y - hs >= 0) {
        value += heightmap.at(x, y - hs);
        total++;
    }
    if (y + hs < heightmap.height) {
        value += heightmap.at(x, y + hs);
        total++;
    }
    heightmap.at(x, y) = value / total + rng.getFloat() * scale;
}

// Regular diamond square algorithm with no wrapping
void DiamondSquare::generate(int n)
{
    int res = (1 << n) + 1;
    heightmap = {res, res, std::vector<float>(res * res)};
    // Init corners
    heightmap.at(0, 0) = rng.getFloat();
    heightmap.at(0, res - 1) = rng.getFloat();
    heightmap.at(res - 1, 0) = rng.getFloat();
    heightmap.at(res - 1, res - 1) = rng.getFloat();
    double scale = 1;
    for (int step = res - 1; step > 1; step /= 2, scale /= 2) {
        int halfstep = step / 2;
        for (int y = halfstep; y < res; y += step) {
            for (int x = halfstep; x < res; x += step) diamondStep(x, y, step, scale);
        }
        // Two for loops since the diamond centers are offset every second row
        for (int y = 0; y < res; y += step) {
            for (int x = halfstep; x < res; x += step) squareStep(x, y, step, scale);
        }
        for (int y = halfstep; y < res; y += step) {
            for (int x = 0; x < res; x += step) squareStep(x, y, step, scale);
        }
    }
}

// Diamond step with wrapping
void DiamondSquare::diamondStepWrapped(int x, int y, int step, double scale)
{
    int hs = step / 2;
    heightmap.at(x, y) = (heightmap.at(x - hs, y - hs) + heightmap.at(x + hs, y - hs) + heightmap.at(x - hs, y + hs) +
                          heightmap.at(x + hs, y + hs)) /
                             4 +
                         rng.getFloat() * scale;
}
// Square step with wrapping
void DiamondSquare::squareStepWrapped(int x, int y, int step, double scale)
{
    int hs = step / 2;
    heightmap.at(x, y) = (heightmap.at(x - hs, y + 0) + heightmap.at(x + hs, y + 0) + heightmap.at(x + 0, y - hs) +
                          heightmap.at(x + 0, y + hs)) /
                             4 +
                         rng.getFloat() * scale;
}
// Diamond Square Algorithm using wrapping behavior of heightmap access
void DiamondSquare::generateWrapped(int n, int featureSizeRatio)
{
    int res = (1 << n);
    heightmap = {res, res, std::vector<float>(res * res)};
    // Wrapping behavior allows for variance in the feature size of the algorithm
    // Default feature size of 2 makes more interesting heightmaps (personal opinion)
    int featureSize = res / featureSizeRatio;
    heightmap.at(0, 0) = rng.getFloat();
    heightmap.at(featureSize, 0) = rng.getFloat();
    heightmap.at(0, featureSize) = rng.getFloat();
    heightmap.at(featureSize, featureSize) = rng.getFloat();
    double scale = 1;
    for (int step = featureSize; step > 1; step /= 2, scale /= 2) {
        int halfstep = step / 2;
        for (int y = halfstep; y < heightmap.height + halfstep; y += step)
            for (int x = halfstep; x < heightmap.width + halfstep; x += step) diamondStepWrapped(x, y, step, scale);
        for (int y = 0; y < res; y += step)
            for (int x = halfstep; x < res; x += step) squareStepWrapped(x, y, step, scale);
        for (int y = halfstep; y < res; y += step)
            for (int x = 0; x < res; x += step) squareStepWrapped(x, y, step, scale);
    }
}
