#ifndef GSWIDGET_H
#define GSWIDGET_H

#include <QOpenGLWidget>
#include <QPainter>

class Field;

class GSWidget : public QOpenGLWidget
{
public:
    GSWidget(QWidget *centralwidget);

    void drawPoints();
    void generatePoints(int number);
    void cleanPoints();
    void convexHull();

protected:
    void paintEvent(QPaintEvent *event);

private:
    int h, w;

    QPixmap m_mainPix;

    QPainter m_painter;

    std::vector<QPointF> m_points;
    QPointF m_min;
    std::map<double, QPointF> m_map;
    std::vector<QPointF> m_convex;
    Field* m_field;

};

#endif // GSWIDGET_H
