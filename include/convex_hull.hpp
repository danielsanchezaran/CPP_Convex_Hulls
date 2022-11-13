// This code follows the Google C++ Style guide
#include <vector>
#include <ostream>
class Point
{
public:
    double x, y;
    Point(){};
    Point(double x_, double y_) : x(x_), y(y_){};
    void operator=(const Point &P)
    {
        x = P.x;
        y = P.y;
    }

    Point operator+(const Point &P)
    {
        Point res;
        res.x = x + P.x;
        res.y = y + P.y;
        return res;
    }

    Point operator-(const Point &P)
    {
        Point res;
        res.x = x - P.x;
        res.y = y - P.y;
        return res;
    }
    friend std::ostream &operator<<(std::ostream &stream, const Point &P)
    {
        stream << "(" << P.x << ", " << P.y << ")";
        return stream;
    }
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
    explicit ConvexHull(const std::vector<Point> &vertex_);
    // Area of convex polygon https://byjus.com/maths/convex-polygon/
    void computeArea();
    double getArea();
    std::vector<Point> vertex;
    double area;
};
