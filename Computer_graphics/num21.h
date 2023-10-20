#pragma once
#define WinWidth 800
#define WinHeight 800
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

random_device rd;
mt19937 engine(rd());
uniform_real_distribution<> uidc(0.1, 0.9);
uniform_int_distribution<> uidi(0, 1);
uniform_real_distribution<> uids(0.05, 0.1);
uniform_real_distribution<> uidt(-0.7, 0.7);

class TranMatrix {
public:
    glm::vec3 rotate{ 0.0, 0.0, 0.0 };
    glm::vec3 translate{ 0.0, 0.0, 0.0 };
    glm::vec3 scale{ 1.0, 1.0, 1.0 };

    glm::vec3 pre_rotate{ 0.0, 0.0, 0.0 };
    glm::vec3 pre_translate{ 0.0, 0.0, 0.0 };
    glm::vec3 pre_scale{ 1.0, 1.0, 1.0 };

    glm::vec3 axis_translate{ 0.0, 0.0, 0.0 };

    void Init() {
        translate = glm::vec3(0.0f);
        rotate = glm::vec3(0.0f);
        scale = glm::vec3(1.0f);
        pre_rotate = glm::vec3(0.0f);
        pre_translate = glm::vec3(0.0f);
        axis_translate = glm::vec3(0.0f);
    }
};
class Object : public TranMatrix {
public:
    bool show{ true };
    Object* Parent = nullptr;
    vector<GLfloat> vertex;
    vector<GLfloat> color;
    glm::vec3 pivot{ 0.0f, -0.5f, 0.0f };

    glm::mat4 GetMatrix() {
        glm::mat4 result(1.0f);
        if (Parent) {
            result = Parent->GetMatrix() * result;
        }

        result = glm::translate(result, pivot);
        result = glm::translate(result, pre_translate);
        result = glm::scale(result, pre_scale);
        result = glm::translate(result, -pivot);

        result = glm::translate(result, translate);
        result = glm::translate(result, glm::vec3(0.0, -0.52, axis_translate.z));
        result = glm::rotate(result, glm::radians(rotate.x), glm::vec3(1.0, 0.0, 0.0));
        result = glm::translate(result, glm::vec3(0.0, 0.52, -axis_translate.z));
        result = glm::rotate(result, glm::radians(rotate.y), glm::vec3(0.0, 1.0, 0.0));
        result = glm::rotate(result, glm::radians(rotate.z), glm::vec3(0.0, 0.0, 1.0));
        result = glm::scale(result, scale);

        return result;
    }

    glm::vec3 GetFrontPos() {
        glm::vec3 result(1.0f);
        glm::mat4 temp(1.0f);
        glm::vec4 cubepos = { 0.0, -0.5, 0.5, 1.0 };

        cubepos = GetMatrix() * cubepos;

        result = { cubepos.x, cubepos.y, cubepos.z };
        return result;
    }
    glm::vec3 GetBackPos() {
        glm::vec3 result(1.0f);
        glm::mat4 temp(1.0f);
        glm::vec4 cubepos = { 0.0, -0.5, -0.5, 1.0 };

        cubepos = GetMatrix() * cubepos;

        result = { cubepos.x, cubepos.y, cubepos.z };
        return result;
    }
    glm::vec3 GetLeftPos() {
        glm::vec3 result(1.0f);
        glm::mat4 temp(1.0f);
        glm::vec4 cubepos = { -0.5, -0.5, 0.0, 1.0 };

        cubepos = GetMatrix() * cubepos;

        result = { cubepos.x, cubepos.y, cubepos.z };
        return result;
    }
    glm::vec3 GetRightPos() {
        glm::vec3 result(1.0f);
        glm::mat4 temp(1.0f);
        glm::vec4 cubepos = { 0.5, -0.5, 0.0, 1.0 };

        cubepos = GetMatrix() * cubepos;

        result = { cubepos.x, cubepos.y, cubepos.z };
        return result;
    }
};
class CubeObject : public Object {
public:
    CubeObject() = default;

