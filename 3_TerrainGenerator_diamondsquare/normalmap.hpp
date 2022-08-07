#pragma once
#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

struct Normal {
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
    Normal() = default;
    Normal(const float x, const float y, const float z);
};

std::vector<Normal> calculate_normals(const std::vector<float>& height_image, const size_t resolution);

void save_normalmap(const std::vector<Normal>& normals, uint32_t resolution, const std::string& output_filename);