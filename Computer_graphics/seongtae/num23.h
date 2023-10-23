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
uniform_int_distribution<> uiddir(1, 26);
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
    glm::vec3 GetSize() {
        glm::vec3 result(1.0f);
        result.x = GetRightPos().x - GetLeftPos().x;
        result.y = GetBackPos().y - GetFrontPos().y;
        result.z = GetFrontPos().z - GetBackPos().z;

        return result;
    }
};
class CubeObject : public Object {
public:
    CubeObject() = default;
    bool _90{ true };
    bool _180{ true };
    bool _270{ true };
    bool _360{ true };

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
class GluObject : public Object {
public:
    bool show{ false };
    GLUquadricObj* qobj = gluNewQuadric();
    int dir{ 0 };
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
        proj = glm::rotate(proj, glm::radians(rotate.z), glm::vec3(0.0, 0.0, 1.0));
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
bool Collide();
void Menu();
void BoxMove();
void NewMove();

GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;
Buffer StageBuf[5];
Buffer CubesBuf[3];

Object Stage[5];
//CubeObject* Cubes;
Camera cam;
GluObject ball[5];

bool Drag{ false };
int mousex;

void make_vertexShader() {
    string vertexsource;
    vertexsource = filetobuf("vertex23.glsl");

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
    fragmentsource = filetobuf("fragment23.glsl");

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
    //for (int i = 0; i < 3; ++i) {
    //    glGenVertexArrays(1, &CubesBuf[i].vao); //--- VAO 를 지정하고 할당하기
    //    glBindVertexArray(CubesBuf[i].vao); //--- VAO를 바인드하
    //    glGenBuffers(2, CubesBuf[i].vbo); //--- 2개의 VBO를 지정하고 할당하기
    //    glBindBuffer(GL_ARRAY_BUFFER, CubesBuf[i].vbo[0]);
    //    glBufferData(GL_ARRAY_BUFFER, Cubes[i].vertex.size() * sizeof(GLfloat), Cubes[i].vertex.data(), GL_STATIC_DRAW);
    //    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //    glEnableVertexAttribArray(0);
    //    glBindBuffer(GL_ARRAY_BUFFER, CubesBuf[i].vbo[1]);
    //    glBufferData(GL_ARRAY_BUFFER, Cubes[i].color.size() * sizeof(GLfloat), Cubes[i].color.data(), GL_STATIC_DRAW);
    //    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //    glEnableVertexAttribArray(1);
    //}
    for (int i = 0; i < 5; ++i) {
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
            Stage[2].color.push_back(0.6); Stage[2].color.push_back(0.6); Stage[2].color.push_back(0.6);
        }
        //왼쪽
        Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(-0.5);
        Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(0.5); Stage[3].vertex.push_back(0.5);
        Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(0.5); Stage[3].vertex.push_back(-0.5);
        Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(-0.5);
        Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(0.5);
        Stage[3].vertex.push_back(-0.5); Stage[3].vertex.push_back(0.5); Stage[3].vertex.push_back(0.5);
        for (int i = 0; i < 6; ++i) {
            Stage[3].color.push_back(1.0); Stage[3].color.push_back(0.0); Stage[3].color.push_back(1.0);
        }
        //오른쪽
        Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(0.5);
        Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(-0.5);
        Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(0.5);
        Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(-0.5); Stage[4].vertex.push_back(-0.5);
        Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(-0.5);
        Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(0.5); Stage[4].vertex.push_back(0.5);
        for (int i = 0; i < 6; ++i) {
            Stage[4].color.push_back(0.0); Stage[4].color.push_back(1.0); Stage[4].color.push_back(1.0);
        }
    }
    Stage[1].Parent = Stage[2].Parent = Stage[3].Parent = Stage[4].Parent = &Stage[0];

