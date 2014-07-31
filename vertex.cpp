#include "vertex.h"

using namespace q3ds;

Vertex::Vertex() { }

Vertex::Vertex(qm::Vec3f& position) {
  this->position = position;
}

Vertex::Vertex(qm::Vec3f& position, qm::Vec3f& normal) {
  this->position = position;
  this->normal = normal;
}

Vertex::Vertex(qm::Vec3f& position, qm::Vec3f& normal, qm::Vec2f& uv) {
  this->position = position;
  this->normal = normal;
  this->uv = uv;
}
