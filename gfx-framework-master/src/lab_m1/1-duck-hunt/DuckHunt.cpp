#include "DuckHunt.h"
#include "lab_m1/1-duck-hunt/Objects2D.h"
#include "Transform2D.h"

using namespace gfxc;
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

	bigTR = new gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
	bigTR->Load(window->props.selfDir + "\\assets\\fonts\\ARCADE.TTF", BIG_FONT_SIZE);

	smallTR = new gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
	smallTR->Load(window->props.selfDir + "\\assets\\fonts\\ARCADE.TTF", SMALL_FONT_SIZE);

	mediumTR = new gfxc::TextRenderer(window->props.selfDir, window->GetResolution().x, window->GetResolution().y);
	mediumTR->Load(window->props.selfDir + "\\assets\\fonts\\ARCADE.TTF", MEDIUM_FONT_SIZE);

	NewGameInit();
	CreateObjects();
}

void DuckHunt::NewGameInit()
{
	duckCount = 0;
	lifeCount = 3;
	scoreCount = 0;
	level = 1;

	showLevel = true;
	levelTime = 0;

	freezeGame = false;
	restartHover = false;
	exitHover = false;

	InitNewLevelParams();
}

void DuckHunt::InitNewLevelParams()
{
	// initialize the translation steps
	translate.x = 0;
	translate.y = 0;

	randomColor = rand() % 4 + 1;
	cout << randomColor << "\n";

	// duck is initially ACTIVE
	duckState = ACTIVE;

	moveRight = true;
	moveUp = true;

	movingInward = true;
	angularStep = 0;

	direction = 1;

	duckHover = false;
	bulletCount = 3;
	totalTime = 0;

	showAddedPoints = false;
	addedPointsTime = 0;

	// speed values
	duckSpeed = MOVE_SPEED + (level - 1) * MOVE_SPEED / 2;
	wingsSpeed = duckSpeed * 2;
}

