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
  // Reflection Point p
  Vector3d p = ray.origin + t * ray.direction;
  Vector3d L = Vector3d::Zero();
  Ray shadow_ray;
  shadow_ray.origin = p + 1e-6 * n;
  double max_t;
  for (shared_ptr<Light> light : lights) {
    // Check if we are in shadow
    light->direction(shadow_ray.origin, shadow_ray.direction, max_t);

    int shadow_hit_id;
    double shadow_t;
    Vector3d shadow_n;

    if (first_hit(shadow_ray, 1e-6, objects, shadow_hit_id, shadow_t, shadow_n)) {
      if (shadow_t < max_t) {
        // If we are in shadow, skip this light source
        continue;
      }
    }
    // Calculate Blinn-Phong shading Halfway vector
    Vector3d v = -ray.direction.normalized();
    Vector3d l = shadow_ray.direction.normalized();
    Vector3d h = (l + v).normalized();

    Vector3d diffuse = (objects[hit_id]->material->kd.array() * (light->I).array()).matrix() * max(0.0, n.dot(shadow_ray.direction));
    Vector3d specular = (objects[hit_id]->material->ks.array() * (light->I).array()).matrix() * pow(max(0.0, n.dot(h)), objects[hit_id]->material->phong_exponent);
    L += diffuse + specular;
  }

  Vector3d ambient = 0.1 * objects[hit_id]->material->ka;
  L += ambient;
  return L;
  ////////////////////////////////////////////////////////////////////////////
}
