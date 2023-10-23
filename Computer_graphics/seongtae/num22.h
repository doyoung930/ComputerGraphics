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
uniform_real_distribution<> uidt(-0.3, 0.3);

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
    glm::vec3 pivot{ 0.0f, -0.5f, -0.5f };

    glm::mat4 GetMatrix() {
        glm::mat4 result(1.0f);
        if (Parent) {
            result = Parent->GetMatrix() * result;
        }

        result = glm::translate(result, translate);
        //x축에 맞춰 회전
        
        result = glm::translate(result, -pre_translate);
        result = glm::rotate(result, glm::radians(rotate.y), glm::vec3(0.0, 1.0, 0.0));
        result = glm::rotate(result, glm::radians(rotate.z), glm::vec3(0.0, 0.0, 1.0));
        result = glm::translate(result, pre_translate);

        result = glm::translate(result, axis_translate);
        result = glm::rotate(result, glm::radians(rotate.x), glm::vec3(1.0, 0.0, 0.0));
        result = glm::translate(result, -axis_translate);

        //아랫변과 뒷변에 대해 스케일
        result = glm::translate(result, pivot);
        result = glm::scale(result, glm::vec3(1.0, pre_scale.y, 1.0));
        result = glm::scale(result, glm::vec3(1.0, 1.0, pre_scale.z));
        result = glm::translate(result, -pivot);

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
        glm::vec4 cubepos = { 0.0, 0.5, -0.5, 1.0 };

        cubepos = GetMatrix() * cubepos;

        result = { cubepos.x, cubepos.y, cubepos.z };
        return result;
    }
    glm::vec3 GetLeftPos() {
        glm::vec3 result(1.0f);
        glm::mat4 temp(1.0f);
        glm::vec4 cubepos = { -0.5, -0.5, -0.5, 1.0 };

        cubepos = GetMatrix() * cubepos;

        result = { cubepos.x, cubepos.y, cubepos.z };
        return result;
    }
    glm::vec3 GetRightPos() {
        glm::vec3 result(1.0f);
        glm::mat4 temp(1.0f);
        glm::vec4 cubepos = { 0.5, -0.5, 0.5, 1.0 };

        cubepos = GetMatrix() * cubepos;

        result = { cubepos.x, cubepos.y, cubepos.z };
        return result;
    }
};
class CubeObject : public Object {
public:
    CubeObject() = default;

    CubeObject(GLfloat r, GLfloat g, GLfloat b) {
        //뒷면
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);

        //아래
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);

        //위
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);

        //앞면
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);

        //왼쪽
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);

        //오른쪽
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

enum { Left = 1, Right, Up, Down = 4 };

GLvoid Reshape(int w, int h);
const string filetobuf(const char* file);
void Convert(int x, int y, float* ox, float* oy);
void Init();
bool Collide();
void Menu();
void Can_Move();

GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;

Buffer RobotBuf[3];
Buffer RobotABuf[2];
Buffer RobotLBuf[2];
Buffer StageBuf[6];
Buffer ObstacleBuf;

CubeObject* Robot;
CubeObject* RobotArm;
CubeObject* RobotLeg;
CubeObject* Obstacle;
Object Stage[6];
Camera cam;

bool StageTimer{ false };
int StageDir{ 0 };
int RobotDir{ 0 };
bool LegDir{ true };
bool Jump{ false };
int JumpDir{ 0 };
bool On_Obst{ false };

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
        cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
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
        cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
        return;
    }

}

