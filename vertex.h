#ifndef VERTEX_H
#define VERTEX_H

#include <vec3.h>
#include <vec2.h>


namespace q3ds {

class Vertex {

  public:
    Vertex();
    Vertex(qm::Vec3f& position);
    Vertex(qm::Vec3f& position, qm::Vec3f& normal);
    Vertex(qm::Vec3f& position, qm::Vec3f& normal, qm::Vec2f& uv);

    qm::Vec3f& getPosition() { return position; }
    qm::Vec3f& getNormal() { return normal; }
    qm::Vec2f& getUV() { return uv; }

  protected:
    qm::Vec3f position;
    qm::Vec3f normal;
    qm::Vec2f uv;

};

}

#endif // VERTEX_H
