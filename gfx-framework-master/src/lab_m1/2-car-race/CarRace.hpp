#pragma once

#include <iostream>

#include "components/simple_scene.h"
#include "components/text_renderer.h"

//#include "lab_m1/2-car-race/Objects.hpp"
#include "lab_m1/2-car-race/Transform3D.hpp"
#include "lab_m1/2-car-race/Camera.hpp"

#define DIST_TO_BACKBONE    1.0f

#define STEP                .01f
#define MAX_STEP            .99f

#define SKY_LENGTH	    	50
#define SKY_HEIGHT	    	18

#define SCALE_TREE          glm::vec3(.008, .008, .008)
#define SCALE_CAR           glm::vec3(.005, .005, .005)

// ------------- COLORS -------------
#define RACE_TRACK_COLOR    glm::vec3(0.3113208, 0.1450872, 0.1450872)
#define SKY_DARK_BLUE       glm::vec3(0.0166429, 0.1716965, 0.5188679)
#define SKY_LIGHT_BLUE      glm::vec3(0.5364009, 0.8382195, 1)

#define EPS					.001f


#define CAMERA_SPEED		1.0f
#define CAMERA_OFFSET		glm::vec3(.23, 1.2, camera->distanceToTarget)
#define MOVE_SPEED			2.5f
#define SENSITIVITY			.5f

namespace m1
{/*
	typedef struct {
		glm::vec3 frontLeft;
		glm::vec3 frontRight;
		glm::vec3 backLeft;
		glm::vec3 backRight;
	} FramingCorners;*/

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


		Mesh* CreateRaceTrack(const std::string& name, glm::vec3 color);
		Mesh* CreateSky(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 colorBottom, glm::vec3 colorTop);


		void CreateObjects();
		void RenderGrass();
		void RenderRaceTrack();
		void RenderSky();
		void RenderTrees();
		void RenderEnvironment();
		void RenderPlayer();
		void DivideRaceTrackVertices();
		bool SameSide(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b);
		bool PointInTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
		/*void ComputeFramingCorners();*/
		float TriangleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		bool InsideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);


		float Magnitude(glm::vec3 p1, glm::vec3 p2);
		float DistanceToLine(glm::vec3 p, glm::vec3 p1, glm::vec3 p2);
		bool PlayerIsOnTrack(/*std::vector<VertexFormat> vertices*/);

	protected:
		camera_implementation::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		bool projectionType;
		GLfloat fov, width;

		std::vector<VertexFormat> trackInnerVertices, trackOuterVertices;
		std::vector<VertexFormat> innerVertices, outerVertices;

		//FramingCorners* fc;

		glm::mat4 modelMatrix;
		glm::vec3 playerPosition, playerCenter;
		/*glm::vec3 playerCornerFL, playerCornerFR, playerCornerBL, playerCornerBR;*/
		float playerAngle;
		bool freezeMovement;
	};
}	// namespace m1