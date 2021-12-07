#include "openglwindow.h"

using namespace std;

/*                           PUBLIC                                           */
/******************************************************************************/
// Constructors & Destructors
OpenGLWindow::OpenGLWindow(
    const char* title,
    const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
    const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
    bool resizable
)
    :
    WINDOW_WIDTH(WINDOW_WIDTH),
    WINDOW_HEIGHT(WINDOW_HEIGHT),
    GL_VERSION_MAJOR(GL_VERSION_MAJOR),
    GL_VERSION_MINOR(GL_VERSION_MINOR),
    startPos(glm::vec3(0.f, 0.f, 2.f)),
    startWorldUp(glm::vec3(0.f, 1.f, 0.f)),
    startFacing(glm::vec3(0.f, 0.f, -1.f))
{

    this->window = nullptr;
    this->framebufferWidth = this->WINDOW_WIDTH;
    this->framebufferHeight = this->WINDOW_HEIGHT;


    this->camPosition = this->startPos;
    this->worldUp = this->startWorldUp;
    this->camFront = this->startFacing;
    this->camRight = glm::vec3(0.f);
    this->camRight = glm::normalize(glm::cross(this->camFront, this->worldUp));
    this->camUp = glm::normalize(glm::cross(this->camRight, this->camFront));

    this->pitch = 0.f;
    this->yaw = -90.f;
    // this->roll = 0.f;
    this->sensitivity = 0.1f;
    this->movementSpeed = 0.05f;

    this->projectType = true;
    this->fov = 90.f;
    this->nearPlane = 0.1f; // Due to where we want clipping to be
    this->farPlane = 1000.f; // Test on itchy, if slow dump to 100.f
    this->top = 1.0f;
    this->obliqueScale = 0.0f;
    this->obliqueAngleRad = pi_f/4.0f;

    this->showGui = true;

    this->initGLFW();
    this->initWindow(title, resizable);
    this->initGLEW();
    this->initImGui();
    this->initOpenGLOptions();
}

OpenGLWindow::~OpenGLWindow(void){
    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(this->window);
    glfwTerminate();

    for (size_t i = 0; i < this->shaders.size(); i++){
        delete this->shaders[i];
    }

    for (size_t i = 0; i < this->textures.size(); i++){
        delete this->textures[i];
    }

    for (size_t i = 0; i < this->materials.size(); i++){
        delete this->materials[i];
    }

    for (auto*& i: this->models)
        delete i;

    for (size_t i = 0; i < this->lights.size(); i++){
        delete this->lights[i];
    }
}

void OpenGLWindow::initialize(void){
    this->initMatrices();
    this->initShaders();
    this->initTextures();
    this->initMaterials();
    string tempString = "resources/objfiles/cube.obj";
    this->initModels(tempString);
    this->initLights();
    this->initUniforms();
}
// Accessors
int OpenGLWindow::getWindowShouldClose(void){
    return glfwWindowShouldClose(this->window);
}

// Modifiers
void OpenGLWindow::render(void){
    // Clear
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // STENCIL BUFFER NOT USED

    this->updateUniforms();

    for (auto&i : this->models)
		  i->render(this->shaders[SHADER_CORE_PROGRAM]);


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    /* END DRAWING SEGMENT */
    glfwSwapBuffers(this->window); // Swapping between the buffer being drawn to with the one currently shown
    glFlush();

    glBindVertexArray(0);
    this->shaders[SHADER_CORE_PROGRAM]->unuse();
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLWindow::start(void){
  /*****************MAINLOOP**********************/
  while(!this->getWindowShouldClose()){
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Draw the gui
    if(this->showGui){
      DrawGui();
    }

    // Update Input
    this->render();

    // glfwSwapBuffers(this->window); // Swapping between the buffer being drawn to with the one currently shown
    glfwWaitEvents();
  }
}

/*                           PRIVATE                                          */
/******************************************************************************/
// Attributes

// Private functions
void OpenGLWindow::initGLFW(void){
    // Initialize glfw
    if (!glfwInit()){
        cout << "Could not intilialize GLFW3!" << endl;
        exit(EXIT_FAILURE);
    }
}

void OpenGLWindow::initWindow(const char* title, bool resizable){
    // Set minimum supported OpenGL version and OpenGL profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Mac os

    this->window = glfwCreateWindow(this->WINDOW_HEIGHT, this->WINDOW_WIDTH, title, NULL, NULL);
    if (this->window == NULL) {
        glfwTerminate();
        cerr << "Could not open window or initialize OpenGL context." << endl;
        exit(EXIT_FAILURE);
    }
    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

    glfwMakeContextCurrent(this->window); // NOW GLEW CAN INITIALIZE
    glfwSwapInterval(1);
}

void OpenGLWindow::initGLEW(void){
  // Initialize glew
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
      cout << "glew init error:" << endl << glewGetErrorString(glewError) << endl;
      exit(EXIT_FAILURE);
  }

  if (!GLEW_VERSION_4_3) {
      cout << "Warning: OpenGL 4.3+ not supported by the GPU!" << endl;
      cout << "Decreace supported OpenGL version if needed." << endl;
  }

}

