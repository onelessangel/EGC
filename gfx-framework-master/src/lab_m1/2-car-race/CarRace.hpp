#pragma once

#include <iostream>
#include <cmath>

#include "components/simple_scene.h"
#include "components/text_renderer.h"
#include "glm/gtx/vector_angle.hpp"

//#include "lab_m1/2-car-race/Objects.hpp"
#include "lab_m1/2-car-race/Transform3D.hpp"
#include "lab_m1/2-car-race/Camera.hpp"

#define AXIS_OX				glm::vec3(-1, 0, 0)

#define DIST_TO_BACKBONE    1.0f
#define DIST_PATH_1			.45f
#define DIST_PATH_2			0.0f
#define DIST_PATH_3			-.45f

#define STEP_BIG            .01f
#define MAX_STEP_BIG        .99f

#define STEP_SMALL			.001f
#define MAX_STEP_SMALL		.999f

#define SKY_LENGTH	    	50
#define SKY_HEIGHT	    	18

#define SCALE_TREE          glm::vec3(.008, .008, .008)
#define SCALE_CAR           glm::vec3(.005, .005, .005)

#define CAR_RADIUS			.5f;
#define CAR_COORD_Y			.15f
#define OBSTACLE_COORD_Y	.149

#define OBSTACLE_SPEED_1	100
#define OBSTACLE_SPEED_2	50
#define OBSTACLE_SPEED_3	150

#define START_POS_1			15000
#define START_POS_2			20000
#define START_POS_3			100000

// ------------- COLORS -------------
#define RACE_TRACK_COLOR    glm::vec3(0.3113208, 0.1450872, 0.1450872)
#define SKY_DARK_BLUE       glm::vec3(0.0166429, 0.1716965, 0.5188679)
#define SKY_LIGHT_BLUE      glm::vec3(0.5364009, 0.8382195, 1)

#define CAMERA_SPEED		6.0f
#define CAMERA_OFFSET		glm::vec3(.23, 1.2, camera->distanceToTarget)
#define MOVE_SPEED			2.5f
#define SENSITIVITY			.5f

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


		void CreateVertexPaths(glm::vec3 color);
		Mesh* CreateSky(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 colorBottom, glm::vec3 colorTop);


		void CreateObjects();
		void RenderGrass();
		void RenderRaceTrack();
		void RenderSky();
		void RenderTrees();
		void RenderObstacles();
		void RenderEnvironment();
		void RenderPlayer();
		//void DivideRaceTrackVertices();
		bool SameSide(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b);
		bool PointInTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);
		/*void ComputeFramingCorners();*/
		/*float TriangleArea(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		bool InsideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);*/


		/*float Magnitude(glm::vec3 p1, glm::vec3 p2);
		float DistanceToLine(glm::vec3 p, glm::vec3 p1, glm::vec3 p2);*/
		bool PlayerIsOnTrack(glm::vec3 playerPos);
		bool CarRace::CollidesObstacle(glm::vec3 obstaclePosition);

	protected:
		enum ObstacleId { BLUE_CAR, GREEN_CAR, PURPLE_CAR };
		camera_implementation::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		bool projectionType;
		GLfloat fov, width;

		std::vector<VertexFormat> trackVertices;
		std::vector<GLuint> trackIndices;
		std::vector<VertexFormat> trackInnerVertices, trackOuterVertices;
		std::vector<glm::vec3> obstaclePath1, obstaclePath2, obstaclePath3;
		std::vector<glm::vec3> innerTreePath, outerTreePath;
		//std::vector<VertexFormat> innerVertices, outerVertices;

		//FramingCorners* fc;

		glm::mat4 modelMatrix;
		glm::vec3 playerPosition, playerCenter, playerPos;
		glm::vec3 obstaclePosition1, obstaclePosition2, obstaclePosition3, currPathPoint, nextPathPoint, dir;
		int obstaclePosIdx1, obstaclePosIdx2, obstaclePosIdx3;
		float angle;
		float playerAngle;
		bool onTrack;

		glm::vec3 oldCameraPos, oldPlayerPos;
	};
}	// namespace m1