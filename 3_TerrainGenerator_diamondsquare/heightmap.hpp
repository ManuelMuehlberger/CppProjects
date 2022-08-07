#pragma once
#include <math.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

std::vector<float> mipMap(std::vector<float>&);

float getVal(int, int, int);

void setVal(int, int, float, int, std::vector<float>&);

void fillArr(std::vector<float>&);

void printArr(std::vector<float>& heightMap);

struct Heightmap {
    /**
     * @brief Save access with wrapping behavior
     *
     * @param x x-cooordinate
     * @param y y-coordinate
     * @return float&, reference to the value, allowing read and write with one function
     */
    float& at(int x, int y);
    /**
     * @brief Remaps the values in the heightmap to the rango zero to one
     *
     */
    void normalize();
    int width, height;
    std::vector<float> data;
};

class RNG {
    
public:
    RNG();
    RNG(uint32_t seed);
    /**
     * @brief receive a random float between -1 and 1
     *
     */
    float getFloat();
    /**
     * @brief Set the seed of the generator
     *
     */
    void reSeed(uint32_t seed);
    /**
     * @brief Returns the currently used seed
     *
     */
    uint32_t getSeed();

private:
    std::random_device rd;

    uint32_t seed;

    std::mt19937 generator;
};

class DiamondSquare {
public:
    /**
     * @brief Uses the diamond square algorithm to construct a heightmap
     *
     * @param n power of two as in 2^n
     * @param wrap Whether the heightmap can be tiled
     * @param featureSizeRatio Decreases the feature size for wrapped implementation
     * @param seed Seed for the random number generator
     */
    DiamondSquare(int n, bool wrap = false, int featureSizeRatio = 1, uint32_t seed = 0);
    /**
     * @brief Returns the reference to the generated heightmap
     *
     */
    Heightmap& getHeightmap();

private:
    RNG rng;

    Heightmap heightmap;

    void diamondStep(int x, int y, int stepsize, double scale);

    void squareStep(int x, int y, int stepsize, double scale);

    void generate(int n);

    // Alternative Implementation
    void diamondStepWrapped(int x, int y, int stepsize, double scale);

    void squareStepWrapped(int x, int y, int stepsize, double scale);

    void generateWrapped(int n, int featureSizeRatio);
};