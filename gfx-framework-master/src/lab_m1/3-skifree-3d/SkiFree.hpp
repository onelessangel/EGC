#pragma once

#include <iostream>
#include <cmath>

#include "components/simple_scene.h"
#include "components/text_renderer.h"
#include "glm/gtx/vector_angle.hpp"

#include "lab_m1/3-skifree-3d/Camera.hpp"
#include "lab_m1/3-skifree-3d/Transform3D.hpp"

#define CAMERA_SPEED			4.5f
#define CAMERA_SENSITIVITY_OX	.002f
#define CAMERA_SENSITIVITY_OY	.002f

#define SCALE_PLAYER			glm::vec3(.003, .003, .003)

#define SLOPE_ANGLE				(M_PI / 6)

namespace m1
{
	class SkiFree : public gfxc::SimpleScene
	{
	public:
		SkiFree();
		~SkiFree();

		void Init() override;

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

	protected:
		skifree_camera::Camera *camera;
		glm::mat4 projectionMatrix;
		GLfloat fov, width;

		glm::mat4 modelMatrix;
		std::unordered_map<std::string, Texture2D*> mapTextures;

		glm::ivec2 resolution;
		glm::vec2 currPos, playerPos, verticalDir, mouseDir;
		float angle;

		bool renderCameraTarget;
		GLboolean mixTextures;
	};

}	// namespace m1