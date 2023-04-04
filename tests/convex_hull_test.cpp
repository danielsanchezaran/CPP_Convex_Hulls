#include "convex_hull.hpp"

#include <gtest/gtest.h>

// Point tests
TEST(PointTest, DefaultConstructor) {
  Point P;
  EXPECT_DOUBLE_EQ(P.x, 0);
  EXPECT_DOUBLE_EQ(P.y, 0);
  EXPECT_DOUBLE_EQ(P.angle, 0);
}

TEST(PointTest, ConstructorWithParameters) {
  Point P(1, 2);
  EXPECT_DOUBLE_EQ(P.x, 1);
  EXPECT_DOUBLE_EQ(P.y, 2);
  EXPECT_DOUBLE_EQ(P.angle, std::atan2(2, 1));
}

TEST(PointTest, GetAngle) {
  Point P1(1, 0);
  Point P2(0, 1);
  EXPECT_NEAR(P1.get_angle(P2), 3 * M_PI / 4, 1e-6);
  EXPECT_NEAR(P2.get_angle(P1), -M_PI / 4, 1e-6);
}

TEST(PointTest, SetAngle) {
  Point P;
  P.set_angle(M_PI);
  EXPECT_DOUBLE_EQ(P.angle, M_PI);
}

TEST(PointTest, ComputeAngle) {
  Point P(1, 1);
  P.computeAngle();
  EXPECT_DOUBLE_EQ(P.angle, M_PI / 4);
}

TEST(PointTest, LessThanOperator) {
  Point P1(1, 2);
  Point P2(2, 1);
  EXPECT_TRUE(P2 < P1);
  EXPECT_FALSE(P1 < P2);
}

TEST(PointTest, MultiplicationOperator) {
  Point P1(1, 2);
  Point P2 = P1 * 2;
  EXPECT_DOUBLE_EQ(P2.x, 2);
  EXPECT_DOUBLE_EQ(P2.y, 4);
}

TEST(PointTest, AdditionOperator) {
  Point P1(1, 2);
  Point P2(2, 1);
  Point P3 = P1 + P2;
  EXPECT_DOUBLE_EQ(P3.x, 3);
  EXPECT_DOUBLE_EQ(P3.y, 3);
  EXPECT_DOUBLE_EQ(P3.angle, std::atan2(3, 3));
}

TEST(PointTest, SubtractionOperator) {
  Point P1(1, 2);
  Point P2(2, 1);
  Point P3 = P1 - P2;
  EXPECT_DOUBLE_EQ(P3.x, -1);
  EXPECT_DOUBLE_EQ(P3.y, 1);
  EXPECT_DOUBLE_EQ(P3.angle, std::atan2(1, -1));
}

// Matrix tests
TEST(MatrixTest, DefaultConstructor) {
  Matrix M;
  EXPECT_DOUBLE_EQ(M.x_00, 0);
  EXPECT_DOUBLE_EQ(M.x_01, 0);
  EXPECT_DOUBLE_EQ(M.x_10, 0);
  EXPECT_DOUBLE_EQ(M.x_11, 0);
}

TEST(MatrixTest, ConstructorWithParameters) {
  Point P1(1, 2);
  Point P2(2, 1);
  Matrix M(P1, P2);
  EXPECT_DOUBLE_EQ(M.x_00, 1);
  EXPECT_DOUBLE_EQ(M.x_01, 2);
  EXPECT_DOUBLE_EQ(M.x_10, 2);
  EXPECT_DOUBLE_EQ(M.x_11, 1);
}

TEST(LineIntersectionTest, Intersection) {
  Point P1(8.64869, 17.23681);
  Point P2(7.05143, 16.39631);
  Line L1(P1, P2);

  Point P3(8.2447, 18.4155);
  Point P4(8.0056, 15.5648);
  Line L2(P3, P4);

  Point intersect;
  double eps = 0.0001;
  EXPECT_TRUE(segmentsIntersect(&L2, &L1, &intersect, eps));
  EXPECT_NEAR(intersect.x, 8.122619, 1e-6);
  EXPECT_NEAR(intersect.y, 16.959984, 1e-6);
}

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