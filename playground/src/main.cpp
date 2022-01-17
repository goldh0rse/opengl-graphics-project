/* main.cpp - The main loop of the OpenGL project
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#include "callbackmanager.h"

OpenGLWindow* CallbackManager::app = nullptr;

int main(int argc, char const *argv[]) {

  OpenGLWindow* window = new OpenGLWindow(
    "Project", 768, 1024, 4, 3, true
  );
  CallbackManager::initCallbacks(window);
  window->initialize();

  window->start();

  return 0;
}
