#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;
using namespace std;

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  Vector3d x1 = get<0>(Triangle::corners);
  Vector3d x2 = get<1>(Triangle::corners);
  Vector3d x3 = get<2>(Triangle::corners);
  Vector3d t1 = x2 - x1; 
  Vector3d t2 = x3 - x1;
  Matrix3d A; 

  A << t1, t2, -ray.direction;
  Vector3d b = ray.origin - x1;
  bool invertible = A.determinant() != 0;
  if (!invertible) {
    return false;
  }
  Vector3d x = A.inverse() * b;
  if (x[0] >= 0 && x[1] >= 0 && x[2] >= min_t && x[0] + x[1] <= 1) {
    t = x[2];
    n = t1.cross(t2).normalized();
    return true;
  }
  return false;

  ////////////////////////////////////////////////////////////////////////////
}