    CubeObject(GLfloat r, GLfloat g, GLfloat b) {
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);

        //�Ʒ�
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);

        //��
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);

        //�ո�
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);

        //����
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);

        //������
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);

        for (int i = 0; i < 36; ++i) {
            color.push_back(r); color.push_back(g); color.push_back(b);
        }
    }
};
class Camera : public TranMatrix {
    glm::vec3 cameraRight;
public:
    glm::vec3 campos{ 0.0, 1.0, 5.0 };
    glm::vec3 targetpos{ 0.0f, 0.0f, 0.0f };

    glm::mat4 GetLookAt() {
        glm::vec3 cameraPos = glm::vec3(campos.x, campos.y, campos.z); //EYE
        glm::vec3 cameraTarget = glm::vec3(targetpos.x, targetpos.y, targetpos.z); // At
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Up


        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); //n
        if (glm::normalize(cameraDirection) == glm::normalize(up)) {
            cameraRight = { 1.0f, 0.0f, 0.0f }; //v
        }
        else {
            cameraRight = glm::normalize(glm::cross(up, cameraDirection)); //v
        }
        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight); //u

        return glm::lookAt(cameraPos, cameraDirection, cameraUp);
    }
    glm::mat4 GetPerspective() {
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WinWidth / (float)WinHeight, 0.1f, 50.0f);
        proj = glm::translate(proj, translate);
        proj = glm::rotate(proj, glm::radians(rotate.y), glm::vec3(0.0, 1.0, 0.0));
        return proj;
    }
    glm::mat4 GetOrtho() {
        glm::mat4 proj = glm::mat4(1.0f);
        proj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 10.0f, -50.0f);
        proj = glm::translate(proj, translate);
        proj = glm::rotate(proj, glm::radians(rotate.z), glm::vec3(0.0, 0.0, 1.0));
        return proj;
    }
};
struct Buffer {
    GLuint vao;
    GLuint vbo[2];
};

GLvoid Reshape(int w, int h);
const string filetobuf(const char* file);
void Convert(int x, int y, float* ox, float* oy);
void Init();
int Collide();
void Menu();

GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;
Buffer CBuf[16];
Buffer EBuf[2];
CubeObject* Cubes;
CubeObject* Erase;
Object Base;
Camera cam;

void make_vertexShader() {
    string vertexsource;
    vertexsource = filetobuf("vertex.glsl");


    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* raw_str = vertexsource.c_str();

    glShaderSource(vertexShader, 1, &raw_str, NULL);
    glCompileShader(vertexShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        cerr << "ERROR: vertex shader ������ ����\n" << errorLog << endl;
        return;
    }
}

void make_fragmentShader() {
    string fragmentsource;
    fragmentsource = filetobuf("fragment.glsl");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* raw_str = fragmentsource.c_str();
    glShaderSource(fragmentShader, 1, &raw_str, NULL);
    glCompileShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        cerr << "ERROR: fragment shader ������ ����\n" << errorLog << endl;
        return;
    }

}

