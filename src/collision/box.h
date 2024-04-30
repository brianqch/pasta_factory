#ifndef COLLISIONOBJECT_BOX_H
#define COLLISIONOBJECT_BOX_H

#include <nanogui/nanogui.h>
#include <set>

#include "../clothMesh.h"
#include "collisionObject.h"
#include "plane.h"

using namespace nanogui;
using namespace CGL;
using namespace std;

struct Box : public CollisionObject {
public:
  Box(Vector3D center, float dist, double friction, double cloth_width);

  void render(GLShader &shader); //do render /w ea of 6 planes
  void collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter, set<float> &slice_coords_set); //check collide w/ ea of 6 planes
  //2 planes phantom, don't render phantom planes (front one dont care, back one - split pasta)
  void renderSlicers(GLShader &shader, int num_slicers, double slicerHeight);

  Vector3D center;
  float dist;
  double friction;
  double cloth_width;

  Plane plane1;
  Plane plane2;
  Plane plane3;
  Plane plane4;
  Plane plane5;
  Plane plane6;
  Plane cut1;
  Plane cut2;
  Plane cut3;
  Plane cut4;
  Plane cut5;
  Plane cut6;
  Plane cut7;
  bool collided;
};

#endif /* COLLISIONOBJECT_BOX_H */
