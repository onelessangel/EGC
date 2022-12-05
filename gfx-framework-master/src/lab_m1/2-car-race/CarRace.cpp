#include "lab_m1/2-car-race/CarRace.hpp"

using namespace gfxc;
using namespace std;
using namespace m1;
using namespace transform3D;
using namespace objects;

CarRace::CarRace()
{

}

CarRace::~CarRace()
{

}

void CarRace::Init()
{
    renderCameraTarget = false;

	playerPosition = glm::vec3(-21.4, .15, 5);
	playerAngle = -M_PI_2 + .1;
	// glm::vec3(-21.4, 1, 6)

    camera = new camera_implementation::Camera();
    camera->Set(playerPosition + CAMERA_OFFSET, playerPosition - glm::vec3(0, -.15, 0), glm::vec3(0, 1, 0));

	playerPosition = glm::vec3(camera->GetTargetPosition().x, playerPosition.y, camera->GetTargetPosition().z);

    // After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    fov = RADIANS(60);
    width = 0;

    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);

	CreateObjects();
}

void CarRace::CreateObjects()
{
	Mesh* raceTrack = CreateRaceTrack("raceTrack", RACE_TRACK_COLOR);
	AddMeshToList(raceTrack);

	Mesh* skySide = CreateSky("sky_side", glm::vec3(0, 0, 0), SKY_LENGTH, SKY_HEIGHT, SKY_LIGHT_BLUE, SKY_DARK_BLUE);
	AddMeshToList(skySide);

	Mesh* skyTop = CreateSky("sky_top", glm::vec3(0, 0, 0), SKY_LENGTH, SKY_LENGTH, SKY_DARK_BLUE, SKY_DARK_BLUE);
	AddMeshToList(skyTop);

	Mesh* lightTree = new Mesh("light_tree");
	lightTree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/light_tree"), "light_tree.fbx");
	AddMeshToList(lightTree);

	Mesh* darkTree = new Mesh("dark_tree");
	darkTree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/dark_tree"), "dark_tree.fbx");
	AddMeshToList(darkTree);

	Mesh* orangeTree = new Mesh("orange_tree");
	orangeTree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/orange_tree"), "orange_tree.fbx");
	AddMeshToList(orangeTree);

	Mesh* yellowTree = new Mesh("yellow_tree");
	yellowTree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/yellow_tree"), "yellow_tree.fbx");
	AddMeshToList(yellowTree);

	Mesh* greenForest = new Mesh("green_forest");
	greenForest->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/green_forest"), "green_forest.fbx");
	AddMeshToList(greenForest);

	Mesh* autumnForest = new Mesh("autumn_forest");
	autumnForest->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/autumn_forest"), "autumn_forest.fbx");
	AddMeshToList(autumnForest);

	Mesh* grass2 = new Mesh("grass2");
	grass2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/grass/grass2"), "grass2.fbx");
	AddMeshToList(grass2);

	Mesh* player = new Mesh("player");
	player->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/race_cars/player"), "player.fbx");
	AddMeshToList(player);

	Mesh* obstacle1 = new Mesh("obstacle1");
	obstacle1->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/race_cars/obstacle1"), "obstacle1.fbx");
	AddMeshToList(obstacle1);

	Mesh* obstacle2 = new Mesh("obstacle2");
	obstacle2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/race_cars/obstacle2"), "obstacle2.fbx");
	AddMeshToList(obstacle2);

	Mesh* obstacle3 = new Mesh("obstacle3");
	obstacle3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/race_cars/obstacle3"), "obstacle3.fbx");
	AddMeshToList(obstacle3);

	// DEBUG
	Mesh* mesh = new Mesh("sphere");
	mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
	meshes[mesh->GetMeshID()] = mesh;
}

void CarRace::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void CarRace::RenderGrass() {
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0));
	RenderMesh(meshes["grass2"], shaders["Simple"], modelMatrix);
}

void CarRace::RenderRaceTrack()
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, .01, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(.8, .8, .8));
	RenderMesh(meshes["raceTrack"], shaders["VertexColor"], modelMatrix);
}

