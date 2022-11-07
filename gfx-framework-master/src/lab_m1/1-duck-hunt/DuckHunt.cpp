#include "DuckHunt.h"
#include "lab_m1/1-duck-hunt/Objects2D.h"
#include "Transform2D.h"

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

	movingInward = true;
	angularStep = 0;

	direction = 1;

	CreateObjects();
}

void DuckHunt::CreateObjects()
{
	glm::vec3 corner, centerPos, color;
	float height, length;

	glm::ivec2 resolution = window->GetResolution();

	// DUCK - SQUARE
	corner = glm::vec3(0);
	length = TOTAL_DUCK_SIZE;
	color = glm::vec3(1, 1, 1);

	Mesh* duck = Objects2D::CreateSquare("duck", corner, length, color, true);
	AddMeshToList(duck);

	// DUCK - HEAD
	centerPos = glm::vec3(0);
	color = glm::vec3(0, 0.392, 0.196);

	Mesh* duckHead = Objects2D::CreateCircle("duck_head", centerPos, color, true);
	AddMeshToList(duckHead);

	// DUCK - BODY
	corner = glm::vec3(0);
	length = BODY_SIZE;
	//color = glm::vec3(0.309, 0.168, 0.149);
	color = glm::vec3(0, 0, 1);

	Mesh* duckBody = Objects2D::CreateTriangle("duck_body", corner, length, color, true);
	AddMeshToList(duckBody);

	// DUCK - LEFT WING
	corner = glm::vec3(0);
	length = L_WING_SIZE;
	//color = glm::vec3(0.309, 0.168, 0.149);
	color = glm::vec3(1, 0, 0);

	Mesh* leftDuckWing = Objects2D::CreateTriangle("left_duck_wing", corner, length, color, true);
	AddMeshToList(leftDuckWing);

	// DUCK - RIGHT WING
	corner = glm::vec3(0);
	length = R_WING_SIZE;
	//color = glm::vec3(0.309, 0.168, 0.149);
	color = glm::vec3(1, 0, 0);

	Mesh* rightDuckWing = Objects2D::CreateTriangle("right_duck_wing", corner, length, color, true);
	AddMeshToList(rightDuckWing);

	// DUCK - BEAK
	corner = glm::vec3(0);
	length = BEAK_SIZE;
	color = glm::vec3(0.949, 0.733, 0.156);

	Mesh* duckBeak = Objects2D::CreateTriangle("duck_beak", corner, length, color, true);
	AddMeshToList(duckBeak);

	// DUCK - EYES
	centerPos = glm::vec3(0);
	color = glm::vec3(0);

	Mesh* duckEyes = Objects2D::CreateCircle("duck_eyes", centerPos, color, true);
	AddMeshToList(duckEyes);

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

	// LIFE
	centerPos = glm::vec3(0);
	color = glm::vec3(1, 0, 0);

	Mesh* life = Objects2D::CreateCircle("life", centerPos, color, true);
	AddMeshToList(life);

	// BULLET
	corner = glm::vec3(0);
	height = SMALL_OBJ_DIM2;
	length = SMALL_OBJ_DIM;
	color = glm::vec3(0.090, 0.623, 0.015);

	Mesh* bullet = Objects2D::CreateRectangle("bullet", corner, height, length, color, true);
	AddMeshToList(bullet);

	// SCORE BOX
	corner = glm::vec3(0);
	height = SMALL_OBJ_DIM2;
	length = 200;
	color = glm::vec3(0, 0, 1);

	Mesh* scoreBox = Objects2D::CreateRectangle("score_box", corner, height, length, color);
	AddMeshToList(scoreBox);

	// SCORE UNIT
	corner = glm::vec3(0, 0, 0);
	height = SMALL_OBJ_DIM2;
	length = 10;
	color = glm::vec3(0.043, 0.513, 0.768);

	Mesh* scoreUnit = Objects2D::CreateRectangle("score_unit", corner, height, length, color, true);
	AddMeshToList(scoreUnit);
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

void DuckHunt::RenderLives()
{
	modelMatrixMain = transform2D::Translate(1090, 680);
	modelMatrixMain *= transform2D::Scale(SMALL_OBJ_DIM, SMALL_OBJ_DIM);

	// init pos
	modelMatrixObj1 = glm::mat3(1);
	modelMatrixObj2 = transform2D::Translate(SMALL_OBJ_DIM2 + SMALL_OBJ_DIM, 0);
	modelMatrixObj3 = transform2D::Translate(2 * (SMALL_OBJ_DIM2 + SMALL_OBJ_DIM), 0);

	// screen pos
	modelMatrixObj1 *= modelMatrixMain;
	modelMatrixObj2 *= modelMatrixMain;
	modelMatrixObj3 *= modelMatrixMain;

	RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrixObj1);
	RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrixObj2);
	RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrixObj3);
}

