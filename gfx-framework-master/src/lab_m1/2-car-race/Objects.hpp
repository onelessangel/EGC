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

#define NO_VERTICES         334
#define DIST_TO_BACKBONE    3.0f

namespace objects
{
    class Objects : public gfxc::SimpleScene
    {
     public:
        void CreateRaceTrack(const std::string& name, glm::vec3 color, bool fill = true);
     
     private:
        void CreateMesh(const std::string& name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);
    };
}