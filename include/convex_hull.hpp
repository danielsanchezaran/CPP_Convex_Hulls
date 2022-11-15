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

struct Point
{
public:
    double x, y, angle;
    Point() : x(0), y(0), angle(0) {}
    Point(double x_, double y_) : x(x_), y(y_) { computeAngle(); }

    // get angle between this point and another.
    // Will be used to organize points CCW
    double get_angle(Point &P)
    {
        // check to make sure the angle won't be "0"
        if (P.x == x)
        {
            return 0;
        }

        return (std::atan2((P.y - y), (P.x - x)));
    }
    void set_angle(double d) { angle = d; }
    void computeAngle()
    {
        angle = std::atan2(y, x);
    }

    // for sorting based on angles
    bool operator<(const Point &p) const
    {
        return (angle < p.angle);
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

    Point(const Point &other) = default;
    Point &operator=(const Point &other) = default;

    friend std::ostream &operator<<(std::ostream &stream, const Point &P)
    {
        stream << "(" << P.x << ", " << P.y << ")";
        return stream;
    }
};

struct Line
{
public:
    Point p1, p2;
    Line(Point p1_, Point p2_) : p1(p1_), p2(p2_){};
    Line(){};
    Line(const Line &other) = default;
    Line &operator=(const Line &other) = default;
};

struct Matrix
{
public:
    double x_00, x_01, x_10, x_11;
    Matrix(){};
    Matrix(Point P1, Point P2) : x_00(P1.x), x_01(P2.x), x_10(P1.y), x_11(P2.y){};

    Matrix(const Matrix &other) = default;
    Matrix &operator=(const Matrix &other) = default;

    Matrix operator+(Matrix const &obj)
    {
        Matrix res;
        res.x_00 = x_00 + obj.x_00;
        res.x_01 = x_01 + obj.x_01;
        res.x_10 = x_10 + obj.x_10;
        res.x_11 = x_11 + obj.x_11;
        return res;
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
    ConvexHull(const ConvexHull &other) = default;
    ConvexHull &operator=(const ConvexHull &other) = default;

    double getArea();

    int getNvertices();
    int getNSegments();

    /**
     * Fill an empty convex hull with its apexes.
     * @param apex_: Vector of points (C. Hull vertices ordered CCW)
     **/
    void set_apexes(std::vector<Point> const &apex_);

    /**
     * Uses the Ray casting algorithm: https://en.wikipedia.org/wiki/Point_in_polygon to
     * determine if a Point is inside this Convex Hull
     **/
    bool isPointInside(Point &P);

private:
    /**
        * Area of convex polygon computed following this approach https://byjus.com/maths/convex-polygon/
        * We compute and add the area of the inner triangles of the c. hull to get its total area.
       \return convex hull area (double)
    **/
    void computeArea();
    /**
     * Fills an internal class member: line_segments with the lines or "edges" conecting each polygon vertex
     */
    void computeLineSegments();
};

using json = nlohmann::json;

/**
  Reads a Json file with convexHull information and stores the data in a vector of ConvexHull class
  \return vector of ConvexHull
  **/
std::vector<ConvexHull> convexHullsFromJson(json data);

json convexHullsToJson(std::vector<ConvexHull> c_hull_vector);

/**
    This Function uses the ray-casting algorithm to decide whether the point is inside
    the given polygon. See https://en.wikipedia.org/wiki/Point_in_polygon#Ray_casting_algorithm.
    For this implementation, the ray goes in the -x direction, from P(x,y) to P(-inf,y)
    @param vertices: Vertices of the Polygon. vector of Points.
    @param P: The Point that is being tested.
    @return true or false
*/
bool pointInPolygon(std::vector<Point> const &vertices, Point &P);

/**
 * Check if two Line segments insertect
 *@param vertices: Vertices of the Polygon
 *@param L1: First Line Segment to test.
 *@param L2: Second Line Segment to test.
 *@param intersect_point: The intersection point data (if it exists) will be copied here.
 *@param epsilon: The tolerance used when comparing floating point substraction results to 0
 *@return true or false
 */
bool segmentsIntersect(Line &L1, Line &L2, Point &intersect_point, double &epsilon);

/**
 * Sorts a vector of Points CCW by setting one Point as "center", and checking the angle difference between said point and the rest.
 * The points are then arranged based on the pair-wise angle different between each point and the "Center".
 * @param point_vector: Vector of points to sort CCW
 */
void sortPointsCCW(std::vector<Point> &point_vector);

/**
 * If two polygons intersect, returns a non-ordered list of vertices corresponding to the polygon formed by the intersection of the
 *  two original polygons
 * @param C1: Convex Hull to check for intersection.
 * @param C2: Convex Hull to check for intersection.
 * @returns
 */
std::vector<Point> getIntersectionPolygonVertices(ConvexHull &C1, ConvexHull &C2);

/**
 * If two polygons intersect, stores the corresponding polygon created by the intersection
 * @param C1: Convex Hull to check for intersection.
 * @param C2: Convex Hull to check for intersection.
 * @param Intersection: Intersecting polygon (if it exists) data is stored here
 * @returns true or false, f the polygons intersect or not
 */
bool getIntersectingPolygon(ConvexHull &C1, ConvexHull &C2, ConvexHull &Intersection);

/**
* Compute and find the vertices from each polygon/c. hull that is contained in the other polygon
* Compute and find the intersection points between each polygon 
* Compute the Polygon shaped by these vertices by ordering them CCW.
* A Polygon is tagged as "to be eliminated" if the resulting intersection polygon has an area that is greater than the input overlapping_percent of the Polygon area.
* @param input: Vector of Convex Hulls.
* @param overlapping_percent: How much % of the overlaped area of a polygon is necessary to consider it "eliminated"
* @returns Vector of remaining polygons/C. Hulls.
*/
std::vector<ConvexHull> eliminateOverlappingCHulls(std::vector<ConvexHull> &input, double overlapping_percent);

#endif //  CONVEX_HULL_HPP_
