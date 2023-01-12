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

    //treePos.emplace_back(-25, 0, 8);
    ////treePos.emplace_back(0, 0, 7);
    //lampPostPos.emplace_back(-50, 0, 8);
    //giftPos.emplace_back(0, 0, 6);
    rockPos.emplace_back(0, 0, 6);

   /* for (int i = 0; i < treePos.size(); i++) {
        treePos[i] = ComputeTreePosition(treePos[0]);
    }

    for (int i = 0; i < lampPostPos.size(); i++) {
        lampPostPos[i] = ComputeLampPostPosition(lampPostPos[0]);
    }

    for (int i = 0; i < giftPos.size(); i++) {
        giftPos[i] = ComputeGiftPosition(giftPos[0]);
    }*/

    isTerrain = true;

    CreateObjects();
    CreateShaders();
    LoadTextures();
    GenerateRandomObjects();
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
    {
        Shader* shader = new Shader("SkiFreeShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "3-skifree-3d", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "3-skifree-3d", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
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


void SkiFree::GenerateRandomObjects()
{
    glm::vec3 pos;
    ObjectType type;
    int objectRange;

    for (int i = 0; i < NMAX; i++) {
        pos = glm::vec3(0);
        type = ObjectType (rand() % 8);   // aici ar fi corect!!!!!!!!!!!

        if (type == GIFT1 || type == GIFT2 || type == GIFT3 || type == GIFT4)
        {
            objectRange = 10;
        }
        else {
            objectRange = 25;
        }

        pos.x = -objectRange + (rand() % (2 * objectRange + 1));
        pos.z = rand() % 100;

        //objects.push_back(ObjectProperties{ pos, type, true });
        objects[i] = ObjectProperties{ pos, type, true };

        //lightPosition.emplace_back(ComputeLightPosition(pos, type));
        lightPosition[i] = ComputeLightPosition(pos, type);

        if (type == GIFT1 || type == GIFT2 || type == GIFT3 || type == GIFT4)
        {
            lightType[i] = 0;
            lightColor[i] = glm::vec3(1, 0, 0);
            //objects[i].position = ComputeGiftPosition(objects[i].position);
        }
        else if (type == TREE1 || type == TREE2 || type == TREE3) {
            lightType[i] = 0;
            lightColor[i] = glm::vec3(0, 1, 0);
            //objects[i].position = ComputeTreePosition(objects[i].position);
        }
        else if (type == LAMP_POST) {
            lightType[i] = 1;
            lightColor[i] = glm::vec3(0, 0, 1);
            //objects[i].position = ComputeLampPostPosition(objects[i].position);
        }

        //switch (type)
        //{
        //    case GIFT1: case GIFT2: case GIFT3: case GIFT4:
        //        /*lightType.emplace_back(0);
        //        lightColor.emplace_back(glm::vec3(1, 0, 0));*/
        //        //obj.position = ComputeGiftPosition(obj.position);
        //        lightType
        //        break;

        //    case LAMP_POST:
        //        /*lightType.emplace_back(1);
        //        lightColor.emplace_back(glm::vec3(0.98, 0.95, 0.75));*/
        //        //obj.position = ComputeLampPostPosition(obj.position);
        //        break;

        //    case TREE1: case TREE2: case TREE3:
        //        /*lightType.emplace_back(0);
        //        lightColor.emplace_back(glm::vec3(0, 1, 0));*/
        //        //obj.position = ComputeTreePosition(obj.position);
        //        break;

        //    //case ROCK:
        //        // rock case
        //        //break;

        //    default:
        //        break;
        //}
    }

    //sort(objects.begin(), objects.end(), sortFunc);

    //for (auto obj : objects) {      // am folosit auto inainte auto obj : objects
    //    //cout << obj.position.x << " " << obj.position.y << " " << obj.position.z << "\n";
    //    //obj.type = ObjectType(rand() % 8);
    //    lightPosition.emplace_back(ComputeLightPosition(obj.position, obj.type));

    //    switch (obj.type)
    //    {
    //        case GIFT1: case GIFT2: case GIFT3: case GIFT4:
    //            lightType.emplace_back(0);
    //            lightColor.emplace_back(glm::vec3(1, 0, 0));
    //            //obj.position = ComputeGiftPosition(obj.position);
    //            break;

    //        case LAMP_POST:
    //            lightType.emplace_back(1);
    //            lightColor.emplace_back(glm::vec3(0.98, 0.95, 0.75));
    //            //obj.position = ComputeLampPostPosition(obj.position);
    //            break;

    //        case TREE1: case TREE2: case TREE3:
    //            lightType.emplace_back(0);
    //            lightColor.emplace_back(glm::vec3(0, 1, 0));
    //            //obj.position = ComputeTreePosition(obj.position);
    //            break;

    //        //case ROCK:
    //            // rock case
    //            //break;

    //        default:
    //            break;
    //    }
    //}
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


glm::vec3 SkiFree::ComputeRockPosition(glm::vec3 pos)
{
    // compute position using model offset and slope angle
    glm::vec3 rockPos = pos * ROCK_SIZE_EQUIV;
    rockPos.x += ROCK_OFFSET.x;
    rockPos.y = -SLOPE_ANGLE_TAN * rockPos.z + ROCK_OFFSET.y;
    rockPos.z += ROCK_OFFSET.z;

    return rockPos;
}


glm::vec3 SkiFree::ComputeLightPosition(glm::vec3 pos, ObjectType objectType)
{
    glm::vec3 lightPos = glm::vec3(0);
    glm::vec3 objectOffset = glm::vec3(0);

    switch (objectType)
    {
        case GIFT1: case GIFT2: case GIFT3: case GIFT4:
            lightPos = glm::vec3(pos.x, -SLOPE_ANGLE_TAN * pos.z, pos.z);
            objectOffset = glm::vec3(0, .2, 0);
            break;

        case LAMP_POST:
            lightPos = glm::vec3(pos.x, -SLOPE_ANGLE_TAN * pos.z + 1.5, pos.z);
            objectOffset = glm::vec3(0, .4, .4);
            break;

        case TREE1: case TREE2: case TREE3:
            lightPos = glm::vec3(pos.x, -SLOPE_ANGLE_TAN * pos.z, pos.z);
            objectOffset = glm::vec3(0, .5, 1);
            break;

        default:
            objectOffset = glm::vec3(0);
            break;
    }

    return lightPos + objectOffset;
}


bool SkiFree::CollidesObstacle(glm::vec3 obstaclePosition, ObjectType type)
{
    float obstacleHitboxRange;
    
    switch (type)
    {
        case GIFT1: case GIFT2: case GIFT3: case GIFT4:
            obstacleHitboxRange = HITBOX_RANGE_GIFT;
            break;
    
        case LAMP_POST:
            obstacleHitboxRange = HITBOX_RANGE_LAMP_POST;
            break;
    
        case TREE1: case TREE2: case TREE3:
            obstacleHitboxRange = HITBOX_RANGE_TREE;
            break;

        /*case ROCK:
            break;*/
    
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
    //playerPos3D += translationStep;
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, SCALE_PLAYER);
    modelMatrix = glm::translate(modelMatrix, playerPos3D * PLAYER_SIZE_EQUIV);
    modelMatrix *= transform_3d::RotateOY(M_PI / 2);
    modelMatrix *= transform_3d::RotateOZ(SLOPE_ANGLE);
    modelMatrix *= transform_3d::RotateOY(playerAngle);
    RenderSimpleMesh(meshes["player"], shaders["SkiFreeShader"], modelMatrix);

    // render ground
    modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, playerPos3D);
    modelMatrix *= transform_3d::RotateOX(SLOPE_ANGLE);
    RenderSimpleMesh(meshes["terrain"], shaders["SkiFreeShader"], modelMatrix, isTerrain, mapTextures["terrain"]);

    modelMatrix = glm::mat4(1);
    modelMatrix = glm::scale(modelMatrix, SCALE_ROCK);
    modelMatrix = glm::translate(modelMatrix, ComputeRockPosition(glm::vec3(0, 0, 3)));
    //modelMatrix *= transform_3d::RotateOX(SLOPE_ANGLE);
    RenderSimpleMesh(meshes["rock"], shaders["SkiFreeShader"], modelMatrix);

   /* {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, ComputeLightPosition(giftPos[0], GIFT));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 1, 1));
        RenderSimpleMesh(meshes["sphere"], shaders["SkiFreeShader"], modelMatrix);
    }*/

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

    /*if (CollidesObstacle(treePos[0], TREE)) {
        cout << "I've been hit: " << counter++ << "\n";
    }

    if (CollidesObstacle(lampPostPos[0], LAMP_POST)) {
        cout << "I've been hit: " << counter++ << "\n";
    }

    if (CollidesObstacle(giftPos[0], GIFT)) {
        cout << "I've been hit: " << counter++ << "\n";
    }*/

    // render objects
    for (int i = 0; i < NMAX; i++) {
        // hide object if it is not visible
        /*if (!objects[i].visible) {
            continue;
        }*/

        // mark object as not visible if too far
        if (abs(playerPos3D.z - objects[i].position.z) / SLOPE_ANGLE_COS > TERRAIN_SIZE_HALF)
        {
            objects[i].visible = false;
            continue;
        }

        if (abs((playerPos3D.z - objects[i].position.z)) / SLOPE_ANGLE_COS < TERRAIN_SIZE_HALF)
        {
            objects[i].visible = true;
        }

        // render object if it is in viewport
        if (objects[i].visible) {
            //RenderObject(objects[i]);
        }
    }

    //camera->Set(playerPos3D + CAMERA_OFFSET, playerPos3D, glm::vec3(0, 1, 0));
}
    

void SkiFree::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}

void SkiFree::RenderObject(ObjectProperties obj)
{
    string meshName;

    if (obj.type == GIFT1 || obj.type == GIFT2 || obj.type == GIFT3 || obj.type == GIFT4)
    {
        switch (obj.type)
        {
            case GIFT1:
                meshName = "gift1";
                break;

            case GIFT2:
                meshName = "gift2";
                break;

            case GIFT3:
                meshName = "gift3";
                break;

            case GIFT4:
                meshName = "gift4";
                break;

            default:
                meshName = "gift1";
                break;
        }

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, SCALE_GIFT);
        modelMatrix = glm::translate(modelMatrix, ComputeGiftPosition(obj.position));
        modelMatrix *= transform_3d::RotateOX(SLOPE_ANGLE);
        RenderSimpleMesh(meshes[meshName], shaders["SkiFreeShader"], modelMatrix);
    }
    else if (obj.type == TREE1 || obj.type == TREE2 || obj.type == TREE3)
    {
        switch (obj.type)
        {
        case TREE1:
            meshName = "tree1";
            break;

        case TREE2:
            meshName = "tree2";
            break;

        case TREE3:
            meshName = "tree3";
            break;

        default:
            meshName = "tree1";
            break;
        }

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
        modelMatrix = glm::translate(modelMatrix, ComputeTreePosition(obj.position));
        RenderSimpleMesh(meshes[meshName], shaders["SkiFreeShader"], modelMatrix);
    }
    else if (obj.type == LAMP_POST)
    {
        meshName = "lamp_post";

        modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, SCALE_LAMP_POST);
        modelMatrix = glm::translate(modelMatrix, ComputeLampPostPosition(obj.position));
        modelMatrix *= transform_3d::RotateOY(M_PI / 2);
        RenderSimpleMesh(meshes["lamp_post"], shaders["SkiFreeShader"], modelMatrix);
    }
    //else if (obj.type == ROCK)
    //{
    //    // rock code
    //}
}