void DuckHunt::CreateObjects()
{
	glm::vec3 corner, centerPos, color, color1, color2, color3, color4;
	float height, length;

	glm::ivec2 resolution = window->GetResolution();

	// DUCK - RECTANGLE
	corner = glm::vec3(0);
	height = TOTAL_DUCK_HEIGHT;
	length = TOTAL_DUCK_LENGTH;
	color = glm::vec3(1, 1, 1);

	Mesh* duck = Objects2D::CreateRectangle("duck", corner, height, length, color, true);
	AddMeshToList(duck);

	// DUCK - HEAD
	centerPos = glm::vec3(0);
	color = glm::vec3(0, 0.392, 0.196);

	Mesh* duckHead = Objects2D::CreateCircle("duck_head", centerPos, color, true);
	AddMeshToList(duckHead);

	// DUCK - BODY
	corner = glm::vec3(0);
	length = BODY_SIZE;
	color1 = glm::vec3(0.560, 0.290, 0.247);
	//color = glm::vec3(0, 0, 1);
	color2 = glm::vec3(0.772, 0.360, 0.086);
	color3 = glm::vec3(0.796, 0.211, 0.129);
	color4 = glm::vec3(0.423, 0.239, 0.611);

	Mesh* duckBody1 = Objects2D::CreateTriangle("duck_body1", corner, length, color1, true);
	Mesh* duckBody2 = Objects2D::CreateTriangle("duck_body2", corner, length, color2, true);
	Mesh* duckBody3 = Objects2D::CreateTriangle("duck_body3", corner, length, color3, true);
	Mesh* duckBody4 = Objects2D::CreateTriangle("duck_body4", corner, length, color4, true);

	AddMeshToList(duckBody1);
	AddMeshToList(duckBody2);
	AddMeshToList(duckBody3);
	AddMeshToList(duckBody4);

	// DUCK - LEFT WING
	corner = glm::vec3(0);
	length = L_WING_SIZE;
	color1 = glm::vec3(0.309, 0.168, 0.149);
	//color = glm::vec3(1, 0, 0);
	color2 = glm::vec3(0.584, 0.274, 0.066);
	color3 = glm::vec3(0.537, 0.145, 0.086);
	color4 = glm::vec3(0.309, 0.172, 0.447);

	Mesh* leftDuckWing1 = Objects2D::CreateTriangle("left_duck_wing1", corner, length, color1, true);
	Mesh* leftDuckWing2 = Objects2D::CreateTriangle("left_duck_wing2", corner, length, color2, true);
	Mesh* leftDuckWing3 = Objects2D::CreateTriangle("left_duck_wing3", corner, length, color3, true);
	Mesh* leftDuckWing4 = Objects2D::CreateTriangle("left_duck_wing4", corner, length, color4, true);

	AddMeshToList(leftDuckWing1);
	AddMeshToList(leftDuckWing2);
	AddMeshToList(leftDuckWing3);
	AddMeshToList(leftDuckWing4);

	// DUCK - RIGHT WING
	corner = glm::vec3(0);
	length = R_WING_SIZE;
	color1 = glm::vec3(0.309, 0.168, 0.149);
	//color = glm::vec3(1, 0, 0);
	color2 = glm::vec3(0.584, 0.274, 0.066);
	color3 = glm::vec3(0.537, 0.145, 0.086);
	color4 = glm::vec3(0.309, 0.172, 0.447);

	Mesh* rightDuckWing1 = Objects2D::CreateTriangle("right_duck_wing1", corner, length, color1, true);
	Mesh* rightDuckWing2 = Objects2D::CreateTriangle("right_duck_wing2", corner, length, color2, true);
	Mesh* rightDuckWing3 = Objects2D::CreateTriangle("right_duck_wing3", corner, length, color3, true);
	Mesh* rightDuckWing4 = Objects2D::CreateTriangle("right_duck_wing4", corner, length, color4, true);

	AddMeshToList(rightDuckWing1);
	AddMeshToList(rightDuckWing2);
	AddMeshToList(rightDuckWing3);
	AddMeshToList(rightDuckWing4);

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
	/*corner = glm::vec3(0, 0, 0);
	height = (float) resolution.y / 4;
	length = (float) resolution.x;
	color = glm::vec3(0.337, 0.184, 0.129);

	Mesh* ground = Objects2D::CreateRectangle("ground_basic", corner, height, length, color, true);
	AddMeshToList(ground);*/

	Mesh* pixelatedGround = new Mesh("pixelated_ground");
	pixelatedGround->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/pixelated_ground"), "pixelated_ground.fbx");
	meshes[pixelatedGround->GetMeshID()] = pixelatedGround;

	// GRASS
	//corner = glm::vec3(0, resolution.y / 4, 0);
	//height = (float) resolution.y / 4;
	//length = (float) resolution.x;
	//color = glm::vec3(0.047, 0.714, 0.012);

	//Mesh* grass = Objects2D::CreateRectangle("grass", corner, height, length, color, false);
	//AddMeshToList(grass);

	Mesh* pixelatedGrass = new Mesh("pixelated_grass");
	pixelatedGrass->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/pixelated_grass"), "pixelated_grass.fbx");
	meshes[pixelatedGrass->GetMeshID()] = pixelatedGrass;

	// SKY
	//corner = glm::vec3(0, resolution.y / 2, 0);
	//height = (float) resolution.y / 2;
	//length = (float) resolution.x;
	//color = glm::vec3(0.686, 0.894, 0.996);

	//Mesh* sky = Objects2D::CreateRectangle("sky", corner, height, length, color, false);
	//AddMeshToList(sky);

	Mesh* pixelatedSky = new Mesh("pixelated_sky");
	pixelatedSky->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/pixelated_sky"), "pixelated_sky.fbx");
	meshes[pixelatedSky->GetMeshID()] = pixelatedSky;


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
	length = SCORE_BOX_LENGTH;
	color = glm::vec3(0, 0, 1);

	Mesh* scoreBox = Objects2D::CreateRectangle("score_box", corner, height, length, color);
	AddMeshToList(scoreBox);

	// SCORE UNIT
	corner = glm::vec3(0, 0, 0);
	height = SMALL_OBJ_DIM2;
	length = SCORE_UNIT_LENGTH;
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

	if (lifeCount >= 1) {
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrixObj1);
	}
	
	if (lifeCount >= 2) {
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrixObj2);
	}
	
	if (lifeCount >= 3) {
		RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrixObj3);
	}
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

	if (bulletCount >= 1) {
		RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrixObj1);
	}
	
	if (bulletCount >= 2) {
		RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrixObj2);
	}
	
	if (bulletCount >= 3) {
		RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrixObj3);
	}
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
	modelMatrixObj2 *= transform2D::Translate(-SCORE_UNIT_LENGTH, 0);

	RenderMesh2D(meshes["score_box"], shaders["VertexColor"], modelMatrixObj1);

	for (int i = 0; i < scoreCount; i++) {
		modelMatrixObj2 *= transform2D::Translate(SCORE_UNIT_LENGTH, 0);
		RenderMesh2D(meshes["score_unit"], shaders["VertexColor"], modelMatrixObj2);
	}

	if (showAddedPoints) {
		smallTR->RenderText("+ 10 POINTS", 1097, 110, 1, glm::vec3(0, 0, 1));
	}
}

