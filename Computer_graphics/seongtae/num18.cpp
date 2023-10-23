#define WinWidth 800
#define WinHeight 800
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;


struct Object {
    GLUquadricObj* qobj = gluNewQuadric();

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    Object* Parent = nullptr;

    glm::mat4 GetMatrix() {
        glm::mat4 result = glm::mat4(1.0f);
        if (Parent) {
            result = Parent->GetMatrix() * result;
        }
        result = glm::translate(result, Position);
        result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0.0, 0.0));
        result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0.0, 1.0, 0.0));
        result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0.0, 0.0, 1.0));
        result = glm::scale(result, glm::vec3(Scale.x, Scale.y, Scale.z));
        return result;
    }
};
struct Circle {
    vector<GLfloat> pos;
    vector<GLfloat> color;
    glm::vec3 Rotation = { 0.0, 0.0, 0.0 };
    glm::vec3 Start = { 0.0, 0.0, 0.0 };
    glm::vec3 Scale = { 1.0, 1.0, 1.0 };

    vector<GLfloat> GetPos() {
        if (pos.size()) {
            return pos;
        }
        for (int i = 0; i < 361; ++i) {
            float temp = (float)i;
            float x = 0.4 * glm::cos(glm::radians(temp));
            float y = 0.0;
            float z = 0.4 * glm::sin(glm::radians(temp));
            pos.push_back(x); pos.push_back(y); pos.push_back(z);
        }
        return pos;
    }

    vector<GLfloat> GetColor() {
        if (color.size()) {
            return color;
        }
        for (int i = 0; i < 361; ++i) {
            color.push_back(1.0); color.push_back(1.0); color.push_back(1.0);
        }
        return color;
    }

    glm::mat4 GetMatrix() {
        glm::mat4 result = glm::mat4(1.0f);
        result = glm::translate(result, glm::vec3(Start.x, Start.y, Start.z));
        result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0.0, 0.0));
        result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0.0, 0.0, 1.0));
        result = glm::scale(result, glm::vec3(Scale.x, Scale.y, Scale.z));
        return result;
    }
    void Init() {
        Rotation = glm::vec3(1.0f);
        Start = glm::vec3(0.0f);
        Scale = glm::vec3(1.0f);
    }
};
struct Camera {
    float movex{ 0.0 }, movey{ 0.0 }, movez{ 0.0 };
    glm::vec3 campos{ 0.0f, 0.1f, 1.0f };
    glm::vec3 targetpos{ 0.0f, 0.0f, 0.0f };

    glm::vec3 cameraPos = glm::vec3(campos.x, campos.y, campos.z); //EYE
    glm::vec3 cameraTarget = glm::vec3(targetpos.x, targetpos.y, targetpos.z); // At
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Up
    
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 GetLookAt() {
        return glm::lookAt(cameraPos, cameraDirection, cameraUp);
    }
    glm::mat4 GetPerspective() {
        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WinWidth / (float)WinHeight, 0.1f, 50.0f);
        proj = glm::translate(proj, glm::vec3(movex, movey, movez));
        return proj;
    }
};
struct Buffer {
    GLuint vao;
    GLuint vbo[2];
};

Object Sun, Earth, Moon;
Circle circle;
Camera cam;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
const string filetobuf(const char* file);
void Convert(int x, int y, float* ox, float* oy);
void KeyBoard(unsigned char key, int x, int y);
void TimerFunction(int value);
void TimerFunction2(int value);

GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;
GLuint s_program;
Buffer CBuf[6];

bool Solid{ false };
float revol1{ 0.0f }, revol2{ 0.0f }, revol3{ 0.0f };
bool dirY{ false }, rotY{ false };

void make_vertexShader() {
    string vertexsource;
    vertexsource = filetobuf("vertex18.glsl");


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
    fragmentsource = filetobuf("fragment18.glsl");

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
    for (int i = 0; i < 6; ++i) {
        glGenVertexArrays(1, &CBuf[i].vao); //--- VAO 를 지정하고 할당하기

        glBindVertexArray(CBuf[i].vao); //--- VAO를 바인드하기

        glGenBuffers(2, CBuf[i].vbo); //--- 2개의 VBO를 지정하고 할당하기

        glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, circle.GetPos().size() * sizeof(GLfloat), circle.GetPos().data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, circle.GetColor().size() * sizeof(GLfloat), circle.GetColor().data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
    }
}

//void MKVaoVbo(GLuint vao, GLuint vbo[2], vector<GLfloat> vertex, vector<GLfloat> color) {
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    glGenBuffers(2, vbo); 
//
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
//    glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(GLfloat), vertex.data(), GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
//    glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(GLfloat), color.data(), GL_STATIC_DRAW);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    glEnableVertexAttribArray(1);
//}

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

