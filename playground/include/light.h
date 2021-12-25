#include <glm/glm.hpp>
#include "shader.h"

using namespace std;

class Light {
  public:
    Light(glm::vec3 position, glm::vec3 color, glm::vec3 ambient  );
    ~Light(void);

    void updatePosition(float x, float y, float z);
    void updateColor(float r, float y, float z);
    void updateAmbient(float r, float y, float z);

    inline glm::vec3 getPosition(void) { return this->position; }
    inline glm::vec3 getColor(void) { return this->color; }
    inline glm::vec3 getAmbient(void) { return this->ambient; }
    void sendToShader(Shader &program);


  private:
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 ambient;
};