void OpenGLWindow::initOpenGLOptions(void){
    // OPENGL OPTIONS
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE); // Only draw face that is facing camera
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW); // Triangle drawing direction, DEFINES WHICH FACE IS FRONT AND BACK

    glEnable(GL_BLEND); // Enable blending of colors
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL FILL (Fill the shape with a color)
}

void OpenGLWindow::initMatrices(void){
    // this->camera = new Camera(this->camPosition, this->worldUp, this->camFront);

    // ViewMatrix
    this->ViewMatrix = glm::mat4(1.f);
    this->ViewMatrix = glm::lookAt(
        this->camPosition,
        this->camPosition + this->camFront,
        this->worldUp
    );

    // ProjectionMatrix
    this->ProjectionMatrix = glm::mat4(1.f);
    this->ProjectionMatrix = glm::perspective(
        glm::radians(this->fov),
        static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
        this->nearPlane,
        this->farPlane
    );
}

void OpenGLWindow::initShaders(void){
    this->shaders.push_back(new Shader("src/shaders/vshader.glsl", "src/shaders/fshader.glsl", ""));
}

void OpenGLWindow::initTextures(void){
    this->textures.push_back(new Texture("resources/images/pusheen.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("resources/images/pusheen_specular.png", GL_TEXTURE_2D));

    this->textures.push_back(new Texture("resources/images/wood.png", GL_TEXTURE_2D));
    this->textures.push_back(new Texture("resources/images/wood_specular.png", GL_TEXTURE_2D));
}

void OpenGLWindow::initMaterials(void){
    this->materials.push_back(
        new Material(
            glm::vec3(0.5f),
            glm::vec3(1.f),
            glm::vec3(1.f),
            0,
            1
        )
    );
}

void OpenGLWindow::initModels(string fileName) {

    vector<Mesh*> meshes;
    vector<Vertex> mesh = loadObject(fileName);

    meshes.push_back(
        new Mesh(
            this->shaders[SHADER_CORE_PROGRAM],
            mesh.data(), mesh.size(),
            NULL, 0,
            glm::vec3(1.f, 0.f, 0.f),
            glm::vec3(0.f),
            glm::vec3(0.f),
            glm::vec3(1.f)
        )
    );

    if(this->models.size() > 0){
        for (auto*& i: this->models)
            delete i;
    }

    this->models.push_back(new Model(
        glm::vec3(0.f),
        this->materials[MAT_1],
        this->textures[TEX_WOOD],
        this->textures[TEX_WOOD_SPECULAR],
        meshes
    ));

    for (auto*& i: meshes)
        delete i;
}

void OpenGLWindow::initLights(void){
    this->lights.push_back(
        new glm::vec3(0.f, 0.f, 1.f)
    );
}

void OpenGLWindow::initUniforms(void){
    // Send Matricies to shader
    // glm::mat4 ViewMatrix = this->camera.getViewMatrix();
    // glm::vec3 cameraPos = this->camera.getPosition();
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
    this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");

    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(*this->lights[0], "lightPos0");
    this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
}

void OpenGLWindow::updateUniforms(void){
  // Update ViewMatrix
  this->ViewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->camUp);

  this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ViewMatrix, "ViewMatrix");
  this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camPosition, "cameraPos");
  // this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->camera.getViewMatrix(), "ViewMatrix");
  // this->shaders[SHADER_CORE_PROGRAM]->setVec3f(this->camera.getPosition(), "cameraPos");

  // Update Uniforms
  this->shaders[SHADER_CORE_PROGRAM]->set1i(0, "texture0");
  this->shaders[SHADER_CORE_PROGRAM]->set1i(1, "texture1");

  // Update framebuffersize & ProjectionMatrix
  glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

  // Projection Matrix
  this->ProjectionMatrix = glm::mat4(1.f);
  if (this->projectType){
    // Perspective
    this->ProjectionMatrix = glm::perspective(
        	glm::radians(this->fov),
        	static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
        	this->nearPlane, this->farPlane
  	);
  } else {
    // Parallel
    this->bottom = -this->top;
    this->right = this->top * (static_cast<float>(this->framebufferWidth) / this->framebufferHeight);
    this->left = -this->right;

    // ST
    this->ProjectionMatrix = glm::ortho(
      this->left, this->right,
      this->bottom, this->top,
      this->nearPlane, this->farPlane
    );

    // H(alpha)
    this->ProjectionMatrix[0][2] = this->obliqueScale * glm::cos(this->obliqueAngleRad);
    this->ProjectionMatrix[1][2] = this->obliqueScale * glm::sin(this->obliqueAngleRad);
  }

  this->shaders[SHADER_CORE_PROGRAM]->setMat4fv(this->ProjectionMatrix, "ProjectionMatrix");
}

