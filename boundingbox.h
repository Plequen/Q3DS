#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <vec3.h>

#include "ray.h"

namespace q3ds {

class BoundingBox {

  public:
    BoundingBox(qm::Vec3f& min, qm::Vec3f& max);

    bool intersect(Ray& ray, float t0, float t1) const;

    qm::Vec3f& getCenter() { return center; }
    qm::Vec3f& getMin() { return boundaries[0]; }
    qm::Vec3f& getMax() { return boundaries[1]; }

    bool contains(qm::Vec3f& point);

  private:
    qm::Vec3f boundaries[2];
    qm::Vec3f center;

};

}

#endif // BOUNDINGBOX_H
