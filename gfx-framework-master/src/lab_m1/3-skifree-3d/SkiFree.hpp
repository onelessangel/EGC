#pragma once

#include <iostream>
#include <cmath>

#include "components/simple_scene.h"
#include "components/text_renderer.h"
#include "glm/gtx/vector_angle.hpp"

#include "lab_m1/3-skifree-3d/Camera.hpp"
#include "lab_m1/3-skifree-3d/Transform3D.hpp"

#define CAMERA_OFFSET			glm::vec3(0, 4, 10)
#define CAMERA_SPEED			4.5f
#define CAMERA_SENSITIVITY_OX	.002f
#define CAMERA_SENSITIVITY_OY	.002f

#define MOVEMENT_SPEED			glm::vec3(.3, 0, .3)

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

#define MAX_PLAYER_ANGLE		M_PI_2
#define SLOPE_ANGLE				(M_PI / 4)
//#define SLOPE_ANGLE				0
#define SLOPE_ANGLE_TAN			glm::tan(SLOPE_ANGLE)

#define HITBOX_RANGE_PLAYER		.18f
#define HITBOX_RANGE_TREE		.275f
#define HITBOX_RANGE_LAMP_POST	.075f
#define HITBOX_RANGE_GIFT		.2f

//#define HITBOX_PLAYER			(glm::vec3(.36, 0, 1.25) * .5f)
//#define HITBOX_TREE				(glm::vec3(.5, 0, .55)	 * .5f)
//#define HITBOX_LAMP_POST		(glm::vec3(.15, 0, .15)  * .5f)
//#define HITBOX_GIFT				(glm::vec3(.4, 0, .4)	 * .5f)

namespace m1
{
	class SkiFree : public gfxc::SimpleScene
	{
	public:
		SkiFree();
		~SkiFree();

		void Init() override;
		enum ObjectType { GIFT, LAMP_POST, TREE };

	private:

		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL);

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

		void UpdateTranslationStep(float deltaTimeSeconds);
		glm::vec3 ComputeTreePosition(glm::vec3 pos);
		glm::vec3 ComputeLampPostPosition(glm::vec3 pos);
		glm::vec3 ComputeGiftPosition(glm::vec3 pos);
		bool CollidesObstacle(glm::vec3 obstaclePosition, ObjectType type);

	protected:
		skifree_camera::Camera *camera;
		glm::mat4 projectionMatrix;
		GLfloat fov, width;

		glm::mat4 modelMatrix;
		std::unordered_map<std::string, Texture2D*> mapTextures;

		glm::ivec2 resolution;
		glm::vec2 currPos, playerPos, verticalDir, mouseDir;
		float playerAngle, prevAngle;

		std::vector<glm::vec3> treePos;
		std::vector<glm::vec3> lampPostPos;
		std::vector<glm::vec3> giftPos;

		glm::vec3 playerPos3D;
		glm::vec3 translationStep;

		bool renderCameraTarget;
		GLboolean mixTextures;
		int counter = 0;
	};

}	// namespace m1