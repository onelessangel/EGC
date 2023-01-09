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
    camera->Set(CAMERA_OFFSET, glm::vec3(0), glm::vec3(0, 1, 0));

    // uncomment for global view camera
    //camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    fov = RADIANS(60);
    width = 0;
    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);

    playerAngle = 0;
    prevAngle = 0;

    resolution = window->GetResolution();
    playerPos = glm::vec2(resolution.x / 2, resolution.y / 2);

    playerPos3D = glm::vec3(0, 0, 0);

    translationStep = glm::vec3(0);

    treePos.emplace_back(0, 0, 6);
    //treePos.emplace_back(0, 0, 7);
    lampPostPos.emplace_back(0, 0, 8);
    giftPos.emplace_back(0, 0, 10);

   /* for (int i = 0; i < treePos.size(); i++) {
        treePos[i] = ComputeTreePosition(treePos[0]);
    }

    for (int i = 0; i < lampPostPos.size(); i++) {
        lampPostPos[i] = ComputeLampPostPosition(lampPostPos[0]);
    }

    for (int i = 0; i < giftPos.size(); i++) {
        giftPos[i] = ComputeGiftPosition(giftPos[0]);
    }*/

    CreateObjects();
    CreateShaders();
    LoadTextures();
}


void SkiFree::CreateObjects()
{
    Mesh* terrain = new Mesh("terrain");
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
    lampPost->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree/lamp_post_long"), "lamp_post_long.fbx");
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

    // TESTING OBJECTS
    Mesh* sphereMesh = new Mesh("sphere");
    sphereMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
    meshes[sphereMesh->GetMeshID()] = sphereMesh;

    Mesh* boxMesh = new Mesh("box");
    boxMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    meshes[boxMesh->GetMeshID()] = boxMesh;
}


void SkiFree::CreateShaders()
{
    Shader* shader = new Shader("TerrainShader");
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "3-skifree-3d", "shaders", "Terrain_VertexShader.glsl"), GL_VERTEX_SHADER);
    shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "3-skifree-3d", "shaders", "Terrain_FragmentShader.glsl"), GL_FRAGMENT_SHADER);
    shader->CreateAndLink();
    shaders[shader->GetName()] = shader;
}


void SkiFree::LoadTextures()
{
    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "skifree", "ski_slope");

    {
        Texture2D* texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "snow01.png").c_str(), GL_REPEAT);
        mapTextures["terrain"] = texture;
    }
}


void SkiFree::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*glm::ivec2 resolution = window->GetResolution();*/
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void SkiFree::UpdateTranslationStep(float deltaTimeSeconds)
{
    translationStep.z = deltaTimeSeconds * MOVEMENT_SPEED.z;
    translationStep.y = -SLOPE_ANGLE_TAN * translationStep.z;

    if (prevAngle < 0 && playerAngle > 0 ||
        prevAngle > 0 && playerAngle < 0) {
        translationStep.x = 0;
    }
    prevAngle = playerAngle;

    if (playerAngle == 0)
    {
        translationStep.x = 0;
    }
    else if (playerAngle < 0)
    {
        translationStep.x = -cos(playerAngle) * deltaTimeSeconds * MOVEMENT_SPEED.x;
    }
    else
    {
        translationStep.x = cos(playerAngle) * deltaTimeSeconds * MOVEMENT_SPEED.x;
    }
}


glm::vec3 SkiFree::ComputeTreePosition(glm::vec3 pos)
{
    // compute position using model offset and slope angle
    glm::vec3 treePos = pos * TREE_SIZE_EQUIV;
    treePos.x += TREE_OFFSET.x;
    treePos.y = -SLOPE_ANGLE_TAN * treePos.z + TREE_OFFSET.y;
    treePos.z += TREE_OFFSET.z;

    return treePos;
}


glm::vec3 SkiFree::ComputeLampPostPosition(glm::vec3 pos)
{
    // compute position using model offset and slope angle
    glm::vec3 lampPostPos = pos * LAMP_POST_SIZE_EQUIV;
    lampPostPos.x += LAMP_POST_OFFSET.x;
    lampPostPos.y = -SLOPE_ANGLE_TAN * lampPostPos.z + LAMP_POST_OFFSET.y;
    lampPostPos.z += LAMP_POST_OFFSET.z;

    return lampPostPos;
}


glm::vec3 SkiFree::ComputeGiftPosition(glm::vec3 pos)
{
    // compute position using model offset and slope angle
    glm::vec3 giftPos = pos * GIFT_SIZE_EQUIV;
    giftPos.x += GIFT_OFFSET.x;
    giftPos.y = -SLOPE_ANGLE_TAN * giftPos.z + GIFT_OFFSET.y;
    giftPos.z += GIFT_OFFSET.z;

    return giftPos;
}
 
