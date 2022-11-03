#include "DuckHunt.h"
#include "lab_m1/1-duck-hunt/Objects2D.h"
#include "transform2D.h"
//#include "lab_m1/1-duck-hunt/Environment.h"

using namespace std;
using namespace m1;

DuckHunt::DuckHunt()
{

}

DuckHunt::~DuckHunt()
{

}

void DuckHunt::Init()
{
	glm::ivec2 resolution = window->GetResolution();

	// set camera
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (GLfloat)resolution.x, 0, (GLfloat)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// initialize the translation steps
	translate.x = 0;
	translate.y = 0;

	// duck is initially ACTIVE
	duckState = DuckState::ACTIVE;

	moveRight = true;
	moveUp = true;

	CreateObjects();
}

void DuckHunt::CreateObjects()
{
	glm::vec3 corner, color;
	float height, length;

	glm::ivec2 resolution = window->GetResolution();

	// DUCK
	corner = glm::vec3(0, 0, 0);
	length = 150;
	color = glm::vec3(0, 0.392, 0.196);

	Mesh* duck = Objects2D::CreateSquare("duck", corner, length, color, true);
	AddMeshToList(duck);

	// GROUND
	corner = glm::vec3(0, 0, 0);
	height = (float) resolution.y / 4;
	length = (float) resolution.x;
	color = glm::vec3(0.337, 0.184, 0.129);

	Mesh* ground = Objects2D::CreateRectangle("ground", corner, height, length, color, true);
	AddMeshToList(ground);

	// GRASS
	corner = glm::vec3(0, resolution.y / 4, 0);
	height = (float) resolution.y / 4;
	length = (float) resolution.x;
	color = glm::vec3(0.047, 0.714, 0.012);

	Mesh* grass = Objects2D::CreateRectangle("grass", corner, height, length, color);
	AddMeshToList(grass);

	// SKY
	corner = glm::vec3(0, resolution.y / 2, 0);
	height = (float) resolution.y / 2;
	length = (float) resolution.x;
	color = glm::vec3(0.686, 0.894, 0.996);

	Mesh* sky = Objects2D::CreateRectangle("sky", corner, height, length, color, true);
	AddMeshToList(sky);
}

void DuckHunt::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void DuckHunt::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	//Environment* environment = new m1::Environment();
	//environment->DrawEnvironment();

	RenderMesh2D(meshes["ground"], shaders["VertexColor"], glm::mat3(1));
	RenderMesh2D(meshes["grass"], shaders["VertexColor"], glm::mat3(1));

	{
		// set starting point
		modelMatrix = transform2D::Translate(resolution.x / 2 - 150 / 2, resolution.y / 4);

		// dc e resolutia relativa la starting modelMatrix??

		if (moveRight) {
			translate.x += deltaTimeSeconds * resolution.x * RATIO_X * MOVE_SPEED;
			
			if (translate.x >= resolution.x * RES_LIMIT_X) {
				moveRight = false;
			}
		}
		else {
			translate.x -= deltaTimeSeconds * resolution.x * RATIO_X * MOVE_SPEED;

			if (translate.x <= -resolution.x * RES_LIMIT_X) {
				moveRight = true;
			}
		}

		if (moveUp) {
			translate.y += deltaTimeSeconds * resolution.y * RATIO_Y * MOVE_SPEED;

			if (translate.y >= resolution.y * RES_LIMIT_Y) {
				moveUp = false;
			}
		}
		else {
			translate.y -= deltaTimeSeconds * resolution.y * RATIO_Y * MOVE_SPEED;

			if (translate.y <= resolution.y / 4) {
				moveUp = true;
			}
		}

		modelMatrix *= transform2D::Translate(translate.x, translate.y);
		RenderMesh2D(meshes["duck"], shaders["VertexColor"], modelMatrix);
	}

	RenderMesh2D(meshes["sky"], shaders["VertexColor"], glm::mat3(1));
}

void DuckHunt::FrameEnd()
{

}

void DuckHunt::OnInputUpdate(float deltaTime, int mods)
{

}


void DuckHunt::OnKeyPress(int key, int mods)
{

}


void DuckHunt::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void DuckHunt::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event
}


void DuckHunt::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void DuckHunt::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void DuckHunt::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}


void DuckHunt::OnWindowResize(int width, int height)
{

}
