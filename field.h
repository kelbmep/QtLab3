#ifndef FIELD_H
#define FIELD_H
#include<vector>

class Field
{
public:
    std::vector<double> m_points;

    Field();

    void generate(int num, int w, int h);

private:
    int m_height;
    int m_width;
};

#endif // FIELD_H