// ImGui functions
void OpenGLWindow::initImGui(void){
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Set Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(this->window, true);
  ImGui_ImplOpenGL3_Init(NULL);
}

void OpenGLWindow::DrawGui(void){
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context.");

    static ImGuiSliderFlags flags = ImGuiSliderFlags_AlwaysClamp;

    ImGui::Begin("3D Studio");

    if (ImGui::CollapsingHeader("OBJ File")) {
        ImGui::Text("OBJ file: %s", this->objFileName.c_str());
        if (ImGui::Button("Open File"))
            igfd::ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".obj", ".");

        if (igfd::ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey")) {
            if (igfd::ImGuiFileDialog::Instance()->IsOk == true) {
                this->objFileName = igfd::ImGuiFileDialog::Instance()->GetCurrentFileName();
                this->objFilePath = igfd::ImGuiFileDialog::Instance()->GetCurrentPath();

                this->objFullPath = igfd::ImGuiFileDialog::Instance()->GetFilePathName();

                // cout << "Full FilePathName: " << this->objFullPath << endl;
                cout << "OBJ file: " << this->objFileName << endl << "Path: " << this->objFilePath << endl;

                this->initModels(this->objFullPath);
            }
            // close
            igfd::ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
        }
    }

    if (ImGui::CollapsingHeader("Projection")) {
        // THIS IS WHERE I NEED TO CHANGE THE PROJECTION

        const char* items[] = {"Perspective", "Parallel" };
        static int proj_current_idx = 0;
        if (ImGui::Combo("projektion", &proj_current_idx, items, IM_ARRAYSIZE(items), IM_ARRAYSIZE(items)));
        if (proj_current_idx == 0) {
            ImGui::SliderFloat("Field of view",&this->fov, 20.0f, 160.0f, "%1.0f", flags);
            ImGui::SliderFloat("Far",&this->farPlane, 1.0f, 1000.0f, "%1.0f", flags);
            this->projectType = true;
        }
        if (proj_current_idx == 1) {
            ImGui::SliderFloat("Top",&this->top, 1.0f, 100.0f, "%.1f", flags);
            ImGui::SliderFloat("Far",&this->farPlane, 1.0f, 1000.0f, "%1.0f", flags);
            ImGui::SliderFloat("Oblique scale",&this->obliqueScale, 0.0f, 1.0f, "%.1f", flags);
            ImGui::SliderAngle("Oblique angle",&this->obliqueAngleRad, 15, 75, "%1.0f", flags);
            this->projectType = false;
        }
    }

    ImGui::End();
}

void OpenGLWindow::moveCamera(const int direction){
	//Update position vector
	switch (direction){
	case FORWARD:
		this->camPosition += this->camFront * this->movementSpeed;// * dt;
		break;
	case BACKWARD:
		this->camPosition -= this->camFront * this->movementSpeed;
		break;
	case LEFT:
		this->camPosition -= this->camRight * this->movementSpeed;
		break;
	case RIGHT:
		this->camPosition += this->camRight * this->movementSpeed;
		break;
  case UP:
    this->camPosition += this->camUp * this->movementSpeed;
    break;
  case DOWN:
    this->camPosition -= this->camUp * this->movementSpeed;
    break;
	default:
		break;
	}

}

// Callbacks
void OpenGLWindow::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) const {
  	if(glfwGetCurrentContext() == NULL){
		return;
	}

	glViewport(0, 0, fbW, fbH);
}

