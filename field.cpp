#include "field.h"
#include "generator.h"

Field::Field()
{

}

void Field::generate(int num, int w, int h)
{
    m_width = w;
    m_height = h;

    m_points.resize(num * 2);
    Generator::generate(m_points, w, h);
}
