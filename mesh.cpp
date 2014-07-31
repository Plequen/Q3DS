#include "mesh.h"

using namespace q3ds;
using namespace std;

Mesh::Mesh() { }

void Mesh::addTriangle(Vertex v0, Vertex v1, Vertex v2) {
  unsigned int p = positions.size();
  unsigned int n = normals.size();
  unsigned int uv = uvs.size();

  positions.push_back(v0.getPosition());
  positions.push_back(v1.getPosition());
  positions.push_back(v2.getPosition());

  normals.push_back(v0.getNormal());
  normals.push_back(v1.getNormal());
  normals.push_back(v2.getNormal());

  uvs.push_back(v0.getUV());
  uvs.push_back(v1.getUV());
  uvs.push_back(v2.getUV());

  triangles.push_back(Triangle(
    p, p+1, p+2,
    n, n+1, n+2,
    uv, uv+1, uv+2
  ));
}

void Mesh::computeVertices(float* p, float* n, float* uv) {
  bool withNormals = normals.size() > 0;
  bool withUVs = uvs.size() > 0;

  unsigned int posIndex, normalIndex, uvIndex;
  int vertices = 0;
  for (vector<Triangle>::iterator it = triangles.begin() ; it != triangles.end() ; it++) {
    for (unsigned int j = 0 ; j < 3 ; j++) {
      it->getVertex(j, posIndex, normalIndex, uvIndex);
      p[3*vertices] = positions[posIndex][0];
      p[3*vertices+1] = positions[posIndex][1];
      p[3*vertices+2] = positions[posIndex][2];
      if (withNormals) {
        n[3*vertices] = normals[normalIndex][0];
        n[3*vertices+1] = normals[normalIndex][1];
        n[3*vertices+2] = normals[normalIndex][2];
      }
      if (withUVs) {
        uv[2*vertices] = uvs[uvIndex][0];
        uv[2*vertices+1] = uvs[uvIndex][1];
      }
      vertices++;
    }
  }
}

void Mesh::clear() {
  positions.clear();
  normals.clear();
  uvs.clear();
  triangles.clear();
}
