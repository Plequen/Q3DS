#include "octree.h"

using namespace q3ds;

template<typename T>
OctreePoint<T>::OctreePoint(qm::Vec3f& position, T& value) {
  this->position = position;
  this->value = value;
  parent = NULL;
}

template<typename T>
Octree<T>::Octree(qm::Vec3f& min, qm::Vec3f max) {
  boundingBox = new BoundingBox(min, max);
  children = NULL;
  data = NULL;
  parent = NULL;
}

template<typename T>
Octree<T>::~Octree() {
  if (children != NULL) {
    for (unsigned int i = 0 ; i < 8 ; i++)
      delete children[i];
    delete[] children;
  }
  delete data;
  delete boundingBox;
}

template<typename T>
void Octree<T>::insert(OctreePoint<T>* data) {
  if (children == NULL) { // leaf
    if (this->data != NULL) { // already used
      children = new Octree<T>*[8];
      qm::Vec3f diagonal = 0.5 * (boundingBox->getMax() - boundingBox->getMin());

      for (int i = 0 ; i < 8 ; i++) {
        qm::Vec3f min(
          i&4 ? boundingBox->getCenter()[0] : boundingBox->getMin()[0],
          i&2 ? boundingBox->getCenter()[1] : boundingBox->getMin()[1],
          i&1 ? boundingBox->getCenter()[2] : boundingBox->getMin()[2]
        );
        qm::Vec3f max = min + diagonal;
        children[i] = new Octree<T>(min, max);
        children[i]->setParent(this);
      }
      children[getContainingChildIndex(this->data->position)]->insert(this->data);
      children[getContainingChildIndex(data->position)]->insert(data);
      this->data = NULL;
    }
    else { // not used, use it
      this->data = data;
      data->parent = this;
    }
  }
  else // insert in the adequate child
    children[getContainingChildIndex(data->position)]->insert(data);
}

template<typename T>
void Octree<T>::insert(qm::Vec3f& position, T& value) {
  insert(new OctreePoint<T>(position, value));
}

template<typename T>
void Octree<T>::reverseInsert(OctreePoint<T>* data) {
  if (boundingBox->contains(data->position))
    insert(data);
  else if (parent != NULL)
    parent->reverseInsert(data);
}

template<typename T>
int Octree<T>::getContainingChildIndex(qm::Vec3f& position) {
  // x : - - - - + + + +
  // y : - - + + - - + +
  // z : - + - + - + - +
  int childIndex = 0;
  if (position[0] >= boundingBox->getCenter()[0]) childIndex += 4;
  if (position[1] >= boundingBox->getCenter()[1]) childIndex += 2;
  if (position[2] >= boundingBox->getCenter()[2]) childIndex += 1;
  return childIndex;
}

template<typename T>
void Octree<T>::retrieveRayIntersections(Ray& ray, std::vector<OctreePoint<T>*>& points, float maxDistanceFromRay) {
  if (boundingBox->intersect(ray, 0.f, 1000000000.f)) {
    if (children == NULL) {
      if (data != NULL) {
        float distanceFromRay = qm::Vec3f::crossProduct(ray.getOrigin() - data->position, ray.getDirection()).getLength();
        if (distanceFromRay <= maxDistanceFromRay) {
          points.push_back(data);
        }
      }
    }
    else {
      for (int i = 0 ; i < 8 ; i++)
        children[i]->retrieveRayIntersections(ray, points, maxDistanceFromRay);
    }
  }
}

template<typename T>
void Octree<T>::describe(std::string prefix) const {
  if (children == NULL) {
    if (data != NULL)
      std::cout << prefix << "Value " << (int) data->value << " at position " << data->position;
    else
      std::cout << prefix << "NULL" << std::endl;
  }
  else {
    std::string newPrefix = prefix + "  ";
    for (int i = 0 ; i < 8 ; i++) {
      std::cout << prefix << "Child " << i << " : " << std::endl;
      children[i]->describe(newPrefix);
    }
  }
}


template Octree<int>::~Octree();
template void Octree<int>::insert(qm::Vec3f&, int&);
template void Octree<int>::insert(OctreePoint<int>*);
template void Octree<int>::reverseInsert(OctreePoint<int>*);
template void Octree<int>::describe(std::string prefix) const;
template void Octree<int>::retrieveRayIntersections(Ray&, std::vector<OctreePoint<int>*>&, float);

template Octree<unsigned int>::~Octree();
template void Octree<unsigned int>::insert(qm::Vec3f&, unsigned int&);
template void Octree<unsigned int>::insert(OctreePoint<unsigned int>*);
template void Octree<unsigned int>::reverseInsert(OctreePoint<unsigned int>*);
template void Octree<unsigned int>::describe(std::string prefix) const;
template void Octree<unsigned int>::retrieveRayIntersections(Ray&, std::vector<OctreePoint<unsigned int>*>&, float);