   /* Cubes = new CubeObject[3];
    for (int i = 0; i < 3; ++i) {        
        if (i == 0) {
            Cubes[i] = CubeObject(0.4, 0.0, 0.0);
            Cubes[i].scale = {0.1, 1.0, 0.1};
            Cubes[i].pre_scale.y = 0.1;
            Cubes[i].translate = {0.0, 0.0, 0.0};
        }
        else if (i == 1) {
            Cubes[i] = CubeObject(0.7, 0.0, 0.0);
            Cubes[i].scale = {0.08, 1.0, 0.08};
            Cubes[i].pre_scale.y = 0.08;
            Cubes[i].translate = {0.0, 0.0, 0.09};
        }
        else {
            Cubes[i] = CubeObject(1.0, 0.0, 0.0);
            Cubes[i].scale = {0.05, 1.0, 0.05};
            Cubes[i].pre_scale.y = 0.05;
            Cubes[i].translate = {0.0, 0.0, 0.155};
        }
        Cubes[i].Parent = &Stage[0];
    }*/
    for (int i = 0; i < 5; ++i) {
        ball[i].Parent = &Stage[0];
    }
}
//
//bool Collide() {
//    return false;
//}
//
//void BoxMove() {
//    if (Stage[0].rotate.z > 0.0f && Stage[0].rotate.z < 90.0f ) {
//        for (int i = 0; i < 3; ++i) {
//            if (Cubes[i].GetLeftPos().x > Stage[3].GetLeftPos().x && Cubes[i]._90) {
//                Cubes[i].translate.x -= 0.001f * Stage[0].rotate.z;
//                if (Cubes[i].GetLeftPos().x < Stage[3].GetLeftPos().x) {
//                    Cubes[i].translate.x += Stage[3].GetLeftPos().x - Cubes[i].GetLeftPos().x;
//                }
//            }
//            else if (Cubes[i].GetLeftPos().x < Stage[3].GetLeftPos().x) {
//                Cubes[i].translate.x += Stage[3].GetLeftPos().x - Cubes[i].GetLeftPos().x;
//                Cubes[i]._90 = false;
//            }
//        }
//    }
//    else if (Stage[0].rotate.z > 90.0f && Stage[0].rotate.z < 180.0f) { //Stage의 left의 y를 비교해야함 블럭의 Cube의 left의 x
//        for (int i = 0; i < 3; ++i) {
//            if (Cubes[i].GetLeftPos().x > Stage[3].GetLeftPos().y && Cubes[i]._180) {
//                Cubes[i].translate.y += 0.01f;
//                if (Cubes[i].GetLeftPos().x > Stage[3].GetLeftPos().y && Cubes[i]._180) {
//                   // Cubes[i].translate.x += Stage[3].GetBackPos().y - Cubes[i].GetBackPos().x;
//                }
//            }
//        }
//    }
//    else if (Stage[0].rotate.z > 180.0f && Stage[0].rotate.z < 270.0f) {
//
//    }
//    else if (Stage[0].rotate.z > 270.0f && Stage[0].rotate.z < 360.0f) {
//        for (int i = 0; i < 3; ++i) {
//            if (Cubes[i].GetRightPos().x < Stage[3].GetRightPos().x && Cubes[i]._360) {
//                Cubes[i].translate.x += 0.001f * (Stage[0].rotate.z / 4);
//                if (Cubes[i].GetRightPos().x > Stage[3].GetRightPos().x) {
//                    Cubes[i].translate.x += Stage[3].GetRightPos().x - Cubes[i].GetRightPos().x;
//                }
//            }
//            else if (Cubes[i].GetRightPos().x > Stage[3].GetRightPos().x && Cubes[i]._360) {
//                Cubes[i].translate.x += Stage[3].GetRightPos().x - Cubes[i].GetRightPos().x;
//                Cubes[i]._360 = false;
//            }
//        }
//    }
//    else if (Stage[0].rotate.z >= 360.0f || Stage[0].rotate.z <= -360.0f) {
//        Stage[0].rotate.z = 0.0f;
//    }
//    else if (Stage[0].rotate.z < 0) {
//        for (int i = 0; i < 3; ++i) {
//            Cubes[i]._90 = Cubes[i]._180 = Cubes[i]._270 = Cubes[i]._360 = true;
//        }
//        Stage[0].rotate.z += Stage[0].rotate.z + 360.0f;
//    }
//    else {
//        for (int i = 0; i < 3; ++i) {
//            Cubes[i]._90 = Cubes[i]._180 = Cubes[i]._270 = Cubes[i]._360 = true;
//        }
//    }
//}

//void NewMove() {
//    float go_down = 0.01;
//
//    for (int i = 0; i < 3; ++i) {
//        if (Cubes[i].GetLeftPos().x == Stage[3].GetLeftPos().x) {
//            
//        }
//        else if (Cubes[i].GetRightPos().x == Stage[3].GetRightPos().x) {
//            go_down = 0;
//        }
//        else if (Cubes[i].GetBackPos().y == Stage[3].GetBackPos().y) {
//            go_down = 0;
//        }
//        else if (Cubes[i].GetFrontPos().y == Stage[3].GetFrontPos().y) {
//            go_down = 0;
//        }
//        else {
//
//        }
//    }
//}

void Menu() {
    cout << "공 만들기(z)" << endl;
    cout << "육면체 z축회전(마우스 드래그이동)" << endl;
    cout << "카메라 앞뒤(z, Z)" << endl;
    cout << "카메라 좌우(x, X)" << endl;
    cout << "카메라 공전(y, Y)" << endl;
    cout << "프로그램 종료(q)" << endl;
}