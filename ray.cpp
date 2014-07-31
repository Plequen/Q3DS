#include "ray.h"

using namespace q3ds;

Ray::Ray() {
  origin.init(0.f, 0.f, 0.f);
  direction.init(0.f, 0.f, -1.f);
  processDirection();
}

Ray::Ray(qm::Vec3f& origin, qm::Vec3f& direction) {
  this->origin = origin;
  this->direction = direction;
  this->direction.normalize();
  processDirection();
}

void Ray::setDirection(qm::Vec3f& direction) {
  this->direction = direction;
  this->direction.normalize();
  processDirection();
}

void Ray::processDirection() {
  inverseDirection.init(1 / direction[0], 1 / direction[1], 1 / direction[2]);
  signs[0] = inverseDirection[0] < 0;
  signs[1] = inverseDirection[1] < 0;
  signs[2] = inverseDirection[2] < 0;
}
