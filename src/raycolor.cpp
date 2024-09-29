#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

using namespace std;
using namespace Eigen;

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  if (num_recursive_calls > 5) {
    return false;
  }
  int hit_id;
  double t;
  Vector3d n;
  bool hit = first_hit(ray, min_t, objects, hit_id, t, n);
  if (hit) {
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    Ray mirror_ray;
    mirror_ray.origin = ray.origin + t * ray.direction + 1e-6 * n;
    mirror_ray.direction = reflect(ray.direction, n);
    Vector3d mirror_color;
    if (raycolor(mirror_ray, 1e-6, objects, lights, num_recursive_calls + 1, mirror_color)) {
      rgb += (objects[hit_id]->material->km.array() * mirror_color.array()).matrix();
    }
  }
  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
