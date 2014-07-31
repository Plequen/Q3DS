#ifndef MESH_H
#define MESH_H

#include <vector>
#include <iostream>

#include <vec3.h>
#include <vec2.h>

#include "vertex.h"
#include "triangle.h"


namespace q3ds {

class Mesh {

  public:
    Mesh();

    inline std::vector<qm::Vec3f>& getPositions() { return positions; }
    inline std::vector<qm::Vec3f>& getNormals() { return normals; }
    inline std::vector<qm::Vec2f>& getUVs() { return uvs; }

    inline void addPosition(qm::Vec3f& position) { positions.push_back(position); }
    inline void addNormal(qm::Vec3f& normal) { normals.push_back(normal); }
    inline void addUV(qm::Vec2f& uv) { uvs.push_back(uv); }

    inline void addTriangle(Triangle& triangle) { triangles.push_back(triangle); }
    void addTriangle(Vertex v0, Vertex v1, Vertex v2);

    inline unsigned int positionsNumber() const { return positions.size(); }
    inline unsigned int normalsNumber() const { return normals.size(); }
    inline unsigned int uvsNumber() const { return uvs.size(); }
    inline unsigned int trianglesNumber() const { return triangles.size(); }

    void computeVertices(float* positions, float* normals, float* uvs);

    void clear();

  private:
    std::vector<qm::Vec3f> positions;
    std::vector<qm::Vec3f> normals;
    std::vector<qm::Vec2f> uvs;

    std::vector<Triangle> triangles;

};

}

#endif // MESH_H
