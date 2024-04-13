#include <algorithm>
#include <iostream>
#include <math.h>
#include <random>
#include <vector>

#include "CGL/vector3D.h"
#include "cloth.h"
#include "clothSimulator.h"
#include "collision/collisionObject.h"
#include "collision/plane.h"
#include "collision/sphere.h"
#include "pointMass.h"
#include "spring.h"

using namespace std;

Cloth::Cloth(double width, double height, int num_width_points,
             int num_height_points, float thickness) {
  this->width = width;
  this->height = height;
  this->num_width_points = num_width_points;
  this->num_height_points = num_height_points;
  this->thickness = thickness;

  buildGrid();
  buildClothMesh();
  // split_cloth();
}

Cloth::~Cloth() {
  point_masses.clear();
  springs.clear();

  if (clothMesh) {
    delete clothMesh;
  }
}

void Cloth::buildGrid() {
  // TODO (Part 1): Build a grid of masses and springs.
  // 1) num_width_points by num_height_points masses - row major
  // top left (0,0) bottom right (width, height)
  // if (x,y) in cloth's pinned vector, set point mass's pineed to true
  // 2) if horizontal - set y to 1 while varying pos for xz
  // 3) else (ie vertical) - set z to -1/1000 and 1/1000 (use rand()) and
  // varying pos for xy
  /*
  A B C
  D E F
  G H I
  */
  // cout << "This is my width and height: " << width << "x" << height << "\n";
  // cout << "This is my num_width_points and num_height_points: " <<
  // num_width_points << "x" << num_height_points;
  if (orientation == HORIZONTAL) {
    for (int z = 0; z < num_height_points; z++) {
      for (int x = 0; x < num_width_points; x++) {
        double xPoint = width / (num_width_points - 1) * x;
        double zPoint = height / (num_height_points - 1) * z;
        Vector3D point = Vector3D(xPoint, 1.0, zPoint);
        bool isPinned = false;
        for (vector<int> v : pinned) {
          if (v[0] == x && v[1] == z) {
            isPinned = true;
            break;
          }
        }
        point_masses.push_back(PointMass(point, isPinned));
      }
    }
  } else {
    for (int y = 0; y < num_height_points; y++) {
      for (int x = 0; x < num_width_points; x++) {
        double xPoint = width / (num_width_points - 1) * x;
        double yPoint = height / (num_height_points - 1) * y;
        double randomPoint = (rand() / double(RAND_MAX)) * 0.002 - 0.001;
        Vector3D point = Vector3D(xPoint, yPoint, randomPoint);
        bool isPinned = false;
        for (vector<int> v : pinned) {
          if (v[0] == x && v[1] == y) {
            isPinned = true;
            break;
          }
        }
        point_masses.push_back(PointMass(point, isPinned));
      }
    }
  }

  // structual, shear, and bending constraints
  /*
  X X X X
  X X X X
  X X X X
  w = col
  h = row
  */
  // emplace_back()
  for (int h = 0; h < num_height_points; h++) {
    for (int w = 0; w < num_width_points; w++) {
      PointMass *pm = &point_masses[h * num_width_points + w];
      // Structural
      if (w > 0) {
        // Structural left
        springs.emplace_back(pm, pm - 1, STRUCTURAL);
      }
      if (h > 0) {
        // Structural above
        springs.emplace_back(pm, pm - num_width_points, STRUCTURAL);

        if (w > 0) {
          // Shearing top left
          springs.emplace_back(pm, pm - num_width_points - 1, SHEARING);
        }

        if (w < num_width_points - 1) {
          // Shearing top right
          springs.emplace_back(pm, pm - num_width_points + 1, SHEARING);
        }
      }
      if (w > 1) {
        // Bending left two
        springs.emplace_back(pm, pm - 2, BENDING);
      }
      if (h > 1) {
        // Bending above two
        springs.emplace_back(pm, pm - num_width_points * 2, BENDING);
      }
    }
  }
}

