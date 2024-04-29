#ifndef COLLISIONOBJECT_BOX_H
#define COLLISIONOBJECT_BOX_H

#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "collisionObject.h"
#include "plane.h"

using namespace nanogui;
using namespace CGL;
using namespace std;

struct Box : public CollisionObject {
public:
  Box(Vector3D center, double dist, double friction);

  void render(GLShader &shader); //do render /w ea of 6 planes
  void collide(PointMass &pm, bool isBeltMoving, bool &isHitSplitter); //check collide w/ ea of 6 planes
  //2 planes phantom, don't render phantom planes (front one dont care, back one - split pasta)

  Vector3D center;
  double dist;
  double friction;

  Plane plane1;
  Plane plane2;
  Plane plane3;
  Plane plane4;
  Plane plane5;
  Plane plane6;
};

#endif /* COLLISIONOBJECT_BOX_H */
