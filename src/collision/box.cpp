#include "iostream"
#include <nanogui/nanogui.h>
#include <set>

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

Box::Box(Vector3D center, float dist, double friction, double cloth_width) {
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

    Vector3D point7 = Vector3D(center.x-3*(cloth_width/8), center.y, center.z);
    Vector3D normal7 = (center - point7).unit();
    cut1 = Plane(point7, normal7, friction, true, false);
    cut1.corner1 = toVector3f(point7) + Vector3f(0, dist/2, -dist/2);
    cut1.corner2 = toVector3f(point7) + Vector3f(0, dist/2, dist/2);
    cut1.corner3 = toVector3f(point7) + Vector3f(0, -dist/2, -dist/2);
    cut1.corner4 = toVector3f(point7) + Vector3f(0, -dist/2, dist/2);

    Vector3D point8 = Vector3D(center.x-2*(cloth_width/8), center.y, center.z);
    Vector3D normal8 = (center - point8).unit();
    cut2 = Plane(point8, normal8, friction, true, false);
    cut2.corner1 = toVector3f(point8) + Vector3f(0, dist/2, -dist/2);
    cut2.corner2 = toVector3f(point8) + Vector3f(0, dist/2, dist/2);
    cut2.corner3 = toVector3f(point8) + Vector3f(0, -dist/2, -dist/2);
    cut2.corner4 = toVector3f(point8) + Vector3f(0, -dist/2, dist/2);

    Vector3D point9 = Vector3D(center.x-cloth_width/8, center.y, center.z);
    Vector3D normal9 = (center - point9).unit();
    cut3 = Plane(point9, normal9, friction, true, false);
    cut3.corner1 = toVector3f(point9) + Vector3f(0, dist/2, -dist/2);
    cut3.corner2 = toVector3f(point9) + Vector3f(0, dist/2, dist/2);
    cut3.corner3 = toVector3f(point9) + Vector3f(0, -dist/2, -dist/2);
    cut3.corner4 = toVector3f(point9) + Vector3f(0, -dist/2, dist/2);

    Vector3D point10 = Vector3D(center.x, center.y, center.z);
    Vector3D normal10 = (center - point10).unit();
    cut4 = Plane(point10, normal10, friction, true, false);
    cut4.corner1 = toVector3f(point10) + Vector3f(0, dist/2, -dist/2);
    cut4.corner2 = toVector3f(point10) + Vector3f(0, dist/2, dist/2);
    cut4.corner3 = toVector3f(point10)+ Vector3f(0, -dist/2, -dist/2);
    cut4.corner4 = toVector3f(point10) + Vector3f(0, -dist/2, dist/2);

    Vector3D point11 = Vector3D(center.x+cloth_width/8, center.y, center.z);
    Vector3D normal11 = (center - point11).unit();
    cut5 = Plane(point11, normal11, friction, true, false);
    cut5.corner1 = toVector3f(point11) + Vector3f(0, dist/2, -dist/2);
    cut5.corner2 = toVector3f(point11) + Vector3f(0, dist/2, dist/2);
    cut5.corner3 = toVector3f(point11) + Vector3f(0, -dist/2, -dist/2);
    cut5.corner4 = toVector3f(point11) + Vector3f(0, -dist/2, dist/2);

    Vector3D point12 = Vector3D(center.x+2*(cloth_width/8), center.y, center.z);
    Vector3D normal12 = (center - point12).unit();
    cut6 = Plane(point12, normal12, friction, true, false);
    cut6.corner1 = toVector3f(point12) + Vector3f(0, dist/2, -dist/2);
    cut6.corner2 = toVector3f(point12) + Vector3f(0, dist/2, dist/2);
    cut6.corner3 = toVector3f(point12) + Vector3f(0, -dist/2, -dist/2);
    cut6.corner4 = toVector3f(point12) + Vector3f(0, -dist/2, dist/2);

    Vector3D point13 = Vector3D(center.x+3*(cloth_width/8), center.y, center.z);
    Vector3D normal13 = (center - point13).unit();
    cut7 = Plane(point13, normal13, friction, true, false);
    cut7.corner1 = toVector3f(point13) + Vector3f(0, dist/2, -dist/2);
    cut7.corner2 = toVector3f(point13) + Vector3f(0, dist/2, dist/2);
    cut7.corner3 = toVector3f(point13) + Vector3f(0, -dist/2, -dist/2);
    cut7.corner4 = toVector3f(point13) + Vector3f(0, -dist/2, dist/2);

    // vector<Plane> cuts;

    // cuts.push_back(cut1);
    // cuts.push_back(cut2);
    // cuts.push_back(cut3);
    // cuts.push_back(cut4);
    // cuts.push_back(cut5);
    // cuts.push_back(cut6);
    // cuts.push_back(cut7);

    // for (int i = 0; i < cuts.size(); i++) {
    //     cout << "Slicer " <<  i << "'s Position: " << cuts[i].point.x << "\n";
    // }
}

