/* light.cpp - Header file for the Light class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-17
 */
#ifndef LIGHT_H_
#define LIGHT_H_

#include <glm/glm.hpp>
#include "shader.h"

using namespace std;

class Light {
  public:
    /* CONSTRUCTORS & DECONSTRUCTORS */
    /**
     * Light [Main constructor]
     * @param position  [The starting position of the light source]
     * @param color     [The starting specular color of the light source]
     * @param ambient   [The starting ambient color of the light source]
     */
    Light(glm::vec3 position, glm::vec3 color, glm::vec3 ambient);

    /**
     * ~Light [The class Deconstructor]
     * @note Currently not necessary
     */
    ~Light(void){}; // Not necessary in current version

    /* METHODS */
    /**
     * updatePosition [Updates the position of the light source]
     * @param x  [x world coordinate]
     * @param y  [y world coordinate]
     * @param z  [z world coordinate]
     */
    void updatePosition(float x, float y, float z);

    /**
     * updateColor [Updates the specular color of the light source]
     * @param r  [the red component value]
     * @param g  [the green component value]
     * @param b  [the blue component value]
     */
    void updateColor(float r, float g, float b);

    /**
     * updateAmbient [Updates the ambient color of the light source]
     * @param r  [the red component value]
     * @param g  [the green component value]
     * @param b  [the blue component value]
     */
    void updateAmbient(float r, float g, float b);

    /**
     * sendToShader [Updates the Light uniform in the input shaders]
     * @param program  [A shader where the light source is updated]
     */
    void sendToShader(Shader &program);

    /* INLINE METHODS */
    /**
     * getPosition [a getter method for the position attribute]
     * @return  [the position attribute]
     */
    inline glm::vec3 getPosition(void) { return this->position; }

    /**
     * getColor [a getter method for the color attribute]
     * @return  [the color attribute]
     */
    inline glm::vec3 getColor(void) { return this->color; }

    /**
     * getAmbient [a getter method for the ambient attribute]
     * @return  [the ambient attribute]
     */
    inline glm::vec3 getAmbient(void) { return this->ambient; }


  private:
    /* ATTRIBUTES */
    glm::vec3 position; // The position of the lightsource
    glm::vec3 color;    // The specular color of the light source
    glm::vec3 ambient;  // The ambient color of the light source
};

#endif
