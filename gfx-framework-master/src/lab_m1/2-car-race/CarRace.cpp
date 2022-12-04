#include "lab_m1/2-car-race/CarRace.hpp"

using namespace gfxc;
using namespace std;
using namespace m1;
using namespace objects;

CarRace::CarRace()
{

}

CarRace::~CarRace()
{

}

void CarRace::Init()
{
	Mesh *raceTrack = CreateRaceTrack("raceTrack", glm::vec3(0.3113208, 0.1450872, 0.1450872));
	AddMeshToList(raceTrack);

	Mesh* grass = CreateGrass("grass", glm::vec3(-GRASS_SIZE / 2, 0, -GRASS_SIZE / 2), GRASS_SIZE, glm::vec3(0, 1, 0));
	AddMeshToList(grass);

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

void CarRace::Update(float deltaTimeSeconds)
{
	/*glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);*/

	RenderMesh(meshes["raceTrack"], shaders["VertexColor"], glm::vec3(0, .01, 0), glm::vec3(.8, .8, .8));
	//RenderMesh(meshes["grass"], shaders["VertexColor"], glm::vec3(0, 0, 0));
	RenderMesh(meshes["light_tree"], glm::vec3(0, 2, 0), glm::vec3(.01, .01, .01));
	RenderMesh(meshes["dark_tree"], glm::vec3(1, 2, 0), glm::vec3(.01, .01, .01));
	RenderMesh(meshes["orange_tree"], glm::vec3(0, 2, 1), glm::vec3(.01, .01, .01));
	RenderMesh(meshes["yellow_tree"], glm::vec3(2, 2, 2), glm::vec3(.01, .01, .01));
	RenderMesh(meshes["green_forest"], glm::vec3(10, 0, 0), glm::vec3(.01, .01, .01));
	RenderMesh(meshes["autumn_forest"], glm::vec3(0, 2, 10), glm::vec3(.01, .01, .01));
	RenderMesh(meshes["grass2"], glm::vec3(0, 0, 0));
}

void CarRace::FrameEnd()
{
	DrawCoordinateSystem();
}

void CarRace::OnInputUpdate(float deltaTime, int mods)
{

}


void CarRace::OnKeyPress(int key, int mods)
{

}


void CarRace::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void CarRace::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	
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
