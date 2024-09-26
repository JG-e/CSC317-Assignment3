#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

using namespace std;
using namespace Eigen;

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Reflection Point 
  Vector3d reflection_point = ray.origin + t * ray.direction;
  
  ////////////////////////////////////////////////////////////////////////////
}