void Box::collide(PointMass &pm, bool &isBeltMoving, bool &isHitSplitter, set<float> &slice_coords_set) {
    // plane1.collide(pm, isBeltMoving, isHitSplitter);
    // plane2.collide(pm, isBeltMoving, isHitSplitter);
    // plane3.collide(pm, isBeltMoving, isHitSplitter);
    // plane4.collide(pm, isBeltMoving, isHitSplitter);
    // plane5.collide(pm, isBeltMoving, isHitSplitter);
    // plane6.collide(pm, isBeltMoving, isHitSplitter);
    cut1.collide(pm, isBeltMoving, isHitSplitter, slice_coords_set);
    cut2.collide(pm, isBeltMoving, isHitSplitter, slice_coords_set);
    cut3.collide(pm, isBeltMoving, isHitSplitter, slice_coords_set); 
    cut4.collide(pm, isBeltMoving, isHitSplitter, slice_coords_set);
    cut5.collide(pm, isBeltMoving, isHitSplitter, slice_coords_set);
    cut6.collide(pm, isBeltMoving, isHitSplitter, slice_coords_set);
    cut7.collide(pm, isBeltMoving, isHitSplitter, slice_coords_set);
    if (plane5.collided && plane6.collided) {
        // cout << "hit";
        isHitSplitter = true;
        isBeltMoving = false;
        plane5.collided = false;
        plane6.collided = false;
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

void Box::renderSlicers(GLShader &shader, int num_slicers, double slicerHeight) {
    cut1.slicerHeight = slicerHeight;
    cut2.slicerHeight = slicerHeight;
    cut3.slicerHeight = slicerHeight;
    cut4.slicerHeight = slicerHeight;
    cut5.slicerHeight = slicerHeight;
    cut6.slicerHeight = slicerHeight;
    cut7.slicerHeight = slicerHeight;
    switch (num_slicers) {
        // 1 2 3 4 5 6 7 
        case 0:
            break;
        case 1: 
            cut4.render(shader);
            break;
        case 2:
            cut3.render(shader);
            cut5.render(shader);
            break;
        case 3: 
            cut2.render(shader);
            cut4.render(shader);
            cut6.render(shader);
            break;
        case 4:
            cut1.render(shader);
            cut3.render(shader);
            cut5.render(shader);
            cut7.render(shader);
            break;
        case 5: 
            cut2.render(shader);
            cut3.render(shader);
            cut4.render(shader);
            cut5.render(shader);
            cut6.render(shader);
            break;
        case 6:
            cut1.render(shader);
            cut2.render(shader);
            cut3.render(shader);
            cut5.render(shader);
            cut6.render(shader);
            cut7.render(shader);
            break;
        case 7: 
            cut1.render(shader);
            cut2.render(shader);
            cut3.render(shader);
            cut4.render(shader);
            cut5.render(shader);
            cut6.render(shader);
            cut7.render(shader);
            break;
    }

    // cut1.render(shader);
    // cut2.render(shader);
    // cut3.render(shader);
    // cut4.render(shader);
    // cut5.render(shader);
    // cut6.render(shader);
    // cut7.render(shader);
}

