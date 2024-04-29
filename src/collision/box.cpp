#include "iostream"
#include <nanogui/nanogui.h>

#include "../clothMesh.h"
#include "../clothSimulator.h"
#include "box.h"
#include "nanogui/common.h"
#include "plane.h"

using namespace std;
using namespace CGL;

#define SURFACE_OFFSET 0.0001

inline Vector3f toVector3f(const Vector3D &vec3d) {
    return Vector3f{static_cast<float>(vec3d.x), 
                    static_cast<float>(vec3d.y), 
                    static_cast<float>(vec3d.z)};
}

Box::Box(Vector3D center, double dist, double friction) {
    this->center = center;
    this->dist = dist;
    this->friction = friction;

    Vector3D point1 = Vector3D(center.x+dist/2, center.y, center.z);
    Vector3D normal1 = (center - point1).unit();
    plane1 = Plane(point1, normal1, friction, true);
    plane1.corner1 = toVector3f(point1) + Vector3f(0, dist/2, -dist/2);
    plane1.corner2 = toVector3f(point1) + Vector3f(0, dist/2, dist/2);
    plane1.corner3 = toVector3f(point1) + Vector3f(0, -dist/2, -dist/2);
    plane1.corner4 = toVector3f(point1) + Vector3f(0, -dist/2, dist/2);

    Vector3D point2 = Vector3D(center.x-dist/2, center.y, center.z);
    Vector3D normal2 = (center - point2).unit();
    plane2 = Plane(point2, normal2, friction, true);
    plane2.corner1 = toVector3f(point2) + Vector3f(0, dist/2, -dist/2);
    plane2.corner2 = toVector3f(point2) + Vector3f(0, dist/2, dist/2);
    plane2.corner3 = toVector3f(point2) + Vector3f(0, -dist/2, -dist/2);
    plane2.corner4 = toVector3f(point2) + Vector3f(0, -dist/2, dist/2);

    Vector3D point3 = Vector3D(center.x, center.y+dist/2, center.z);
    Vector3D normal3 = (center - point3).unit();
    plane3 = Plane(point3, normal3, friction, true);
    plane3.corner1 = toVector3f(point3) + Vector3f(-dist/2, 0, dist/2);
    plane3.corner2 = toVector3f(point3) + Vector3f(dist/2, 0, dist/2);
    plane3.corner3 = toVector3f(point3) + Vector3f(-dist/2, 0, -dist/2);
    plane3.corner4 = toVector3f(point3) + Vector3f(dist/2, 0, -dist/2);

    Vector3D point4 = Vector3D(center.x, center.y-dist/2, center.z);
    Vector3D normal4 = (center - point4).unit();
    plane4 = Plane(point4, normal4, friction, true);
    plane4.corner1 = toVector3f(point4) + Vector3f(-dist/2, 0, dist/2);
    plane4.corner2 = toVector3f(point4) + Vector3f(dist/2, 0, dist/2);
    plane4.corner3 = toVector3f(point4) + Vector3f(-dist/2, 0, -dist/2);
    plane4.corner4 = toVector3f(point4) + Vector3f(dist/2, 0, -dist/2);

    Vector3D point5 = Vector3D(center.x, center.y, center.z+dist/2);
    Vector3D normal5 = (center - point5).unit();
    plane5 = Plane(point5, normal5, friction, true, true);
    plane5.corner1 = toVector3f(point5) + Vector3f(-dist/2, dist/2, 0);
    plane5.corner2 = toVector3f(point5) + Vector3f(dist/2, dist/2, 0);
    plane5.corner3 = toVector3f(point5) + Vector3f(-dist/2, -dist/2, 0);
    plane5.corner4 = toVector3f(point5) + Vector3f(dist/2, -dist/2, 0);

    Vector3D point6 = Vector3D(center.x, center.y, center.z-dist/2);
    Vector3D normal6 = (center - point6).unit();
    plane6 = Plane(point6, normal6, friction, true, true);
    plane6.corner1 = toVector3f(point6) + Vector3f(-dist/2, dist/2, 0);
    plane6.corner2 = toVector3f(point6) + Vector3f(dist/2, dist/2, 0);
    plane6.corner3 = toVector3f(point6) + Vector3f(-dist/2, -dist/2, 0);
    plane6.corner4 = toVector3f(point6) + Vector3f(dist/2, -dist/2, 0);
}

void Box::collide(PointMass &pm, bool isBeltMoving, bool &isHitSplitter) {
    plane1.collide(pm, isBeltMoving, isHitSplitter);
    plane2.collide(pm, isBeltMoving, isHitSplitter);
    plane3.collide(pm, isBeltMoving, isHitSplitter);
    plane4.collide(pm, isBeltMoving, isHitSplitter);
    plane5.collide(pm, isBeltMoving, isHitSplitter);
    plane6.collide(pm, isBeltMoving, isHitSplitter);
    if (plane5.collided && plane6.collided) {
        isHitSplitter = true;
    }
}

void Box::render(GLShader &shader) {
    plane1.render(shader);
    plane2.render(shader);
    plane3.render(shader);
    plane4.render(shader);
    plane5.render(shader);
    plane6.render(shader);
}