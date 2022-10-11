#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Lab1 : public gfxc::SimpleScene
    {
    public:
        Lab1();
        ~Lab1();

        void Init() override;

    private:
        GLfloat red, green, blue;
        glm::vec3 position;
        GLfloat moveSpeed;
        GLboolean toggleColor;
        std::string currMesh;

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
    };
}   // namespace m1
