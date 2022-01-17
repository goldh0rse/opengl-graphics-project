/* CallbackManager.h - Header file for the CallBackManager class.
 *
 * @description - Handles all the different callbacks of the program and
 *                redirects them to the correct methods.
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#ifndef CALLBACKMANAGER_H_
#define CALLBACKMANAGER_H_
#include "openglwindow.h"

class CallbackManager {
public:
  /**
   * initCallbacks  [initializer method for assigning all the correct callbaks]
   * @param window  [the window that is to be generating callbacks]
   */
  static void initCallbacks(OpenGLWindow* window){
    app = window;

    glfwSetKeyCallback(app->getWindow(), keyboardCallback);
    glfwSetFramebufferSizeCallback(app->getWindow(), resizeCallback);
    glfwSetCursorPosCallback(app->getWindow(), cursorCallback);
  }

private:
  static OpenGLWindow* app;

  /**
 * keyboardCallback [callback method that defines the behaviour when
 *                   pressing down a key on the keyboard]
 * @param window    [the window that generated the callback]
 * @param key       [the key identifier that was pressed]
 * @param scancode  [the system-specific scancode of the key]
 * @param action    [the type of press action, Press / Release / Repeat]
 * @param mods      [a bit field describing which modifier keys were held down]
 */
  static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    app->keyboard_input_callback(window, key, scancode, action, mods);
  }

  /**
   * resizeCallback [callback method that defines the behaviour when resizing
   *                 the windowframe of the program]
   * @param window  [the window that generated the callback]
   * @param width   [the new width of the windowframe]
   * @param height  [the new height of the windowframe]
   */
  static void resizeCallback(GLFWwindow* window, int width, int height){
    app->framebuffer_resize_callback(window, width, height);
  }

  /**
   * cursorCallback [callback method that defines the behaviour when moving
   *                 the cursor over the window]
   * @param window  [the window that generated the callback]
   * @param xpos    [the window x-coordinate of the cursor]
   * @param ypos    [the window y-coordinate of the cursor]
   */
  static void cursorCallback(GLFWwindow* window, double xpos, double ypos){
    app->cursor_callback(window, xpos, ypos);
  }

};
#endif
