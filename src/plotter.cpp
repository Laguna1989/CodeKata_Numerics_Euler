#include "plotter.hpp"
#include "lodepng.h"
#include <iostream>

namespace {

typedef struct {
    double h; // angle in degrees
    double s; // a fraction between 0 and 1
    double v; // a fraction between 0 and 1
} hsv;

static hsv rgb2hsv(rgb in);
static rgb hsv2rgb(hsv in);

rgb hsv2rgb(hsv in)
{
    double hh, p, q, t, ff;
    long i;
    rgb out;

    if (in.s <= 0.0) { // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if (hh >= 360.0)
        hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch (i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}

} // namespace

Plotter::Plotter()
    : m_xmin { -1 }
    , m_xmax { 1 }
    , m_ymin { -1 }
    , m_ymax { 1 }
{
}

void Plotter::set_xrange(double xmin, double xmax)
{
    m_xmin = xmin;
    m_xmax = xmax;
}

void Plotter::set_yrange(double ymin, double ymax)
{
    m_ymin = ymin;
    m_ymax = ymax;
}

void Plotter::add_data(std::map<double, std::valarray<double>> const& data) { m_data = data; }

void Plotter::write_png(std::string const& filename, int image_width, int image_height)
{
    std::vector<uint8_t> image_data;
    std::size_t const image_vector_size = image_width * image_height * 4;
    image_data.resize(image_vector_size, 255);

    double const width = m_xmax - m_xmin;
    double const height = m_ymax - m_ymin;

    double const tmax = m_data.rbegin()->first;
    for (auto const& kvp : m_data) {

        // absolute values
        double x = 0.0;
        double y = 0.0;
        // 1d data -> use t as x
        if (kvp.second.size() == 1) {
            x = kvp.first;
            y = kvp.second[0];
        }
        // 2d data -> use x,y and t only for color
        else if (kvp.second.size() == 2) {
            x = kvp.second[0];
            y = kvp.second[1];
        }
        // relative position on image
        double const xp = (x - m_xmin) / width;
        double const yp = (y - m_ymin) / height;

        // relative position in pixel coordinates.
        int const xpi = static_cast<int>(xp * image_width);
        int const ypi = static_cast<int>(yp * image_height);

        auto col_rgb = hsv2rgb(hsv { kvp.first / tmax * 360.0, 1.0, 1.0 });

        set_pixel_at(image_data, xpi, ypi, image_width, image_height, col_rgb, 5);
    }
    lodepng::encode(filename, image_data, image_width, image_height);
}


void Plotter::set_pixel_at(std::vector<std::uint8_t>& image_data, int x, int y, int image_width,
    int image_height, rgb col, int point_size)
{
    for (int i = 0; i != point_size; ++i) {
        for (int j = 0; j != point_size; ++j) {
            int const xpi = x + i;
            int const ypi = y + j;
            if (xpi <= 0 || xpi >= image_width)
            {
                continue;
            }
            if (ypi <= 0 || ypi >= image_height)
            {
                continue;
            }
            int const index = (xpi + (image_height - ypi) * image_width) * 4;

            // write RGBA Value to pixel position
            image_data.at(index) = static_cast<std::uint8_t>(col.r * 255);
            image_data.at(index + 1) = static_cast<std::uint8_t>(col.g * 255);
            image_data.at(index + 2) = static_cast<std::uint8_t>(col.b * 255);
            image_data.at(index + 3) = 255;
        }
    }
}
