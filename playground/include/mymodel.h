/* mymodel.h - Header file for the Model class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#ifndef MYMODEL_H_
#define MYMODEL_H_

#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "material.h"

using namespace std;

class Model {
public:
  /* CONSTRUCTOR & DECONSTRUCTOR */
  /**
   * Model [Main Constructor of the class]
   * @param position    [The starting position of the model]
   * @param material    [The material of the model]
   * @param overTexDif  [The diffuse texture id of the model]
   * @param meshes      [The list of meshes that build the model]
   */
  Model(
    glm::vec3 position,
    Material* material,
    Texture* overTexDif,
    vector<Mesh*> meshes
  );

  /**
   * ~Model [The class deconstuctor]
   */
  ~Model(void);

  /* METHODS */
  /**
   * render [Renders the model with the input parameter shader]
   * @param shader  [The shader which to render the model]
   */
  void render(Shader* shader);

  /**
   * setDiffuseTex [A setter for the diffuse texture attribute]
   * @param texture  [the new texture pointer]
   */
  inline void setDiffuseTex(Texture* texture){ this->diffuseTex = texture; }

  /**
   * getMeshes [a getter for the meshes attribute]
   * @return std::vector<Mesh*>
   */
  inline vector<Mesh*> getMeshes(void) { return this->meshes; }

private:
  /* ATTRIBUTES */
  Material* material;   // The material of the model
  Texture* diffuseTex;  // The diffuse texture of the model
  vector<Mesh*> meshes; // The meshes of the model
  glm::vec3 position;   // The position of the model in world coords
};


#endif