void DuckHunt::RenderDuck(glm::mat3 duckPosMatrix)
{
	//eyesMatrix = glm::mat3(1);
	//headMatrix = glm::mat3(1);
	//beakMatrix = glm::mat3(1);
	//bodyMatrix = glm::mat3(1);
	//leftWingMatrix = glm::mat3(1);
	//rightWingMatrix = glm::mat3(1);

	//modelMatrixObj1 = glm::mat3(1);


	// transform duck pos
	eyesMatrix = duckPosMatrix;
	headMatrix = duckPosMatrix;
	beakMatrix = duckPosMatrix;
	bodyMatrix = duckPosMatrix;
	leftWingMatrix = duckPosMatrix;
	rightWingMatrix = duckPosMatrix;

	//modelMatrixObj1 = duckPosMatrix;

	ComputeDuckRotation();

	// rotate duck in case of ESCAPING or being SHOT
	eyesMatrix *= modelMatrixObj2;
	headMatrix *= modelMatrixObj2;
	beakMatrix *= modelMatrixObj2;
	bodyMatrix *= modelMatrixObj2;
	leftWingMatrix *= modelMatrixObj2;
	rightWingMatrix *= modelMatrixObj2;


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
	RenderMesh2D(meshes["left_duck_wing" + to_string(randomColor)], shaders["VertexColor"], leftWingMatrix);
	RenderMesh2D(meshes["duck_body" + to_string(randomColor)], shaders["VertexColor"], bodyMatrix);
	RenderMesh2D(meshes["right_duck_wing" + to_string(randomColor)], shaders["VertexColor"], rightWingMatrix);

	//RenderMesh2D(meshes["duck"], shaders["VertexColor"], modelMatrixObj1);

	/*cout << "(" << translate.x << ", " << translate.y << ") ";
	cout << "(" << translate.x + TOTAL_DUCK_LENGTH << ", " << translate.y + TOTAL_DUCK_HEIGHT << ")\n";*/
}

void DuckHunt::ComputeDuckPosition(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// set starting point
	modelMatrixMain = transform2D::Translate(STARTING_POINT_X, STARTING_POINT_Y);

	switch (duckState) {
		case ACTIVE:
			if (moveRight) {
				translate.x += deltaTimeSeconds * resolution.x * RATIO_X * duckSpeed;

				if (translate.x >= resolution.x * RES_LIMIT_X) {
					moveRight = false;
				}
			}
			else {
				translate.x -= deltaTimeSeconds * resolution.x * RATIO_X * duckSpeed;

				if (translate.x <= -resolution.x * RES_LIMIT_X) {
					moveRight = true;
				}
			}

			if (moveUp) {
				translate.y += deltaTimeSeconds * resolution.y * RATIO_Y * duckSpeed;

				if (translate.y >= resolution.y * RES_LIMIT_Y) {
					moveUp = false;
				}
			}
			else {
				translate.y -= deltaTimeSeconds * resolution.y * RATIO_Y * duckSpeed;

				if (translate.y <= resolution.y / 4) {
					moveUp = true;
				}
			}
			break;

		case SHOT:
			translate.y -= deltaTimeSeconds * resolution.y * RATIO_Y * duckSpeed;

			if (translate.y <= resolution.y / 4 - TOTAL_DUCK_HEIGHT) {
				duckState = GONE;
			}
			break;

		case ESCAPING:
			translate.y += deltaTimeSeconds * resolution.y * RATIO_Y * duckSpeed;

			if (translate.y >= resolution.y) {
				duckState = GONE;
				hasEscaped = true;
				cout << "duck has escaped\n";
			}
			break;
	}
	
	modelMatrixMain *= transform2D::Translate(translate.x, translate.y);
}

