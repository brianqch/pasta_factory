#ifndef COLLISIONOBJECT_HEMISPHERE_H
#define COLLISIONOBJECT_HEMISPHERE_H

#include "../clothMesh.h"
#include "../misc/hemisphere_drawing.h"
#include "collisionObject.h"

using namespace CGL;
using namespace std;

struct Hemisphere : public CollisionObject {
public:
  Hemisphere(const Vector3D &origin, double radius, double friction, int num_lat = 40, int num_lon = 40)
      : origin(origin), radius(radius), radius2(radius * radius),
        friction(friction), m_sphere_mesh(Misc::HemisphereMesh(num_lat, num_lon)) {}

  void render(GLShader &shader);
  void collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter, set<float> &slice_coords_set);
  void renderSlicers(GLShader &shader, int num_slicers, double slicerHeight);

private:
  Vector3D origin;
  double radius;
  double radius2;

  double friction;
  
  Misc::HemisphereMesh m_sphere_mesh;
};

#endif /* COLLISIONOBJECT_SPHERE_H */
