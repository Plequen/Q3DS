#ifndef OCTREE_H
#define OCTREE_H

#include <iostream>
#include <cmath>
#include <vector>

#include <vec3.h>
#include <mat3.h>

#include "ray.h"
#include "boundingbox.h"

namespace q3ds {

template<typename T> class Octree;

/**
 * Data container stored at leaves.
 */
template<typename T> class OctreePoint {

  public:
    OctreePoint(qm::Vec3f& position, T& value);

    qm::Vec3f position;
    T value;

    Octree<T>* parent;

};

/**
 * Octree with double-linking parent-child.
 */
template<typename T> class Octree {

  public:
    Octree(qm::Vec3f& min, qm::Vec3f max);
    ~Octree();

    qm::Vec3f& getCenter() { return boundingBox->getCenter(); }
    OctreePoint<T>* getData() { return data; }
    BoundingBox* getBoundingBox() { return boundingBox; }
    Octree<T>** getChildren() { return children; }

    void setParent(Octree<T>* parent) { this->parent = parent; }
    void setData(OctreePoint<T>* data) { this->data = data; }

    void insert(OctreePoint<T>* data);
    void insert(qm::Vec3f& position, T& value);
    int getContainingChildIndex(qm::Vec3f& position);
    void reverseInsert(OctreePoint<T>* data);

    void retrieveRayIntersections(Ray& ray, std::vector<OctreePoint<T>*>& points, float maxDistanceFromRay);

    void describe(std::string prefix = std::string("")) const;

  private:
    BoundingBox* boundingBox;

    // x : - - - - + + + +
    // y : - - + + - - + +
    // z : - + - + - + - +
    Octree<T>** children;
    Octree<T>* parent;

    OctreePoint<T>* data;

};

}

#endif // OCTREE_H
