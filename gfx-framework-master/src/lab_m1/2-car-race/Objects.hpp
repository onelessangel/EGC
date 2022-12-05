#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "core/engine.h"
#include "utils/gl_utils.h"
#include "components/simple_scene.h"

//#define NO_VERTICES         333
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

namespace objects
{
    Mesh* CreateRaceTrack(const std::string& name, glm::vec3 color);
    Mesh* CreateSky(const std::string& name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 colorBottom, glm::vec3 colorTop);
    //void CreateMesh(const std::string& name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
}