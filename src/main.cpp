#include "CGL/vector3D.h"
#include <iostream>
#include <fstream>
#include <nanogui/nanogui.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include "misc/getopt.h" // getopt for windows
#else
#include <getopt.h>
#include <unistd.h>
#endif
#include <unordered_set>
#include <stdlib.h> // atoi for getopt inputs

#include "CGL/CGL.h"
#include "collision/plane.h"
#include "collision/sphere.h"
#include "collision/belt.h"
#include "collision/splitter.h"
#include "cloth.h"
#include "clothSimulator.h"
#include "json.hpp"
#include "misc/file_utils.h"
#include "collision/box.h"

typedef uint32_t gid_t;

using namespace std;
using namespace nanogui;

using json = nlohmann::json;

#define msg(s) cerr << "[ClothSim] " << s << endl;

const string SPHERE = "sphere";
const string PLANE = "plane";
const string BELT = "belt";
const string SPLITTER = "splitter";
const string CLOTH = "cloth";
const string CLOTH1 = "cloth1";
const string BOX = "box";

const unordered_set<string> VALID_KEYS = {SPHERE, PLANE, BELT, SPLITTER, CLOTH, CLOTH1, BOX};

ClothSimulator *app = nullptr;
GLFWwindow *window = nullptr;
Screen *screen = nullptr;

void error_callback(int error, const char* description) {
  puts(description);
}

void createGLContexts() {
  if (!glfwInit()) {
    return;
  }

  glfwSetTime(0);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_SAMPLES, 0);
  glfwWindowHint(GLFW_RED_BITS, 8);
  glfwWindowHint(GLFW_GREEN_BITS, 8);
  glfwWindowHint(GLFW_BLUE_BITS, 8);
  glfwWindowHint(GLFW_ALPHA_BITS, 8);
  glfwWindowHint(GLFW_STENCIL_BITS, 8);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

  // Create a GLFWwindow object
  window = glfwCreateWindow(800, 800, "Cloth Simulator", nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Could not initialize GLAD!");
  }
  glGetError(); // pull and ignore unhandled errors like GL_INVALID_ENUM

  glClearColor(0.2f, 0.25f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Create a nanogui screen and pass the glfw pointer to initialize
  screen = new Screen();
  screen->initialize(window, true);

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  glfwSwapInterval(1);
  glfwSwapBuffers(window);
}

void setGLFWCallbacks() {
  glfwSetCursorPosCallback(window, [](GLFWwindow *, double x, double y) {
    if (!screen->cursorPosCallbackEvent(x, y)) {
      app->cursorPosCallbackEvent(x / screen->pixelRatio(),
                                  y / screen->pixelRatio());
    }
  });

  glfwSetMouseButtonCallback(
      window, [](GLFWwindow *, int button, int action, int modifiers) {
        if (!screen->mouseButtonCallbackEvent(button, action, modifiers) ||
            action == GLFW_RELEASE) {
          app->mouseButtonCallbackEvent(button, action, modifiers);
        }
      });

  glfwSetKeyCallback(
      window, [](GLFWwindow *, int key, int scancode, int action, int mods) {
        if (!screen->keyCallbackEvent(key, scancode, action, mods)) {
          app->keyCallbackEvent(key, scancode, action, mods);
        }
      });

  glfwSetCharCallback(window, [](GLFWwindow *, unsigned int codepoint) {
    screen->charCallbackEvent(codepoint);
  });

  glfwSetDropCallback(window,
                      [](GLFWwindow *, int count, const char **filenames) {
                        screen->dropCallbackEvent(count, filenames);
                        app->dropCallbackEvent(count, filenames);
                      });

  glfwSetScrollCallback(window, [](GLFWwindow *, double x, double y) {
    if (!screen->scrollCallbackEvent(x, y)) {
      app->scrollCallbackEvent(x, y);
    }
  });

  glfwSetFramebufferSizeCallback(window,
                                 [](GLFWwindow *, int width, int height) {
                                   screen->resizeCallbackEvent(width, height);
                                   app->resizeCallbackEvent(width, height);
                                 });
}

void usageError(const char *binaryName) {
  printf("Usage: %s [options]\n", binaryName);
  printf("Required program options:\n");
  printf("  -f     <STRING>    Filename of scene\n");
  printf("  -r     <STRING>    Project root.\n");
  printf("                     Should contain \"shaders/Default.vert\".\n");
  printf("                     Automatically searched for by default.\n");
  printf("  -a     <INT>       Sphere vertices latitude direction.\n");
  printf("  -o     <INT>       Sphere vertices longitude direction.\n");
  printf("\n");
  exit(-1);
}

