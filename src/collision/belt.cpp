#include "iostream"
#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../clothSimulator.h"
#include "belt.h"

using namespace std;
using namespace CGL;

#define SURFACE_OFFSET 0.0001

inline bool isPointWithinSquare(const Vector3D& normal, const Vector3f& point0, const Vector3f& point1,
                         const Vector3f& point2, const Vector3f& point3, const Vector3D& point) {
    // Calculate the equation of the plane using the normal vector and one point on the plane
    // Vector3D normalD =  normal.cast<double>();
    // Vector3D normalf = static_cast<float>(normal);
    
    Vector3D n = normal / normal.norm();
    Vector3D point0_3D = Vector3D(point0.x(), point0.y(), point0.z());
    Vector3D point1_3D = Vector3D(point1.x(), point1.y(), point1.z());
    Vector3D point2_3D = Vector3D(point2.x(), point2.y(), point2.z());
    Vector3D point3_3D = Vector3D(point3.x(), point3.y(), point3.z());
    // Project the given point onto the plane
    double t = -(dot(point - point0_3D,n)) / n.norm2();
    Vector3D projectedPoint = point + t * n;

    // cout << projectedPoint;

    // cout << projectedPoint << "\n" << endl;

    // Calculate vectors from the projected point to each corner of the square
    Vector3D v0 = projectedPoint - point0_3D;
    Vector3D v1 = projectedPoint - point1_3D;
    Vector3D v2 = projectedPoint - point2_3D;
    Vector3D v3 = projectedPoint - point3_3D;

    // Check if the projected point lies within the boundaries of the square
    double dot0 = dot(v0, point1_3D-point0_3D);
    double dot1 = dot(v1, point3_3D-point1_3D);
    double dot2 = dot(v3, point2_3D-point3_3D);
    double dot3 = dot(v2, point0_3D-point2_3D);

    // cout << dot0 << dot1 << dot2 << dot3 << "\n";
    //cout << point0_3D << point1_3D << point2_3D << point3_3D << "\n";

    return (dot0 >= 0 && dot1 >= 0 && dot2 >= 0 && dot3 >= 0);
}

void Belt::collide(PointMass &pm, bool isBeltMoving, bool &isHitSplitter) {
  Vector3D point0_3D = Vector3D(point0.x(), point0.y(), point0.z());
  Vector3D point1_3D = Vector3D(point1.x(), point1.y(), point1.z());
  Vector3D point2_3D = Vector3D(point2.x(), point2.y(), point2.z());
  Vector3D point3_3D = Vector3D(point3.x(), point3.y(), point3.z());
  // TODO (Part 3): Handle collisions with belts.
  Vector3D point_to_curr = pm.position - point;
  Vector3D point_to_last = pm.last_position - point;
  double signed_dist_point_to_curr = dot(point_to_curr, normal);
  double signed_dist_point_to_last = dot(point_to_last, normal);
  // check for sign change by multiplying and see if < 0
  if (signed_dist_point_to_last * signed_dist_point_to_curr <= 0) {
    if (!isPointWithinSquare(normal, point0, point1, point2, point3, pm.position)){
      return;
    }
    Vector3D tangent_point = pm.position - normal.unit() * signed_dist_point_to_curr;
    Vector3D correction_vector;
    if (signed_dist_point_to_curr < 0) {
      correction_vector = (tangent_point - pm.last_position) + SURFACE_OFFSET * normal;
    } else {
      correction_vector = (tangent_point - pm.last_position) - SURFACE_OFFSET * normal;
    }
    // point velocity TODO: add scaling factor
    if (isBeltMoving) {
      correction_vector +=  (point1_3D-point0_3D) / (point1_3D-point0_3D).norm() *0.0005;
    }
    pm.position = pm.last_position + (1.0 - friction) * correction_vector;
  }
}

void Belt::render(GLShader &shader) {
  nanogui::Color color(0.7f, 0.7f, 0.7f, 1.0f);

  Vector3f sPoint(point.x, point.y, point.z);
  Vector3f sNormal(normal.x, normal.y, normal.z);
  Vector3f sParallel(normal.y - normal.z, normal.z - normal.x,
                     normal.x - normal.y);
  sParallel.normalize();
  Vector3f sCross = sNormal.cross(sParallel);

  MatrixXf positions(3, 4);
  MatrixXf normals(3, 4);

  float lengthScale = 1.5;
  point0 = sPoint + 0.5 * (sCross + sParallel);
  point1 = sPoint + 0.5 * (sCross - sParallel);
  point2 = sPoint + 0.5 * (-sCross + sParallel);
  point3 = sPoint + 0.5 * (-sCross - sParallel);

  point0 += lengthScale * (point0 - point1);
  point1 += lengthScale * (point1 - point0);
  point2 += lengthScale * (point2 - point3);
  point3 += lengthScale * (point3 - point2);

  positions.col(0) << point0;
  positions.col(1) << point1;
  positions.col(2) << point2;
  positions.col(3) << point3;

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
