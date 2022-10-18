#include "lab_m1/lab2/lab2.h"

#include <vector>
#include <iostream>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab2::Lab2()
{
}


Lab2::~Lab2()
{
}


void Lab2::Init()
{
    cullFace = GL_BACK;
    polygonMode = GL_FILL;

    position = glm::vec3(1, 0.5f, .5f);
    t_position = glm::vec3(0, .5f, 1);
    sqr_position = glm::vec3(1, 1, 0);
    circle_position = glm::vec3(1, 1, 1);

    // Load a mesh from file into GPU memory
    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a mesh box using custom data
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0, 1, 1)),
            VertexFormat(glm::vec3(1, 0, 1), glm::vec3(0, 1, 1)),
            VertexFormat(glm::vec3(0, 1, 1), glm::vec3(0, 1, 1)),
            VertexFormat(glm::vec3(1, 1, 1), glm::vec3(0, 1, 1)),
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 1)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 1)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(0, 1, 1)),
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0, 1, 1))
        };

        vector<GLuint> indices =
        {
            0, 1, 2,    // indices for first triangle
            1, 3, 2,    // indices for second triangle
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };

        meshes["cube_A"] = new Mesh("generated cube 1");
        meshes["cube_A"]->InitFromData(vertices, indices);

        // Actually create the mesh from the data
        CreateMesh("cube_B", vertices, indices);
    }

    // TODO(student): Create a tetrahedron mesh. You can create it with
    // only 4 vertices, or you can choose the harder route and create it
    // with 12 vertices. Think about it, why would you want that, and how
    // would you do it? After all, a tetrahedron has only 4 vertices
    // by definition!
    {
        vector<VertexFormat> t_vertices
        {
            VertexFormat(glm::vec3(0, 0, 1), glm::vec3(0.72f, 0.21f, 0.09f)),
            VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0)),
            VertexFormat(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-1, 0, 0), glm::vec3(0, 0, 1))
        };

        vector<GLuint> t_indices =
        {
            ////////////
            /*1, 3, 0,
            0, 2, 1,
            3, 2, 0,
            2, 1, 3*/

            0, 3, 1,
            2, 0, 1,
            2, 3, 0,
            2, 1, 3
        };

        meshes["tetrahedron"] = new Mesh("tetrahedron");
        meshes["tetrahedron"]->InitFromData(t_vertices, t_indices);
    }

    // Create a square using two triangles with opposing vertex orientations.
    {
        vector<VertexFormat> sqr_vertices
        {
            VertexFormat(glm::vec3(1, 1, 0), glm::vec3(1, 1, 0)),
            VertexFormat(glm::vec3(2, 1, 0), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(2, 2, 0), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1, 2, 0), glm::vec3(1, 0, 0))
        };

        vector<GLuint> sqr_indices =
        {
            0, 1, 3,
            2, 1, 3
        };

        meshes["square"] = new Mesh("square");
        meshes["square"]->InitFromData(sqr_vertices, sqr_indices);
    }

    {
        vector<VertexFormat> circle_vertices;
        vector<GLuint> circle_indices;
        GLfloat arg;

        circle_vertices.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)));

        for (int i = 0; i < NO_TRIANGLES; i++) {
            arg = 2 * M_PI / NO_TRIANGLES * i;

            circle_vertices.push_back(VertexFormat(glm::vec3(cos(arg), sin(arg), 0), glm::vec3(1, 0, 0)));
            circle_indices.push_back(i);
        }

        circle_indices.push_back(NO_TRIANGLES);
        circle_indices.push_back(1);

        CreateMesh("circle", circle_vertices, circle_indices);
        meshes["circle"]->SetDrawMode(GL_TRIANGLE_FAN);
    }

}


void Lab2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    GLuint VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    GLuint IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}


void Lab2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab2::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Enable face culling
    glEnable(GL_CULL_FACE);

    // Set face custom culling. Use the `cullFace` variable.
    glCullFace(cullFace);

    // Render an object using face normals for color
    RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -1.5f), glm::vec3(0.75f));

    // Render an object using colors from vertex
    RenderMesh(meshes["cube_A"], shaders["VertexColor"], glm::vec3(-1.5f, 0.5f, 0), glm::vec3(0.25f));

    // Draw the mesh that was created with `CreateMesh()`
    RenderMesh(meshes["cube_B"], shaders["VertexColor"], position, glm::vec3(.25f));

    // Draw the tetrahedron
    RenderMesh(meshes["tetrahedron"], shaders["VertexColor"], t_position, glm::vec3(.4f));

    // Draw the square
    RenderMesh(meshes["square"], shaders["VertexColor"], sqr_position, glm::vec3(.4f));

    // Draw the circle
    RenderMesh(meshes["circle"], shaders["VertexColor"], circle_position, glm::vec3(.3f));

    // Disable face culling   
    glDisable(GL_CULL_FACE);

}


void Lab2::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab2::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab2::OnKeyPress(int key, int mods)
{
    // TODO(student): Switch between GL_FRONT and GL_BACK culling.
    // Save the state in `cullFace` variable and apply it in the
    // `Update()` method, NOT here!

    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
    else if (key == GLFW_KEY_F2)
    {
        if (cullFace == GL_BACK) {
            cullFace = GL_FRONT;
        }
        else if (cullFace == GL_FRONT) {
            cullFace = GL_BACK;
        }
    }
}


void Lab2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab2::OnWindowResize(int width, int height)
{
}