void main(int argc, char** argv)
{
    Earth.Parent = &Sun;
    Moon.Parent = &Earth;
    Sun.Scale.x = Sun.Scale.y = Sun.Scale.z = 0.3;
    Earth.Scale.x = Earth.Scale.y = Earth.Scale.z = 0.2;
    Moon.Scale.x = Moon.Scale.y = Moon.Scale.z = 0.2;

    glutInit(&argc, argv); // glut 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
    glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
    glutInitWindowSize(WinWidth, WinHeight); // 윈도우의 크기 지정
    glutCreateWindow("Example18"); // 윈도우 생성(윈도우 이름)
    //--- GLEW 초기화하기
    glewExperimental = GL_TRUE;
    glewInit();

    //--- 세이더 읽어와서 세이더 프로그램 만들기
    InitShader();
    InitBuffer();
    /*for (int i = 0; i < 3; ++i) {
        MKVaoVbo(CBuf[i].vao, CBuf[i].vbo, circle[i].GetPos(), circle[i].GetColor());
    }
    MKVaoVbo(LBuf.vao, LBuf.vbo, Line, LineColor);*/

    glutTimerFunc(100, TimerFunction, 1);

    glutDisplayFunc(drawScene); // 출력 함수의 지정
    glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
    glutKeyboardFunc(KeyBoard);
    glutMainLoop(); // 이벤트 처리 시작 
}

GLvoid drawScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(s_program);

    //원근투영===================================================================================================
    unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");
    unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(cam.GetLookAt()));
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(cam.GetPerspective()));

    //태양===================================================================================================
    glm::mat4 color = { 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
    unsigned int colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Sun.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));

    if (Solid) {
        gluQuadricDrawStyle(Sun.qobj, GLU_FILL);
    }
    else {
        gluQuadricDrawStyle(Sun.qobj, GLU_LINE);
    }
    gluSphere(Sun.qobj, 0.3, 50, 50);


    //지구===================================================================================================
    //1번 지구
    color = { 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Earth.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));

    Earth.Position.x = glm::cos(glm::radians(revol1)) * 1.3;
    Earth.Position.y = 0.0f;
    Earth.Position.z = glm::sin(glm::radians(revol1)) * 1.3;
    Earth.Position = glm::vec4(Earth.Position.x, Earth.Position.y, Earth.Position.z, 1);

    if (Solid) {
        gluQuadricDrawStyle(Earth.qobj, GLU_FILL);
    }
    else {
        gluQuadricDrawStyle(Earth.qobj, GLU_LINE);
    }
    gluSphere(Earth.qobj, 0.3, 50, 50);

    glBindVertexArray(CBuf[3].vao);
    color = { 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0 };
    circle.Init();
    circle.Start = Earth.Position;
    circle.Scale.x = circle.Scale.y = circle.Scale.z = 0.3;
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Sun.GetMatrix() * circle.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));
    glDrawArrays(GL_LINE_STRIP, 0, circle.GetPos().size());

    color = { 0.0, 0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Moon.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));

    Moon.Position.x = glm::cos(glm::radians(revol1)) * 0.6;
    Moon.Position.y = 0.0f;
    Moon.Position.z = glm::sin(glm::radians(revol1)) * 0.6;
    Moon.Position = glm::vec4(Moon.Position.x, Moon.Position.y, Moon.Position.z, 1);

    if (Solid) {
        gluQuadricDrawStyle(Moon.qobj, GLU_FILL);
    }
    else {
        gluQuadricDrawStyle(Moon.qobj, GLU_LINE);
    }
    gluSphere(Moon.qobj, 0.3, 50, 50);

    //2번지구
    color = { 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Earth.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));

    Earth.Position.x = glm::cos(glm::radians(revol2)) * 1.3;
    Earth.Position.y = 0.0f;
    Earth.Position.z = glm::sin(glm::radians(revol2)) * 1.3;
    glm::mat4 R1 = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0, 0, 1));
    Earth.Position = glm::vec4(Earth.Position.x, Earth.Position.y, Earth.Position.z, 1) * R1;

    if (Solid) {
        gluQuadricDrawStyle(Earth.qobj, GLU_FILL);
    }
    else {
        gluQuadricDrawStyle(Earth.qobj, GLU_LINE);
    }
    gluSphere(Earth.qobj, 0.3, 50, 50);

    glBindVertexArray(CBuf[4].vao);
    color = { 1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0 };
    circle.Init();
    circle.Start = Earth.Position;
    circle.Scale.x = circle.Scale.y = circle.Scale.z = 0.3;
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Sun.GetMatrix() * circle.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));
    glDrawArrays(GL_LINE_STRIP, 0, circle.GetPos().size());

    color = { 0.5, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Moon.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));

    Moon.Position.x = glm::cos(glm::radians(revol1)) * 0.6;
    Moon.Position.y = 0.0f;
    Moon.Position.z = glm::sin(glm::radians(revol1)) * 0.6;
    Moon.Position = glm::vec4(Moon.Position.x, Moon.Position.y, Moon.Position.z, 1);

    if (Solid) {
        gluQuadricDrawStyle(Moon.qobj, GLU_FILL);
    }
    else {
        gluQuadricDrawStyle(Moon.qobj, GLU_LINE);
    }
    gluSphere(Moon.qobj, 0.3, 50, 50);

    //3번 지구
    color = { 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Earth.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));

    Earth.Position.x = glm::cos(glm::radians(revol3)) * 1.3;
    Earth.Position.y = 0.0f;
    Earth.Position.z = glm::sin(glm::radians(revol3)) * 1.3;
    R1 = glm::mat4(1.0f);
    R1 = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0, 0, 1));
    Earth.Position = glm::vec4(Earth.Position.x, Earth.Position.y, Earth.Position.z, 1) * R1;

    if (Solid) {
        gluQuadricDrawStyle(Earth.qobj, GLU_FILL);
    }
    else {
        gluQuadricDrawStyle(Earth.qobj, GLU_LINE);
    }
    gluSphere(Earth.qobj, 0.3, 50, 50);

    glBindVertexArray(CBuf[5].vao);
    color = { 1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0 };
    circle.Init();
    circle.Start = Earth.Position;
    circle.Scale.x = circle.Scale.y = circle.Scale.z = 0.3;
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Sun.GetMatrix() * circle.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));
    glDrawArrays(GL_LINE_STRIP, 0, circle.GetPos().size());

    color = { 0.5, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    colorLocation = glGetUniformLocation(s_program, "GluColor");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Moon.GetMatrix()));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));

    Moon.Position.x = glm::cos(glm::radians(revol1)) * 0.6;
    Moon.Position.y = 0.0f;
    Moon.Position.z = glm::sin(glm::radians(revol1)) * 0.6;
    Moon.Position = glm::vec4(Moon.Position.x, Moon.Position.y, Moon.Position.z, 1);

    if (Solid) {
        gluQuadricDrawStyle(Moon.qobj, GLU_FILL);
    }
    else {
        gluQuadricDrawStyle(Moon.qobj, GLU_LINE);
    }
    gluSphere(Moon.qobj, 0.3, 50, 50);

    //원궤적===================================================================================================
    glBindVertexArray(CBuf[0].vao);
    color = { 1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0 };
    glm::mat4 MT = glm::mat4(1.0f);
    MT = glm::scale(MT, glm::vec3(3.3, 3.3, 3.3));

    colorLocation = glGetUniformLocation(s_program, "GluColor");
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Sun.GetMatrix() * MT));
    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));
    glDrawArrays(GL_LINE_STRIP, 0, circle.GetPos().size());

    glBindVertexArray(CBuf[1].vao);
    circle.Init();
    circle.Rotation.z = 45.0f;
    circle.Scale.x = 3.3; circle.Scale.y = 3.3; circle.Scale.z = 3.3;
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Sun.GetMatrix() * circle.GetMatrix()));
    glDrawArrays(GL_LINE_STRIP, 0, circle.GetPos().size());

    glBindVertexArray(CBuf[2].vao);
    circle.Init();
    circle.Rotation.z = -45.0f;
    circle.Scale.x = 3.3; circle.Scale.y = 3.3; circle.Scale.z = 3.3;
    modelLocation = glGetUniformLocation(s_program, "modelTransform");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Sun.GetMatrix() * circle.GetMatrix()));
    glDrawArrays(GL_LINE_STRIP, 0, circle.GetPos().size());

    glutSwapBuffers(); // 화면에 출력하기
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

