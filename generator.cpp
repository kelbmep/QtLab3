#include "generator.h"
#include <random>
#include <ctime>

void Generator::generate(std::vector<double> &points,
    double maxX, double maxY)
{
    std::mt19937 gen(time(0));

    double maxx = gen.max() / (maxX - 50);
    double maxy = gen.max() / (maxY - 50);

    for (size_t i = 0; i < points.size(); i += 2)
    {
        points[i] = gen() / maxx + 25;
        points[i + 1] = gen() / maxy + 25;
    }
}

void Generator::generate(std::vector<double>& points)
{
    std::mt19937 gen(time(0));
    double max = gen.max();

    for (size_t i = 0; i < points.size(); i++)
            points[i] = gen() / max;
}
