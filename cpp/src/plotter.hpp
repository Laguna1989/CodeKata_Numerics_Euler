#ifndef CODE_KATA_PLOTTER_H
#define CODE_KATA_PLOTTER_H

#include <map>
#include <string>
#include <valarray>
#include <vector>

typedef struct {
    double r; // a fraction between 0 and 1
    double g; // a fraction between 0 and 1
    double b; // a fraction between 0 and 1
} rgb;

class Plotter {
public:
    Plotter();
    void set_xrange(double xmin, double xmax);
    void set_yrange(double ymin, double ymax);

    void add_data(std::map<double, std::valarray<double>> const& data);

    void write_png(std::string const& filename, int image_width, int image_height);

private:
    double m_xmin;
    double m_xmax;
    double m_ymin;
    double m_ymax;

    std::map<double, std::valarray<double>> m_data;

    void set_pixel_at(std::vector<std::uint8_t>& image_data, int x, int y, int image_width,
        int image_height, rgb col, int point_size);
};

#endif // CODE_KATA_PLOTTER_H
