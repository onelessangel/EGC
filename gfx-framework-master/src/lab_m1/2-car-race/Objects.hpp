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

#define NO_VERTICES         333
#define DIST_TO_BACKBONE    0.9f

namespace objects
{
    Mesh* CreateRaceTrack(const std::string& name, glm::vec3 color);
    Mesh* CreateGrass(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
    //void CreateMesh(const std::string& name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
}