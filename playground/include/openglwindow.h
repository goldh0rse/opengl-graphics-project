/* openglwindow.h - Header file for the OpenGLWindow class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#ifndef OPENGLWINDOW_H_
#define OPENGLWINDOW_H_

#include <string>
#include <vector>

// Graphics
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <limits>
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
enum shader_enum    { PHONG_SHADER = 0, GOURAUD_SHADER, SKYBOX_SHADER , GROUND_PLANE_SHADER };
enum texture_enum   { TEX_CAT = 0, TEX_WOOD, TEX_LOADABLE };
enum material_enum  { MAT_1 = 0 };
enum mesh_enum      { MESH_QUAD = 0 };

// The skybox coordinate absolute values
const float skybox_size = 10000.f;


class OpenGLWindow {
public:
  /* CONSTRUCTORS & DECONSTRUCTORS */
  /**
   * OpenGLWindow [The main class that holds everything together]
   * @param title             [The title of the "program"]
   * @param WINDOW_WIDTH      [The width of the window]
   * @param WINDOW_HEIGHT     [The height of the window]
   * @param GL_VERSION_MAJOR  [The major version of OpenGL used]
   * @param GL_VERSION_MINOR  [The minor version of OpenGL used]
   * @param resizable         [A boolean defining if the window should be
   *                           resizable or not]
   */
  OpenGLWindow(const char* title,
    const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
    const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
    bool resizable
  );

  /**
   * OpenGLWindow  [The class deconstructor]
   */
  ~OpenGLWindow(void);

  /* METHODS */
  /**
   * initialize [The main initializer, calls the other initializers]
   */
  void initialize(void);

  /**
   * start [Starts the rendering loop of the program]
   */
  void start(void);

  /**
   * render [The main render function]
   */
  void render(void);

  /**
   * getWindow [A getter for the window attribute]
   * @return GLFWwindow* [The window attriute]
   */
  inline GLFWwindow* getWindow(void) { return window; }

  /* CALLBACK FUNCTIONS */
  /**
   * framebuffer_resize_callback [The window resize callback function]
   * @param window  [The window to resize]
   * @param fbW     [The framebuffer width]
   * @param fbH     [the framebuffer height]
   */
  virtual void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) const;

  /**
   * keyboard_input_callback [The keyboard input callback function,
   *                          defines the behaviour of pressing different
   *                          keys of the keyboard]
   * @param window    [the window that generated the callback]
   * @param key       [the key identifier that was pressed]
   * @param scancode  [the system-specific scancode of the key]
   * @param action    [the type of press action, Press / Release / Repeat]
   * @param mods      [a bit field describing which modifier keys were held down]
   */
  virtual void keyboard_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  /**
   * cursor_callback [callback method that defines the behaviour when moving
   *                  the cursor over the window]
   * @param window  [the window that generated the callback]
   * @param xpos    [the window x-coordinate of the cursor]
   * @param ypos    [the window y-coordinate of the cursor]
   */
  virtual void cursor_callback(GLFWwindow* window, double xpos, double ypos);

