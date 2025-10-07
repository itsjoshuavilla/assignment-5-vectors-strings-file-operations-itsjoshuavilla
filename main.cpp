#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include "pixel.h"

// I wrote this helper to parse one CSV line using only .find() and .substr(),
// the instructions suggested (so no stringstream).
// Expected format per line: x,y,r,g,b
bool parse_pixel_line(const std::string &line, Pixel &out)
{
    // I locate commas first, then slice substrings between them.
    size_t p0 = 0;
    size_t c1 = line.find(',', p0);
    if (c1 == std::string::npos) return false;

    size_t c2 = line.find(',', c1 + 1);
    if (c2 == std::string::npos) return false;

    size_t c3 = line.find(',', c2 + 1);
    if (c3 == std::string::npos) return false;

    size_t c4 = line.find(',', c3 + 1);
    if (c4 == std::string::npos) return false;

    // Now I cut each field out of the string.
    std::string sx = line.substr(p0, c1 - p0);
    std::string sy = line.substr(c1 + 1, c2 - (c1 + 1));
    std::string sr = line.substr(c2 + 1, c3 - (c2 + 1));
    std::string sg = line.substr(c3 + 1, c4 - (c3 + 1));
    std::string sb = line.substr(c4 + 1);

    // Convert text to numbers. If anything fails, I reject the line.
    try {
        out.x = std::stoi(sx);
        out.y = std::stoi(sy);
        out.r = std::stof(sr);
        out.g = std::stof(sg);
        out.b = std::stof(sb);
    } catch (...) {
        return false;
    }
    return true;
}

// function computes the average R, G, and B over the whole image.
// I'm printing them to the console so I can check they look reasonable.
void average_colors(std::vector<Pixel> &pixel_list)
{
    if (pixel_list.empty()) {
        std::cout << "No pixels loaded.\n";
        return;
    }

    long double rsum = 0.0L, gsum = 0.0L, bsum = 0.0L;

    // I just sum all the colors and divide by the count at the end.
    for (const auto &p : pixel_list) {
        rsum += p.r;
        gsum += p.g;
        bsum += p.b;
    }

    long double n = static_cast<long double>(pixel_list.size());
    long double ravg = rsum / n;
    long double gavg = gsum / n;
    long double bavg = bsum / n;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Average R: " << static_cast<double>(ravg) << "\n";
    std::cout << "Average G: " << static_cast<double>(gavg) << "\n";
    std::cout << "Average B: " << static_cast<double>(bavg) << "\n";
}

// Here I flip the image vertically. Conceptually, top row swaps with bottom row.
// I don’t hardcode the height, I find max_y from the data and do y to max_y - y.
// For a 256-height image with y in [0,255], this gives the correct mirror.
void flip_vertically(std::vector<Pixel> &pixel_list)
{
    if (pixel_list.empty()) return;

    // First pass: figure out the biggest y so I know the height-1.
    int max_y = pixel_list.front().y;
    for (const auto &p : pixel_list) {
        if (p.y > max_y) max_y = p.y;
    }

    // Second pass: apply the flip to every pixel (x stays the same).
    for (auto &p : pixel_list) {
        p.y = max_y - p.y;
    }
}

int main(int argc, char *argv[])
{
    // I read the filename from the command line to follow the spec.
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>\n";
        std::cerr << "Example: " << argv[0] << " pixels.dat\n";
        return 1;
    }

    std::string input_path = argv[1];

    // This vector stores every pixel I read from the file.
    std::vector<Pixel> pixel_list;
    // Pre-reserving helps performance since we expect 512*256 = 131072 pixels.
    pixel_list.reserve(131072);

    // Open the input CSV (comma-separated) file.
    std::ifstream fin(input_path);
    if (!fin) {
        std::cerr << "Error: could not open input file '" << input_path << "'.\n";
        return 1;
    }

    // I read line by line and parse each into a Pixel.
    std::string line;
    size_t line_num = 0, loaded = 0, bad = 0;
    while (std::getline(fin, line)) {
        ++line_num;
        if (line.empty()) continue;

        Pixel px;
        if (parse_pixel_line(line, px)) {
            pixel_list.push_back(px); // storing into the vector as required
            ++loaded;
        } else {
            // If the line was malformed, skip it and keep going.
            ++bad;
        }
    }
    fin.close();

    if (loaded == 0) {
        std::cerr << "No valid pixels were read. Aborting.\n";
        return 1;
    }

    std::cout << "Loaded " << loaded << " pixels";
    if (bad > 0) std::cout << " (" << bad << " malformed line(s) skipped)";
    std::cout << ".\n";

    // Step 4: show the average colors so I can verify the data looks sane.
    average_colors(pixel_list);

    // Step 4: perform the vertical flip on the whole image.
    flip_vertically(pixel_list);

    // Step 5: write the flipped image to a new file with the same CSV layout.
    const std::string out_path = "flipped.dat";
    std::ofstream fout(out_path);
    if (!fout) {
        std::cerr << "Error: could not open output file '" << out_path << "' for writing.\n";
        return 1;
    }

    // I keep high precision so I don’t lose detail when saving floats.
    fout << std::fixed << std::setprecision(16);
    for (const auto &p : pixel_list) {
        // Keep the exact "x,y,r,g,b" format (comma-separated, one pixel per line).
        fout << p.x << "," << p.y << ","
             << static_cast<double>(p.r) << ","
             << static_cast<double>(p.g) << ","
             << static_cast<double>(p.b) << "\n";
    }
    fout.close();

    std::cout << "Wrote flipped pixels to '" << out_path << "'.\n";
    return 0;
}
