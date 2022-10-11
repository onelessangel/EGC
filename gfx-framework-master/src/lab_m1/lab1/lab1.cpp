#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

#define DEFAULT_MESH "box"

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`  .
 */


Lab1::Lab1()
{
    // TODO(student): Never forget to initialize class variables!

}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    red = 0;
    green = 0;
    blue = 0;

    currMesh = DEFAULT_MESH;

    position = glm::vec3(0, 0.5f, 2);

    moveSpeed = 2.5f;

    toggleColor = true;

    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh.
    {
        Mesh* mesh_box = new Mesh("box");
        mesh_box->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh_box->GetMeshID()] = mesh_box;

        Mesh* mesh_sphere = new Mesh("sphere");
        mesh_sphere->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh_sphere->GetMeshID()] = mesh_sphere;

        Mesh* mesh_teapot = new Mesh("teapot");
        mesh_teapot->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[mesh_teapot->GetMeshID()] = mesh_teapot;

        Mesh* mesh_archer = new Mesh("archer");
        mesh_archer->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters//archer"), "Archer.fbx");
        meshes[mesh_archer->GetMeshID()] = mesh_archer;
    }
}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

    // TODO(student): Generalize the arguments of `glClearColor`.
    glClearColor(red, green, blue, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object
    RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

    // Render the object again but with different properties
    RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

    // Render sphere
    //RenderMesh(meshes["sphere"], glm::vec3(3, 0.5, 0));

    // Render archer
    //RenderMesh(meshes["archer"], glm::vec3(0, 0.5, -2), glm::vec3(0.01f));

    // Render changable object
    RenderMesh(meshes[currMesh], position);
}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    // Treat continuous update based on input
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        if (window->KeyHold(GLFW_KEY_W)) {
            position.z -= deltaTime * moveSpeed;
        }
        else if (window->KeyHold(GLFW_KEY_S)) {
            position.z += deltaTime * moveSpeed;
        }
        else if (window->KeyHold(GLFW_KEY_A)) {
            position.x -= deltaTime * moveSpeed;
        }
        else if (window->KeyHold(GLFW_KEY_D)) {
            position.x += deltaTime * moveSpeed;
        }
        else if (window->KeyHold(GLFW_KEY_Q)) {
            position.y -= deltaTime * moveSpeed;
        }
        else if (window->KeyHold(GLFW_KEY_E)) {
            position.y += deltaTime * moveSpeed;
        }
    }
}


void Lab1::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_C) {
        // Change the values of the color components.
        if (toggleColor) {
            red = 0.52f;
            green = 0.76f;
            blue = 0.96f;
        }
        else {
            red = 0;
            green = 0;
            blue = 0;
        }

        toggleColor = !toggleColor;
    }

    // Cycle through multiple meshes, rendered at the same position.
    if (key == GLFW_KEY_1) {
        currMesh = "box";
    }
    else if (key == GLFW_KEY_2) {
        currMesh = "sphere";
    }
    else if (key == GLFW_KEY_3) {
        currMesh = "teapot";
    }
}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
