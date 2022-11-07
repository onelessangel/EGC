#pragma once

#include <iostream>

#include "components/simple_scene.h"

#define RATIO_X					.25f
#define RATIO_Y					.15f
#define RES_LIMIT_X				.444f	// ???????????
#define RES_LIMIT_Y				.625f
#define MOVE_SPEED				.1f

#define SMALL_OBJ_DIM			13
#define SMALL_OBJ_DIM2			(SMALL_OBJ_DIM * 2)

#define TOTAL_DUCK_SIZE			150
#define BODY_SIZE				80
#define HEAD_SIZE				24
#define EYES_SIZE				4
#define BEAK_SIZE				16
#define L_WING_SIZE				36
#define R_WING_SIZE				32  

#define EYES_RIGHT_X			(BODY_SIZE * M_SQRT2 + 8)
#define EYES_RIGHT_Y			(BODY_SIZE * M_SQRT2 / 2 + 6)
#define EYES_LEFT_X				(HEAD_SIZE + BEAK_SIZE - 2 - 8)
#define EYES_LEFT_Y				EYES_RIGHT_Y

#define HEAD_RIGHT_X			(BODY_SIZE * M_SQRT2)
#define HEAD_RIGHT_Y			(BODY_SIZE * M_SQRT2 / 2)
#define HEAD_LEFT_X				(HEAD_SIZE + BEAK_SIZE - 3)
#define HEAD_LEFT_Y				HEAD_RIGHT_Y

#define BEAK_RIGHT_X			(BODY_SIZE * M_SQRT2 + HEAD_SIZE - 2)
#define BEAK_RIGHT_Y			(BODY_SIZE * M_SQRT2 / 2 - 8)
#define BEAK_LEFT_X				(BEAK_SIZE - 2)
#define BEAK_LEFT_Y				BEAK_RIGHT_Y

#define BODY_RIGHT_X			(BODY_SIZE * M_SQRT2 / 2)
#define BODY_RIGHT_Y			0
#define	BODY_LEFT_X				(BODY_SIZE * M_SQRT2 / 2 + HEAD_SIZE + BEAK_SIZE - 3)
#define	BODY_LEFT_Y				BODY_RIGHT_Y

#define LEFT_WING_RIGHT_X		(BODY_SIZE * M_SQRT2 / 2 - 20)
#define LEFT_WING_RIGHT_Y		(BODY_SIZE * M_SQRT2 / 2)
#define LEFT_WING_LEFT_X		(BODY_SIZE * M_SQRT2 / 2 + HEAD_SIZE + BEAK_SIZE - 3 + 20)
#define LEFT_WING_LEFT_Y		LEFT_WING_RIGHT_Y

#define RIGHT_WING_RIGHT_X		(BODY_SIZE * M_SQRT2 / 2 + R_WING_SIZE + 5)
#define RIGHT_WING_RIGHT_Y		5
#define RIGHT_WING_LEFT_X		(BODY_SIZE * M_SQRT2 / 2)
#define RIGHT_WING_LEFT_Y		RIGHT_WING_RIGHT_Y	

#define MAX_ANGLE				1.3f

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
		 void RenderLives();
		 void RenderBullets();
		 void RenderScore();
		 void RenderDuck(glm::mat3 duckPosMatrix, glm::mat3 leftWingPosMatrix, glm::mat3 rightWingPosMatrix, float deltaTimeSeconds);
		 glm::mat3 ComputeDuckPosition(float deltaTimeSeconds);
		 void ComputeWingsPosition(float deltaTimeSeconds);

	 protected:
		 enum DuckState { ACTIVE, SHOT, ESCAPED};
		 glm::mat3 modelMatrixMain, modelMatrixObj1, modelMatrixObj2, modelMatrixObj3;
		 glm::mat3 leftWingPosMatrix = glm::mat3(1), rightWingPosMatrix = glm::mat3(1);
		 glm::mat3 bodyMatrix, headMatrix, beakMatrix, leftWingMatrix, rightWingMatrix, eyesMatrix;
		 glm::vec2 translate;
		 bool moveRight, moveUp, movingInward;
		 bool duckState;
		 int duckCounter;
		 float angularStep;
	};
}	// namespace m1