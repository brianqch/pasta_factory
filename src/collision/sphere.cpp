#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../misc/sphere_drawing.h"
#include "CGL/misc.h"
#include "sphere.h"
#include <set>

using namespace nanogui;
using namespace CGL;

void Sphere::collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter, set<float> &slice_coords_set) {
  //TODO (Part 3): Handle collisions with spheres.
  Vector3D origin_to_position = (pm.position - origin);
  Vector3D unit_origin_to_position = origin_to_position.unit();
  double distance = origin_to_position.norm();
  Vector3D origin_to_last_position = (pm.last_position - origin);
  double last_distance = origin_to_last_position.norm();

  if (pm.position.y <= origin.y) {
    // Vector3D tangent_point = origin + unit_orgin_to_position * radius;
    // Vector3D correction_vector = tangent_point - pm.last_position;
    // pm.position = pm.last_position + (1.0 - friction) * correction_vector;
    bool was_inside = last_distance < radius*0.82;

    // Check if the point mass is now outside the bowl
    bool is_outside = distance >= radius*0.82;

    // If the point mass was inside the bowl at the last time step but is now outside
    if (was_inside && is_outside) {
        //cout << "COLLISION" << endl;
        // Move the point mass back inside the bowl
        Vector3D surface_point = origin + (1.0 - EPS_D) * unit_origin_to_position * radius * 0.82;
        Vector3D correction_vector = surface_point - pm.last_position;
        //pm.position = pm.last_position + (1.0-friction) * correction_vector;
        pm.position =  pm.last_position +(1.0-friction)* correction_vector;
    }

  }
}


void Sphere::render(GLShader &shader) {
  // We decrease the radius here so flat triangles don't behave strangely
  // and intersect with the sphere when rendered
  m_sphere_mesh.draw_sphere(shader, origin, radius * 0.92);
}

void Sphere::renderSlicers(GLShader &shader, int num_slicers, double slicerHeight) {}

