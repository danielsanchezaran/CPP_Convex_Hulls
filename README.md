About this project:
The goal of this project is to implement a Convex Hull Class without using 3rd party libraries (except for the Nlohman Json library).

This Git repository provides functionality for processing and manipulating Convex Hulls data in JSON format. The code can parse a JSON file containing Convex Hulls data and eliminate overlapping Convex Hulls based on a user-defined overlap threshold. The resulting Convex Hulls are then written to a new JSON file.

The main capabilities of the code include:

    Parsing a JSON file containing Convex Hulls data.
    Eliminating overlapping Convex Hulls based on a user-defined overlap threshold.
    Writing the resulting Convex Hulls to a new JSON file.

To use this code, a user can provide a JSON file containing Convex Hulls data as an input. Optionally, the user can also provide an overlap threshold to control the elimination of overlapping Convex Hulls. The resulting Convex Hulls will be written to a new JSON file, which can be further processed or used for visualization.

HOW TO COMPILE:
    Requirements: 
        CMake >= 3.14
        g++ >= 9.4.0
    
    Instructions to follow on the terminal (once inside this project's root folder):
        1) mkdir build
        2) cd build 
        3) cmake ../ 
        4) make

    To get the desired result (non overlapping convex hull json file):
        5) execute the app running ./app "path/to/json/file". If you run the app by just typing ./app the program will search for a file called "convex_hulls.json" on a folder one level up the hierarchy of the executable, which is equivalent to running ./app ../convex_hulls.json
        6) a file called result_convex_hulls.json will be created on your build folder with the remaining C.Hulls as specified by Directions.pdf

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