void incompleteObjectError(const char *object, const char *attribute) {
  cout << "Incomplete " << object << " definition, missing " << attribute << endl;
  exit(-1);
}

bool loadObjectsFromFile(string filename, vector<Cloth *> * cloths, ClothParameters *cp, vector<CollisionObject *>* objects, int sphere_num_lat, int sphere_num_lon) {
  // Read JSON from file
 
  ifstream i(filename);
  if (!i.good()) {
    return false;
  }
  json j;
  i >> j;

  int clothCounter = 0;
  // Loop over objects in scene
  for (json::iterator it = j.begin(); it != j.end(); ++it) {
    string key = it.key();
    cout << key;

    // Check that object is valid
    unordered_set<string>::const_iterator query = VALID_KEYS.find(key);
    if (query == VALID_KEYS.end()) {
      cout << "Invalid scene object found: " << key << endl;
      exit(-1);
    }

    // Retrieve object
    json object = it.value();

    // Parse object depending on type (cloth, sphere, or plane)
    if (key == CLOTH) {
        cout << "CLOTH NUMBER: " << clothCounter << endl;
      
      // Cloth
      // cout << "cloth";
      double width, height;
      int num_width_points, num_height_points;
      float thickness;
      e_orientation orientation;
      vector<vector<int>> pinned;
      vector<double> xOffset;
      vector<double> yOffset;
      vector<double> zOffset;

      auto it_width = object.find("width");
      if (it_width != object.end()) {
        width = *it_width;
      } else {
        incompleteObjectError("cloth", "width");
      }

      auto it_height = object.find("height");
      if (it_height != object.end()) {
        height = *it_height;
      } else {
        incompleteObjectError("cloth", "height");
      }

      auto it_num_width_points = object.find("num_width_points");
      if (it_num_width_points != object.end()) {
        num_width_points = *it_num_width_points;
      } else {
        incompleteObjectError("cloth", "num_width_points");
      }

      auto it_num_height_points = object.find("num_height_points");
      if (it_num_height_points != object.end()) {
        num_height_points = *it_num_height_points;
      } else {
        incompleteObjectError("cloth", "num_height_points");
      }

      auto it_thickness = object.find("thickness");
      if (it_thickness != object.end()) {
        thickness = *it_thickness;
      } else {
        incompleteObjectError("cloth", "thickness");
      }

      auto it_orientation = object.find("orientation");
      if (it_orientation != object.end()) {
        orientation = *it_orientation;
      } else {
        incompleteObjectError("cloth", "orientation");
      }

      auto it_pinned = object.find("pinned");
      if (it_pinned != object.end()) {
        vector<json> points = *it_pinned;
        for (auto pt : points) {
          vector<int> point = pt;
          pinned.push_back(point);
        }
      }

      auto it_xOffset = object.find("xOffset");
      if (it_xOffset != object.end()) {
          vector<double> points = *it_xOffset;
          xOffset = points;
      } else {
          xOffset.push_back(0.0);
      }

      auto it_yOffset = object.find("yOffset");
      if (it_yOffset != object.end()) {
          vector<double> points = *it_yOffset;
          yOffset = points;
      } else {
          yOffset.push_back(0.0);
      }

      auto it_zOffset = object.find("zOffset");
      if (it_zOffset != object.end()) {
          vector<double> points = *it_zOffset;
          zOffset = points;
      } else {
          zOffset.push_back(0.0);
      }

      if (xOffset.size() != yOffset.size() || yOffset.size() != zOffset.size()) {
          incompleteObjectError("cloth", "Offsets Unequal");
      }


      for (int counter = 0; counter < zOffset.size(); counter++) {
          Cloth* cloth = new Cloth();
          cloth->width = width;
          cloth->height = height;
          cloth->num_width_points = num_width_points;
          cloth->num_height_points = num_height_points;
          cloth->thickness = thickness;
          cloth->orientation = orientation;
          cloth->pinned = pinned;
          cloth->xOffset = xOffset[counter];
          cloth->yOffset = yOffset[counter];
          cloth->zOffset = zOffset[counter];
          cloths->push_back(cloth);
          clothCounter++;
      }

      // Cloth parameters
      bool enable_structural_constraints, enable_shearing_constraints, enable_bending_constraints;
      double damping, density, ks;

      auto it_enable_structural = object.find("enable_structural");
      if (it_enable_structural != object.end()) {
        enable_structural_constraints = *it_enable_structural;
      } else {
        incompleteObjectError("cloth", "enable_structural");
      }

      auto it_enable_shearing = object.find("enable_shearing");
      if (it_enable_shearing != object.end()) {
        enable_shearing_constraints = *it_enable_shearing;
      } else {
        incompleteObjectError("cloth", "it_enable_shearing");
      }

      auto it_enable_bending = object.find("enable_bending");
      if (it_enable_bending != object.end()) {
        enable_bending_constraints = *it_enable_bending;
      } else {
        incompleteObjectError("cloth", "it_enable_bending");
      }

      auto it_damping = object.find("damping");
      if (it_damping != object.end()) {
        damping = *it_damping;
      } else {
        incompleteObjectError("cloth", "damping");
      }

      auto it_density = object.find("density");
      if (it_density != object.end()) {
        density = *it_density;
      } else {
        incompleteObjectError("cloth", "density");
      }

      auto it_ks = object.find("ks");
      if (it_ks != object.end()) {
        ks = *it_ks;
      } else {
        incompleteObjectError("cloth", "ks");
      }

      cp->enable_structural_constraints = enable_structural_constraints;
      cp->enable_shearing_constraints = enable_shearing_constraints;
      cp->enable_bending_constraints = enable_bending_constraints;
      cp->density = density;
      cp->damping = damping;
      cp->ks = ks;
      
    } else if (key == SPHERE) {
      Vector3D origin;
      double radius, friction;

      auto it_origin = object.find("origin");
      if (it_origin != object.end()) {
        vector<double> vec_origin = *it_origin;
        origin = Vector3D(vec_origin[0], vec_origin[1], vec_origin[2]);
      } else {
        incompleteObjectError("sphere", "origin");
      }

      auto it_radius = object.find("radius");
      if (it_radius != object.end()) {
        radius = *it_radius;
      } else {
        incompleteObjectError("sphere", "radius");
      }

      auto it_friction = object.find("friction");
      if (it_friction != object.end()) {
        friction = *it_friction;
      } else {
        incompleteObjectError("sphere", "friction");
      }

      Sphere *s = new Sphere(origin, radius, friction, sphere_num_lat, sphere_num_lon);
      objects->push_back(s);
    } else if (key == BELT) {
      Vector3D point, normal;
      double friction;

      auto it_point = object.find("point");
      if (it_point != object.end()) {
        vector<double> vec_point = *it_point;
        point = Vector3D(vec_point[0], vec_point[1], vec_point[2]);
      } else {
        incompleteObjectError("belt", "point");
      }

      auto it_normal = object.find("normal");
      if (it_normal != object.end()) {
        vector<double> vec_normal = *it_normal;
        normal = Vector3D(vec_normal[0], vec_normal[1], vec_normal[2]);
      } else {
        incompleteObjectError("belt", "normal");
      }

      auto it_friction = object.find("friction");
      if (it_friction != object.end()) {
        friction = *it_friction;
      } else {
        incompleteObjectError("belt", "friction");
      }
      Belt *b = new Belt(point, normal, friction);
      objects->push_back(b);
    } else if (key == SPLITTER) {
        Vector3D point, normal;
      double friction;

      auto it_point = object.find("point");
      if (it_point != object.end()) {
        vector<double> vec_point = *it_point;
        point = Vector3D(vec_point[0], vec_point[1], vec_point[2]);
      } else {
        incompleteObjectError("splitter", "point");
      }

      auto it_normal = object.find("normal");
      if (it_normal != object.end()) {
        vector<double> vec_normal = *it_normal;
        normal = Vector3D(vec_normal[0], vec_normal[1], vec_normal[2]);
      } else {
        incompleteObjectError("splitter", "normal");
      }

      auto it_friction = object.find("friction");
      if (it_friction != object.end()) {
        friction = *it_friction;
      } else {
        incompleteObjectError("splitter", "friction");
      }
      Splitter *b = new Splitter(point, normal, friction);
      objects->push_back(b);
    }
    // else if (key == CLOTH1) { 
    //         // cout << "cloth1";

    //   // Cloth
    //   double width, height;
    //   int num_width_points, num_height_points;
    //   float thickness;
    //   e_orientation orientation;
    //   vector<vector<int>> pinned;

    //   auto it_width = object.find("width");
    //   if (it_width != object.end()) {
    //     width = *it_width;
    //   } else {
    //     incompleteObjectError("cloth", "width");
    //   }

    //   auto it_height = object.find("height");
    //   if (it_height != object.end()) {
    //     height = *it_height;
    //   } else {
    //     incompleteObjectError("cloth", "height");
    //   }

    //   auto it_num_width_points = object.find("num_width_points");
    //   if (it_num_width_points != object.end()) {
    //     num_width_points = *it_num_width_points;
    //   } else {
    //     incompleteObjectError("cloth", "num_width_points");
    //   }

    //   auto it_num_height_points = object.find("num_height_points");
    //   if (it_num_height_points != object.end()) {
    //     num_height_points = *it_num_height_points;
    //   } else {
    //     incompleteObjectError("cloth", "num_height_points");
    //   }

    //   auto it_thickness = object.find("thickness");
    //   if (it_thickness != object.end()) {
    //     thickness = *it_thickness;
    //   } else {
    //     incompleteObjectError("cloth", "thickness");
    //   }

    //   auto it_orientation = object.find("orientation");
    //   if (it_orientation != object.end()) {
    //     orientation = *it_orientation;
    //   } else {
    //     incompleteObjectError("cloth", "orientation");
    //   }

    //   auto it_pinned = object.find("pinned");
    //   if (it_pinned != object.end()) {
    //     vector<json> points = *it_pinned;
    //     for (auto pt : points) {
    //       vector<int> point = pt;
    //       pinned.push_back(point);
    //     }
    //   }

    //   cloth1->width = width;
    //   cloth1->height = height;
    //   cloth1->num_width_points = num_width_points;
    //   cloth1->num_height_points = num_height_points;
    //   cloth1->thickness = thickness;
    //   cloth1->orientation = orientation;
    //   cloth1->pinned = pinned;

    //   // Cloth parameters
    //   bool enable_structural_constraints, enable_shearing_constraints, enable_bending_constraints;
    //   double damping, density, ks;

    //   auto it_enable_structural = object.find("enable_structural");
    //   if (it_enable_structural != object.end()) {
    //     enable_structural_constraints = *it_enable_structural;
    //   } else {
    //     incompleteObjectError("cloth", "enable_structural");
    //   }

    //   auto it_enable_shearing = object.find("enable_shearing");
    //   if (it_enable_shearing != object.end()) {
    //     enable_shearing_constraints = *it_enable_shearing;
    //   } else {
    //     incompleteObjectError("cloth", "it_enable_shearing");
    //   }

    //   auto it_enable_bending = object.find("enable_bending");
    //   if (it_enable_bending != object.end()) {
    //     enable_bending_constraints = *it_enable_bending;
    //   } else {
    //     incompleteObjectError("cloth", "it_enable_bending");
    //   }

    //   auto it_damping = object.find("damping");
    //   if (it_damping != object.end()) {
    //     damping = *it_damping;
    //   } else {
    //     incompleteObjectError("cloth", "damping");
    //   }

    //   auto it_density = object.find("density");
    //   if (it_density != object.end()) {
    //     density = *it_density;
    //   } else {
    //     incompleteObjectError("cloth", "density");
    //   }

    //   auto it_ks = object.find("ks");
    //   if (it_ks != object.end()) {
    //     ks = *it_ks;
    //   } else {
    //     incompleteObjectError("cloth", "ks");
    //   }

    //   cp->enable_structural_constraints = enable_structural_constraints;
    //   cp->enable_shearing_constraints = enable_shearing_constraints;
    //   cp->enable_bending_constraints = enable_bending_constraints;
    //   cp->density = density;
    //   cp->damping = damping;
    //   cp->ks = ks;
    // } 
    else if (key == BOX) {
      Vector3D center;
      double dist, friction, cloth_width;

      auto it_center = object.find("center");
      if (it_center != object.end()) {
        vector<double> vec_center = *it_center;
        center = Vector3D(vec_center[0], vec_center[1], vec_center[2]);
      } else {
        incompleteObjectError("box", "center");
      } 

      auto it_dist = object.find("dist");
      if (it_dist != object.end()) {
        dist = *it_dist;
      } else {
        incompleteObjectError("box", "dist");
      }

      auto it_friction = object.find("friction");
      if (it_friction != object.end()) {
        friction = *it_friction;
      } else {
        incompleteObjectError("box", "friction");
      }

      auto it_cloth_width = object.find("cloth_width");
      if (it_cloth_width != object.end()) {
        cloth_width = *it_cloth_width;
      } else {
        incompleteObjectError("box", "cloth_width");
      }

      Box *b = new Box(center, dist, friction, cloth_width);
      objects->push_back(b);
    }
    else { // PLANE
      Vector3D point, normal;
      double friction;

      auto it_point = object.find("point");
      if (it_point != object.end()) {
        vector<double> vec_point = *it_point;
        point = Vector3D(vec_point[0], vec_point[1], vec_point[2]);
      } else {
        incompleteObjectError("plane", "point");
      }

      auto it_normal = object.find("normal");
      if (it_normal != object.end()) {
        vector<double> vec_normal = *it_normal;
        normal = Vector3D(vec_normal[0], vec_normal[1], vec_normal[2]);
      } else {
        incompleteObjectError("plane", "normal");
      }

      auto it_friction = object.find("friction");
      if (it_friction != object.end()) {
        friction = *it_friction;
      } else {
        incompleteObjectError("plane", "friction");
      }

      Plane *p = new Plane(point, normal, friction);
      objects->push_back(p);
    }
  }

  i.close();
  
  return true;
}

