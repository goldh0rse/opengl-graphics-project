//#include "libs.h"
#include "callbackmanager.h"
// #include "openglwindow.h"

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
