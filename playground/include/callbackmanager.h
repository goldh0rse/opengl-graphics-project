#include "openglwindow.h"


class CallbackManager {
  static OpenGLWindow* app;

  static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    app->keyboard_input_callback(window, key, scancode, action, mods);
  }

  static void resizeCallback(GLFWwindow* window, int width, int height){
    app->framebuffer_resize_callback(window, width, height);
  }

  static void cursorCallback(GLFWwindow* window, double xpos, double ypos){
    app->cursor_callback(window, xpos, ypos);
  }


public:
  static void initCallbacks(OpenGLWindow* window){
    app = window;

    glfwSetKeyCallback(app->getWindow(), keyboardCallback);
    glfwSetFramebufferSizeCallback(app->getWindow(), resizeCallback);
    glfwSetCursorPosCallback(app->getWindow(), cursorCallback);

  }
};
