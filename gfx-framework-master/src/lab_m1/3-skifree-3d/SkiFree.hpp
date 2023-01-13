#pragma once

#include <iostream>
#include <cmath>

#include "components/simple_scene.h"
#include "components/text_renderer.h"
#include "glm/gtx/vector_angle.hpp"

#include "lab_m1/3-skifree-3d/Camera.hpp"
#include "lab_m1/3-skifree-3d/Transform3D.hpp"

#define NMAX					200	// 500

#define CAMERA_OFFSET			glm::vec3(0, 4, 10)
#define CAMERA_SPEED			6.f	// 4.5
#define CAMERA_SENSITIVITY_OX	.002f
#define CAMERA_SENSITIVITY_OY	.002f

#define BIG_FONT_SIZE			100
#define MEDIUM_FONT_SIZE		75

#define MOVEMENT_SPEED			glm::vec3(1.4, 0, 1)

#define SCALE_PLAYER			glm::vec3(.003, .003, .003)
#define PLAYER_SIZE_EQUIV		(1 / SCALE_PLAYER.x)

#define SCALE_TREE				glm::vec3(.01, .01, .01)
#define TREE_SIZE_EQUIV			(1 / SCALE_TREE.x)
#define TREE_OFFSET				(glm::vec3(.27, .6, -.1) * TREE_SIZE_EQUIV)

#define SCALE_LAMP_POST			glm::vec3(.01, .01, .01)
#define LAMP_POST_SIZE_EQUIV	(1 / SCALE_LAMP_POST.x)
#define LAMP_POST_OFFSET		(glm::vec3(0, 0, 0) * LAMP_POST_SIZE_EQUIV)

#define SCALE_GIFT				glm::vec3(.004, .004, .004)
#define GIFT_SIZE_EQUIV			(1 / SCALE_GIFT.x)
#define GIFT_OFFSET				(glm::vec3(0, .2, 0) * GIFT_SIZE_EQUIV)

#define SCALE_ROCK				glm::vec3(.007, .007, .007)
#define ROCK_SIZE_EQUIV			(1 / SCALE_ROCK.x)
#define ROCK_OFFSET				(glm::vec3(0, .2, 0) * ROCK_SIZE_EQUIV)

#define TERRAIN_SIZE			50
#define TERRAIN_SIZE_HALF		(TERRAIN_SIZE / 2)

#define MAX_PLAYER_ANGLE		M_PI_2
#define SLOPE_ANGLE				(M_PI / 4)
#define SLOPE_ANGLE_TAN			glm::tan(SLOPE_ANGLE)
#define SLOPE_ANGLE_COS			glm::cos(SLOPE_ANGLE)

#define HITBOX_RANGE_PLAYER		.18f
#define HITBOX_RANGE_TREE		.275f
#define HITBOX_RANGE_LAMP_POST	.075f
#define HITBOX_RANGE_GIFT		.2f
#define HITBOX_RANGE_ROCK		.25f

#define OBJECT_KS				.5
#define TERRAIN_KS				0

namespace m1
{
	class SkiFree : public gfxc::SimpleScene
	{
	public:
		SkiFree();
		~SkiFree();

		void Init() override;

	protected:
		enum ObjectType { TREE1, TREE2, TREE3, LAMP_POST1, LAMP_POST2, GIFT1, GIFT2, GIFT3, GIFT4, ROCK1, ROCK2}; // de adaugat piatra

	public:
		struct ObjectProperties
		{
			glm::vec3 position;
			ObjectType type;
			bool visible;
			bool collected;
		};

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void CreateObjects();
		void CreateShaders();
		void LoadTextures();

		void NewGameInit();
		void GenerateRandomObjects();

		void UpdateTranslationStep(float deltaTimeSeconds);
		glm::vec3 ComputeTreePosition(glm::vec3 pos);
		glm::vec3 ComputeLampPostPosition(glm::vec3 pos);
		glm::vec3 ComputeGiftPosition(glm::vec3 pos);
		glm::vec3 ComputeRockPosition(glm::vec3 pos);
		glm::vec3 ComputeLightPosition(glm::vec3 pos, ObjectType objectType);

		void RenderPlayer();
		void RenderGround();
		void RenderObjects();
		void RenderSingleObject(ObjectProperties obj);
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, bool isTerrain = false, Texture2D* texture1 = NULL);

		bool CollidesObstacle(glm::vec3 obstaclePosition, ObjectType type);
		void CheckCollision(ObjectProperties* obj, int pos);

	protected:
		skifree_camera::Camera *camera;
		glm::mat4 projectionMatrix;
		GLfloat fov, width;
		glm::ivec2 resolution;

		glm::mat4 modelMatrix;
		std::unordered_map<std::string, Texture2D*> mapTextures;
		
		glm::vec2 currPos, playerPos, verticalDir, mouseDir;
		float playerAngle, prevAngle;

		ObjectProperties objects[NMAX];
		glm::vec3 lightPosition[NMAX];
		int lightType[NMAX];			// POINT - 0; SPOT - 1; INVISIBLE - 2
		glm::vec3 lightColor[NMAX];

		glm::vec3 playerPos3D;
		glm::vec3 translationStep;

		bool isTerrain;

		int score, maxScore;
		bool freezeGame;
		bool newHighScore;
	};

}	// namespace m1