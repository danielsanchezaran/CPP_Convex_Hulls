#include <convex_hull.hpp>

ConvexHull::ConvexHull(std::vector<Point> const &apex_, int id_) : apex(apex_), id(id_)
{
    assert(apex.size() >= 3);
    computeArea();
}

ConvexHull::ConvexHull() {}

void ConvexHull::computeArea()
{
    Matrix apexMatrix;
    apexMatrix = Matrix(apex[apex.size() - 1], apex[0]);
    area = apexMatrix.getDeterminant();
    for (int i = 0; i < apex.size() - 1; ++i)
    {
        Matrix temp(apex[i], apex[i + 1]);
        area += temp.getDeterminant();
    }

    area = 0.5 * area;
    if (area < 0)
        area *= -1.;
}

double ConvexHull::getArea() { return area; }

std::vector<ConvexHull> convexHullFromJson(json data)
{
    int n_hulls = data["convex hulls"].size();
    std::vector<ConvexHull> convex_hull_v;
    convex_hull_v.reserve(n_hulls);
    for (int n = 0; n < n_hulls; ++n)
    {
        int n_apexes = data["convex hulls"][n]["apexes"].size();
        std::vector<Point> apexes;
        apexes.reserve(n_apexes);
        for (int a = 0; a < n_apexes; ++a)
        {
            double x, y;
            x = data["convex hulls"][n]["apexes"][a]["x"];
            y = data["convex hulls"][n]["apexes"][a]["y"];
            Point p(x, y);
            apexes.push_back(p);
        }
        int id = data["convex hulls"][n]["ID"];
        ConvexHull c(apexes,id);
        convex_hull_v.push_back(c);
    }
    return convex_hull_v;
}
