cmake_minimum_required (VERSION 3.14)
project (test)
set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories( ./include ./src ./apps ./3rdParty)
 
add_executable (point_test ./tests/point_test.cpp)
add_executable (matrix_test ./tests/matrix_test.cpp)

add_executable (app ./apps/app.cpp)
target_link_libraries(app PRIVATE Threads::Threads)