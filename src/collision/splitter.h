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
  Splitter() : point(Vector3D()), normal(Vector3D()), friction(0.0) {}
  Splitter(const Vector3D &point, const Vector3D &normal, double friction, bool manualrender = false, bool hidden = false)
      : point(point), normal(normal.unit()), friction(friction), manualRender(manualrender), hidden(hidden), slicerHeight(0.0)  {}

  void render(GLShader &shader);
  void collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter, set<float> &slice_coords_set, int num_slicers);
  void renderSlicers(GLShader &shader, int num_slicers, double slicerHeight);

  Vector3D point;
  Vector3D normal;

  bool manualRender;
  bool hidden;
  bool collided;
  double slicerHeight;
  
  Vector3f corner1;
  Vector3f corner2;
  Vector3f corner3;
  Vector3f corner4;

  double friction;
};

#endif /* COLLISIONOBJECT_SPLITTER_H */
