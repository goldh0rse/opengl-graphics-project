#ifndef MYMODEL_H_
#define MYMODEL_H_

#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "material.h"

using namespace std;

class Model {
public:
    Model(
    glm::vec3 position,
    Material* material,
    Texture* overTexDif,
    vector<Mesh*> meshes);

    ~Model();

    void render(Shader* shader);
    void update(void);
    void updateUniforms(void);
    inline vector<Mesh*> getMeshes(void) { return meshes; }

private:
    Material* material;
    Texture* overideTextureDiffuse;
    vector<Mesh*> meshes;
    glm::vec3 position;
};


#endif
