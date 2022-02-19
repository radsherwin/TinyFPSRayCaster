#include <iostream>
#include <cassert>
#include <fstream>
#include <cstdint>
#include <vector>

/* My coding standard
member variables: mVarName
local variables: varName
functions: func_name()
class names: class_name
*/

uint32_t pack_color(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255)
{
    return (a << 24) + (b << 16) + (g << 8) + r;
}

void unpack_color(const uint32_t &color, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a)
{
    r = (color >> 0) & 255;
    g = (color >> 8) & 255;
    b = (color >> 16) & 255;
    a = (color >> 24) & 255;
}

void create_ppm_image(const std::string filename, const std::vector<uint32_t> &image, const size_t w, const size_t h)
{
    assert(image.size() == w * h);
    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << w << " " << h << "\n255\n";
    for (size_t i = 0; i < h * w; ++i)
    {
        uint8_t r, g, b, a;
        unpack_color(image[i], r, g, b, a);
        ofs << static_cast<char>(r) << static_cast<char>(g) << static_cast<char>(b);
    }
    ofs.close();
}

int main()
{
    const size_t winW = 512;
    const size_t winH = 512;
    std::vector<uint32_t> framebuffer(winW*winH, 255);

    for(size_t j = 0; j < winH; j++)
    {
        for(size_t i = 0; i < winW; i++)
        {
            uint8_t r = 255 * j / float(winH); // varies between 0 and 255 as j sweeps the vertical
            uint8_t g = 255 * i / float(winW); // varies between 0 and 255 as i sweeps the horizontal
            uint8_t b = 0;
            framebuffer[i + j * winW] = pack_color(r, g, b);
        }
    }

    create_ppm_image("./out.ppm", framebuffer, winW, winH);

    return 0;

}