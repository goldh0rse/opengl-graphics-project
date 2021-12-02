#include "openglwindow.h"


class CallbackManager {
  static OpenGLWindow* app;

  static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    app->keyboard_input_callback(window, key, scancode, action, mods);
  }

  static void resizeCallback(GLFWwindow* window, int width, int height){
    app->framebuffer_resize_callback(window, width, height);
  }


public:
  static void initCallbacks(OpenGLWindow* window){
    app = window;

    glfwSetKeyCallback(app->getWindow(), keyboardCallback);
    glfwSetFramebufferSizeCallback(app->getWindow(), resizeCallback);

  }
};
