#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include "SOIL2.h"

#include "shader.h"
#include "texture.h"
#include "material.h"
#include "primitive.h"
#include "mesh.h"
#include "mymodel.h"
#include "loader.h"

#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace std;

// ENUMERATIONS
enum shader_enum { SHADER_CORE_PROGRAM = 0 };
enum texture_enum { TEX_CAT = 0, TEX_CAT_SPECULAR, TEX_WOOD, TEX_WOOD_SPECULAR };
enum material_enum { MAT_1 = 0 };
enum mesh_enum { MESH_QUAD = 0 };

const float pi_f = 3.1415926f;

class OpenGLWindow {
public:
  //Constructors & Destructors
  OpenGLWindow(const char* title,
    const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
    const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
    bool resizable
  );
  ~OpenGLWindow(void);

  // Accessors
  int getWindowShouldClose(void);

  // Functions
  void initialize(void);
  void start(void);
  void render(void);

  inline GLFWwindow* getWindow(void) { return window; }
  // Callback functions
  virtual void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) const;
  virtual void keyboard_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) const;

private:
  // window
  GLFWwindow* window;

  // Attributes
  const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	//OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;


  // MATRICES
  glm::mat4 ViewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;

  bool projectType;
	glm::mat4 ProjectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

  float top;
  float bottom;
  float left;
  float right;
  float obliqueScale;
  float obliqueAngleRad;

  string objFileName;
  string objFilePath;
  string objFullPath;

  // Shaders
  vector<Shader*> shaders;

  // Textures
  vector<Texture*> textures;

  // Materials
  vector<Material*> materials;

  // Models
  vector<Model*> models;

  // Lights
  vector<glm::vec3*> lights;


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
  void DrawGui();
  void initImGui();
  // void loadNewObject(void);

};
