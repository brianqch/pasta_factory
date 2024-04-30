#ifndef COLLISIONOBJECT
#define COLLISIONOBJECT

#include <nanogui/nanogui.h>

#include "../clothMesh.h"

using namespace CGL;
using namespace std;
using namespace nanogui;

class CollisionObject {
public:
  virtual void render(GLShader &shader) = 0;
  virtual void collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter) = 0;
  virtual void renderSlicers(GLShader &shader, int num_slicers, double slicerHeight) = 0;
  double slicerHeight;

private:
  double friction;
};

#endif /* COLLISIONOBJECT */