void OpenGLWindow::keyboard_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // QUIT
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }

    // CAMERA
    if (key == GLFW_KEY_E && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // Up (E) Moves p0 and pref relative the camera's positive y-axis.
      this->moveCamera(UP);
    }
    if (key == GLFW_KEY_Q && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // Down (Q) Moves p0 and pref relative the camera's negative y-axis.
      this->moveCamera(DOWN);
    }
    if (key == GLFW_KEY_W && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // Forward (W) Moves p0 and pref relative the camera's negative(!) z-axis.
      this->moveCamera(FORWARD);
    }
    if (key == GLFW_KEY_S && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // Backwards (S) Moves p0 and pref relative the camera's positive z-axis.
      this->moveCamera(BACKWARD);
    }
    if (key == GLFW_KEY_D && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // Right (D) Moves p0 and pref relative the camera's positive x-axis.
      this->moveCamera(RIGHT);
    }
    if (key == GLFW_KEY_A && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // Left (A) Moves p0 and pref relative the camera's negative x-axis.
      this->moveCamera(LEFT);
    }

    // Activate Cursor
    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS){
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
      this->showGui = false;
      // glfwSetCursorPos(window, 0, 0);
      glfwSetCursorPos(window, this->framebufferWidth/2, this->framebufferHeight / 2);
      // Hide mouse, activate mouse input
    } else if(key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE){
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      this->showGui = true;
      // Show mouse, disable mouse input
    }

    // TRANSLATE OBJECT
    if(key == GLFW_KEY_J && action == GLFW_PRESS){
      // TRANSLATE OBJECT "LEFT"
      for (auto&i : this->models)
          for (auto&j : i->getMeshes())
              j->move(glm::vec3(-0.1f, 0.f ,0.f));
    }
    if(key == GLFW_KEY_L && action == GLFW_PRESS){
      //  TRANSLATE OBJECT "RIGHT"
      for (auto&i : this->models)
          for (auto&j : i->getMeshes())
              j->move(glm::vec3(0.1f, 0.f ,0.f));
    }

    // ROTATE
    if(key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // NEGATIVE ROTATION AROUND X AXIS
      for (auto&i : this->models)
          for (auto&j : i->getMeshes())
              j->rotate(glm::vec3(-1.f, 0.f ,0.f));
    }
    if(key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // POSITIVE ROTATION AROUND X AXIS
      for (auto&i : this->models)
          for (auto&j : i->getMeshes())
              j->rotate(glm::vec3(1.f, 0.f ,0.f));
    }
    if(key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // NEGATIVE ROTATION AROUND Y AXIS
      for (auto&i : this->models)
          for (auto&j : i->getMeshes())
              j->rotate(glm::vec3(0.f, -1.f ,0.f));
    }
    if(key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS)){
      // NEGATIVE ROTATION AROUND X AXIS
      for (auto&i : this->models)
          for (auto&j : i->getMeshes())
              j->rotate(glm::vec3(0.f, 1.f ,0.f));
    }

    // SCALE
    if(key == GLFW_KEY_I && action == GLFW_PRESS){
      // SCALE "UP Y"
      for (auto&i : this->models)
          for (auto&j : i->getMeshes())
              j->scaleMesh(glm::vec3(0.f, 0.01f ,0.f));
    }
    if(key == GLFW_KEY_K && action == GLFW_PRESS){
      // SCALE "DOWN Y"
      for (auto&i : this->models)
          for (auto&j : i->getMeshes())
              j->scaleMesh(glm::vec3(0.f, -0.01f ,0.f));
    }
}

void OpenGLWindow::cursor_callback(GLFWwindow* window, double xpos, double ypos) {
  if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED){
    // Update Camera
    this->offsetX = xpos - (this->framebufferWidth / 2);
    this->offsetY = (this->framebufferHeight / 2) - ypos;

    this->pitch += static_cast<GLfloat>(this->offsetY) * this->sensitivity;
  	this->yaw += static_cast<GLfloat>(this->offsetX) * this->sensitivity;

  	if (this->pitch > 80.f){
      this->pitch = 80.f;

    }	else if (this->pitch < -80.f){
      this->pitch = -80.f;
    }

  	if (this->yaw > 360.f || this->yaw < -360.f){
  			this->yaw = 0.f;
    }

    this->camFront.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->camFront.y = sin(glm::radians(this->pitch));
    this->camFront.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->camFront = glm::normalize(this->camFront);
    this->camRight = glm::normalize(glm::cross(this->camFront, this->worldUp));
    this->camUp = glm::normalize(glm::cross(this->camRight, this->camFront));

    glfwSetCursorPos(window, this->framebufferWidth/2, this->framebufferHeight / 2);

  }
}
