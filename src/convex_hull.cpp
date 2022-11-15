#include <convex_hull.hpp>

ConvexHull::ConvexHull(std::vector<Point> const &apex_, int id_) : apex(apex_), id(id_)
{
    assert(apex.size() >= 3);
    computeArea();
    computeLineSegments();
}

ConvexHull::ConvexHull() {}

void ConvexHull::computeArea()
{
    area = 0;
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

void ConvexHull::computeLineSegments()
{
    line_segments.reserve(apex.size());

    for (int i = 0; i < apex.size() - 1; ++i)
    {
        Line segment(apex[i], apex[i + 1]);
        line_segments.push_back(segment);
    }
    Line segment(apex[apex.size() - 1], apex[0]);
    line_segments.push_back(segment);
}

double ConvexHull::getArea()
{
    computeArea();
    return area;
}
int ConvexHull::getNvertices() { return apex.size(); }
int ConvexHull::getNSegments() { return line_segments.size(); }

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
        ConvexHull c(apexes, id);
        convex_hull_v.push_back(c);
    }
    return convex_hull_v;
}

bool ConvexHull::isPointInside(Point &P)
{
    return pointInPolygon(apex, P);
}

void ConvexHull::set_apexes(std::vector<Point> const &apex_)
{
    apex = apex_;
    assert(apex.size() >= 3);
    computeArea();
    computeLineSegments();
}

bool pointInPolygon(std::vector<Point> const &vertices, Point &P)
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

bool segmentsIntersect(Line &L1, Line &L2, Point &intersect_point, double &epsilon)
{
    float ax = L1.p2.x - L1.p1.x; // direction of line a
    float ay = L1.p2.y - L1.p1.y; // ax and ay as above

    float bx = L2.p1.x - L2.p2.x; // direction of line b, reversed
    float by = L2.p1.y - L2.p2.y; 

    float dx = L2.p1.x - L1.p1.x; // right-hand side
    float dy = L2.p1.y - L1.p1.y;

    double det = ax * by - ay * bx;

    // floating point error forces us to use a non zero, small epsilon
    if (std::abs(det) < epsilon)
    { // lines are parallel, they could be collinear, but in that case,  we dont care since the points will be inside
      //  the polygon and detected by pointInPolygon function

        return false; 
    }

    double t = (dx * by - dy * bx) / det;
    double u = (ax * dy - ay * dx) / det;
    // if both t and u between 0 and 1, the segements intersect
    bool intersect = !(t < 0 || t > 1 || u < 0 || u > 1);

    if (intersect)
    {
        // If both lines intersect, we have the point by the equation P = P1 + (P2-P1)*t
        // or P = P3 + (P4-P3) * u
        intersect_point = L1.p1 + (L1.p2 - L1.p1) * t;
    }

    return intersect;
}

bool getIntersectingPolygon(ConvexHull &C1, ConvexHull &C2, ConvexHull &Intersection)
{
    std::vector<Point> insideVertices;
    int n_vert_C1 = C1.getNvertices();
    int n_vert_C2 = C2.getNvertices();

    int n_segment_C1 = C1.getNSegments();
    int n_segment_C2 = C2.getNSegments();

    insideVertices.reserve(n_vert_C1 + n_vert_C2);

    // Check which apexes of Convexhull1 (if any) are inside convexhull2
    for (int i = 0; i < n_vert_C1; ++i)
    {
        if (C2.isPointInside(C1.apex[i]))
        {
            insideVertices.push_back(C1.apex[i]);
        }
    }
    // Check which apexes of Convexhull2 (if any) are inside convexhull1
    for (int i = 0; i < n_vert_C2; ++i)
    {
        if (C1.isPointInside(C2.apex[i]))
        {
            insideVertices.push_back(C2.apex[i]);
        }
    }

    // Check if the line segments connecting each apex of each convexhull, happen to intersect
    for (int i = 0; i < n_segment_C1; ++i)
    {

        for (int j = 0; j < n_segment_C2; ++j)
        {
            Point Intersection;
            double eps = 0.00001;

            bool segments_intersect = segmentsIntersect(C1.line_segments[i], C2.line_segments[j], Intersection, eps);
            if (segments_intersect)
            {
                insideVertices.push_back(Intersection);
            }
        }
    }

    if (insideVertices.size() < 3)
        return false; // intersect polygon requires 3 vertices to exist

    // Now we have the points that make the intersection of two convexhulls, we need to organize them CCW
    Point center = insideVertices[0]; //  We make a pivot to check angles against

    // sort all points by polar angle
    for (Point &p : insideVertices)
    {
        double angle = center.get_angle(p);
        p.set_angle(angle);
    }

    // sort the points using overloaded < operator
    // this program sorts them counterclockwise;
    std::sort(insideVertices.begin(), insideVertices.end());
    Intersection.set_apexes(insideVertices);
    return true;
}

std::vector<ConvexHull> eliminateOverlappingCHulls(std::vector<ConvexHull> &input, double overlapping_percent)
{
    // Use a vector to keep track of which C Hulls should remain
    std::vector<bool> remaining_convex_hulls(input.size(), true);
    std::vector<ConvexHull> output;
    output.reserve(input.size());
    for (int i = 0; i < input.size() - 1; ++i)
    {
        for (int j = i + 1; j < input.size(); ++j)
        {
            ConvexHull intersection;
            bool c_hulls_intersect = getIntersectingPolygon(input[i], input[j], intersection);
            if (c_hulls_intersect)
            {

                if (intersection.getArea() > overlapping_percent * input[i].getArea())
                    remaining_convex_hulls[i] = false;
                if (intersection.getArea() > overlapping_percent * input[j].getArea())
                    remaining_convex_hulls[j] = false;
            }
        }
    }

    for (int i = 0; i < remaining_convex_hulls.size(); ++i)
    {
        if (remaining_convex_hulls[i])
            output.push_back(input[i]);
    }
    return output;
}