void CarRace::RenderSky()
{
	{
		modelMatrix = Translate(-SKY_LENGTH / 2, 0, -SKY_LENGTH / 2);
		RenderMesh(meshes["sky_side"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Translate(-SKY_LENGTH / 2, SKY_HEIGHT, -SKY_LENGTH / 2);
		RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = Translate(SKY_LENGTH / 2, 0, -SKY_LENGTH / 2);
		modelMatrix *= RotateOY(-M_PI_2);
		RenderMesh(meshes["sky_side"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Translate(SKY_LENGTH / 2, SKY_HEIGHT, -SKY_LENGTH / 2);
		modelMatrix *= RotateOY(-M_PI_2);
		RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = Translate(-SKY_LENGTH / 2, 0, SKY_LENGTH / 2);
		RenderMesh(meshes["sky_side"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Translate(-SKY_LENGTH / 2, SKY_HEIGHT, SKY_LENGTH / 2);
		RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = Translate(-SKY_LENGTH / 2, 0, SKY_LENGTH / 2);
		modelMatrix *= RotateOY(M_PI_2);
		RenderMesh(meshes["sky_side"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Translate(-SKY_LENGTH / 2, SKY_HEIGHT, SKY_LENGTH / 2);
		modelMatrix *= RotateOY(M_PI_2);
		RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
	}


	modelMatrix = Translate(-SKY_LENGTH / 2, SKY_HEIGHT + SKY_LENGTH, -SKY_LENGTH / 2);
	modelMatrix *= RotateOX(M_PI_2);
	RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
}

void CarRace::RenderTrees()
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(17.5, -.89, -2));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(3 * M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(13, -.89, -2));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(3 * M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(19.5, .24, -4.8));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(18, .24, -4.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(17, .24, -4.8));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(16, .24, -4.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(15, -.89, 1));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(M_PI_2);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(18, -.89, 6));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(.6);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(18, -.89, 11.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(18, -.89, 11));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-3.5);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(18, -.89, 11));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-3.5);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(9, -.89, -.58));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(M_PI_2 + 1.3);
	modelMatrix *= RotateOY(M_PI_2);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(6, -.89, -3.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-.5);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(2.6, -.89, -7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(4, .24, -7.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(2, -.89, -2.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5, .24, -7.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, .24, -6));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5, .24, -5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.5, .24, -4.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, .24, -6.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, .24, -5.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5, .24, -5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -.89, -2.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, -.89, .5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -.89, 2));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5, -.89, 6));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.1, -.89, 11));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.5, -.89, -.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-10.6, -.89, -6));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-5.5, .24, -3.6));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-7, .24, -4));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-8.5, .24, -5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-11.5, -.89, 1));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-16, -.89, 4));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-17.5, -.89, 9));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-M_PI_4 + .8);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	// ------ EXTERIOR TRACK ------

	/*modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -.89, -14));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, -.89, -12));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -.89, -9));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix)*/;
}

void CarRace::RenderEnvironment()
{
	RenderGrass();
	RenderSky();
	RenderTrees();
	RenderRaceTrack();	
}

void CarRace::RenderPlayer()
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, playerPosition);
	modelMatrix = glm::scale(modelMatrix, SCALE_CAR);
	modelMatrix *= RotateOY(playerAngle);
	RenderMesh(meshes["player"], shaders["Simple"], modelMatrix);
}

void CarRace::Update(float deltaTimeSeconds)
{
    RenderEnvironment();
    RenderPlayer();

    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }
}


void CarRace::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void CarRace::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
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

void CarRace::OnInputUpdate(float deltaTime, int mods)
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
	else {
		if (window->KeyHold(GLFW_KEY_W)) {
			camera->MoveForward(deltaTime * MOVE_SPEED);
			playerPosition.z = camera->GetTargetPosition().z;
			playerPosition.x = camera->GetTargetPosition().x;
		}
		
		if (window->KeyHold(GLFW_KEY_S)) {	
			camera->MoveForward(-deltaTime * MOVE_SPEED);
			playerPosition.z = camera->GetTargetPosition().z;
			playerPosition.x = camera->GetTargetPosition().x;
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			playerAngle += deltaTime * MOVE_SPEED;
			camera->RotateThirdPerson_OY(deltaTime * MOVE_SPEED);
		}
		
		if (window->KeyHold(GLFW_KEY_D)) {
			playerAngle -= deltaTime * MOVE_SPEED;
			camera->RotateThirdPerson_OY(-deltaTime * MOVE_SPEED);
		}
	}

    //if (window->KeyHold(GLFW_KEY_Z)) {
    //    fov += deltaTime;
    //    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 100.0f);
    //}

    //if (window->KeyHold(GLFW_KEY_X)) {
    //    fov -= deltaTime;
    //    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 100.0f);
    //}

 /*   if (window->KeyHold(GLFW_KEY_C)) {
        width += deltaTime;
        projectionMatrix = glm::ortho(-1.0f, width, -1.0f, 1.0f, 0.0f, 100.0f);
    }

    if (window->KeyHold(GLFW_KEY_V)) {
        width -= deltaTime;
        projectionMatrix = glm::ortho(width, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);
    }*/
}


void CarRace::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    ////Switch projections
    //if (key == GLFW_KEY_O)
    //{
    //    projectionMatrix = glm::ortho(-1, 1, -1, 1, 0, 100);
    //}
    //if (key == GLFW_KEY_P)
    //{
    //    projectionMatrix = glm::perspective(RADIANS(45), window->props.aspectRatio, 0.01f, 100.0f);
    //}
}


void CarRace::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void CarRace::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.002f;
        float sensivityOY = 0.002f;

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
            camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
        }
    }
}


void CarRace::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void CarRace::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void CarRace::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void CarRace::OnWindowResize(int width, int height)
{
}
