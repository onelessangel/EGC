#include "lab_m1/1-duck-hunt/Environment.h"
#include "lab_m1/1-duck-hunt/object2D.h"
#include "lab_m1/1-duck-hunt/transform2D.h"

using namespace std;
using namespace m1;

Environment::Environment()
{

}

Environment::~Environment()
{

}

//void Environment::Init()
//{
//	glm::ivec2 resolution = window->GetResolution();
//
//	// set camera
//	auto camera = GetSceneCamera();
//	camera->SetOrthographic(0, (GLfloat)resolution.x, 0, (GLfloat)resolution.y, 0.01f, 400);
//	camera->SetPosition(glm::vec3(0, 0, 50));
//	camera->SetRotation(glm::vec3(0, 0, 0));
//	camera->Update();
//	GetCameraInput()->SetActive(false);
//
//	CreateGround(resolution);
//}

//void Environment::FrameStart()
//{
//	// clears the color buffer (using the previously set color) and depth buffer
//	glClearColor(0, 0, 0, 1);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// sets the screen area where to draw
//	glm::ivec2 resolution = window->GetResolution();
//	glViewport(0, 0, resolution.x, resolution.y);
//}

void Environment::DrawEnvironment()
{
	glm::ivec2 resolution = window->GetResolution();



	// test
	Mesh* test = object2D::CreateSquare("test", glm::vec3(0, 0, 0), .1f, glm::vec3(1, 0, 0), true);
	AddMeshToList(test);
	RenderMesh2D(meshes["test"], shaders["VertexColor"], glm::mat3(1));








	CreateGround(resolution);
	RenderMesh2D(meshes["ground"], shaders["VertexColor"], glm::mat3(1));
}

void Environment::CreateGround(glm::ivec2 resolution)
{
	// temp ground params
	glm::vec3 corner = glm::vec3(0, 0, 0);
	GLfloat groundHeight = resolution.y;
	GLfloat groundLength = resolution.x;
	glm::vec3 color = glm::vec3(0.623, 0.404, 0.243);

	Mesh* ground = object2D::CreateRectangle("ground", corner, groundHeight, groundLength, color);
	AddMeshToList(ground);
}

//void Environment::Update(float deltaTime)
//{
//	glm::ivec2 resolution = window->GetResolution();
//
//	DrawEnvironment();
//}

//void Environment::FrameEnd()
//{
//
//}
//
//void Environment::OnInputUpdate(float deltaTime, int mods)
//{
//
//}
//
//
//void Environment::OnKeyPress(int key, int mods)
//{
//
//}
//
//
//void Environment::OnKeyRelease(int key, int mods)
//{
//	// Add key release event
//}
//
//
//void Environment::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
//{
//	// Add mouse move event
//}
//
//
//void Environment::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
//{
//	// Add mouse button press event
//}
//
//
//void Environment::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
//{
//	// Add mouse button release event
//}
//
//
//void Environment::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
//{
//
//}
//
//
//void Environment::OnWindowResize(int width, int height)
//{
//
//}