void DuckHunt::ComputeDuckRotation()
{
	switch (duckState) {
		case SHOT:
			if (moveRight) {
				modelMatrixObj2 = transform2D::Rotate(-M_PI_2);
			}
			else {
				modelMatrixObj2 = transform2D::Translate(TOTAL_DUCK_LENGTH, -TOTAL_DUCK_HEIGHT);
				modelMatrixObj2 *= transform2D::Rotate(M_PI_2);
			}
			leftWingPosMatrix = glm::mat3(1);
			rightWingPosMatrix = glm::mat3(1);
			break;

		case ESCAPING:
			if (moveRight) {
				modelMatrixObj2 = transform2D::Translate(TOTAL_DUCK_LENGTH, 0);
				modelMatrixObj2 *= transform2D::Rotate(M_PI_2);
			}
			else {
				modelMatrixObj2 = transform2D::Translate(0, TOTAL_DUCK_LENGTH);
				modelMatrixObj2 *= transform2D::Rotate(-M_PI_2);
			}
			break;

		default:
			modelMatrixObj2 = glm::mat3(1);
			break;
	}
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
		angularStep += deltaTimeSeconds * wingsSpeed;
	}
	else {
		angularStep -= deltaTimeSeconds * wingsSpeed;
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

	leftWingPosMatrix = transform2D::Translate(leftWingPosX, leftWingPosY);
	leftWingPosMatrix *= transform2D::Rotate(angularStep * direction);
	leftWingPosMatrix *= transform2D::Translate(-leftWingPosX, -leftWingPosY);

	rightWingPosMatrix = transform2D::Translate(rightWingPosX, rightWingPosY);
	rightWingPosMatrix *= transform2D::Rotate(-angularStep * direction);
	rightWingPosMatrix *= transform2D::Translate(-rightWingPosX, -rightWingPosY);
}

