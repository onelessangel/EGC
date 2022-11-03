#pragma once

#include <iostream>

#include "components/simple_scene.h"

namespace m1
{
	class Environment : public gfxc::SimpleScene
	{
	public:
		Environment();
		~Environment();

		/*void Init() override;*/
		void DrawEnvironment();

	private:
		/*void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;*/

		void CreateGround(glm::ivec2 resolution);

	protected:
		glm::mat3 modelMatrix;
	};
}	// namespace m1