void InitBuffer() {
    for (int i = 0; i < 3; ++i) {
        glGenVertexArrays(1, &RobotBuf[i].vao); //--- VAO 를 지정하고 할당하기
        glBindVertexArray(RobotBuf[i].vao); //--- VAO를 바인드하
        glGenBuffers(2, RobotBuf[i].vbo); //--- 2개의 VBO를 지정하고 할당하기
        glBindBuffer(GL_ARRAY_BUFFER, RobotBuf[i].vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, Robot[i].vertex.size() * sizeof(GLfloat), Robot[i].vertex.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, RobotBuf[i].vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, Robot[i].color.size() * sizeof(GLfloat), Robot[i].color.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
    }
    for (int i = 0; i < 2; ++i) {
        glGenVertexArrays(1, &RobotABuf[i].vao); //--- VAO 를 지정하고 할당하기
        glBindVertexArray(RobotABuf[i].vao); //--- VAO를 바인드하
        glGenBuffers(2, RobotABuf[i].vbo); //--- 2개의 VBO를 지정하고 할당하기
        glBindBuffer(GL_ARRAY_BUFFER, RobotABuf[i].vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, RobotArm[i].vertex.size() * sizeof(GLfloat), RobotArm[i].vertex.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, RobotABuf[i].vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, RobotArm[i].color.size() * sizeof(GLfloat), RobotArm[i].color.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
    }
    for (int i = 0; i < 2; ++i) {
        glGenVertexArrays(1, &RobotLBuf[i].vao); //--- VAO 를 지정하고 할당하기
        glBindVertexArray(RobotLBuf[i].vao); //--- VAO를 바인드하
        glGenBuffers(2, RobotLBuf[i].vbo); //--- 2개의 VBO를 지정하고 할당하기
        glBindBuffer(GL_ARRAY_BUFFER, RobotLBuf[i].vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, RobotLeg[i].vertex.size() * sizeof(GLfloat), RobotLeg[i].vertex.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, RobotLBuf[i].vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, RobotLeg[i].color.size() * sizeof(GLfloat), RobotLeg[i].color.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
    }
    for (int i = 0; i < 6; ++i) {
        glGenVertexArrays(1, &StageBuf[i].vao); //--- VAO 를 지정하고 할당하기
        glBindVertexArray(StageBuf[i].vao); //--- VAO를 바인드하
        glGenBuffers(2, StageBuf[i].vbo); //--- 2개의 VBO를 지정하고 할당하기
        glBindBuffer(GL_ARRAY_BUFFER, StageBuf[i].vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, Stage[i].vertex.size() * sizeof(GLfloat), Stage[i].vertex.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, StageBuf[i].vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, Stage[i].color.size() * sizeof(GLfloat), Stage[i].color.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
    }
    glGenVertexArrays(1, &ObstacleBuf.vao); //--- VAO 를 지정하고 할당하기
    glBindVertexArray(ObstacleBuf.vao); //--- VAO를 바인드하
    glGenBuffers(2, ObstacleBuf.vbo); //--- 2개의 VBO를 지정하고 할당하기
    glBindBuffer(GL_ARRAY_BUFFER, ObstacleBuf.vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, Obstacle[0].vertex.size() * sizeof(GLfloat), Obstacle[0].vertex.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, ObstacleBuf.vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, Obstacle[0].color.size() * sizeof(GLfloat), Obstacle[0].color.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
}

void InitShader()
{
    make_vertexShader(); //--- 버텍스 세이더 만들기
    make_fragmentShader(); //--- 프래그먼트 세이더 만들기
    //-- shader Program

    s_program = glCreateProgram();
    glAttachShader(s_program, vertexShader);
    glAttachShader(s_program, fragmentShader);
    glLinkProgram(s_program);
    //  checkCompileErrors(s_program, "PROGRAM");

        //--- 세이더 삭제하기
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //--- Shader Program 사용하기
    glUseProgram(s_program);

}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
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
    cam.campos = { 0.0, 0.0, 2.5 };

    {
        //뒷면
        Stage[0].vertex.push_back(0.5); Stage[0].vertex.push_back(-0.5); Stage[0].vertex.push_back(-0.5);
        Stage[0].vertex.push_back(-0.5); Stage[0].vertex.push_back(-0.5); Stage[0].vertex.push_back(-0.5);
        Stage[0].vertex.push_back(-0.5); Stage[0].vertex.push_back(0.5); Stage[0].vertex.push_back(-0.5);
        Stage[0].vertex.push_back(0.5); Stage[0].vertex.push_back(0.5); Stage[0].vertex.push_back(-0.5);
        Stage[0].vertex.push_back(0.5); Stage[0].vertex.push_back(-0.5); Stage[0].vertex.push_back(-0.5);
        Stage[0].vertex.push_back(-0.5); Stage[0].vertex.push_back(0.5); Stage[0].vertex.push_back(-0.5);
        for (int i = 0; i < 6; ++i) {
            Stage[0].color.push_back(0.0); Stage[0].color.push_back(0.0); Stage[0].color.push_back(0.0);
        }
        //아래
        Stage[1].vertex.push_back(-0.5); Stage[1].vertex.push_back(-0.5); Stage[1].vertex.push_back(0.5);
        Stage[1].vertex.push_back(-0.5); Stage[1].vertex.push_back(-0.5); Stage[1].vertex.push_back(-0.5);
        Stage[1].vertex.push_back(0.5); Stage[1].vertex.push_back(-0.5); Stage[1].vertex.push_back(-0.5);
        Stage[1].vertex.push_back(-0.5); Stage[1].vertex.push_back(-0.5); Stage[1].vertex.push_back(0.5);
        Stage[1].vertex.push_back(0.5); Stage[1].vertex.push_back(-0.5); Stage[1].vertex.push_back(-0.5);
        Stage[1].vertex.push_back(0.5); Stage[1].vertex.push_back(-0.5); Stage[1].vertex.push_back(0.5);
        for (int i = 0; i < 6; ++i) {
            Stage[1].color.push_back(0.3); Stage[1].color.push_back(0.3); Stage[1].color.push_back(0.3);
        }
        //위
        Stage[2].vertex.push_back(-0.5); Stage[2].vertex.push_back(0.5); Stage[2].vertex.push_back(0.5);
        Stage[2].vertex.push_back(0.5); Stage[2].vertex.push_back(0.5); Stage[2].vertex.push_back(0.5);
        Stage[2].vertex.push_back(-0.5); Stage[2].vertex.push_back(0.5); Stage[2].vertex.push_back(-0.5);
        Stage[2].vertex.push_back(0.5); Stage[2].vertex.push_back(0.5); Stage[2].vertex.push_back(0.5);
        Stage[2].vertex.push_back(0.5); Stage[2].vertex.push_back(0.5); Stage[2].vertex.push_back(-0.5);
        Stage[2].vertex.push_back(-0.5); Stage[2].vertex.push_back(0.5); Stage[2].vertex.push_back(-0.5);
        for (int i = 0; i < 6; ++i) {
            Stage[2].color.push_back(0.0); Stage[2].color.push_back(0.0); Stage[2].color.push_back(1.0);
        }
        //앞면
        Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(0.5);
        Stage[3].vertex.push_back(0.5); Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(0.5);
        Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(0.5); Stage[3].vertex.push_back(0.5);
        Stage[3].vertex.push_back(0.5); Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(0.5);
        Stage[3].vertex.push_back(0.5); Stage[3].vertex.push_back(0.5); Stage[3].vertex.push_back(0.5);
        Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(0.5); Stage[3].vertex.push_back(0.5);
        for (int i = 0; i < 6; ++i) {
            Stage[3].color.push_back(1.0); Stage[3].color.push_back(1.0); Stage[3].color.push_back(0.0);
        }
        //왼쪽
        Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(-0.5);
        Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(0.5);
        Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(-0.5);
        Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(-0.5);
        Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(0.5);
        Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(0.5);
        for (int i = 0; i < 6; ++i) {
            Stage[4].color.push_back(1.0); Stage[4].color.push_back(0.0); Stage[4].color.push_back(1.0);
        }
        //오른쪽
        Stage[5].vertex.push_back(0.5); Stage[5].vertex.push_back(-0.5); Stage[5].vertex.push_back(0.5);
        Stage[5].vertex.push_back(0.5); Stage[5].vertex.push_back(-0.5); Stage[5].vertex.push_back(-0.5);
        Stage[5].vertex.push_back(0.5); Stage[5].vertex.push_back(0.5); Stage[5].vertex.push_back(0.5);
        Stage[5].vertex.push_back(0.5); Stage[5].vertex.push_back(-0.5); Stage[5].vertex.push_back(-0.5);
        Stage[5].vertex.push_back(0.5); Stage[5].vertex.push_back(0.5); Stage[5].vertex.push_back(-0.5);
        Stage[5].vertex.push_back(0.5); Stage[5].vertex.push_back(0.5); Stage[5].vertex.push_back(0.5);
        for (int i = 0; i < 6; ++i) {
            Stage[5].color.push_back(0.0); Stage[5].color.push_back(1.0); Stage[5].color.push_back(1.0);
        }
    }
    Stage[1].Parent = Stage[2].Parent = Stage[3].Parent = Stage[4].Parent = Stage[5].Parent = &Stage[0];

    Robot = new CubeObject[3];
    for (int i = 0; i < 3; ++i) {
        if (i == 0) {
            Robot[i] = CubeObject(0.0, 0.0, 1.0);
            Robot[i].scale = { 0.05, 1.0, 0.05 };
            Robot[i].pre_scale.y = 0.05;
            Robot[i].translate = { 0.0, 0.2, 0.0 };
        }
        else if (i == 1) {
            Robot[i] = CubeObject(0.0, 0.0, 1.0);
            Robot[i].scale = { 0.1, 1.0, 0.1 };
            Robot[i].pre_scale.y = 0.15;
            Robot[i].translate = { 0.0, 0.05, 0.0 };
        }
        else {
            Robot[i] = CubeObject(0.0, 0.7, 0.2);
            Robot[i].scale = { 0.01, 1.0, 1.0 };
            Robot[i].pre_scale.y = 0.01;
            Robot[i].pre_scale.z = 0.03;
            Robot[i].translate = { 0.0, 0.225, 0.525 };
            Robot[i].pre_translate = Robot[i].translate;
        }
        Robot[i].Parent = &Stage[0];  
    }

    RobotArm = new CubeObject[2];
    for (int i = 0; i < 2; ++i) {
        if (i == 0) {
            RobotArm[i] = CubeObject(1.0, 0.0, 1.0);
            RobotArm[i].translate = {1.0, -1.5, 0.0};
            RobotArm[i].rotate.z = -45.0f;
        }
        else {
            RobotArm[i] = CubeObject(0.0, 1.0, 1.0);
            RobotArm[i].translate = {-1.0, -1.5, 0.0};
            RobotArm[i].rotate = -RobotArm[0].rotate;
        }
        RobotArm[i].scale = { 2.5, 0.5, 0.5 };

        RobotArm[i].Parent = &Robot[0];
    }
    RobotLeg = new CubeObject[2];
    for (int i = 0; i < 2; ++i) {
        RobotLeg[i] = CubeObject(1.0, 1.0, 0.0);
        RobotLeg[i].scale = { 0.3, 1.0, 0.3 };
        if (i == 0) {
            RobotLeg[i].translate = {0.4, -4.0, 0.0};
        }
        else {
            RobotLeg[i].translate = { -0.4, -4.0, 0.0 };
        }
        RobotLeg[i].Parent = &Robot[0];
    }
    Obstacle = new CubeObject;
    Obstacle[0] = CubeObject(0.8, 0.8, 0.8);
    Obstacle[0].scale = {0.3, 1.0, 0.2};
    Obstacle[0].pre_scale.y = 0.03;
    Obstacle[0].translate.z = uidt(engine);
    Obstacle[0].translate.x = uidt(engine);

    
}

bool Collide() {
    if ((RobotLeg[0].GetFrontPos().y <= Obstacle[0].GetBackPos().y &&
        RobotLeg[0].GetFrontPos().z >= Obstacle[0].GetBackPos().z && RobotLeg[0].GetFrontPos().z <= Obstacle[0].GetFrontPos().z &&
        RobotLeg[0].GetRightPos().x >= Obstacle[0].GetLeftPos().x && RobotLeg[0].GetRightPos().x <= Obstacle[0].GetRightPos().x) ||
        (RobotLeg[1].GetFrontPos().y <= Obstacle[0].GetBackPos().y &&
            RobotLeg[1].GetFrontPos().z >= Obstacle[0].GetBackPos().z && RobotLeg[1].GetFrontPos().z <= Obstacle[0].GetFrontPos().z &&
            RobotLeg[1].GetRightPos().x >= Obstacle[0].GetLeftPos().x && RobotLeg[1].GetRightPos().x <= Obstacle[0].GetRightPos().x)) {
        return true;
    }
    else {
        return false;
    }
}

void Can_Move() {
    if (Robot[2].GetRightPos().x <= Stage[0].GetLeftPos().x) {        
        float dis = Stage[0].GetRightPos().x - Robot[1].GetRightPos().x;
        for (int i = 0; i < 3; ++i) {
            Robot[i].translate.x += dis;
        }
    }
    else if (Robot[2].GetRightPos().x >= Stage[0].GetRightPos().x) {
        float dis = Stage[0].GetLeftPos().x - Robot[1].GetRightPos().x;
        for (int i = 0; i < 3; ++i) {
            Robot[i].translate.x += dis;
        }
    }
    else if (Robot[2].GetFrontPos().z >= Stage[0].GetFrontPos().z) {
        float dis = Stage[0].GetBackPos().z - Robot[1].GetBackPos().z;
        for (int i = 0; i < 3; ++i) {
            Robot[i].translate.z += dis;
        }
    }
    else if (Robot[2].GetFrontPos().z <= Stage[0].GetBackPos().z) {
        float dis = Stage[0].GetFrontPos().z - Robot[1].GetBackPos().z;
        for (int i = 0; i < 3; ++i) {
            Robot[i].translate.z += dis;
        }
    }
    else if (Robot[1].GetFrontPos().z >= Obstacle[0].GetBackPos().z && Robot[1].GetBackPos().z < Obstacle[0].GetBackPos().z && (
        (Robot[1].GetLeftPos().x <= Obstacle[0].GetLeftPos().x && Robot[1].GetRightPos().x >= Obstacle[0].GetLeftPos().x) ||
        (Robot[1].GetRightPos().x >= Obstacle[0].GetRightPos().x && Robot[1].GetLeftPos().x <= Obstacle[0].GetRightPos().x) ||
        (Robot[1].GetLeftPos().x >= Obstacle[0].GetLeftPos().x && Robot[1].GetRightPos().x <= Obstacle[0].GetRightPos().x)) && !Jump) {
        RobotDir = 0;
        float dis = Obstacle[0].GetBackPos().z - Robot[1].GetFrontPos().z;
        for (int i = 0; i < 3; ++i) {
            Robot[i].translate.z += dis;
        }
    }
    else if (Robot[1].GetFrontPos().z <= Obstacle[0].GetFrontPos().z && Robot[1].GetBackPos().z > Obstacle[0].GetFrontPos().z && (
        (Robot[1].GetLeftPos().x <= Obstacle[0].GetLeftPos().x && Robot[1].GetRightPos().x >= Obstacle[0].GetLeftPos().x) ||
        (Robot[1].GetRightPos().x >= Obstacle[0].GetRightPos().x && Robot[1].GetLeftPos().x <= Obstacle[0].GetRightPos().x) ||
        (Robot[1].GetLeftPos().x >= Obstacle[0].GetLeftPos().x && Robot[1].GetRightPos().x <= Obstacle[0].GetRightPos().x)) && !Jump) {
        RobotDir = 0;
        float dis = Obstacle[0].GetFrontPos().z - Robot[1].GetFrontPos().z;
        for (int i = 0; i < 3; ++i) {
            Robot[i].translate.z += dis;
        }
    }
    else if ((Robot[1].GetLeftPos().x >= Obstacle[0].GetLeftPos().x && Robot[1].GetRightPos().x < Obstacle[0].GetLeftPos().x) && (
        (Robot[1].GetLeftPos().z <= Obstacle[0].GetBackPos().z && Robot[1].GetRightPos().z >= Obstacle[0].GetBackPos().z) ||
        (Robot[1].GetLeftPos().z >= Obstacle[0].GetBackPos().z && Robot[1].GetRightPos().z <= Obstacle[0].GetFrontPos().z) ||
        (Robot[1].GetLeftPos().z <= Obstacle[0].GetFrontPos().z && Robot[1].GetRightPos().z >= Obstacle[0].GetFrontPos().z)) && !Jump) {
        RobotDir = 0;
        float dis = Obstacle[0].GetLeftPos().x - Robot[1].GetLeftPos().x;
        for (int i = 0; i < 3; ++i) {
            Robot[i].translate.x += dis;
        }
    }
    else if ((Robot[1].GetLeftPos().x <= Obstacle[0].GetRightPos().x && Robot[1].GetRightPos().x > Obstacle[0].GetRightPos().x) && (
        (Robot[1].GetLeftPos().z <= Obstacle[0].GetBackPos().z && Robot[1].GetRightPos().z >= Obstacle[0].GetBackPos().z) ||
        (Robot[1].GetLeftPos().z >= Obstacle[0].GetBackPos().z && Robot[1].GetRightPos().z <= Obstacle[0].GetFrontPos().z) ||
        (Robot[1].GetLeftPos().z <= Obstacle[0].GetFrontPos().z && Robot[1].GetRightPos().z >= Obstacle[0].GetFrontPos().z)) && !Jump) {
        RobotDir = 0;
        float dis = Obstacle[0].GetRightPos().x - Robot[1].GetLeftPos().x;
        for (int i = 0; i < 3; ++i) {
            Robot[i].translate.x += dis;
        }
    }
}

void Menu() {
    cout << "무대열기(o,O)" << endl;
    cout << "로봇움직이기(wasd)" << endl;
    cout << "로봇점프(j, J)" << endl;
    cout << "초기화(i, I)" << endl;
    cout << "카메라 앞뒤(z, Z)" << endl;
    cout << "카메라 좌우(x, X)" << endl;
    cout << "카메라 공전(y, Y)" << endl;
    cout << "프로그램 종료(q)" << endl;
}