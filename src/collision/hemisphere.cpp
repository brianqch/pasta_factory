#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../misc/hemisphere_drawing.h"
#include "hemisphere.h"

using namespace nanogui;
using namespace CGL;

void Hemisphere::collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter) {
  // TODO (Part 3): Handle collisions with spheres.
  Vector3D origin_to_position = (pm.position - origin);
  Vector3D unit_orgin_to_position = origin_to_position.unit();
  double distance = origin_to_position.norm();
  if (distance <= radius) {
    Vector3D tangent_point = origin + unit_orgin_to_position * radius;
    Vector3D correction_vector = tangent_point - pm.last_position;
    pm.position = pm.last_position + (1.0 - friction) * correction_vector;
  }
}

void Hemisphere::render(GLShader &shader) {
  // We decrease the radius here so flat triangles don't behave strangely
  // and intersect with the sphere when rendered
  m_sphere_mesh.draw_sphere(shader, origin, radius * 0.92);
}

void Hemisphere::renderSlicers(GLShader &shader, int num_slicers, double slicerHeight) {

}
