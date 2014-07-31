#ifndef RAY_H
#define RAY_H

#include <vec3.h>

namespace q3ds {

class Ray {

  public:
    Ray();
    Ray(qm::Vec3f& origin, qm::Vec3f& direction);

    qm::Vec3f& getOrigin() { return origin; }
    qm::Vec3f& getDirection() { return direction; }

    void setOrigin(qm::Vec3f& origin) { this->origin = origin; }
    void setDirection(qm::Vec3f& direction);

    void processDirection();

    qm::Vec3f origin;
    qm::Vec3f direction;

    // used for quick intersection tests with bounding boxes
    qm::Vec3f inverseDirection;
    int signs[3];

};

}

#endif // RAY_H
