// This code follows the Google C++ Style guide
#ifndef CONVEX_HULL_HPP_
#define CONVEX_HULL_HPP_

#include <vector>
#include <ostream>
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <json.hpp>
#include <cmath>

class Point
{
public:
    double x, y, angle;
    Point() : x(0), y(0), angle(0) {}
    Point(double x_, double y_) : x(x_), y(y_) { computeAngle(); }

    // get angle between this point and another
    double get_angle(Point &P)
    {
        // check to make sure the angle won't be "0"
        if (P.x == x)
        {
            return 0;
        }

        return (std::atan2((P.y - y) , (P.x - x)));
    }
    void set_angle(double d) { angle = d; }
    void computeAngle()
    {
        angle = std::atan2(y, x);
    }
    void operator=(const Point &P)
    {
        x = P.x;
        y = P.y;
        angle = P.angle;
    }

    Point operator*(const double &scalar)
    {
        Point res;
        res.x = x * scalar;
        res.y = y * scalar;
        return res;
    }

    Point operator+(const Point &P)
    {
        Point res;
        res.x = x + P.x;
        res.y = y + P.y;
        res.computeAngle();
        return res;
    }

    Point operator-(const Point &P)
    {
        Point res;
        res.x = x - P.x;
        res.y = y - P.y;
        res.computeAngle();
        return res;
    }
    // for sorting based on angles

    bool operator<(const Point &p) const
    {
        return (angle < p.angle);
    }

    friend std::ostream &operator<<(std::ostream &stream, const Point &P)
    {
        stream << "(" << P.x << ", " << P.y << ")";
        return stream;
    }
};

class Line
{
public:
    Point p1, p2;
    Line(Point p1_, Point p2_) : p1(p1_), p2(p2_){};
    Line(){};
};

class Matrix
{
public:
    double x_00, x_01, x_10, x_11;
    Matrix(){};
    Matrix(Point P1, Point P2) : x_00(P1.x), x_01(P2.x), x_10(P1.y), x_11(P2.y){};
    Matrix operator+(Matrix const &obj)
    {
        Matrix res;
        res.x_00 = x_00 + obj.x_00;
        res.x_01 = x_01 + obj.x_01;
        res.x_10 = x_10 + obj.x_10;
        res.x_11 = x_11 + obj.x_11;
        return res;
    }

    void operator=(Matrix const &obj)
    {
        x_00 = obj.x_00;
        x_01 = obj.x_01;
        x_10 = obj.x_10;
        x_11 = obj.x_11;
    }
    Matrix operator*(double const &scalar)
    {
        Matrix res;
        res.x_00 = scalar * x_00;
        res.x_01 = scalar * x_01;
        res.x_10 = scalar * x_10;
        res.x_11 = scalar * x_11;
        return res;
    }
    friend std::ostream &operator<<(std::ostream &stream, const Matrix &M)
    {
        stream << "\n[" << M.x_00 << ", " << M.x_01 << "]"
               << "\n[" << M.x_10 << ", " << M.x_11 << "]\n";
        return stream;
    }

    double getDeterminant()
    {
        return x_00 * x_11 - x_01 * x_10;
    }
};

class ConvexHull
{
public:
    std::vector<Point> apex;
    std::vector<Line> line_segments;

    double area;
    int id;
    ConvexHull();
    ConvexHull(std::vector<Point> const &apex_, int id_);
    /**
    Area of convex polygon computed following this https://byjus.com/maths/convex-polygon/
    We compute and add the area of the inner triangles of the polygon
    \return convex hull area (double)
    **/
    double getArea();
    void set_apexes(std::vector<Point> const &apex_);
    int getNvertices();
    int getNSegments();
    bool isPointInside(Point &P);

private:
    void computeArea();
    void computeLineSegments();
};

using json = nlohmann::json;

/**
  Reads a Json file with convexHull information and stores the data in a vector of ConvexHull class
  \return vector of ConvexHull
  **/
std::vector<ConvexHull> convexHullsFromJson(json data);

/**
    This Function uses the ray-casting algorithm to decide whether the point is inside
    the given polygon. See https://en.wikipedia.org/wiki/Point_in_polygon#Ray_casting_algorithm.
    For this implementation, the ray goes in the -x direction, from P(x,y) to P(-inf,y)
*/
bool pointInPolygon(std::vector<Point> const &vertices, Point &P);

bool segmentsIntersect(Line &L1, Line &L2, Point &intersect_point, double &epsilon);

bool getIntersectingPolygon(ConvexHull &C1, ConvexHull &C2, ConvexHull &Intersection);

std::vector<ConvexHull> eliminateOverlappingCHulls(std::vector<ConvexHull> &input, double overlapping_percent);

#endif //  CONVEX_HULL_HPP_