void DuckHunt::RenderBullets()
{
	modelMatrixMain = transform2D::Translate(1195, 667);	// 680 - LIFE_RADIUS

	// init pos
	modelMatrixObj1 = glm::mat3(1);
	modelMatrixObj2 = transform2D::Translate(SMALL_OBJ_DIM2, 0);
	modelMatrixObj3 = transform2D::Translate(2 * SMALL_OBJ_DIM2, 0);

	// screen pos
	modelMatrixObj1 *= modelMatrixMain;
	modelMatrixObj2 *= modelMatrixMain;
	modelMatrixObj3 *= modelMatrixMain;

	RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrixObj1);
	RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrixObj2);
	RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrixObj3);
}

void DuckHunt::RenderScore()
{
	modelMatrixMain = transform2D::Translate(1070, 667 - SMALL_OBJ_DIM2 - SMALL_OBJ_DIM);	 // 1087 = 1100 (life) - 13 (small_dim)

	// init pos
	modelMatrixObj1 = glm::mat3(1);
	modelMatrixObj2 = glm::mat3(1);

	// screen pos
	modelMatrixObj1 *= modelMatrixMain;
	modelMatrixObj2 *= modelMatrixMain;

	RenderMesh2D(meshes["score_box"], shaders["VertexColor"], modelMatrixObj1);
	RenderMesh2D(meshes["score_unit"], shaders["VertexColor"], modelMatrixObj2);
}

void DuckHunt::RenderDuck(glm::mat3 duckPosMatrix, glm::mat3 leftWingPosMatrix, glm::mat3 rightWingPosMatrix)
{
	/*eyesMatrix = glm::mat3(1);
	headMatrix = glm::mat3(1);
	beakMatrix = glm::mat3(1);
	bodyMatrix = glm::mat3(1);
	leftWingMatrix = glm::mat3(1);
	rightWingMatrix = glm::mat3(1);*/

	// transform duck pos
	eyesMatrix = duckPosMatrix;
	headMatrix = duckPosMatrix;
	beakMatrix = duckPosMatrix;
	bodyMatrix = duckPosMatrix;
	leftWingMatrix = duckPosMatrix;
	rightWingMatrix = duckPosMatrix;

	// rotate wings
	leftWingMatrix *= leftWingPosMatrix;
	rightWingMatrix *= rightWingPosMatrix;

	// reassemble the duck

	// EYES
	if (moveRight) {
		eyesMatrix *= transform2D::Translate(EYES_RIGHT_X, EYES_RIGHT_Y);
	}
	else {
		eyesMatrix *= transform2D::Translate(EYES_LEFT_X, EYES_LEFT_Y);
	}
	eyesMatrix *= transform2D::Scale(EYES_SIZE, EYES_SIZE);
	

	// HEAD
	if (moveRight) {
		headMatrix *= transform2D::Translate(HEAD_RIGHT_X, HEAD_RIGHT_Y);
	}
	else {
		headMatrix *= transform2D::Translate(HEAD_LEFT_X, HEAD_LEFT_Y);
	}
	headMatrix *= transform2D::Scale(HEAD_SIZE, HEAD_SIZE);

	// BEAK
	if (moveRight) {
		beakMatrix *= transform2D::Translate(BEAK_RIGHT_X, BEAK_RIGHT_Y);
		beakMatrix *= transform2D::Rotate(M_PI_4 - .3);
	}
	else {
		beakMatrix *= transform2D::Translate(BEAK_LEFT_X, BEAK_LEFT_Y);
		beakMatrix *= transform2D::Rotate(M_PI_4 + .3);
	}

	// BODY
	if (moveRight) {
		bodyMatrix *= transform2D::Translate(BODY_RIGHT_X, BODY_RIGHT_Y);
	}
	else {
		bodyMatrix *= transform2D::Translate(BODY_LEFT_X, BODY_LEFT_Y);
	}
	bodyMatrix *= transform2D::Rotate(M_PI_4);

	// LEFT WING
	if (moveRight) {
		leftWingMatrix *= transform2D::Translate(LEFT_WING_RIGHT_X, LEFT_WING_RIGHT_Y);
	}
	else {
		leftWingMatrix *= transform2D::Translate(LEFT_WING_LEFT_X, LEFT_WING_LEFT_Y);
		leftWingMatrix *= transform2D::Rotate(M_PI_2);
	}

	// RIGHT WING
	if (moveRight) {
		rightWingMatrix *= transform2D::Translate(RIGHT_WING_RIGHT_X, RIGHT_WING_RIGHT_Y);
		rightWingMatrix *= transform2D::Rotate(M_PI_2);
	}
	else {
		rightWingMatrix *= transform2D::Translate(RIGHT_WING_LEFT_X, RIGHT_WING_LEFT_Y);
	}

	// render the duck
	RenderMesh2D(meshes["duck_eyes"], shaders["VertexColor"], eyesMatrix);
	RenderMesh2D(meshes["duck_head"], shaders["VertexColor"], headMatrix);
	RenderMesh2D(meshes["duck_beak"], shaders["VertexColor"], beakMatrix);
	RenderMesh2D(meshes["left_duck_wing"], shaders["VertexColor"], leftWingMatrix);
	RenderMesh2D(meshes["duck_body"], shaders["VertexColor"], bodyMatrix);
	RenderMesh2D(meshes["right_duck_wing"], shaders["VertexColor"], rightWingMatrix);
}

