#include <iostream>

#include "ray.h"
#include "boundingbox.h"
#include "octree.h"
#include "mesh.h"
#include "triangle.h"
#include "vertex.h"

using namespace std;
using namespace q3ds;

int main() {
  cout << "--------------- Q3DS ---------------" << endl << endl;
  //
  // Octrees
  //
  qm::Vec3f min(-5000.f, -5000.f, -5000.f);
  qm::Vec3f max(+5000.f, +5000.f, +5000.f);
  Octree<int> octree(min, max);

  cout << "------------------" << endl;
  cout << "Octrees" << endl;
  cout << "------------------" << endl;

  qm::Vec3f p1(0.f, 0.f, 0.f);
  int v1 = 1;
  qm::Vec3f p2(-10.f, -10.f, 0.f);
  int v2 = 2;
  qm::Vec3f p3(20.f, -50.f, 10.f);
  int v3 = 3;
  octree.insert(p1, v1);
  octree.insert(p2, v2);
  octree.insert(p3, v3);

  cout << "Octree : " << endl;
  octree.describe();

  qm::Vec3f p4(500.f, -50.f, 10.f);
  int v4 = 4;
  qm::Vec3f p5(3000.f, -50.f, 10.f);
  int v5 = 5;

  octree.insert(p4, v4);
  octree.insert(p5, v5);

  cout << endl << endl << "Octree : " << endl;
  octree.describe();
  cout << endl;

  //
  // Octree-Ray intersections
  //
  qm::Vec3f origin(0.f, 0.f, 0.f);
  qm::Vec3f direction(10.f, -20.f, 10.f);
  Ray ray(origin, direction);

  cout << "------------------" << endl;
  cout << "Octree-Ray intersections" << endl;
  cout << "------------------" << endl;
  vector<OctreePoint<int>*> points;
  octree.retrieveRayIntersections(ray, points, 20.f);

  cout << endl << "Intersections : " << points.size() << endl;
  for (unsigned int i = 0 ; i < points.size() ; i++)
    cout << points[i]->value << ", ";
  cout << endl;
  cout << endl;


  //
  // Meshes
  //
  cout << "------------------" << endl;
  cout << "Meshes" << endl;
  cout << "------------------" << endl;
  Mesh mesh;
  qm::Vec3f position1(-1.f, -1.f, 0.f);
  qm::Vec3f normal1(0.f, 0.f, 1.f);
  qm::Vec3f position2(1.f, -1.f, 0.f);
  qm::Vec3f position3(1.f, 1.f, 0.f);
  qm::Vec3f position4(-1.f, 1.f, 0.f);
  mesh.addPosition(position1);
  mesh.addNormal(normal1);
  mesh.addPosition(position2);
  mesh.addPosition(position3);
  mesh.addPosition(position4);
  Triangle triangle1(0, 1, 2, 0, 0, 0);
  Triangle triangle2(0, 2, 3, 0, 0, 0);
  mesh.addTriangle(triangle1);
  mesh.addTriangle(triangle2);

  float* positions = new float[mesh.trianglesNumber() * 3 * 3];
  float* normals = new float[mesh.trianglesNumber() * 3 * 3];
  float* uvs = NULL;

  cout << "Compute vertices" << endl;
  mesh.computeVertices(positions, normals, uvs);
  cout << "Positions : " << endl;
  for (unsigned int i = 0 ; i < mesh.trianglesNumber() * 3 * 3 ; i++)
    cout << positions[i] << ", ";
  cout << endl;
  cout << "Normals : " << endl;
  for (unsigned int i = 0 ; i < mesh.trianglesNumber() * 3 * 3 ; i++)
    cout << normals[i] << ", ";
  cout << endl;

  delete[] positions;
  delete[] normals;

  return 0;
}

