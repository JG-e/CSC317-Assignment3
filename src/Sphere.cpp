#include "Sphere.h"
#include "Ray.h"
using namespace std;
#include <iostream>
#include <cmath>
#include <Eigen/Core>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  double a = ray.direction.dot(ray.direction);
  double b = 2 * ray.direction.dot(ray.origin - center);
  double c = (ray.origin - center).dot(ray.origin - center) - radius * radius;

  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return false;
  }
  else {
    double t1 = (-b + sqrt(discriminant)) / (2 * a);
    double t2 = (-b - sqrt(discriminant)) / (2 * a);
    if (t1 < min_t && t2 < min_t) {
      return false;
    } else if (t1 < min_t) {
      t = t2;
    } else if (t2 < min_t) {
      t = t1;
    } else {
      t = min(t1, t2);
    }
    n = (ray.origin + t * ray.direction - center) / radius;
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
  
}

