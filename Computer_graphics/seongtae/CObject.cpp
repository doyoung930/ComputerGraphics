#include "CObject.h"

CObject::CObject()
{
	rotate = glm::vec3(0.0f);
	translate = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

void CObject::Render(GLuint s_program)
{
    glBindVertexArray(vao);
    unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(GetMatrix()));
    glDrawArrays(GL_TRIANGLES, 0, vertex.size());
}

CObject::CObject(vector<GLfloat>& vertex, vector<GLfloat>& color) :vertex{ vertex }, color{ color }
{
    glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기
    glBindVertexArray(vao); //--- VAO를 바인드하
    glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(GLfloat), color.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
}