void InitBuffer() {
    for (int i = 0; i < 16; ++i) {
        glGenVertexArrays(1, &CBuf[i].vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�

        glBindVertexArray(CBuf[i].vao); //--- VAO�� ���ε��ϱ�

        glGenBuffers(2, CBuf[i].vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�

        if (i < 15) {
            glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[0]);
            glBufferData(GL_ARRAY_BUFFER, Cubes[i].vertex.size() * sizeof(GLfloat), Cubes[i].vertex.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[1]);
            glBufferData(GL_ARRAY_BUFFER, Cubes[i].color.size() * sizeof(GLfloat), Cubes[i].color.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(1);
        }
        else {
            glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[0]);
            glBufferData(GL_ARRAY_BUFFER, Base.vertex.size() * sizeof(GLfloat), Base.vertex.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[1]);
            glBufferData(GL_ARRAY_BUFFER, Base.color.size() * sizeof(GLfloat), Base.color.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(1);
        }
    }

    glGenVertexArrays(1, &EBuf[0].vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
    glBindVertexArray(EBuf[0].vao); //--- VAO�� ���ε��ϱ�
    glGenBuffers(2, EBuf[0].vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�

    glBindBuffer(GL_ARRAY_BUFFER, EBuf[0].vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, Erase[0].vertex.size() * sizeof(GLfloat), Erase[0].vertex.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, EBuf[0].vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, Erase[0].color.size() * sizeof(GLfloat), Erase[0].color.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &EBuf[1].vao); //--- VAO �� �����ϰ� �Ҵ��ϱ�
    glBindVertexArray(EBuf[1].vao); //--- VAO�� ���ε��ϱ�
    glGenBuffers(2, EBuf[1].vbo); //--- 2���� VBO�� �����ϰ� �Ҵ��ϱ�

    glBindBuffer(GL_ARRAY_BUFFER, EBuf[1].vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, Erase[1].vertex.size() * sizeof(GLfloat), Erase[1].vertex.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, EBuf[1].vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, Erase[1].color.size() * sizeof(GLfloat), Erase[1].color.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
}

void InitShader()
{
    make_vertexShader(); //--- ���ؽ� ���̴� �����
    make_fragmentShader(); //--- �����׸�Ʈ ���̴� �����
    //-- shader Program

    s_program = glCreateProgram();
    glAttachShader(s_program, vertexShader);
    glAttachShader(s_program, fragmentShader);
    glLinkProgram(s_program);
    //  checkCompileErrors(s_program, "PROGRAM");

        //--- ���̴� �����ϱ�
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //--- Shader Program ����ϱ�
    glUseProgram(s_program);

}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ� 
{
    glViewport(0, 0, w, h);
}

const string filetobuf(const char* file) {
    string content = "";
    string line = "";
    ifstream in(file, ios::in);

    while (!in.eof()) {
        getline(in, line);
        content.append(line + "\n");
    }

    in.close();
    return content;
}

void Convert(int x, int y, float* ox, float* oy) {
    *ox = (float)((x - (float)WinWidth / 2) * (float)(1 / (float)(WinWidth / 2)));
    *oy = -(float)((y - (float)WinHeight / 2) * (float)(1 / (float)(WinHeight / 2)));
}

void Init() {
    cam.campos = { 0.0, 0.5, 2.5 };

    //�ٴ�
    {
        Base.vertex.push_back(0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(-0.8);
        Base.vertex.push_back(0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(0.8);
        Base.vertex.push_back(-0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(-0.8);
        Base.vertex.push_back(-0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(-0.8);
        Base.vertex.push_back(0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(0.8);
        Base.vertex.push_back(-0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(0.8);

        for (int i = 0; i < 18; ++i) {
            Base.color.push_back(0.0);
        }
    }

    Cubes = new CubeObject[17];
    for (int i = 0; i < 15; ++i) {
        Cubes[i] = CubeObject((float)uidc(engine), (float)uidc(engine), (float)uidc(engine));
        Cubes[i].Parent = &Base;
        float scale = (float)uids(engine);
        float transx = (float)uidt(engine);
        float transz = (float)uidt(engine);
        Cubes[i].scale = { scale, 1, scale };
        Cubes[i].pre_scale.y = scale;
        Cubes[i].translate = { transx, -0.3, transz };
    }

    Erase = new CubeObject[2];
    for (int i = 0; i < 2; ++i) {
        Erase[i].Parent = &Base;
    }
    Erase[0] = CubeObject(1.0, 0.0, 0.0);
    Erase[0].scale = { 0.2, 1.0, 0.1 };
    Erase[0].pre_scale.y = 0.1;
    Erase[0].translate = { 0.0, -0.3, 0.0 };

    Erase[1] = CubeObject(0.0, 0.0, 1.0);
    Erase[1].scale = { 0.1, 1.0, 0.07 };
    Erase[1].pre_scale.y = 0.3;
    Erase[1].translate = { 0.0, -0.2, 0.0 };
}

int Collide() {
    for (int i = 0; i < 15; ++i) {
        if ((Erase[0].GetLeftPos().x <= Cubes[i].GetRightPos().x && Erase[0].GetLeftPos().x >= Cubes[i].GetLeftPos().x) && //�¿�(x��ǥ) ���찳 ����
            ((Cubes[i].GetRightPos().z <= Erase[0].GetFrontPos().z && Cubes[i].GetRightPos().z >= Erase[0].GetBackPos().z) ||
                (Erase[0].GetFrontPos().z <= Cubes[i].GetFrontPos().z && Erase[0].GetFrontPos().z >= Cubes[i].GetBackPos().z) ||
                (Erase[0].GetBackPos().z <= Cubes[i].GetFrontPos().z && Erase[0].GetBackPos().z >= Cubes[i].GetBackPos().z)
                ) && Cubes[i].show) {
            return i;
        }
        else if ((Erase[0].GetRightPos().x >= Cubes[i].GetLeftPos().x && Erase[0].GetRightPos().x <= Cubes[i].GetRightPos().x) && //�¿�(x��ǥ) ���찳 ������
            ((Cubes[i].GetLeftPos().z <= Erase[0].GetFrontPos().z && Cubes[i].GetLeftPos().z >= Erase[0].GetBackPos().z) ||
                (Erase[0].GetFrontPos().z <= Cubes[i].GetFrontPos().z && Erase[0].GetFrontPos().z >= Cubes[i].GetBackPos().z) ||
                (Erase[0].GetBackPos().z <= Cubes[i].GetFrontPos().z && Erase[0].GetBackPos().z >= Cubes[i].GetBackPos().z)
                ) && Cubes[i].show) {
            return i;
        }
        else if ((Erase[0].GetFrontPos().z <= Cubes[i].GetFrontPos().z && Erase[0].GetFrontPos().z >= Cubes[i].GetBackPos().z) &&
            ((Cubes[i].GetBackPos().x >= Erase[0].GetLeftPos().x && Cubes[i].GetBackPos().x <= Erase[0].GetRightPos().x) ||
                (Cubes[i].GetRightPos().x >= Erase[0].GetLeftPos().x && Cubes[i].GetRightPos().x <= Erase[0].GetRightPos().x) ||
                (Cubes[i].GetLeftPos().x <= Erase[0].GetRightPos().x && Cubes[i].GetLeftPos().x >= Erase[0].GetLeftPos().x)
                ) && Cubes[i].show) {
            return i;
        }
        else if ((Erase[0].GetBackPos().z <= Cubes[i].GetFrontPos().z && Erase[0].GetBackPos().z >= Cubes[i].GetBackPos().z) &&
            ((Cubes[i].GetBackPos().x >= Erase[0].GetLeftPos().x && Cubes[i].GetBackPos().x <= Erase[0].GetRightPos().x) ||
                (Cubes[i].GetRightPos().x >= Erase[0].GetLeftPos().x && Cubes[i].GetRightPos().x <= Erase[0].GetRightPos().x) ||
                (Cubes[i].GetLeftPos().x <= Erase[0].GetRightPos().x && Cubes[i].GetLeftPos().x >= Erase[0].GetLeftPos().x)
                ) && Cubes[i].show) {
            return i;
        }
        else if (Erase[0].GetRightPos().x >= Cubes[i].GetRightPos().x &&
            Erase[0].GetLeftPos().x <= Cubes[i].GetLeftPos().x &&
            Erase[0].GetFrontPos().z >= Cubes[i].GetFrontPos().z &&
            Erase[0].GetBackPos().z <= Cubes[i].GetBackPos().z &&
            Cubes[i].show) {
            return i;
        }
    }
}

void Menu() {
    cout << "���찳 x�࿡ ���� �̵�(a,d)" << endl;
    cout << "���찳 z�࿡ ���� �̵�(w,s)" << endl;
    cout << "ī�޶� ����(r,R)" << endl;
    cout << "�ʱ�ȭ(c)" << endl;
    cout << "���α׷�����(q)" << endl;
}