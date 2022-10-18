#pragma once

#include <vector>
#include <cmath>

#include "components/simple_scene.h"

#define NO_TRIANGLES   100


namespace m1
{
    class Lab2 : public gfxc::SimpleScene
    {
     public:
        Lab2();
        ~Lab2();

        void Init() override;

     private:
        glm::vec3 position;
        glm::vec3 t_position;
        glm::vec3 sqr_position;
        glm::vec3 circle_position;

        void CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);

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
        GLenum cullFace;
        GLenum polygonMode;
    };
}   // namespace m1
