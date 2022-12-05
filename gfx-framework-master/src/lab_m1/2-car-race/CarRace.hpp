#pragma once

#include <iostream>

#include "components/simple_scene.h"
#include "components/text_renderer.h"

#include "lab_m1/2-car-race/Objects.hpp"
#include "lab_m1/2-car-race/Transform3D.hpp"
#include "lab_m1/2-car-race/Camera.hpp"

#define CAMERA_SPEED		5.0f
#define CAMERA_OFFSET		glm::vec3(.23, 1.2, camera->distanceToTarget)
#define MOVE_SPEED			2.5f

namespace m1
{
	class CarRace : public gfxc::SimpleScene
	{
	public:
		CarRace();
		~CarRace();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void CreateObjects();
		void RenderGrass();
		void RenderRaceTrack();
		void RenderSky();
		void RenderTrees();
		void RenderEnvironment();
		void RenderPlayer();

	protected:
		camera_implementation::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		bool projectionType;
		GLfloat fov, width;

		glm::mat4 modelMatrix;
		glm::vec3 playerPosition;
		float playerAngle;
	};
}	// namespace m1