#include "normalmap.hpp"

#include <tga/tga_utils.hpp>

Normal::Normal(const float x, const float y, const float z) : x{x}, y{y}, z{z}
{
    const float invlen = 1.0 / sqrt(x * x + y * y + z * z);
    this->x *= invlen;
    this->y *= invlen;
    this->z *= invlen;
}

std::vector<Normal> calculate_normals(const std::vector<float>& height_image, const size_t resolution)
{
    std::vector<Normal> normals(resolution * resolution);
    const auto height_at = [&](const size_t x, const size_t y) -> double { return height_image.at(x + y * resolution); };
    const auto normal_at = [&](const size_t x, const size_t y) -> Normal& { return normals.at(x + y * resolution); };
    const double normal_scaling = resolution / 2.0;
    // edge case: corner values
    // top left
    const size_t x = 0;
    const size_t y = 0;
    const double u = height_at(x, y) - height_at(x + 1, 0);
    const double v = height_at(x, y) - height_at(0, y + 1);
    normal_at(x, y) = Normal(u * normal_scaling, v * normal_scaling, 1.f);

    // top right
    x = resolution - 1;
    y = 0;
    height_at(x - 1, y) - height_at(x, y);
    v = height_at(x, y) - height_at(x, y + 1);
    normal_at(x, y) = Normal(u * normal_scaling, v * normal_scaling, 1.f);

    // bottom left
    x = 0;
    y = resolution - 1;
    u = height_at(x, y) - height_at(x + 1, y);
    v = height_at(x, y - 1) - height_at(x, y);
    normal_at(x, y) = Normal(u * normal_scaling, v * normal_scaling, 1.f);

    // bottom right
    x = resolution - 1;
    y = resolution - 1;
    u = height_at(x - 1, y) - height_at(x, y);
    v = height_at(x, y - 1) - height_at(x, y);
    normal_at(x, y) = Normal(u * normal_scaling, v * normal_scaling, 1.f);

    // edge case: border values
    for (size_t x = 1; x < resolution - 1; ++x) {
        // top edge
            y = 0;
            u = (height_at(x - 1, y) - height_at(x + 1, y)) / 2.f;
            v = height_at(x, y) - height_at(x, y + 1);
            normal_at(x, y) = Normal(u * normal_scaling, v * normal_scaling, 1.f);

        // bottom edge
            y = resolution - 1;
            u = (height_at(x - 1, y) - height_at(x + 1, y)) / 2.f;
            v = height_at(x, y - 1) - height_at(x, y);
            normal_at(x, y) = Normal(u * normal_scaling, v * normal_scaling, 1.f);
    }
    for (size_t y = 1; y < resolution - 1; ++y) {
        // left edge
            x = 0;
            u = height_at(x, y) - height_at(x + 1, y);
            v = (height_at(x, y - 1) - height_at(x, y + 1)) / 2.f;
            normal_at(x, y) = Normal(u * normal_scaling, v * normal_scaling, 1.f);

        // right edge
            x = resolution - 1;
            u = height_at(x - 1, y) - height_at(x, y);
            v = (height_at(x, y - 1) - height_at(x, y + 1)) / 2.f;
            normal_at(x, y) = Normal(u * normal_scaling, v * normal_scaling, 1.f);
    }
    // general case
    for (size_t y = 1; y < resolution - 1; ++y) {
        for (size_t x = 1; x < resolution - 1; ++x) {
            u = (height_at(x - 1, y) - height_at(x + 1, y)) / 2.f;
            v = (height_at(x, y - 1) - height_at(x, y + 1)) / 2.f;
            normal_at(x, y) = Normal(u * normal_scaling, v * normal_scaling, 1.f);
        }
    }
    return normals;
}

void save_normalmap(const std::vector<Normal>& normals, uint32_t resolution, const std::string& output_filename)
{
    auto quantized_rgb = std::vector<uint8_t>(normals.size() * 3);
    auto quantize = [](float v) -> uint8_t {
        v = (v + 1.0) / 2.0;
        if (v >= 1.0) {
            return 255;
        } else if (v <= 0.0) {
            return 0;
        } else {
            return static_cast<uint8_t>(v * 256.0);
        }
    };
    for (size_t i = 0; i < normals.size(); ++i) {
        quantized_rgb[i * 3 + 0] = quantize(normals.at(i).x);
        quantized_rgb[i * 3 + 1] = quantize(normals.at(i).y);
        quantized_rgb[i * 3 + 2] = quantize(normals.at(i).z);
    }

    tga::writePNG(output_filename, resolution, resolution, tga::Format::r8g8b8_uint, quantized_rgb);
}