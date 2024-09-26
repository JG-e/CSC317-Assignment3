#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Find the u, v of the top-left corner of the image plane
  double u = - camera.width/2;
  double v = camera.height/2;

  // Shift by half of a pixel to get to the center of the pixel
  u += camera.width / width * .5;
  v -= camera.height / height * .5;

  // Shift it by i and j to get to the correct pixel
  u += camera.width / width * j;
  v -= camera.height / height * i;

  // Compute the origin of the ray
  ray.origin = camera.e;
  // Compute the direction of the ray
  ray.direction = -camera.d * camera.w + u * camera.u + v * camera.v;
  ////////////////////////////////////////////////////////////////////////////
}
