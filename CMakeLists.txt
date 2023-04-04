cmake_minimum_required (VERSION 3.14)
project (test)
set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
# Find and configure Google Test
find_package(GTest REQUIRED)
include(GoogleTest)

include_directories( ./include ./src ./apps ./3rdParty)
 
add_executable (point_test ./tests/point_test.cpp ./src/convex_hull.cpp)
add_executable (line_test ./tests/line_test.cpp ./src/convex_hull.cpp)
add_executable (matrix_test ./tests/matrix_test.cpp ./src/convex_hull.cpp)
add_executable (convex_hull_test ./tests/convex_hull_test.cpp ./src/convex_hull.cpp)
add_executable (json_test ./tests/json_test.cpp ./src/convex_hull.cpp)
target_link_libraries(convex_hull_test PRIVATE GTest::GTest GTest::Main)
add_test(NAME convex_hull_test COMMAND convex_hull_test)

add_executable (app ./apps/app.cpp ./src/convex_hull.cpp)
target_link_libraries(app PRIVATE Threads::Threads)