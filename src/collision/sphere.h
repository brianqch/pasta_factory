#ifndef COLLISIONOBJECT_SPHERE_H
#define COLLISIONOBJECT_SPHERE_H

#include "../clothMesh.h"
#include "../misc/sphere_drawing.h"
#include "collisionObject.h"
#include <set>

using namespace CGL;
using namespace std;

struct Sphere : public CollisionObject {
public:
  Sphere(const Vector3D &origin, double radius, double friction, int num_lat = 40, int num_lon = 40)
      : origin(origin), radius(radius), radius2(radius * radius),
        friction(friction), m_sphere_mesh(Misc::SphereMesh(num_lat, num_lon)) {}

  void render(GLShader &shader);
  void collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter, set<float> &slice_coords_set, int num_slicers);
  void renderSlicers(GLShader &shader, int num_slicers, double slicerHeight);

private:
  Vector3D origin;
  double radius;
  double radius2;

  double friction;
  
  Misc::SphereMesh m_sphere_mesh;
};

#endif /* COLLISIONOBJECT_SPHERE_H */
