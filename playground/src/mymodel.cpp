/* mymodel.h - Header file for the Model class.
 *
 * @author      - Klas Holmberg
 * @email       - hed16khg@cs.umu.se
 * @date        - 2022-01-13
 */
#include "mymodel.h"

Model::Model(
    glm::vec3 position,
    Material* material,
    Texture* overTexDif,
    vector<Mesh*> meshes
){
    this->position = position;
    this->material = material;
    this->diffuseTex = overTexDif;
    for(auto*i : meshes){
        this->meshes.push_back(new Mesh(*i));
    }

    for (auto& i: this->meshes){
        i->move(this->position);
        i->setOrigin(this->position);
    }
}

Model::~Model(void){
    this->meshes.clear();
}


void Model::render(Shader* shader){
    //Update uniforms
    this->material->sendToShader(*shader);

    //Use a program (BECAUSE SHADER CLASS LAST UNIFORM UPDATE UNUSES IT)
    shader->use();

    //Draw
    for (auto& i : this->meshes){
        //Activate texture for each mesh
        this->diffuseTex->bind(0);
        i->render(); //Activates shader & renders mesh
    }
}
