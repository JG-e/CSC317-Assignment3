#include "DirectionalLight.h"
#include <limits>
#include <iostream>
using namespace std;
void DirectionalLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // cout << "DirectionalLight::q" << q << endl;
  d = -(DirectionalLight::d).normalized();
  max_t = std::numeric_limits<double>::infinity();
  ////////////////////////////////////////////////////////////////////////////
}

