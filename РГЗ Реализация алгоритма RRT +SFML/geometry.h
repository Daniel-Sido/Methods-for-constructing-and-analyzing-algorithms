#ifndef GEOMETRY_H    
#include <math.h>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;
#define ftype double 
const ftype EPS = 1e-6;//точность

struct Point {
    ftype x, y;
    Point() {}
    Point(ftype x, ftype y) : x(x), y(y) {}
    Point &operator+=(const Point &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    Point &operator-=(const Point &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    Point &operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    Point &operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    Point operator+(const Point &t) const {
        return Point(*this) += t;
    }
    Point operator-(const Point &t) const {
        return Point(*this) -= t;
    }
    Point operator*(ftype t) const {
        return Point(*this) *= t;
    }
    Point operator/(ftype t) const {
        return Point(*this) /= t;
    }
    ftype dot(const Point &t) const {
        return (x * t.x + y * t.y);
    }
    ftype cross(const Point &t) const {
        return x * t.y - y * t.x;
    }
    ftype cross(const Point &a, const Point &b) const {
        return (a - *this).cross(b - *this);
    }
    ftype distance(const Point &t) const {
        const double x_diff = x - t.x, y_diff = y - t.y;
        return sqrt(x_diff * x_diff + y_diff * y_diff);
    }
    Point steer(const Point &t, ftype DELTA) {
        if (this->distance(t) < DELTA) {
            return t;
        }
        else {
            double theta = atan2(t.y - y, t.x - x);
            return Point(x + DELTA * cos(theta), y + DELTA * sin(theta));
        }
    }
    bool operator==(const Point &rhs) const
    {
        return fabs(x - rhs.x) < EPS and fabs(y - rhs.y) < EPS;
    }
};
Point operator*(ftype a, Point b) {
    return b * a;
}
ftype distance(Point &a, Point &b) {
    const ftype x_diff = a.x - b.x, y_diff = a.y - b.y;
    return sqrt(x_diff * x_diff + y_diff * y_diff);
}
ftype dot(Point a, Point b) {
    return (a.x * b.x + a.y * b.y);
}
ftype cross(Point a, Point b) {
    return (a.x * b.y - b.x * a.y);
}
Point stepNear(Point &p1, Point &p2, ftype DELTA)//возвращает точку в направлении вектора p2p1
{
    if ((distance(p1, p2) - DELTA) <= EPS)
        return p2;
    else {
        ftype theta = atan2(p2.y - p1.y, p2.x - p1.x);
        return Point(p1.x + DELTA * cos(theta), p1.y + DELTA * sin(theta));
    }
}
struct circ
{
    Point points;
    int radius;
    void addPoint(const Point pnt) {
        points.x=pnt.x;
        points.y = pnt.y;

    }
    void addRadius(const int r) {
        radius=r;
    }
    int returnRad()
    {
        return radius;
    }
    Point returnPoint()
    {
        return points;
    }
};
bool checkCollision(Point lineFrom, Point lineTo, Point location, ftype radius)
{
    location += Point(radius, radius);
    ftype ab2, acab, h2;
    Point ac = location - lineFrom;
    Point ab = lineTo - lineFrom;
    ab2 = dot(ab, ab); acab = dot(ac, ab);
    ftype t = acab / ab2;

    if (t < 0) t = 0;
    else if (t > 1) t = 1;

    Point h = ((ab * t) + lineFrom) - location;
    h2 = dot(h, h);
    return (h2 <= (radius * radius));
}
bool lineSegmentIntersectsCircle(Point lineFrom, Point lineTo, circ O) {
    O.points += Point(O.radius, O.radius);
    ftype ab2, acab, h2;
    Point ac = O.points - lineFrom;
    Point ab = lineTo - lineFrom;
    ab2 = dot(ab, ab); acab = dot(ac, ab);
    ftype t = acab / ab2;

    if (t < 0) t = 0;
    else if (t > 1) t = 1;

    Point h = ((ab * t) + lineFrom) - O.points;
    h2 = dot(h, h);
    return (h2 <= (O.radius * O.radius));
}
#endif 
