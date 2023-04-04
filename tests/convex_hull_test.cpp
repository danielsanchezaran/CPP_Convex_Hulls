#include "convex_hull.hpp"

#include <gtest/gtest.h>

// Fixture for testing ConvexHull
class ConvexHullTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create some test points
    Point p1(0, 0);
    Point p2(0, 1);
    Point p3(1, 0);
    Point p4(1, 1);
    Point p5(-1, 0);

    // Create a vector of points for a convex hull
    std::vector<Point> points1 = {p1, p2, p3};
    std::vector<Point> points2 = {p5, p2, p4, p3};

    // Create the convex hulls
    ch1 = ConvexHull(points1, 1);
    ch2 = ConvexHull(points2, 2);
  }

  // Members for testing
  ConvexHull ch1;
  ConvexHull ch2;
};

// Test that the area of a convex hull is calculated correctly
TEST_F(ConvexHullTest, AreaTest) {
  // Check that the areas are calculated correctly
  EXPECT_NEAR(ch1.getArea(), 0.5, 1e-6);
  EXPECT_NEAR(ch2.getArea(), 1.5, 1e-6);
}

// Test that the number of vertices and segments are correct
TEST_F(ConvexHullTest, VertexAndSegmentTest) {
  EXPECT_EQ(ch1.getNvertices(), 3);
  EXPECT_EQ(ch1.getNSegments(), 3);
  EXPECT_EQ(ch2.getNvertices(), 4);
  EXPECT_EQ(ch2.getNSegments(), 4);
}

// Test that a point inside the convex hull is detected correctly
TEST_F(ConvexHullTest, PointInConvexHullTest) {
  // Check that a point inside the hull is detected correctly
  Point insidePoint(0.85, 0.25);
  EXPECT_TRUE(ch2.isPointInside(insidePoint));

  // Check that a point outside the hull is detected correctly
  Point outsidePoint(1.5, 0.5);
  EXPECT_FALSE(ch2.isPointInside(outsidePoint));
}