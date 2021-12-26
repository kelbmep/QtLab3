#include "gswidget.h"
#include "../untitled4/Predicates.h"
#include "field.h"
#include <QOpenGLFunctions>

GSWidget::GSWidget(QWidget *centralwidget)
    : QOpenGLWidget(centralwidget)
{
    m_field = new Field();

    m_mainPix = QPixmap(2000, 2000);
    m_mainPix.fill(Qt::white);
    m_min = QPointF(10000, 10000);
    m_map.clear();
    m_convex.clear();
}
bool compare(QPointF a, QPointF b)
{
    return(a.x() < b.x());
}

bool operator<(const QPointF &a, const QPointF &b)
{
    return a.x() < b.x();
}

void GSWidget::paintEvent(QPaintEvent */*event*/)
{
    m_painter.begin(this);
    m_painter.drawPixmap(0, 0, m_mainPix);
    m_painter.end();
}

void GSWidget::drawPoints()
{
    QPainter tempPainter(&m_mainPix);
    tempPainter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::FlatCap));
    tempPainter.drawPoints(m_points.data(), m_points.size());

    m_painter.begin(this);
    m_painter.drawPixmap(0, 0, m_mainPix);
    m_painter.end();
}

void GSWidget::generatePoints(int number)
{
    cleanPoints();

    m_field->generate(number, w, h);

    m_points.clear();
    m_points.reserve(m_points.size() / 2);
    m_min = QPointF(10000, 10000);

    for(size_t i = 0; i < m_field->m_points.size(); i += 2)
    {
        if(m_field->m_points[i] < m_min.x())
            m_min = QPointF(m_field->m_points[i], m_field->m_points[i + 1]);
        m_points.push_back(QPointF(
            m_field->m_points[i],
            m_field->m_points[i + 1]
        ));
    }
    m_mainPix = QPixmap(w, h);
    m_mainPix.fill(Qt::white);

    drawPoints();
}

void GSWidget::cleanPoints()
{
    auto g = geometry();
    h = g.height();
    w = g.width();

    m_mainPix = QPixmap(w, h);
    m_mainPix.fill(Qt::white);

    m_painter.begin(this);
    m_painter.drawPixmap(0, 0, m_mainPix);
    m_painter.end();
    m_map.clear();
    m_convex.clear();
}

void GSWidget::convexHull()
{
    QPainter tempPainter(&m_mainPix);
    tempPainter.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::FlatCap));
    for(size_t i = 0; i < m_points.size(); i++)
        if(m_points[i] != m_min)
            m_map[((double)m_points[i].y() - m_min.y()) / (m_points[i].x() - m_min.x())] = m_points[i];
        else
            m_map[999999] = m_points[i];
    m_convex.push_back(m_min);
    std::map<double, QPointF>::iterator it = m_map.begin();
    auto* pa = new double[2];
    auto* pb = new double[2];
    auto* pc = new double[2];
    QPointF v = it->second;
    it++;
    QPointF w = it->second;
    it++;
    while(v != m_min)
    {
        pa[0] = m_convex.back().x();
        pa[1] = m_convex.back().y();
        pb[0] = v.x();
        pb[1] = v.y();
        pc[0] = w.x();
        pc[1] = w.y();
        if(exact::orient2d(pa, pb, pc) == -1)
        {
            v = m_convex.back();
            m_convex.pop_back();
        }
        else
        {
            m_convex.push_back(v);
            v = w;
            if(it == m_map.end())
                w = m_min;
            else
                w = it->second;
            it++;
        }
    }
    for(size_t i = 0; i < m_convex.size() - 1; i++)
       tempPainter.drawLine(m_convex[i], m_convex[i+1]);
    tempPainter.drawLine(m_convex[m_convex.size() - 1], m_convex[0]);
    m_painter.begin(this);
    m_painter.drawPixmap(0, 0, m_mainPix);
    m_painter.end();
}
