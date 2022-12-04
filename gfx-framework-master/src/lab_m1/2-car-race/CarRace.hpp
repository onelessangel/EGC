#pragma once

#include <iostream>

#include "components/simple_scene.h"
#include "components/text_renderer.h"

#include "lab_m1/2-car-race/Objects.hpp"

//#define NO_VERTICES         333
//#define DIST_TO_BACKBONE    0.9f

#define GRASS_SIZE		50

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

	protected:

	};
}	// namespace m1