void Cloth::simulate(double frames_per_sec, double simulation_steps,
                     ClothParameters *cp,
                     vector<Vector3D> external_accelerations,
                     vector<CollisionObject *> *collision_objects, vector<Cloth *> cloth_obj_queue) {
  double mass =
      width * height * cp->density / num_width_points / num_height_points;
  double delta_t = 1.0f / frames_per_sec / simulation_steps;

  // TODO (Part 2): Compute total force acting on each point mass.

  // Compute total external force based on F = ma and apply this external force
  // to every point mass.
  Vector3D total_external_force = Vector3D();

  for (Vector3D &acceleration : external_accelerations) {
    total_external_force += mass * acceleration;
  }
  for (PointMass &pm : point_masses) {
    pm.forces = total_external_force;
  }

  // Compute and apply spring correction forces.
  for (Spring &spring : springs) {
    // cout << "Position A: " << spring.pm_a->position;
    // cout << "Position B: " << spring.pm_b->position << "\n";
    Vector3D pa_to_pb = spring.pm_b->position - spring.pm_a->position;
    double pa_to_pb_magnitude = pa_to_pb.norm();
    double Fs = cp->ks * (pa_to_pb_magnitude - spring.rest_length);
    Vector3D force_vector = pa_to_pb.unit() * Fs;

    if (spring.spring_type == STRUCTURAL && cp->enable_structural_constraints) {
      spring.pm_a->forces += force_vector;
      spring.pm_b->forces -= force_vector;
    } else if (spring.spring_type == SHEARING &&
               cp->enable_shearing_constraints) {
      spring.pm_a->forces += force_vector;
      spring.pm_b->forces -= force_vector;
    } else if (spring.spring_type == BENDING &&
               cp->enable_bending_constraints) {
      Fs = (0.2) * cp->ks * (pa_to_pb_magnitude - spring.rest_length);
      force_vector = pa_to_pb.unit() * Fs;
      spring.pm_a->forces += force_vector;
      spring.pm_b->forces -= force_vector;
    }
  }

  // TODO (Part 2): Use Verlet integration to compute new point mass positions

  for (PointMass &pm : point_masses) {
    if (pm.pinned)
      continue;
    Vector3D xt = pm.position;
    Vector3D xt_minus_dt = pm.last_position;
    Vector3D at = pm.forces / mass;
    Vector3D xt_plus_dt = xt + (1 - cp->damping / 100) * (xt - xt_minus_dt) +
                          at * (delta_t * delta_t);
    pm.position = xt_plus_dt;
    pm.last_position = xt;
  }

  // TODO (Part 4): Handle self-collisions.
  build_spatial_map();
  for (PointMass &pm : point_masses) {
    self_collide(pm, simulation_steps);

    // TODO (Part 3): Handle collisions with other primitives.
    for (CollisionObject *obj : *collision_objects) {
      obj->collide(pm);
    }
  }

  // TODO (Part 2): Constrain the changes to be such that the spring does not
  // change in length more than 10% per timestep [Provot 1995].

  for (Spring &spring : springs) {
    if (spring.pm_a->pinned && spring.pm_b->pinned)
      continue;
    Vector3D pa_to_pb = spring.pm_b->position - spring.pm_a->position;
    double pa_to_pb_magnitude = pa_to_pb.norm();
    double curr_length = pa_to_pb_magnitude;
    double new_length = spring.rest_length * 1.10;

    if (curr_length > new_length) {
      Vector3D correction = (pa_to_pb.unit() * (curr_length - new_length));
      if (spring.pm_a->pinned) {
        spring.pm_b->position -= correction;
      } else if (spring.pm_b->pinned) {
        spring.pm_a->position += correction;
      } else {
        spring.pm_a->position += correction * 0.5;
        spring.pm_b->position -= correction * 0.5;
      }
    }
  }
}

void Cloth::build_spatial_map() {
  for (const auto &entry : map) {
    delete (entry.second);
  }
  map.clear();

  // TODO (Part 4): Build a spatial map out of all of the point masses.

  for (PointMass &pm : point_masses) {
    Vector3D position = pm.position;
    float f = hash_position(position);

    if (!map[f]) {
      map[f] = new vector<PointMass *>();
    }
    map[f]->push_back(&pm);
  }
}

void Cloth::self_collide(PointMass &pm, double simulation_steps) {
  // TODO (Part 4): Handle self-collision for a given point mass.
  float hashedPosition = hash_position(pm.position);
  Vector3D corrVector = Vector3D();
  int num = 0;
  if (map[hashedPosition]) {
    for (PointMass *candidate : *map[hashedPosition]) {
      // Skip itself
      if (candidate == &pm)
        continue;
      Vector3D diff_vector = pm.position - candidate->position;
      if (diff_vector.norm() <= 2 * thickness) {
        Vector3D correction = diff_vector.unit() * (2 * thickness - diff_vector.norm());
        corrVector += correction;
        num += 1;
      }
    }
  }
  if (num > 0) {
    corrVector /= num;
    corrVector /= simulation_steps;
    pm.position += corrVector;
  }
}

