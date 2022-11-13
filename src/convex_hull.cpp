#include <convex_hull.hpp>

ConvexHull::ConvexHull(std::vector<Point> const &vertex_, int id_) : vertex(vertex_), id(id_)
{
    assert(vertex.size() >= 3);
    computeArea();
}

ConvexHull::ConvexHull() {}

void ConvexHull::computeArea()
{
    Matrix vertMatrix;
    vertMatrix = Matrix(vertex[vertex.size() - 1], vertex[0]);
    area = vertMatrix.getDeterminant();
    for (int i = 0; i < vertex.size() - 1; ++i)
    {
        Matrix temp(vertex[i], vertex[i + 1]);
        area += temp.getDeterminant();
    }

    area = 0.5 * area;
    if (area < 0)
        area *= -1.;
}

double ConvexHull::getArea() { return area; }
