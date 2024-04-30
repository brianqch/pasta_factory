#include "iostream"
#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../clothSimulator.h"
#include "plane.h"

using namespace std;
using namespace CGL;

#define SURFACE_OFFSET 0.0001

void Plane::collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter) {
  // TODO (Part 3): Handle collisions with planes.
  Vector3D point_to_curr = pm.position - point;
  Vector3D point_to_last = pm.last_position - point;
  double signed_dist_point_to_curr = dot(point_to_curr, normal);
  double signed_dist_point_to_last = dot(point_to_last, normal);
  // check for sign change by multiplying and see if < 0
  if (signed_dist_point_to_last * signed_dist_point_to_curr <= 0) {
    Vector3D tangent_point = pm.position - normal.unit() * signed_dist_point_to_curr;
    Vector3D correction_vector;
    if (manualRender) { //in manualRender, if a collision occurs outside the face's bounding box - don't adjust w/ correction vectorwe
      float min_x =
          std::min({corner1.x(), corner2.x(), corner3.x(), corner4.x()});
      float max_x =
          std::max({corner1.x(), corner2.x(), corner3.x(), corner4.x()});
      float min_y =
          std::min({corner1.y(), corner2.y(), corner3.y(), corner4.y()});
      float max_y =
          std::max({corner1.y(), corner2.y(), corner3.y(), corner4.y()});
      float min_z =
          std::min({corner1.z(), corner2.z(), corner3.z(), corner4.z()});
      float max_z =
          std::max({corner1.z(), corner2.z(), corner3.z(), corner4.z()});
      if (!(tangent_point.x >= min_x && tangent_point.x <= max_x && tangent_point.y >= min_y &&
          tangent_point.y <= max_y && tangent_point.z >= min_z && tangent_point.z <= max_z)) {
        return;
      }
    }
    if (signed_dist_point_to_curr < 0) {
      correction_vector =
          (tangent_point - pm.last_position) + SURFACE_OFFSET * normal;
    } else {
      correction_vector =
          (tangent_point - pm.last_position) - SURFACE_OFFSET * normal;
    }
    collided = true;
    if (hidden) return;
    pm.position = pm.last_position + (1.0 - friction) * correction_vector;
  }
}

void Plane::render(GLShader &shader) {
  if (hidden) return;

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
  if (manualRender) {
    positions.col(0) << corner1;
    positions.col(1) << corner2;
    positions.col(2) << corner3;
    positions.col(3) << corner4;
  }

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
