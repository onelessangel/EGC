#include "lab_m1/3-skifree-3d/SkiFree.hpp"

using namespace gfxc;
using namespace std;
using namespace m1;

SkiFree::SkiFree()
{

}


SkiFree::~SkiFree()
{

}


void SkiFree::Init()
{
    // set camera
    renderCameraTarget = false;

    camera = new skifree_camera::Camera();
    //camera->Set(playerCenter + CAMERA_OFFSET, playerCenter - glm::vec3(0, -.2, 0), glm::vec3(0, 1, 0));

    // uncomment for global view camera
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    fov = RADIANS(60);
    width = 0;
    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);

    // Load textures
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree", "ski_slope");

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "snow01.png").c_str(), GL_REPEAT);
        mapTextures["terrain"] = texture;
    }

    {
        Shader* shader = new Shader("TerrainShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "3-skifree-3d", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "3-skifree-3d", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    CreateObjects();
}

void SkiFree::CreateObjects()
{
    Mesh* terrain = new Mesh("terrain");
    //terrain->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/ski_slope"), "ski_slope.fbx");
    terrain->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/ski_slope"), "ground.obj");
    AddMeshToList(terrain);

    Mesh* player = new Mesh("player");
    player->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/player"), "player.fbx");
    AddMeshToList(player);

    Mesh* tree1 = new Mesh("tree1");
    tree1->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/tree1"), "tree1.fbx");
    AddMeshToList(tree1);

    Mesh* tree2 = new Mesh("tree2");
    tree2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/tree2"), "tree2.fbx");
    AddMeshToList(tree2);

    Mesh* tree3 = new Mesh("tree3");
    tree3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/tree3"), "tree3.fbx");
    AddMeshToList(tree3);

    Mesh* rock = new Mesh("rock");
    rock->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/rock"), "rock.fbx");
    AddMeshToList(rock);

    Mesh* lampPost = new Mesh("lamp_post");
    lampPost->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/lamp_post"), "lamp_post.fbx");
    AddMeshToList(lampPost);

    Mesh* gift1 = new Mesh("gift1");
    gift1->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/gift1"), "gift1.fbx");
    AddMeshToList(gift1);

    Mesh* gift2 = new Mesh("gift2");
    gift2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/gift2"), "gift2.fbx");
    AddMeshToList(gift2);

    Mesh* gift3 = new Mesh("gift3");
    gift3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/gift3"), "gift3.fbx");
    AddMeshToList(gift3);

    Mesh* gift4 = new Mesh("gift4");
    gift4->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/gift4"), "gift4.fbx");
    AddMeshToList(gift4);
}


void SkiFree::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void SkiFree::Update(float deltaTimeSeconds)
{
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, SCALE_PLAYER);
    modelMatrix *= transform_3d::RotateOY(M_PI / 2);
    modelMatrix *= transform_3d::RotateOZ(SLOPE_ANGLE);
    RenderMesh(meshes["player"], shaders["Simple"], modelMatrix);

    modelMatrix = glm::mat4(1);
    //modelMatrix = glm::scale(modelMatrix, glm::vec3(.5, .5, .5));
    modelMatrix *= transform_3d::RotateOX(SLOPE_ANGLE);
    //RenderMesh(meshes["terrain"], shaders["Simple"], modelMatrix);
    RenderSimpleMesh(meshes["terrain"], shaders["TerrainShader"], modelMatrix, mapTextures["terrain"]);
}


void SkiFree::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void SkiFree::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

void SkiFree::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;


    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Set any other shader uniforms that you need
    GLint locTime = glGetUniformLocation(shader->program, "time");

    if (mesh == meshes["terrain"])
    {
        glUniform1f(locTime, (GLfloat)Engine::GetElapsedTime());
    }
    else
    {
        glUniform1f(locTime, -1.f);
    }

    //glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), mixTextures);

    if (texture1)
    {
        // Activate texture location 0
        glActiveTexture(GL_TEXTURE0);

        // Bind the texture1 ID
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

        // Send texture uniform value
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);

    //mesh->Render();
}

void SkiFree::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        if (window->KeyHold(GLFW_KEY_W)) {
            // Translate the camera forward
            camera->TranslateForward(deltaTime * CAMERA_SPEED);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // Translate the camera to the left
            camera->TranslateRight(-deltaTime * CAMERA_SPEED);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // Translate the camera backward
            camera->TranslateForward(-deltaTime * CAMERA_SPEED);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // Translate the camera to the right
            camera->TranslateRight(deltaTime * CAMERA_SPEED);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // Translate the camera downward
            camera->MoveUpward(-deltaTime * CAMERA_SPEED);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // Translate the camera upward
            camera->MoveUpward(deltaTime * CAMERA_SPEED);
        }
    }
}


void SkiFree::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void SkiFree::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void SkiFree::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            camera->RotateFirstPerson_OX(-CAMERA_SENSITIVITY_OX * deltaY);
            camera->RotateFirstPerson_OY(-CAMERA_SENSITIVITY_OY * deltaX);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            camera->RotateThirdPerson_OX(CAMERA_SENSITIVITY_OX * -deltaY);
            camera->RotateThirdPerson_OY(CAMERA_SENSITIVITY_OY * -deltaX);
        }
    }
}


void SkiFree::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void SkiFree::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void SkiFree::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void SkiFree::OnWindowResize(int width, int height)
{
}