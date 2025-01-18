#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "App/app.h"

// RGB struct to store pixel data
struct RGB {
    int r, g, b;
};

// Load BMP image and return pixel data (simplified version)
std::vector<RGB> LoadBMP(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Error loading BMP file" << std::endl;
        return {};
    }

    // Read header data (simplified, assumes 24-bit BMP)
    file.seekg(18);
    file.read(reinterpret_cast<char*>(&width), sizeof(width));
    file.read(reinterpret_cast<char*>(&height), sizeof(height));

    // Skip to pixel data (simplified)
    file.seekg(54); // BMP header is 54 bytes

    std::vector<RGB> pixels(width * height);
    file.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * sizeof(RGB));

    return pixels;
}

// Define the color codes for each level object
enum class LevelObject {
    None,       // Empty space
    Obstacle,   // Wall or obstacle
    Patch,      // Physics patch (boost, friction)
    Goal        // Goal area
};

LevelObject GetLevelObjectFromColor(const RGB& color) {
    if (color.r == 255 && color.g == 0 && color.b == 0) return LevelObject::Obstacle;   // Red
    if (color.r == 0 && color.g == 255 && color.b == 0) return LevelObject::Patch;      // Green
    if (color.r == 0 && color.g == 0 && color.b == 255) return LevelObject::Goal;       // Blue
    return LevelObject::None;
}

void BuildLevelFromImage(const std::vector<RGB>& pixels, int width, int height) {
    // Loop through all pixels and create corresponding objects
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            RGB pixel = pixels[y * width + x];
            LevelObject objType = GetLevelObjectFromColor(pixel);

            // Based on the object type, place it in the level
            switch (objType) {
                case LevelObject::Obstacle:
                    std::cout << "Found obstacle at (" << x << ", " << y << ")\n";
                    // Create obstacle at this position
                    break;
                case LevelObject::Patch:
                    std::cout << "Found patch at (" << x << ", " << y << ")\n";
                    // Create physics patch at this position
                    break;
                case LevelObject::Goal:
                    std::cout << "Found goal at (" << x << ", " << y << ")\n";
                    // Create goal at this position
                    break;
                default:
                    break;
            }
        }
    }
}

int main() {
    int width, height;
    std::vector<RGB> pixels = LoadBMP("level.bmp", width, height);

    if (!pixels.empty()) {
        BuildLevelFromImage(pixels, width, height);
    }

    return 0;
}
