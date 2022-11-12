#include "lab_m1/1-duck-hunt/Objects2D.h"

Mesh* Objects2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}


Mesh* Objects2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float height,
    float length,
    glm::vec3 color,
    bool fill)
{
    //const std::string& texturePath
    glm::vec3 corner = leftBottomCorner;

   /* VertexFormat v0 = VertexFormat(corner, color, glm::vec3(0.f, 1.f, 1.f), glm::vec2(0.f, 0.f));
    VertexFormat v1 = VertexFormat(corner + glm::vec3(length, 0, -10), color, glm::vec3(1.f, 0.f, 1.f), glm::vec2(1.f, 0.f));
    VertexFormat v2 = VertexFormat(corner + glm::vec3(length, height, 10), color, glm::vec3(1.f, 0.f, 0.f), glm::vec2(1.f, 1.f));
    VertexFormat v3 = VertexFormat(corner + glm::vec3(0, height, -10), color, glm::vec3(0.f, 1.f, 0.f), glm::vec2(0.f, 1.f));*/

    /*std::vector<glm::vec3> vertices =
    {
        v0.position, v1.position, v2.position, v3.position
    };*/

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    ///* Normals for the object */
    //std::vector<glm::vec3> normals
    //{
    //    v0.normal, v1.normal, v2.normal, v3.normal
    //};

    ///* Texture coordinates for the object */
    //std::vector<glm::vec2> textureCoords
    //{
    //    v0.text_coord, v1.text_coord, v2.text_coord, v3.text_coord
    //};

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    //rectangle->InitFromData(vertices, normals, textureCoords, indices);

    //auto texture = new Texture2D();
    //texture->Load2D(texturePath.c_str(), GL_REPEAT);

    return rectangle;
}

Mesh* Objects2D::CreateCircle(
    const std::string& name,
    glm::vec3 centerPos,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    float arg;

    vertices.emplace_back(centerPos, color);

    for (int i = 0; i < NO_TRIANGLES; i++) {
        arg = 2 * M_PI / NO_TRIANGLES * i;

        vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), color);
        indices.emplace_back(i);
    }

    indices.emplace_back(NO_TRIANGLES);
    indices.emplace_back(1);

    Mesh* circle = new Mesh(name);

    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    circle->InitFromData(vertices, indices);
    circle->SetDrawMode(GL_TRIANGLE_FAN);

    return circle;
}

Mesh* Objects2D::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2};

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}