void SkiFree::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, bool isTerrain, Texture2D* texture)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    
    glm::vec3 eyePosition = camera->GetCameraPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    if (isTerrain) {
        glUniform1f(material_ks, TERRAIN_KS);
    }
    else {
        glUniform1f(material_ks, OBJECT_KS);
    }
    
    GLint locLight = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(locLight, NMAX, glm::value_ptr(lightPosition[0]));

   /* glm::vec3 pos = ComputeLightPosition(treePos[0], TREE);
    cout << pos.x << " " << pos.y << " " << pos.z << "\n";*/

    GLint locLightType = glGetUniformLocation(shader->program, "type_of_light");
    //glUniform1iv(locLightType, NMAX, glm::value_ptr(lightType[0])); 
    glUniform1iv(locLightType, NMAX, &(lightType[0])); // nu e spotlight (pt spotlight ar fi 1)

    GLint locLightColor = glGetUniformLocation(shader->program, "light_color");
    glUniform3fv(locLightColor, NMAX, glm::value_ptr(lightColor[0]));

    GLint locIsTerrain = glGetUniformLocation(shader->program, "is_terrain");
    glUniform1i(locIsTerrain, isTerrain);

    GLint locTranslation = glGetUniformLocation(shader->program, "translation");
    glUniform2fv(locTranslation, 1, glm::value_ptr(glm::vec2(playerPos3D.x, playerPos3D.z / glm::cos(SLOPE_ANGLE))));

    if (texture)
    {
        // activate texture location 0
        glActiveTexture(GL_TEXTURE0);

        // bind the texture1 ID
        glBindTexture(GL_TEXTURE_2D, texture->GetTextureID()); 

        // send texture uniform value
        glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
    }

    if (isTerrain)
    {
        // Draw the object
        glBindVertexArray(mesh->GetBuffers()->m_VAO);
        glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
    }
    else
    {
        mesh->Render();
    }
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

    // compute angle
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