#pragma once
#include "stdafx.h"

class CObject
{
    vector<GLfloat> vertex;
    vector<GLfloat> color;
    glm::vec3 rotate;
    glm::vec3 translate;
    glm::vec3 scale{ 1.f };
    GLuint vao{ 0 };
    GLuint vbo[2]{ 0 };
    CObject* parent{ nullptr };
    //glm::vec3 pivot{ 0.0f, -0.5f, -0.5f };
    glm::mat4 GetMatrix() {
        glm::mat4 result(1.0f);
        if (parent) {
            result = parent->GetMatrix() * result;
        }

        result = glm::translate(result, translate);
        //x축에 맞춰 회전

        result = glm::rotate(result, glm::radians(rotate.x), glm::vec3(1.0, 0.0, 0.0));
        result = glm::rotate(result, glm::radians(rotate.y), glm::vec3(0.0, 1.0, 0.0));
        result = glm::rotate(result, glm::radians(rotate.z), glm::vec3(0.0, 0.0, 1.0));

        result = glm::scale(result, scale);

        return result;
    }
public:
    CObject();
    CObject(vector<GLfloat>& vertex, vector<GLfloat>& color);
    virtual ~CObject() = default;
    virtual void Render(GLuint s_program);
};