bool SkiFree::CollidesObstacle(glm::vec3 obstaclePosition, ObjectType type)
{
    float obstacleHitboxRange;
    
    switch (type)
    {
        case GIFT:
            obstacleHitboxRange = HITBOX_RANGE_GIFT;
            break;
    
        case LAMP_POST:
            obstacleHitboxRange = HITBOX_RANGE_LAMP_POST;
            break;
    
        case TREE:
            obstacleHitboxRange = HITBOX_RANGE_TREE;
            break;
    
        default:
            obstacleHitboxRange = 0;
            break;
    }

    auto distance = sqrt(
        (playerPos3D.x - obstaclePosition.x) * (playerPos3D.x - obstaclePosition.x) +
        (playerPos3D.z - obstaclePosition.z) * (playerPos3D.z - obstaclePosition.z)
    );

    return distance < HITBOX_RANGE_PLAYER + obstacleHitboxRange;
}


void SkiFree::Update(float deltaTimeSeconds)
{
    UpdateTranslationStep(deltaTimeSeconds);

    // render player
    playerPos3D += translationStep;
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, SCALE_PLAYER);
    modelMatrix = glm::translate(modelMatrix, playerPos3D * PLAYER_SIZE_EQUIV);
    modelMatrix *= transform_3d::RotateOY(M_PI / 2);
    modelMatrix *= transform_3d::RotateOZ(SLOPE_ANGLE);
    modelMatrix *= transform_3d::RotateOY(playerAngle);
    RenderMesh(meshes["player"], shaders["Simple"], modelMatrix);

    // render shape box
    //modelMatrix = glm::mat4(1);
    ////modelMatrix = glm::scale(modelMatrix, glm::vec3(.36, 1, 1.25)); // player
    ////modelMatrix = glm::scale(modelMatrix, glm::vec3(.5, .2, .55)); // tree
    ////modelMatrix = glm::scale(modelMatrix, glm::vec3(.15, .2, .15)); // lamp post
    //modelMatrix = glm::scale(modelMatrix, glm::vec3(.4, .2, .4));     // gift
    ////modelMatrix = glm::translate(modelMatrix, playerPos3D);
    //modelMatrix *= transform_3d::RotateOZ(SLOPE_ANGLE);
    ////modelMatrix *= transform_3d::RotateOY(playerAngle);
    //RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

    // render tree
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
    modelMatrix = glm::translate(modelMatrix, ComputeTreePosition(treePos[0]));
    RenderMesh(meshes["tree1"], shaders["Simple"], modelMatrix);

    if (CollidesObstacle(treePos[0], TREE)) {
        cout << "I've been hit: " << counter++ << "\n";
    }

    if (CollidesObstacle(lampPostPos[0], LAMP_POST)) {
        cout << "I've been hit: " << counter++ << "\n";
    }

    if (CollidesObstacle(giftPos[0], GIFT)) {
        cout << "I've been hit: " << counter++ << "\n";
    }

    // render lamp post  
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, SCALE_LAMP_POST);
    modelMatrix = glm::translate(modelMatrix, ComputeLampPostPosition(lampPostPos[0]));
    modelMatrix *= transform_3d::RotateOY(M_PI / 2);
    RenderMesh(meshes["lamp_post"], shaders["Simple"], modelMatrix);

    // render gift
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, SCALE_GIFT);
    modelMatrix = glm::translate(modelMatrix, ComputeGiftPosition(giftPos[0]));
    RenderMesh(meshes["gift4"], shaders["Simple"], modelMatrix);

    // render ground
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, playerPos3D);
    modelMatrix *= transform_3d::RotateOX(SLOPE_ANGLE);
    RenderSimpleMesh(meshes["terrain"], shaders["TerrainShader"], modelMatrix, mapTextures["terrain"]);

    camera->Set(playerPos3D + CAMERA_OFFSET, playerPos3D, glm::vec3(0, 1, 0));
    //camera->Set(glm::vec3(0) + CAMERA_OFFSET, glm::vec3(0), glm::vec3(0, 1, 0));
}


void SkiFree::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
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


void SkiFree::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;


    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    GLint locTranslation = glGetUniformLocation(shader->program, "translation");
    glUniform2fv(locTranslation, 1, glm::value_ptr(glm::vec2(playerPos3D.x, playerPos3D.z / glm::cos(SLOPE_ANGLE))));
         
    if (texture)
    {
        // Activate texture location 0
        glActiveTexture(GL_TEXTURE0);

        // Bind the texture1 ID
        glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

        // Send texture uniform value
        glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
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
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
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

    currPos.x = mouseX + deltaX;
    currPos.y = mouseY + deltaY;

    // ignore mouse if it is above player
    if (currPos.y < playerPos.y) {
        return;
    }

    verticalDir = glm::normalize(glm::vec2(resolution.x / 2, resolution.y) - playerPos);
    mouseDir = glm::normalize(currPos - playerPos);

    playerAngle = -glm::orientedAngle(verticalDir, mouseDir);

    // QUESTIONABLE :( -- in functie de camera zoom i guess
    if (playerAngle < .005 && playerAngle > -.005) {
        playerAngle = 0;
    }

    // limit angle to 90 degrees
    if (playerAngle < 0) {
        playerAngle = MAX(playerAngle, -MAX_PLAYER_ANGLE);
    }
    else {
        playerAngle = MIN(playerAngle, MAX_PLAYER_ANGLE);
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