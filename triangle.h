#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vec3.h>


namespace q3ds {

/**
 * Triangle.
 * To use with the Mesh class.
 * For each of the 3 vertices, remember the index of the position,
 * the index of the normal and the index of the UV coordinates.
 */
class Triangle {

  public:
    inline Triangle() { }

    inline Triangle(unsigned int p0, unsigned int p1, unsigned int p2) {
      initPositions(p0, p1, p2);
    }

    inline Triangle(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int n0, unsigned int n1, unsigned int n2) {
      initPositions(p0, p1, p2);
      initNormals(n0, n1, n2);
    }

    inline Triangle(unsigned int p0, unsigned int p1, unsigned int p2, unsigned int n0, unsigned int n1, unsigned int n2, unsigned int uv0, unsigned int uv1, unsigned int uv2) {
      initPositions(p0, p1, p2);
      initNormals(n0, n1, n2);
      initUVs(uv0, uv1, uv2);
    }

    inline void initPositions(unsigned int p0, unsigned int p1, unsigned int p2) {
      positions[0] = p0;
      positions[1] = p1;
      positions[2] = p2;
    }

    inline void initNormals(unsigned int n0, unsigned int n1, unsigned int n2) {
      normals[0] = n0;
      normals[1] = n1;
      normals[2] = n2;
    }

    inline void initUVs(unsigned int uv0, unsigned int uv1, unsigned int uv2) {
      uvs[0] = uv0;
      uvs[1] = uv1;
      uvs[2] = uv2;
    }

    inline void setVertex(unsigned int vertex, unsigned int positionIndex, unsigned int normalIndex, unsigned int uvIndex) {
      positions[vertex] = positionIndex;
      normals[vertex] = normalIndex;
      uvs[vertex] = uvIndex;
    }

    inline void getVertex(unsigned int vertex, unsigned int& position, unsigned int& normal, unsigned int& uv) {
      position = positions[vertex];
      normal = normals[vertex];
      uv = uvs[vertex];
    }

  private:
    // indexes
    unsigned int positions[3];
    unsigned int normals[3];
    unsigned int uvs[3];

    //qm::Vec3f normal;

};

}

#endif // TRIANGLE_H
