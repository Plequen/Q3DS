#include "boundingbox.h"

using namespace q3ds;

BoundingBox::BoundingBox(qm::Vec3f& min, qm::Vec3f& max) {
  boundaries[0] = min;
  boundaries[1] = max;
  center = 0.5 * (boundaries[0] + boundaries[1]);
}

bool BoundingBox::intersect(Ray& ray, float t0, float t1) const {
  float txMin, txMax, tyMin, tyMax, tzMin, tzMax;

  txMin = (boundaries[ray.signs[0]][0] - ray.origin[0]) * ray.inverseDirection[0];
  txMax = (boundaries[1-ray.signs[0]][0] - ray.origin[0]) * ray.inverseDirection[0];
  tyMin = (boundaries[ray.signs[1]][1] - ray.origin[1]) * ray.inverseDirection[1];
  tyMax = (boundaries[1-ray.signs[1]][1] - ray.origin[1]) * ray.inverseDirection[1];
  if (txMin > tyMax || tyMin > txMax)
    return false;
  if (tyMin > txMin)
    txMin = tyMin;
  if (tyMax < txMax)
    txMax = tyMax;
  tzMin = (boundaries[ray.signs[2]][2] - ray.origin[2]) * ray.inverseDirection[2];
  tzMax = (boundaries[1-ray.signs[2]][2] - ray.origin[2]) * ray.inverseDirection[2];
  if (txMin > tzMax || tzMin > txMax)
    return false;
  if (tzMin > txMin)
    txMin = tzMin;
  if (tzMax < txMax)
    txMax = tzMax;

  return txMin < t1 && txMax > t0;
}

bool BoundingBox::contains(qm::Vec3f& point) {
  return boundaries[0] <= point && point <= boundaries[1];
}