float Cloth::hash_position(Vector3D pos) {
  // TODO (Part 4): Hash a 3D position into a unique float identifier that
  // represents membership in some 3D box volume.

  if (std::isnan(pos.x) || std::isnan(pos.y) || std::isnan(pos.z)) {
    // Handle NaN input gracefully
    return 0.0; // Or any other suitable default value
  }
  float w = 3.0 * width / num_width_points;
  float h = 3.0 * height / num_height_points;
  float t = max(w, h);

  float newX = floor(pos.x / w);
  float newY = floor(pos.y / h);
  float newZ = floor(pos.z / t);

  return newX * 97 + newY * 97 + newZ;
}

///////////////////////////////////////////////////////
/// YOU DO NOT NEED TO REFER TO ANY CODE BELOW THIS ///
///////////////////////////////////////////////////////

void Cloth::reset() {
  PointMass *pm = &point_masses[0];
  for (int i = 0; i < point_masses.size(); i++) {
    pm->position = pm->start_position;
    pm->last_position = pm->start_position;
    pm++;
  }
}

void Cloth::buildClothMesh() {
  if (point_masses.size() == 0)
    return;

  ClothMesh *clothMesh = new ClothMesh();
  vector<Triangle *> triangles;

  // Create vector of triangles
  for (int y = 0; y < num_height_points - 1; y++) {
    for (int x = 0; x < num_width_points - 1; x++) {
      PointMass *pm = &point_masses[y * num_width_points + x];
      // Get neighboring point masses:
      /*                      *
       * pm_A -------- pm_B   *
       *             /        *
       *  |         /   |     *
       *  |        /    |     *
       *  |       /     |     *
       *  |      /      |     *
       *  |     /       |     *
       *  |    /        |     *
       *      /               *
       * pm_C -------- pm_D   *
       *                      *
       */

      float u_min = x;
      u_min /= num_width_points - 1;
      float u_max = x + 1;
      u_max /= num_width_points - 1;
      float v_min = y;
      v_min /= num_height_points - 1;
      float v_max = y + 1;
      v_max /= num_height_points - 1;

      PointMass *pm_A = pm;
      PointMass *pm_B = pm + 1;
      PointMass *pm_C = pm + num_width_points;
      PointMass *pm_D = pm + num_width_points + 1;

      Vector3D uv_A = Vector3D(u_min, v_min, 0);
      Vector3D uv_B = Vector3D(u_max, v_min, 0);
      Vector3D uv_C = Vector3D(u_min, v_max, 0);
      Vector3D uv_D = Vector3D(u_max, v_max, 0);

      // Both triangles defined by vertices in counter-clockwise orientation
      triangles.push_back(new Triangle(pm_A, pm_C, pm_B, uv_A, uv_C, uv_B));
      triangles.push_back(new Triangle(pm_B, pm_C, pm_D, uv_B, uv_C, uv_D));
    }
  }

  // For each triangle in row-order, create 3 edges and 3 internal halfedges
  for (int i = 0; i < triangles.size(); i++) {
    Triangle *t = triangles[i];

    // Allocate new halfedges on heap
    Halfedge *h1 = new Halfedge();
    Halfedge *h2 = new Halfedge();
    Halfedge *h3 = new Halfedge();

    // Allocate new edges on heap
    Edge *e1 = new Edge();
    Edge *e2 = new Edge();
    Edge *e3 = new Edge();

    // Assign a halfedge pointer to the triangle
    t->halfedge = h1;

    // Assign halfedge pointers to point masses
    t->pm1->halfedge = h1;
    t->pm2->halfedge = h2;
    t->pm3->halfedge = h3;

    // Update all halfedge pointers
    h1->edge = e1;
    h1->next = h2;
    h1->pm = t->pm1;
    h1->triangle = t;

    h2->edge = e2;
    h2->next = h3;
    h2->pm = t->pm2;
    h2->triangle = t;

    h3->edge = e3;
    h3->next = h1;
    h3->pm = t->pm3;
    h3->triangle = t;
  }

  // Go back through the cloth mesh and link triangles together using halfedge
  // twin pointers

  // Convenient variables for math
  int num_height_tris = (num_height_points - 1) * 2;
  int num_width_tris = (num_width_points - 1) * 2;

  bool topLeft = true;
  for (int i = 0; i < triangles.size(); i++) {
    Triangle *t = triangles[i];

    if (topLeft) {
      // Get left triangle, if it exists
      if (i % num_width_tris != 0) { // Not a left-most triangle
        Triangle *temp = triangles[i - 1];
        t->pm1->halfedge->twin = temp->pm3->halfedge;
      } else {
        t->pm1->halfedge->twin = nullptr;
      }

      // Get triangle above, if it exists
      if (i >= num_width_tris) { // Not a top-most triangle
        Triangle *temp = triangles[i - num_width_tris + 1];
        t->pm3->halfedge->twin = temp->pm2->halfedge;
      } else {
        t->pm3->halfedge->twin = nullptr;
      }

      // Get triangle to bottom right; guaranteed to exist
      Triangle *temp = triangles[i + 1];
      t->pm2->halfedge->twin = temp->pm1->halfedge;
    } else {
      // Get right triangle, if it exists
      if (i % num_width_tris !=
          num_width_tris - 1) { // Not a right-most triangle
        Triangle *temp = triangles[i + 1];
        t->pm3->halfedge->twin = temp->pm1->halfedge;
      } else {
        t->pm3->halfedge->twin = nullptr;
      }

      // Get triangle below, if it exists
      if (i + num_width_tris - 1 < 1.0f * num_width_tris * num_height_tris /
                                       2.0f) { // Not a bottom-most triangle
        Triangle *temp = triangles[i + num_width_tris - 1];
        t->pm2->halfedge->twin = temp->pm3->halfedge;
      } else {
        t->pm2->halfedge->twin = nullptr;
      }

      // Get triangle to top left; guaranteed to exist
      Triangle *temp = triangles[i - 1];
      t->pm1->halfedge->twin = temp->pm2->halfedge;
    }

    topLeft = !topLeft;
  }

  clothMesh->triangles = triangles;
  this->clothMesh = clothMesh;
}