void DuckHunt::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();

	// functie gestionare timp
	totalTime += deltaTimeSeconds;
	cout << totalTime << "\n";
	cout << duckSpeed << "\n";
	cout << duckCount << "\n";

	if (showAddedPoints) {
		addedPointsTime += deltaTimeSeconds;
	}

	if (showLevel) {
		levelTime += deltaTimeSeconds;
	}

	//RenderMesh(meshes["sky"], shaders["VertexColor"], glm::vec3(0, 0, -200), glm::vec3(1, 1, 1));
	RenderMesh(meshes["pixelated_sky"], glm::vec3(625, 550, -200), glm::vec3(550, 380, 0));
	RenderMesh(meshes["pixelated_grass"], glm::vec3(650, 270, 0), glm::vec3(200, 180, 0));
	//RenderMesh(meshes["grass"], shaders["VertexColor"], glm::vec3(0, 0, 5), glm::vec3(1, 1, 1));
	//RenderMesh(meshes["ground_basic"], shaders["VertexColor"], glm::vec3(0, 0, 5), glm::vec3(1, 1, 1));
	RenderMesh(meshes["pixelated_ground"], glm::vec3(650, 100, 0), glm::vec3(220, 200, 0));

	if (totalTime >= TIME_LIMIT && duckState == ACTIVE) {
		duckState = ESCAPING;
	}

	if (duckState == GONE) {
		if (hasEscaped) {
			lifeCount--;
		}

		duckCount++;

		if (duckCount % 4 == 0 && duckCount < MAX_SCORE) {
			level++;

			showLevel = true;
			levelTime = 0;
		}

		InitNewLevelParams();
	}

	if (showLevel) {
		bigTR->RenderText("LEVEL " + to_string(level), resolution.x / 2 - 150, resolution.y / 2 - 100, 1, glm::vec3(0, 0, 1));
	}

	hasEscaped = false;

	if (bulletCount == 0 && duckState == ACTIVE) {
		duckState = ESCAPING;
	}
	else {
		RenderBullets();
	}

	RenderLives();
	RenderScore();

	if (addedPointsTime >= SHOW_POINTS_TIME) {
		showAddedPoints = false;
		addedPointsTime = 0;
	}

	if (levelTime >= LEVEL_TIME) {
		showLevel = false;	
		levelTime = 0;
	}

	if (duckCount == MAX_SCORE || lifeCount == 0) {
		bigTR->RenderText("GAME OVER", resolution.x / 2 - 200, resolution.y / 2 - 250, 1, glm::vec3(0, 0, 1));
		mediumTR->RenderText("Your score: " + to_string(scoreCount * 10), resolution.x / 2 - 225, resolution.y / 2 - 150, 1, glm::vec3(0, 0, .502));

		if (restartHover) {
			mediumTR->RenderText(">TRY AGAIN", resolution.x / 2 - 155, resolution.y / 2 - 75, .5f, glm::vec3(0, 0, 1));
		}
		else {
			mediumTR->RenderText("TRY AGAIN", resolution.x / 2 - 150, resolution.y / 2 - 75, .5f, glm::vec3(0, 0, 1));
		}
		

		if (exitHover) {
			mediumTR->RenderText(">EXIT", resolution.x / 2 + 120, resolution.y / 2 - 75, .5f, glm::vec3(0, 0, 1));
		}
		else {
			mediumTR->RenderText("EXIT", resolution.x / 2 + 125, resolution.y / 2 - 75, .5f, glm::vec3(0, 0, 1));
		}
		

		bulletCount = 3;
		freezeGame = true;
	}

	if (!freezeGame) {
		ComputeDuckPosition(deltaTimeSeconds);
		ComputeWingsPosition(deltaTimeSeconds);
		RenderDuck(modelMatrixMain);
	}

	//RenderMesh2D(meshes["ground_basic"], shaders["VertexColor"], glm::mat3(1));
	//RenderMesh2D(meshes["grass"], shaders["VertexColor"], glm::mat3(1));
	//RenderMesh2D(meshes["sky"], shaders["VertexColor"], glm::mat3(1));
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
	glm::ivec2 resolution = window->GetResolution();

	duckHover = false;

	currPosX = mouseX + deltaX;
	currPosY = mouseY + deltaY;

	if (!freezeGame) {
		if (duckState == ACTIVE) {
			leftDownCornerX = translate.x + STARTING_POINT_X;
			leftDownCornerY = resolution.y - STARTING_POINT_Y - translate.y;
			rightUpCornerX = translate.x + STARTING_POINT_X + TOTAL_DUCK_LENGTH;
			rightUpCornerY = resolution.y - STARTING_POINT_Y - (translate.y + TOTAL_DUCK_HEIGHT);

			if (currPosX >= leftDownCornerX && currPosX <= rightUpCornerX &&
				currPosY <= leftDownCornerY && currPosY >= rightUpCornerY) {
				duckHover = true;
				//cout << "mouse is over duck\n";
			}
		}


		if (duckState == ESCAPING) {
			leftDownCornerX = translate.x + STARTING_POINT_X + TOTAL_DUCK_HEIGHT;
			leftDownCornerY = resolution.y - (translate.y + STARTING_POINT_Y);
			rightUpCornerX = translate.x + STARTING_POINT_X - TOTAL_DUCK_HEIGHT;
			rightUpCornerY = resolution.y - STARTING_POINT_Y - (translate.y + TOTAL_DUCK_LENGTH);

			if (currPosX >= rightUpCornerX && currPosX <= leftDownCornerX &&
				currPosY <= leftDownCornerY && currPosX >= rightUpCornerY) {
				duckHover = true;
				//cout << "mouse is over duck\n";
			}
		}

		return;
	}

	leftDownCornerX = 490;
	leftDownCornerY = 304;
	rightUpCornerX = 665;
	rightUpCornerY = 270;

	cout << currPosX << " " << currPosY << "\n";

	if (currPosX >= leftDownCornerX && currPosX <= rightUpCornerX &&
		currPosY <= leftDownCornerY && currPosY >= rightUpCornerY) {
		restartHover = true;
		cout << "mouse is over button\n";
	}
	else {
		restartHover = false;
	}

	leftDownCornerX = 760;
	leftDownCornerY = 304;
	rightUpCornerX = 830;
	rightUpCornerY = 280;

	if (currPosX >= leftDownCornerX && currPosX <= rightUpCornerX &&
		currPosY <= leftDownCornerY && currPosY >= rightUpCornerY) {
		exitHover = true;
		cout << "mouse is over button\n";
	}
	else {
		exitHover = false;
	}
}


void DuckHunt::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
		if (freezeGame) {
			if (restartHover) {
				NewGameInit();
			}

			if (exitHover) {
				exit(0);
			}

			return;
		}

		if (duckHover && duckState != SHOT && bulletCount > 0) {
			duckState = SHOT;
			cout << "I've been shot\n";

			scoreCount++;

			showAddedPoints = true;
		}

		bulletCount--;
	}
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
