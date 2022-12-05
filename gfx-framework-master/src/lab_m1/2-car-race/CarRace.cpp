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
	RenderMesh(meshes["grass2"], glm::vec3(0, 0, 0));
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


	RenderMesh(meshes["dark_tree"], glm::vec3(19.5, .24, -4.8), SCALE_TREE);
	RenderMesh(meshes["light_tree"], glm::vec3(18, .24, -4.5), SCALE_TREE);
	RenderMesh(meshes["light_tree"], glm::vec3(17, .24, -4.8), SCALE_TREE);
	RenderMesh(meshes["dark_tree"], glm::vec3(16, .24, -4.7), SCALE_TREE);

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

	RenderMesh(meshes["light_tree"], glm::vec3(4, .24, -7.5), SCALE_TREE);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(2, -.89, -2.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	RenderMesh(meshes["dark_tree"], glm::vec3(-1.5, .24, -7.5), SCALE_TREE);
	RenderMesh(meshes["light_tree"], glm::vec3(-2, .24, -6), SCALE_TREE);
	RenderMesh(meshes["dark_tree"], glm::vec3(-2.5, .24, -5), SCALE_TREE);
	RenderMesh(meshes["light_tree"], glm::vec3(-3.5, .24, -4.5), SCALE_TREE);

	RenderMesh(meshes["light_tree"], glm::vec3(-0.5, .24, -6.5), SCALE_TREE);
	RenderMesh(meshes["dark_tree"], glm::vec3(-0.5, .24, -5.5), SCALE_TREE);
	RenderMesh(meshes["light_tree"], glm::vec3(-1.5, .24, -5), SCALE_TREE);

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

	RenderMesh(meshes["light_tree"], glm::vec3(-5.5, .24, -3.6), SCALE_TREE);
	RenderMesh(meshes["dark_tree"], glm::vec3(-7, .24, -4), SCALE_TREE);
	RenderMesh(meshes["light_tree"], glm::vec3(-8.5, .24, -5), SCALE_TREE);

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

	RenderMesh(meshes["raceTrack"], shaders["VertexColor"], glm::vec3(0, .01, 0), glm::vec3(.8, .8, .8));
}

void CarRace::RenderPlayer()
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-21.4, .15, 5));
	modelMatrix = glm::scale(modelMatrix, SCALE_CAR);
	modelMatrix *= RotateOY(-M_PI_2 + .1);
	RenderMesh(meshes["player"], shaders["Simple"], modelMatrix);
}

void CarRace::Update(float deltaTimeSeconds)
{
	RenderEnvironment();

	RenderPlayer();

	/*RenderMesh(meshes["light_tree"], glm::vec3(0, 2, 0), SCALE_TREE);
	RenderMesh(meshes["dark_tree"], glm::vec3(1, 2, 0), SCALE_TREE);
	RenderMesh(meshes["orange_tree"], glm::vec3(0, 2, 1), SCALE_TREE);
	RenderMesh(meshes["yellow_tree"], glm::vec3(2, 2, 2), SCALE_TREE);*/
	
	/*RenderMesh(meshes["autumn_forest"], glm::vec3(0, 2, 10), SCALE_TREE);*/
	
	/*RenderMesh(meshes["obstacle1"], glm::vec3(-9, .5, 0), SCALE_CAR);
	RenderMesh(meshes["obstacle2"], glm::vec3(-8, .5, 0), SCALE_CAR);
	RenderMesh(meshes["obstacle3"], glm::vec3(-7, .5, 0), SCALE_CAR);*/
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
