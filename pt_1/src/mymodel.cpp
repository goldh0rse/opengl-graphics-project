#include "mymodel.h"

Model::Model(
    glm::vec3 position,
    Material* material,
    Texture* overTexDif,
    Texture* OverTexSpec,
    vector<Mesh*> meshes
){
    this->position = position;
    this->material = material;
    this->overideTextureDiffuse = overTexDif;
    this->overideTextureSpecular = OverTexSpec;
    for(auto*i : meshes){
        this->meshes.push_back(new Mesh(*i));
    }

    for (auto& i: this->meshes){
        i->move(this->position);
        i->setOrigin(this->position);
    }
}

Model::~Model(){
    for(auto*& i : this->meshes)
        delete i;
}

// Public Functions
void Model::update(void){

}

void Model::render(Shader* shader){
    //Update the uniforms
    this->updateUniforms();

    //Update uniforms
    this->material->sendToShader(*shader);

    //Use a program (BECAUSE SHADER CLASS LAST UNIFORM UPDATE UNUSES IT)
    shader->use();

    //Draw
    for (auto& i : this->meshes){   
        //Activate texture for each mesh
        this->overideTextureDiffuse->bind(0);
        this->overideTextureSpecular->bind(1);

        i->render(); //Activates shader also
    }
}

// Private functions
void Model::updateUniforms(void){

}


