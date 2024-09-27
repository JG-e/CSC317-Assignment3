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
  if (first_hit(ray, min_t, objects, hit_id, t, n)) {
    Vector3d color = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    Vector3d hit = ray.origin + t * ray.direction;
    hit += 1e-9 * n;
    Ray mirror_ray(hit, reflect(ray.direction, n));
    Vector3d mirror_color;
    if (raycolor(mirror_ray, 1.0, objects, lights, num_recursive_calls + 1, mirror_color)) {
      rgb = color + objects[hit_id]->material->km * mirror_color;
    } else {
      rgb = color;
    }
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
