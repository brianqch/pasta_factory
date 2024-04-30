#ifndef COLLISIONOBJECT_SPLITTER_H
#define COLLISIONOBJECT_SPLITTER_H

#include <nanogui/nanogui.h>
#include <set>

#include "../clothMesh.h"
#include "collisionObject.h"

using namespace nanogui;
using namespace CGL;
using namespace std;

struct Splitter : public CollisionObject {
public:
  Splitter(const Vector3D &point, const Vector3D &normal, double friction)
      : point(point), normal(normal.unit()), friction(friction) {}

  void render(GLShader &shader);
  void collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter, set<float> &slice_coords_set);
  void renderSlicers(GLShader &shader, int num_slicers, double slicerHeight);

  Vector3D point;
  Vector3D normal;

  Vector3f point0;
  Vector3f point1;
  Vector3f point2;
  Vector3f point3;

  double friction;
};

#endif /* COLLISIONOBJECT_SPLITTER_H */