private:
  /**
   * initGLFW [initialises GLFW]
   */
  void initGLFW(void);

  /**
   * initWindow [initialises the glfw window]
   * @param title      [The title of the window]
   * @param resizable  [A boolean for allowing to resize the window or not]
   */
  void initWindow(const char* title, bool resizable);

  /**
   * initGLEW [initialises GLEW]
   */
  void initGLEW(void);

  /**
   * initOpenGLOptions [sets the OpenGL init options for the program]
   */
  void initOpenGLOptions(void);

  /**
   * initMatrices [initialises the projection matrix]
   */
  void initMatrices(void);

  /**
   * initShaders [initialises the shaders of the program]
   */
  void initShaders(void);

  /**
   * initTextures [initialises the textures]
   */
  void initTextures(void);

  /**
   * initMaterials [initialises the materials]
   */
  void initMaterials(void);

  /**
   * initModels [Initialises the startup model]
   * @param fileName  [The path to the wavefile containing the model]
   */
  void initModels(string fileName);

  /**
   * initLights [initialises the light source]
   */
  void initLights(void);

  /**
   * initSkyBox [initialises the skybox]
   */
  void initSkyBox(void);

  /**
   * initGroundPlane [initialises the ground plane]
   * @note currently not working
   */
  void initGroundPlane(void);

  /**
   * initUniforms [initialises the uniforms that are sent to the shaders]
   */
  void initUniforms(void);

  /**
   * updateUniforms [Updates the shader uniforms]
   */
  void updateUniforms(void);

  /**
   * updateLights [updates the lights with values from the GUI]
   */
  void updateLights(void);

  /**
   * updateMaterials [updates the materials with the values from the GUI]
   */
  void updateMaterials(void);

  /**
   * updateTextures [Updates the textures with the values from the GUI]
   */
  void updateTextures(void);

  /**
   * updateModel [Updates the model with the wavefile that is
   *              supplied by the GUI]
   * @param fileName  [the path to the wavefile to be loaded]
   */
  void updateModel(string fileName);

  /**
   * DrawGui [Renders the GUI and the functionalities]
   */
  void DrawGui(void);

  /**
   * initImGui [Initialises the GUI]
   */
  void initImGui(void);

  /* ATTRIBUTES */
	// window attributes
  GLFWwindow* window;      // The GLFWwindow
  const int WINDOW_WIDTH;  // The initial window width
	const int WINDOW_HEIGHT; // The initial window height
	int framebufferWidth;    // The current window width
	int framebufferHeight;   // The current window height

  //OpenGL Context
	const int GL_VERSION_MAJOR; // The major version of OpenGl (4)
  const int GL_VERSION_MINOR; // The minor version of OpenGL (.3)

  // Camera
  Camera camera;  // The Camera object

  // Lights
  float lightPos[3] = {0.f, 0.f, 0.f};     // The initial light position
  float lightColor[3] = {1.f, 1.f, 1.f};   // The initial light color
  float ambientColor[3] = {.2f, .2f, .2f}; // The initial light ambient color

  float materialAmbient[3] = {.5f, .5f, .5f};   // The material ambient color
  float materialDiffuse[3] = {.5f, .5f, .5f};   // The material diffuse color
  float materialSpecular[3] = {.5f, .5f, .5f};  // The material specular color
  float materialShininess = 1.f;                // The material shinyness

  // Projection
	glm::mat4 ProjectionMatrix;       // The projection matrix
  bool projectType = true;          // The projection type boolean
	float fov = 90.f;                 // The Field-Of-View
	float nearPlane = 0.1f;           // The near plane distance
	float farPlane = 1000.f;          // The far plane distance
  float top = 1.f;                  // The top frustrum value
  float bottom;                     // The bottom frustrum value
  float left;                       // The left frustrum value
  float right;                      // The right frustrum value
  float obliqueScale = 0.f;         // The oblique scale for paralell proj
  float obliqueAngleRad = pi_f/4.f; // The oblique angle for paralell proj

  // Cursors stuff
  double cursorScreenX;   // The cursor screen x coordinate
  double cursorScreenY;   // The cursor screen y coordinate
  double offsetX;         // The cursor offset x coordinate (from center)
  double offsetY;         // The cursor offset y coordiante (from center)
  bool showGui = true;    // Show the GUI boolean

  // Object file-stuff
  string objFullPath;     // The wavefront file path

  // Texture File Stuff
  string textureFilePath;         // The texture file path
  bool textureShow = false;       // Show the texture boolean
  bool loadedNewTexture = false;  // A new texture has been loaded boolean

  // Environment (Skybox + Groundplane)
  unsigned int cubeMapTexture;                  // The cubemap texture id
  unsigned int skyBoxVAO, skyBoxVBO, skyBoxEBO; // The Skybox framebuffers
  unsigned int groundVAO, groundVBO, groundEBO; // The groundplane framebuffers

  // All rendering objects
  unsigned int shaderID = PHONG_SHADER; // The default Shader
  vector<Shader*> shaders;              // The list of loaded Shaders
  vector<Texture*> textures;            // A list of loaded Textures
  vector<Material*> materials;          // A list of loaded Materials
  vector<Model*> models;                // A list of loaded Models
  vector<Light*> lights;                // A list of loaded Lights

};

#endif
