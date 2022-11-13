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

std::vector<ConvexHull> convexHullsFromJson(json data)
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

bool ConvexHull::isPointInside(Point &P){
    return PointInPolygon(apex,P);
}

bool PointInPolygon(std::vector<Point> const &vertices, Point& P)
{
    int n_vertices = vertices.size();
    int i, j;
    bool inside = false;
    // looping for all the edges
    for (i = 0; i < n_vertices; ++i)
    {
        int j = (i + 1) % n_vertices;

        // The vertices of the edge we are checking.
        double xp0 = vertices[i].x;
        double yp0 = vertices[i].y;
        double xp1 = vertices[j].x;
        double yp1 = vertices[j].y;

        // Check whether the edge intersects a line from (-inf,P.y) to (P.x,P.y).

        // First check if the line crosses the horizontal line at P.y in either direction.
        if ((yp0 <= P.y) && (yp1 > P.y) || (yp1 <= P.y) && (yp0 > P.y))
        {
            // If so, get the point where it crosses that line. Note that we can't get a division by zero here -
            // if yp1 == yp0 then the above condition is false.
            double cross = (xp1 - xp0) * (P.y - yp0) / (yp1 - yp0) + xp0;

            // Finally check if it crosses to the left of our test point.
            if (cross < P.x)
                inside = !inside;
        }
    }
    return inside;
}