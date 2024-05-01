#include "iostream"
#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../clothSimulator.h"
#include "splitter.h"

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

void Splitter::collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter, set<float> &slice_coords_set, int num_slicers) {
  double planeX = point.x;
  double planeY = point.y;
  // Error is width / num_width_points
  float errorX = 1.0 / 32.0;
  float errorY = 1.0 / 1000.0;
  // cout << pm.position.y;
  if (planeX - errorX <= pm.position.x && pm.position.x <= planeX + errorX) {
    // cout << "Plane and Slicer Height: " << (planeY + slicerHeight) << "\n";
    if ((planeY + slicerHeight) - 0.05 <= 0 && 0 <= (planeY + slicerHeight) + 0.05 ) {
          // cout << pm.position.y << " PM POS \n";

      if ((planeY + slicerHeight - 0.6000) - errorY<= pm.position.y && pm.position.y <= (planeY + slicerHeight -0.6000) + errorY ) {
        isHitSplitter = true;
        float coord = planeX;
        // cout << "INSERTED INTO SET\n";
        slice_coords_set.insert(coord);
      }
    }
  }


  Vector3D point_to_curr = pm.position - point;
  Vector3D point_to_last = pm.last_position - point;
  double signed_dist_point_to_curr = dot(point_to_curr, normal);
  double signed_dist_point_to_last = dot(point_to_last, normal);
  // check for sign change by multiplying and see if < 0
  if (signed_dist_point_to_last * signed_dist_point_to_curr <= 0) {
    // cout << "INSIDE COLLIDE \n"; 

    Vector3D tangent_point = pm.position - normal.unit() * signed_dist_point_to_curr;
    Vector3D correction_vector;
    if (manualRender) { //in manualRender, if a collision occurs outside the face's bounding box - don't adjust w/ correction vectorwe
      float min_x =
          std::min({corner1.x(), corner2.x(), corner3.x(), corner4.x()});
      float max_x =
          std::max({corner1.x(), corner2.x(), corner3.x(), corner4.x()});
      float min_y =
          std::min({corner1.y(), corner2.y(), corner3.y(), corner4.y()}) + slicerHeight;
      float max_y =
          std::max({corner1.y(), corner2.y(), corner3.y(), corner4.y()}) + slicerHeight;
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

    cout << "HIT";
  }
}

void Splitter::render(GLShader &shader) {
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
    positions.col(0) << corner1 + Vector3f(0, slicerHeight, 0);
    positions.col(1) << corner2 + Vector3f(0, slicerHeight, 0);
    positions.col(2) << corner3 + Vector3f(0, slicerHeight, 0);
    positions.col(3) << corner4 + Vector3f(0, slicerHeight, 0);
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

void Splitter::renderSlicers(GLShader &shader, int num_slicers, double slicerHeight) {}