void KeyBoard(unsigned char key, int x, int y) {
    switch (key) {
    case 'm':
        Solid = true;
        break;
    case 'M':
        Solid = false;
        break;
    case 'w':
        cam.movey += 0.1;
        break;
    case 'a':
        cam.movex -= 0.1;
        break;
    case 's':
        cam.movey -= 0.1;
        break;
    case 'd':
        cam.movex += 0.1;
        break;
    case 'z':
        cam.movez += 0.1;
        break;
    case 'x':
        cam.movez -= 0.1;
        break;
    case 'y':
        if (!rotY) {
            dirY = true;
            rotY = true;
            glutTimerFunc(100, TimerFunction2, 1);
        }
        else {
            rotY = false;
        }
        break;
    case 'Y':
        if (!rotY) {
            dirY = false;
            rotY = true;
            glutTimerFunc(100, TimerFunction2, 1);
        }
        else {
            rotY = false;
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void TimerFunction(int value) {
    revol1 += 5.0f;
    if (revol1 > 360) {
        revol1 = 0;
    }
    revol2 += 3.0f;
    if (revol2 > 360) {
        revol2 = 0;
    }
    revol3 += 1.0f;
    if (revol3 > 360) {
        revol3 = 0;
    }
    glutTimerFunc(100, TimerFunction, 1);
    glutPostRedisplay();
}

void TimerFunction2(int value) {
    if (dirY) {
        Sun.Rotation.y += 5.0f;
    }
    else {
        Sun.Rotation.y -= 5.0f;
    }
    if (rotY) {
        glutTimerFunc(100, TimerFunction2, 1);
    }
}
 