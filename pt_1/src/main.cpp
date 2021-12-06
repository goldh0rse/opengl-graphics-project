#include "callbackmanager.h"

OpenGLWindow* CallbackManager::app = nullptr;

int main(int argc, char const *argv[]) {

  OpenGLWindow* window = new OpenGLWindow(
    "Project", 480, 640, 4, 3, true
  );
  CallbackManager::initCallbacks(window);
  window->initialize();

  window->start();

  return 0;
}
