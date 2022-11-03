#pragma once

#include <iostream>

#include "components/simple_scene.h"

#define RATIO_X		.25f
#define RATIO_Y		.15f
#define RES_LIMIT_X	.444f	// ???????????
#define RES_LIMIT_Y	.54f
#define MOVE_SPEED	1.5f

namespace m1
{
	class DuckHunt : public gfxc::SimpleScene
	{
	 public:
		 DuckHunt();
		 ~DuckHunt();

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

		 void CreateObjects();

	 protected:
		 enum DuckState { ACTIVE, SHOT, ESCAPED};
		 glm::mat3 modelMatrix;
		 glm::vec2 translate;
		 bool moveRight, moveUp;
		 bool duckState;
	};
}	// namespace m1