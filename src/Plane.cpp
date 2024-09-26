#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
    double denominator = ray.direction.dot(normal);
  if (denominator == 0) {
    return false;
  }
  t = (point - ray.origin).dot(normal) / denominator;
  if (t < min_t) {
    return false;
  }
  n = normal;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

