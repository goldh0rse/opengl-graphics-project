#ifndef OPENGLWINDOW_H_
#define OPENGLWINDOW_H_

#include <string>
#include <vector>

// Graphics
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "SOIL2.h"

// GUI
#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Local classes
#include "shader.h"
#include "texture.h"
#include "material.h"
#include "primitive.h"
#include "mesh.h"
#include "mymodel.h"
#include "loader.h"
#include "camera.h"
#include "light.h"


using namespace std;

// ENUMERATIONS
// enum direction_enum { FORWARD = 0, BACKWARD, LEFT, RIGHT, UP, DOWN };
enum shader_enum    { SHADER_CORE_PROGRAM = 0 };
enum texture_enum   { TEX_CAT = 0, TEX_CAT_SPECULAR, TEX_WOOD, TEX_WOOD_SPECULAR };
enum material_enum  { MAT_1 = 0 };
enum mesh_enum      { MESH_QUAD = 0 };

// const float pi_f = 3.1415926f;

class OpenGLWindow {
public:
  //Constructors & Destructors
  OpenGLWindow(const char* title,
    const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
    const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
    bool resizable
  );
  ~OpenGLWindow(void);

  // Functions
  void initialize(void);
  void start(void);
  void render(void);

  inline GLFWwindow* getWindow(void) { return window; }
  // Callback functions
  virtual void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) const;
  virtual void keyboard_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  virtual void cursor_callback(GLFWwindow* window, double xpos, double ypos);

private:
	// window
  GLFWwindow* window;

  // window attributes
  const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

  //OpenGL Context
	const int GL_VERSION_MAJOR;
  const int GL_VERSION_MINOR;


  Camera camera;

  // GUI

  // Lights
  float lightPos[3] = {0.0f, 0.0f, 0.0f};
  float lightColor[3] = {1.0f, 1.0f, 1.0f};
  float ambientColor[3] = {0.2f, 0.2f, 0.2f};

  float materialAmbient[3] = {.5f, .5f, .5f};
  float materialDiffuse[3] = {.5f, .5f, .5f};
  float materialSpecular[3] = {.5f, .5f, .5f};
  float materialShininess = 1.0f;

  // Projection
	glm::mat4 ProjectionMatrix;
  bool projectType;
	float fov;
	float nearPlane;
	float farPlane;
  float top;
  float bottom;
  float left;
  float right;
  float obliqueScale;
  float obliqueAngleRad;

  // Cursors stuff
  double cursorScreenX;
  double cursorScreenY;
  double offsetX;
  double offsetY;
  bool showGui;

  // Object file-stuff
  string objFileName;
  string objFilePath;
  string objFullPath;

  // Texture File Stuff
  bool textureShow = false;


  // Shaders
  vector<Shader*> shaders;

  // Textures
  vector<Texture*> textures;

  // Materials
  vector<Material*> materials;

  // Models
  vector<Model*> models;

  // Lights
  vector<Light*> lights;

  // Private functions
  void initGLFW(void);
  void initWindow(const char* title, bool resizable);
  void initGLEW(void);
  void initOpenGLOptions(void);
  void initMatrices(void);
  void initShaders(void);
  void initTextures(void);
  void initMaterials(void);
  void initModels(string fileName);
  void initLights(void);
  void initUniforms(void);

  void updateUniforms(void);
  void updateLights(void);
  void updateMaterials(void);
  
  void DrawGui(void);
  void initImGui(void);
};

#endif