bool is_valid_project_root(const std::string& search_path) {
    std::stringstream ss;
    ss << search_path;
    ss << "/";
    ss << "shaders/Default.vert";
    
    return FileUtils::file_exists(ss.str());
}

// Attempt to locate the project root automatically
bool find_project_root(const std::vector<std::string>& search_paths, std::string& retval) {
  
  for (std::string search_path : search_paths) {
    if (is_valid_project_root(search_path)) {
      retval = search_path;
      return true;
    }
  }
  return false;
}

int main(int argc, char **argv) {
  // Attempt to find project root
  std::vector<std::string> search_paths = {
    ".",
    "..",
    "../..",
    "../../.."
  };
  std::string project_root;
  bool found_project_root = find_project_root(search_paths, project_root);
  
  ClothParameters cp; // note: currently cp is shared across all cloths.
  vector<CollisionObject *> objects;
  
  int c;
  
  int sphere_num_lat = 40;
  int sphere_num_lon = 40;
  
  std::string file_to_load_from;
  bool file_specified = false;
  
  while ((c = getopt (argc, argv, "f:r:a:o:")) != -1) {
    switch (c) {
      case 'f': {
        file_to_load_from = optarg;
        file_specified = true;
        break;
      }
      case 'r': {
        project_root = optarg;
        if (!is_valid_project_root(project_root)) {
          std::cout << "Warn: Could not find required file \"shaders/Default.vert\" in specified project root: " << project_root << std::endl;
        }
        found_project_root = true;
        break;
      }
      case 'a': {
        int arg_int = atoi(optarg);
        if (arg_int < 1) {
          arg_int = 1;
        }
        sphere_num_lat = arg_int;
        break;
      }
      case 'o': {
        int arg_int = atoi(optarg);
        if (arg_int < 1) {
          arg_int = 1;
        }
        sphere_num_lon = arg_int;
        break;
      }
      default: {
        usageError(argv[0]);
        break;
      }
    }
  }
  
  if (!found_project_root) {
    std::cout << "Error: Could not find required file \"shaders/Default.vert\" anywhere!" << std::endl;
    return -1;
  } else {
    std::cout << "Loading files starting from: " << project_root << std::endl;
  }

  if (!file_specified) { // No arguments, default initialization
    std::stringstream def_fname;
    def_fname << project_root;
    def_fname << "/scene/pinned2.json";
    file_to_load_from = def_fname.str();
  }

  vector<Cloth *> * cloths = new vector<Cloth*>();

  bool success = loadObjectsFromFile(file_to_load_from, cloths, &cp, &objects, sphere_num_lat, sphere_num_lon);
  if (!success) {
      std::cout << "Warn: Unable to load from file: " << file_to_load_from << std::endl;
  }


  glfwSetErrorCallback(error_callback);

  createGLContexts();
  cout << "CLOTHS: " << cloths->size() << endl;
  for (Cloth* cloth : *cloths) {
      // Initialize the Cloth object
      cloth->buildGrid();
      cloth->buildClothMesh();
      
      // vector<Cloth*> cloth_objects;
  }
  // Initialize the ClothSimulator object
  app = new ClothSimulator(project_root, screen);
  app->loadCloths(cloths);
  // copy(cloths->begin(), cloths->end(), app->default_cloth_objects->begin()); // Attempting to reset properly
  app->loadClothParameters(&cp);
  app->loadCollisionObjects(&objects);
  app->init();

  screen->setVisible(true);
  screen->performLayout();

  // Attach callbacks to the GLFW window

  setGLFWCallbacks();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    app->drawContents();

    // Draw nanogui
    screen->drawContents();
    screen->drawWidgets();

    glfwSwapBuffers(window);

    if (!app->isAlive()) {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  return 0;
}
