#pragma once

#include <iostream>

#include "components/simple_scene.h"
#include "components/text_renderer.h"

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

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void NewGameInit();
		void InitNewLevelParams();
		void CreateObjects();
		void RenderLives();
		void RenderBullets();
		void RenderScore();
		void RenderDuck(glm::mat3 duckPosMatrix);
		void ComputeDuckPosition(float deltaTimeSeconds);
		void ComputeDuckRotation();
		void ComputeWingsPosition(float deltaTimeSeconds);
		void ShowEndMenu();

	protected:
		
	};
}	// namespace m1