void DuckHunt::ComputeDuckPosition(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// set starting point
	modelMatrixMain = transform2D::Translate(resolution.x / 2 - 150 / 2, resolution.y / 4);

	// dc e rezolutia relativa la starting modelMatrix??

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

	modelMatrixMain *= transform2D::Translate(translate.x, translate.y);
}

void DuckHunt::ComputeWingsPosition(float deltaTimeSeconds)
{
	if (angularStep > MAX_ANGLE) {
		movingInward = false;
	}
	else if (angularStep < 0) {
		movingInward = true;
	}

	if (movingInward) {
		angularStep += deltaTimeSeconds * MOVE_SPEED_WINGS;
	}
	else {
		angularStep -= deltaTimeSeconds * MOVE_SPEED_WINGS;
	}

	if (moveRight) {
		leftWingPosX = LEFT_WING_RIGHT_X + L_WING_SIZE;
		leftWingPosY = LEFT_WING_RIGHT_Y;

		rightWingPosX = RIGHT_WING_RIGHT_X;
		rightWingPosY = RIGHT_WING_RIGHT_Y + R_WING_SIZE;

		direction = RIGHT_DIRECTION;
	}
	else {
		leftWingPosX = LEFT_WING_LEFT_X - L_WING_SIZE;
		leftWingPosY = LEFT_WING_LEFT_Y;

		rightWingPosX = RIGHT_WING_LEFT_X;
		rightWingPosY = RIGHT_WING_RIGHT_Y + R_WING_SIZE;

		direction = LEFT_DIRECTION;
	}

	leftWingPosMatrix = glm::mat3(1);
	leftWingPosMatrix *= transform2D::Translate(leftWingPosX, leftWingPosY);
	leftWingPosMatrix *= transform2D::Rotate(angularStep * direction);
	leftWingPosMatrix *= transform2D::Translate(-leftWingPosX, -leftWingPosY);

	rightWingPosMatrix = glm::mat3(1);
	rightWingPosMatrix *= transform2D::Translate(rightWingPosX, rightWingPosY);
	rightWingPosMatrix *= transform2D::Rotate(-angularStep * direction);
	rightWingPosMatrix *= transform2D::Translate(-rightWingPosX, -rightWingPosY);
}

void DuckHunt::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	RenderLives();
	RenderBullets();
	RenderScore();

	RenderMesh2D(meshes["ground"], shaders["VertexColor"], glm::mat3(1));
	RenderMesh2D(meshes["grass"], shaders["VertexColor"], glm::mat3(1));


	ComputeDuckPosition(deltaTimeSeconds);
	ComputeWingsPosition(deltaTimeSeconds);
	RenderDuck(modelMatrixMain, leftWingPosMatrix, rightWingPosMatrix);
	

	//RenderMesh2D(meshes["duck"], shaders["VertexColor"], glm::mat3(1));

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
