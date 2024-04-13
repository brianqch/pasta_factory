#include "iostream"
#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../clothSimulator.h"
#include "plane.h"

using namespace std;
using namespace CGL;

#define SURFACE_OFFSET 0.0001

void Plane::collide(PointMass &pm) {
  // TODO (Part 3): Handle collisions with planes.
  Vector3D point_to_curr = pm.position - point;
  Vector3D point_to_last = pm.last_position - point;
  double signed_dist_point_to_curr = dot(point_to_curr, normal);
  double signed_dist_point_to_last = dot(point_to_last, normal);
  // check for sign change by multiplying and see if < 0
  if (signed_dist_point_to_last * signed_dist_point_to_curr <= 0) {
    Vector3D tangent_point = pm.position - normal.unit() * signed_dist_point_to_curr;
    Vector3D correction_vector;
    if (signed_dist_point_to_curr < 0) {
      correction_vector = (tangent_point - pm.last_position) + SURFACE_OFFSET * normal;
    } else {
      correction_vector = (tangent_point - pm.last_position) - SURFACE_OFFSET * normal;
    }
    pm.position = pm.last_position + (1.0 - friction) * correction_vector;
  }
}

void Plane::render(GLShader &shader) {
  nanogui::Color color(0.7f, 0.7f, 0.7f, 1.0f);

  Vector3f sPoint(point.x, point.y, point.z);
  Vector3f sNormal(normal.x, normal.y, normal.z);
  Vector3f sParallel(normal.y - normal.z, normal.z - normal.x,
                     normal.x - normal.y);
  sParallel.normalize();
  Vector3f sCross = sNormal.cross(sParallel);

  MatrixXf positions(3, 4);
  MatrixXf normals(3, 4);

  positions.col(0) << sPoint + 2 * (sCross + sParallel);
  positions.col(1) << sPoint + 2 * (sCross - sParallel);
  positions.col(2) << sPoint + 2 * (-sCross + sParallel);
  positions.col(3) << sPoint + 2 * (-sCross - sParallel);

  normals.col(0) << sNormal;
  normals.col(1) << sNormal;
  normals.col(2) << sNormal;
  normals.col(3) << sNormal;

  if (shader.uniform("u_color", false) != -1) {
    shader.setUniform("u_color", color);
  }
  shader.uploadAttrib("in_position", positions);
  if (shader.attrib("in_normal", false) != -1) {
    shader.uploadAttrib("in_normal", normals);
  }

  shader.drawArray(GL_TRIANGLE_STRIP, 0, 4);
}