void Cloth::split_cloth(vector<Cloth*> cloth_obj_queue) {
    // Find the midpoint of the cloth
    int midpoint = num_width_points / 2;

    // Create a new cloth object for the second half with adjusted parameters
    Cloth* second_half = new Cloth(width, height, num_width_points - midpoint, num_height_points, thickness);
    second_half->orientation = orientation;

    // Update the point masses and springs of the current cloth
    point_masses.erase(point_masses.begin() + midpoint * num_height_points, point_masses.end());
    // point_masses.clear();
    // springs.clear();

    // Rebuild the cloth grid, point masses, and springs for the current cloth
    // buildGrid();c
    // cout << "NUMWIDTH CURR" << num_width_points;
    // Rebuild the cloth grid, point masses, and springs for the second half cloth
    // this->num_width_points = num_width_points - midpoint;
    // buildGrid();
    // second_half->buildGrid();
    // cout << "NUMWIDTH" << second_half->num_width_points;
    second_half->build_springs();

    // Update the cloth object queue with the second half cloth
    // cloth_obj_queue.push_back(second_half);/
}

void Cloth::build_springs() {
  // Clear existing springs as we need to rebuild them
  springs.clear();
  for (int h = 0; h < num_height_points; h++) {
    for (int w = 0; w < num_width_points; w++) {
      PointMass *pm = &point_masses[h * num_width_points + w];
      // Structural
      if (w > 0) {
        // Structural left
        springs.emplace_back(pm, pm - 1, STRUCTURAL);
      }
      if (h > 0) {
        // Structural above
        springs.emplace_back(pm, pm - num_width_points, STRUCTURAL);

        if (w > 0) {
          // Shearing top left
          springs.emplace_back(pm, pm - num_width_points - 1, SHEARING);
        }

        if (w < num_width_points - 1) {
          // Shearing top right
          springs.emplace_back(pm, pm - num_width_points + 1, SHEARING);
        }
      }
      if (w > 1) {
        // Bending left two
        springs.emplace_back(pm, pm - 2, BENDING);
      }
      if (h > 1) {
        // Bending above two
        springs.emplace_back(pm, pm - num_width_points * 2, BENDING);
      }
    }
  }
}

