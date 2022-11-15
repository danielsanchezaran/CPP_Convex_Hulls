NOTE: The code follows the Google C++ Style guide

HOW TO COMPILE:
    Requirements: 
        CMake >= 3.14
        g++ >= 9.4.0
    
    Instructions to follow on the terminal (once inside thisproject's root folder):
        1) mkdir build
        2) cd build 
        3) cmake ../ 
        4) make
        5) execute the app running ./app

![Example](./convex_polygon_intersection.png)
![Example](convex_polygon_intersection.png)

About convex polygon intersection:
    The approach for computing the intersection between to convex polygons is similar to the one described in https://autowarefoundation.gitlab.io/autoware.auto/AutowareAuto/convex-polygon-intersection-2d.html. It reads:

    Intersection of two convex polygons is a convex polygon
    
    A vertex from a polygon that is contained in the other polygon is a vertex of the intersection shape. (Vertices A, C, D in the shape above)
    
    An edge from a polygon that is contained in the other polygon is an edge in the intersection shape. (edge C-D in the shape above)
    
    Edge intersections between two polygons are vertices in the intersection shape. (Vertices B, E in the shape above.)

    Inner-workings / Algorithms:
    With the observation mentioned above, the current algorithm operates in the following way:

        Compute and find the vertices from each polygon that is contained in the other polygon (Vertices A, C, D on the attached image)
        Compute and find the intersection points between each polygon (Verties B, E on the attached image)
        Compute the Polygon shaped by these vertices by ordering them CCW.
        A Polygon is tagged as "to be eliminated" if the resulting intersection polygon has an area that is greater than 50% of the Polygon area.

