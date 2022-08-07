#include "command_line_parser.hpp"
#include "heightmap.hpp"
#include "normalmap.hpp"
#include "splatmap.hpp"

unsigned arrSize1{10};

void printArr(std::vector<float>& heightMap)
{
    for (size_t i = 0; i < arrSize1; i++) {
        for (size_t j = 0; j < arrSize1; j++) {
            std::cout << heightMap.at(i + j * arrSize1) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printUsage()
{
    std::cout << "Required options:\n"
              << "\t-x/--width <num>\n"
              << "\t-y/--height <num>\n"
              << "\t--out-height <filename>\n";
    std::cout << "Optional:\n"
              << "\t-n/--normal-map\n"
              << "\t-p/--splat-map\n"
              << "\t-m/--mipmap\n"
              << "\t-w/--wrap\n"
              << "\t-h/--help\n"
              << "\t-s/--smooth <num>\n"
              << "\t--seed <num>\n"
              << "\t-f/--feature-size-ratio <num>\n";
}

// Variables needed for heightmap creation
struct ProgramArguments {
    int width, height;
    std::string outHeight;
    uint32_t seed = 0;
    int smoothingIterations = 0;
    bool wrap = false;
    int featureSizeRatio = 1;
    bool heightBlur = false;
    bool normalMap = false;
    bool mipMap = false;
    bool splatMap = false;
};

ProgramArguments parseArguments(int argc, char* argv[])
{
    // TODO: options

    // Options to parse from the commandline {short_name, long_name, hasParameter}
    // 0 means there is no short name for that option
    std::vector<Option> options{{'x', "width", true},
                                {'y', "height", true},
                                {'o', "out-height", true},
                                {'s', "smooth", true},
                                {'n', "normal-map"},
                                {'p', "splat-map"},
                                {'m', "mip-map"},
                                // This is the bonus
                                {'h', "help"},
                                {'w', "wrap"},
                                {0, "seed", true},
                                {'f', "feature-size-ratio", true},
                                {0, "height-blur"}};
    ParsingResult parsingResult(argc, argv, options);
    ProgramArguments arguments;
    // Parsing the parameters and acting accordingly
    if (parsingResult.is_present({'h', "help"})) {
        printUsage();
        // If you ask for help, you don't know how the program works
        // We close the program so you can try again
        exit(EXIT_SUCCESS);
    }
    // With the magic of templates, we don't have to write a function for each type
    parsingResult.assign({'x', "width"}, arguments.width);
    parsingResult.assign({'y', "height"}, arguments.height);
    parsingResult.assign({'o', "out-height"}, arguments.outHeight);
    // Optional arguments have default values, so if they are not set, nothing happens
    parsingResult.try_assign({'s', "smooth"}, arguments.smoothingIterations);
    parsingResult.try_assign({0, "seed"}, arguments.seed);
    parsingResult.try_assign({'f', "feature-size-ration"}, arguments.featureSizeRatio);
    arguments.featureSizeRatio = glm::max(arguments.featureSizeRatio, 1);
    // Options that don't have arguments change the program just by being present
    arguments.wrap = parsingResult.is_present({'w', "wrap"});
    arguments.heightBlur = parsingResult.is_present({0, "height-blur"});
    arguments.mipMap = parsingResult.is_present({'m', "mip-map"});
    arguments.normalMap = parsingResult.is_present({'n', "normal-map"});
    arguments.splatMap = parsingResult.is_present({'p', "splat-map"});

    return arguments;
};

Heightmap smoothMeanValue(Heightmap input, int iterations, bool wrap)
{
    Heightmap output = input;                     // This is just to copy the dimensions and initialize the data vector
    for (int it = 0; it < iterations; it++) {     // number of iterations
        for (int y = 0; y < input.height; y++) {  // iterate y
            for (int x = 0; x < input.width; x++) {  // iterate x
                float sum = 0;
                if (wrap) {                                     // Wrap around using safe access
                    for (int i = y - 1; i <= y + 1; i++)        // interpolate
                        for (int j = x - 1; j <= x + 1; j++) {  // interpolate
                            sum += input.at(j, i);
                        }
                    output.at(x, y) = sum / 9;
                } else {  // Reduce sample size
                    int count = 0;
                    for (int i = std::max(0, y - 1); i <= std::min(input.height - 1, y + 1); i++)       // interpolate
                        for (int j = std::max(0, x - 1); j <= std::min(input.width - 1, x + 1); j++) {  // interpolate
                            sum += input.at(j, i);
                            count++;
                        }
                    output.at(x, y) = sum / count;
                }
            }
        }
        // The new input is the old output
        input.data = output.data;
    }
    return output;
}

int main(int argc, char* argv[])
{
    // Parse the program arguments
    ProgramArguments args;
    try {
        args = parseArguments(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "[Resource Generator] Error: " << e.what() << '\n';
        return -1;
    }
    // Determine the closest power of two, cut down extent later
    int maxLen = std::max(args.width, args.height);
    int n = -1;
    while (maxLen) {  // Count how many times you can divide by 2
        n++;
        maxLen /= 2;
    }
    int powerTwo = 1 << n;  // A shift to the left is equivalent to multiplying by 2 and we shift n time
    if (powerTwo < std::max(args.width, args.height)) n++;
    // Restrictions and error checking
    if (n > 13) {
        std::cerr << "Over 8k resolution not available, choose a lower resolution, please\n";
        return -1;
    }
    if (n == -1) {
        std::cerr << "Resolution must be greater than 0\n";
        return -1;
    }
    std::cout << "Squaring the Diamond\n";
    // Construct a heightmap using the diamond square algorightm
    DiamondSquare ds{n, args.wrap, args.featureSizeRatio, args.seed};
    auto& tempHeightmap = ds.getHeightmap();
    // Trim the heightmap to the desired dimensions
    Heightmap heightmap{args.width, args.height, std::vector<float>(args.width * args.height)};
    for (int y = 0; y < args.height; y++)
        for (int x = 0; x < args.width; x++) heightmap.at(x, y) = tempHeightmap.at(x, y);
    // Remap to a valid range, we can't have less than 0 in hdr
    heightmap.normalize();
    // Smooth the heightmap if requested
    if (args.smoothingIterations) {
        std::cout << "Playing Smooth Jazz\n";
        if (args.heightBlur) {  // This just an attempt to make the heightmap more interesting
            // Blur Interpolate with height, more blurred on the bottom
            auto blurred = smoothMeanValue(heightmap, args.smoothingIterations, args.wrap);
            for (int y = 0; y < heightmap.height; y++)
                for (int x = 0; x < heightmap.width; x++) {
                    // Basically alpha blending with height as the alpha
                    auto h = heightmap.at(x, y);
                    auto b = blurred.at(x, y);
                    auto weight = glm::smoothstep(0.f, 1.f, h);
                    heightmap.at(x, y) = weight * h + (1 - weight) * b;
                }
        } else {
            heightmap = smoothMeanValue(heightmap, args.smoothingIterations, args.wrap);
        }
    }
    std::cout << "Saving result as \"" << args.outHeight << "\"\n";
    // Save it as an hdr image and we are done
    tga::writeHDR(args.outHeight, heightmap.width, heightmap.height, tga::Format::r32_sfloat, heightmap.data);
    std::cout << "Done" << std::endl;
    // Mip Map if option was chosen
    if (args.mipMap)
    {
        std::cout << "Mip Mapping" << std::endl;
        heightmap = mipMap(heightmap);
    }
    // Normal Map if option was chosen
    if (args.splatMap) 
    {
        std::cout << "Splat Map" << std::endl;
        SplatMap s = new SplatMap(heightmap, n, 1);
        // save normal map at outHeight+"splatMap"
    } else if (args.normalMap) 
    {
        std::cout << "Normal Map" << std::endl;
        Normalmap n = new Normalmap(heightmap);
        // save normal map at outHeight+"normalMap"
    }

    return 0;
}