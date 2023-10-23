//#define WinWidth 800
//#define WinHeight 800
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//using namespace std;
//
//class TranMatrix {
//public:
//    glm::vec3 rotate{ 0.0, 0.0, 0.0 };
//    glm::vec3 translate{ 0.0, 0.0, 0.0 };
//    glm::vec3 scale{ 1.0, 1.0, 1.0 };
//
//    glm::vec3 pre_rotate{ 0.0, 0.0, 0.0 };
//    glm::vec3 pre_translate{ 0.0, 0.0, 0.0 };
//    glm::vec3 pre_scale{ 1.0, 1.0, 1.0 };
//
//    glm::vec3 axis_translate{ 0.0, 0.0, 0.0 };
//
//    void Init() {
//        translate = glm::vec3(0.0f);
//        rotate = glm::vec3(0.0f);
//        scale = glm::vec3(1.0f);
//    }
//};
//class Object : public TranMatrix {
//public:
//    Object* Parent = nullptr;
//    vector<GLfloat> vertex;
//    vector<GLfloat> color;
//    glm::vec3 pivot{ 0.0f, -0.5f, 0.0f };
//
//    glm::mat4 GetMatrix() {
//        glm::mat4 result(1.0f);
//        if (Parent) {
//            result = Parent->GetMatrix() * result;
//        }
//
//        result = glm::translate(result, pivot);
//        result = glm::translate(result, pre_translate);
//        result = glm::scale(result, pre_scale);
//        result = glm::translate(result, -pivot);
//
//        result = glm::translate(result, translate);
//        result = glm::translate(result, glm::vec3(0.0, -0.52, axis_translate.z));
//        result = glm::rotate(result, glm::radians(rotate.x), glm::vec3(1.0, 0.0, 0.0));
//        result = glm::translate(result, glm::vec3(0.0, 0.52, -axis_translate.z));
//        result = glm::rotate(result, glm::radians(rotate.y), glm::vec3(0.0, 1.0, 0.0));
//        result = glm::rotate(result, glm::radians(rotate.z), glm::vec3(0.0, 0.0, 1.0));
//        result = glm::scale(result, scale);
//
//        return result;
//    }
//
//    glm::vec3 GetTopPos() {
//        glm::vec3 result(1.0f);
//        glm::mat4 temp(1.0f);
//        glm::vec4 cubepos = { 0.0, 0.5, 0.5, 1.0 };
//
//        cubepos = GetMatrix() * cubepos;
//
//        result = { cubepos.x, cubepos.y, cubepos.z };
//        return result;
//    }
//    glm::vec3 GetBottomPos() {
//        glm::vec3 result(1.0f);
//        glm::mat4 temp(1.0f);
//        glm::vec4 cubepos = { 0.0, -0.5, -0.5, 1.0 };
//
//        cubepos = GetMatrix() * cubepos;
//
//        result = { cubepos.x, cubepos.y, cubepos.z };
//        return result;
//    }
//
//};
//class CubeObject : public Object {
//public:
//    CubeObject() = default;
//
//    CubeObject(GLfloat r, GLfloat g, GLfloat b) {
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
//        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
//
//        //아래
//        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
//        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
//
//        //위
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
//        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
//
//        //앞면
//        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
//        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//
//        //왼쪽
//        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
//        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
//        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//
//        //오른쪽
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
//        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
//        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
//
//        for (int i = 0; i < 36; ++i) {
//            color.push_back(r); color.push_back(g); color.push_back(b);
//        }
//    }
//};
//class Camera : public TranMatrix {
//public:
//    glm::vec3 campos{ 0.0, 1.0, 5.0 };
//    glm::vec3 targetpos{ 0.0f, 0.0f, 0.0f };
//
//    glm::mat4 GetLookAt() {
//        glm::vec3 cameraPos = glm::vec3(campos.x, campos.y, campos.z); //EYE
//        glm::vec3 cameraTarget = glm::vec3(targetpos.x, targetpos.y, targetpos.z); // At
//        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Up
//
//        glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
//
//        return glm::lookAt(cameraPos, cameraDirection, cameraUp);
//    }
//    glm::mat4 GetPerspective() {
//        glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WinWidth / (float)WinHeight, 0.1f, 50.0f);
//        proj = glm::translate(proj, translate);
//        proj = glm::rotate(proj, glm::radians(rotate.y), glm::vec3(0.0, 1.0, 0.0));
//        return proj;
//    }
//};
//
//struct Buffer {
//    GLuint vao;
//    GLuint vbo[2];
//};
//
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//const string filetobuf(const char* file);
//void Convert(int x, int y, float* ox, float* oy);
//void KeyBoard(unsigned char key, int x, int y);
//void TimerFunc(int value);
//void Init();
//
//GLuint shaderID;
//GLuint vertexShader;
//GLuint fragmentShader;
//GLuint s_program;
//Buffer CBuf[5];
//CubeObject* Cubes;
//Object Base;
//Camera cam;
//int dirX{ 0 }, dirY{ 0 }, dirZ{ 0 };
//bool TimerX{ false }, TimerY{ false }, TimerZ{ false };
//bool CamR{ false };
//
//void make_vertexShader() {
//    string vertexsource;
//    vertexsource = filetobuf("vertex18.glsl");
//
//
//    vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    const char* raw_str = vertexsource.c_str();
//
//    glShaderSource(vertexShader, 1, &raw_str, NULL);
//    glCompileShader(vertexShader);
//
//    GLint result;
//    GLchar errorLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
//    if (!result)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
//        cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
//        return;
//    }
//}
//
//void make_fragmentShader() {
//    string fragmentsource;
//    fragmentsource = filetobuf("fragment18.glsl");
//
//    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    const char* raw_str = fragmentsource.c_str();
//    glShaderSource(fragmentShader, 1, &raw_str, NULL);
//    glCompileShader(fragmentShader);
//
//    GLint result;
//    GLchar errorLog[512];
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
//    if (!result)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
//        cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
//        return;
//    }
//
//}
//
//void InitBuffer() {
//    for (int i = 0; i < 5; ++i) {
//        glGenVertexArrays(1, &CBuf[i].vao); //--- VAO 를 지정하고 할당하기
//
//        glBindVertexArray(CBuf[i].vao); //--- VAO를 바인드하기
//
//        glGenBuffers(2, CBuf[i].vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//        if (i < 4) {
//            glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[0]);
//            glBufferData(GL_ARRAY_BUFFER, Cubes[i].vertex.size() * sizeof(GLfloat), Cubes[i].vertex.data(), GL_STATIC_DRAW);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[1]);
//            glBufferData(GL_ARRAY_BUFFER, Cubes[i].color.size() * sizeof(GLfloat), Cubes[i].color.data(), GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(1);
//        }
//        else {
//            glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[0]);
//            glBufferData(GL_ARRAY_BUFFER, Base.vertex.size() * sizeof(GLfloat), Base.vertex.data(), GL_STATIC_DRAW);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, CBuf[i].vbo[1]);
//            glBufferData(GL_ARRAY_BUFFER, Base.color.size() * sizeof(GLfloat), Base.color.data(), GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(1);
//        }
//    }
//}
//
//void InitShader()
//{
//    make_vertexShader(); //--- 버텍스 세이더 만들기
//    make_fragmentShader(); //--- 프래그먼트 세이더 만들기
//    //-- shader Program
//
//    s_program = glCreateProgram();
//    glAttachShader(s_program, vertexShader);
//    glAttachShader(s_program, fragmentShader);
//    glLinkProgram(s_program);
//    //  checkCompileErrors(s_program, "PROGRAM");
//
//        //--- 세이더 삭제하기
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//    //--- Shader Program 사용하기
//    glUseProgram(s_program);
//
//}
//
//void main(int argc, char** argv)
//{
//    Init();
//    Cubes[0].Parent = &Base;
//    Cubes[1].Parent = &Cubes[0];
//    Cubes[2].Parent = &Cubes[1];
//    Cubes[3].Parent = &Cubes[1];
//
//    //0.1
//    Cubes[0].pre_scale.y = 0.1;
//    Cubes[0].scale = { 0.3, 1.0, 0.3 };
//
//    //0.07
//    Cubes[1].pre_scale.y = 0.7;
//    Cubes[1].pre_translate.y = 1.0;
//    Cubes[1].scale = { 0.7, 1.0, 0.7 };
//
//    Cubes[2].pre_scale.y = 2.0;
//    Cubes[2].pre_translate.y = 1.0;
//    Cubes[2].pre_translate.x = 0.3;
//    Cubes[2].scale = { 0.2, 1.0, 0.2 };
//
//    Cubes[3].pre_scale.y = 2.0;
//    Cubes[3].pre_translate.y = 1.0;
//    Cubes[3].pre_translate.x = -0.3;
//    Cubes[3].scale = { 0.2, 1.0, 0.2 };
//
//    glutInit(&argc, argv); // glut 초기화
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
//    glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
//    glutInitWindowSize(WinWidth, WinHeight); // 윈도우의 크기 지정
//    glutCreateWindow("Example19"); // 윈도우 생성(윈도우 이름)
//    //--- GLEW 초기화하기
//    glewExperimental = GL_TRUE;
//    glewInit();
//
//
//    //--- 세이더 읽어와서 세이더 프로그램 만들기
//    InitShader();
//    InitBuffer();
//
//    //--- Timer
//    glutTimerFunc(100, TimerFunc, 1);
//
//    glutDisplayFunc(drawScene); // 출력 함수의 지정
//    //glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
//    glutKeyboardFunc(KeyBoard);
//    glutMainLoop(); // 이벤트 처리 시작 
//}
//
//GLvoid drawScene()
//{
//    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//
//    glUseProgram(s_program);
//
//    //원근투영===================================================================================================
//
//    Reshape(WinWidth, WinHeight);
//    unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform");
//    unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
//    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(cam.GetLookAt()));
//    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(cam.GetPerspective()));
//
//    glBindVertexArray(CBuf[4].vao);
//    glm::mat4 color = { 1.0, 0.0, 0.0, 0.0,
//                        0.0, 1.0, 0.0, 0.0,
//                        0.0, 0.0, 1.0, 0.0,
//                        0.0, 0.0, 0.0, 1.0 };
//    glm::mat4 MT = glm::mat4(1.0f);
//
//    unsigned int colorLocation = glGetUniformLocation(s_program, "GluColor");
//    unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Base.GetMatrix()));
//    glUniformMatrix4fv(colorLocation, 1, GL_FALSE, glm::value_ptr(color));
//    glDrawArrays(GL_TRIANGLES, 0, Base.vertex.size());
//
//    glBindVertexArray(CBuf[0].vao);
//    modelLocation = glGetUniformLocation(s_program, "modelTransform");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Cubes[0].GetMatrix()));
//    glDrawArrays(GL_TRIANGLES, 0, Cubes[0].vertex.size());
//
//    glBindVertexArray(CBuf[1].vao);
//    modelLocation = glGetUniformLocation(s_program, "modelTransform");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Cubes[1].GetMatrix()));
//    glDrawArrays(GL_TRIANGLES, 0, Cubes[1].vertex.size());
//
//    glBindVertexArray(CBuf[2].vao);
//    modelLocation = glGetUniformLocation(s_program, "modelTransform");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Cubes[2].GetMatrix()));
//    glDrawArrays(GL_TRIANGLES, 0, Cubes[2].vertex.size());
//
//    glBindVertexArray(CBuf[3].vao);
//    modelLocation = glGetUniformLocation(s_program, "modelTransform");
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(Cubes[3].GetMatrix()));
//    glDrawArrays(GL_TRIANGLES, 0, Cubes[3].vertex.size());
//
//
//    cout << "red : " << Cubes[0].GetTopPos().y << endl;
//    cout << "red : " << Cubes[0].GetBottomPos().y << endl;
//    cout << "blue : " << Cubes[1].GetTopPos().y << endl;
//    cout << "blue : " << Cubes[1].GetBottomPos().y << endl;
//    cout << "green : " << Cubes[2].GetTopPos().y << endl;
//    cout << "green : " << Cubes[2].GetBottomPos().y << endl;
//    cout << "green Front: " << Cubes[2].GetTopPos().z << endl;
//    cout << "green Back : " << Cubes[2].GetBottomPos().z << endl;
//    cout << endl;
//    glutSwapBuffers(); // 화면에 출력하기
//}
//
//GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
//{
//    glViewport(0, 0, w, h);
//}
//
//const string filetobuf(const char* file) {
//    string content = "";
//    string line = "";
//    ifstream in(file, ios::in);
//
//    while (!in.eof()) {
//        getline(in, line);
//        content.append(line + "\n");
//    }
//
//    in.close();
//    return content;
//}
//
//void Convert(int x, int y, float* ox, float* oy) {
//    *ox = (float)((x - (float)WinWidth / 2) * (float)(1 / (float)(WinWidth / 2)));
//    *oy = -(float)((y - (float)WinHeight / 2) * (float)(1 / (float)(WinHeight / 2)));
//}
//
//void KeyBoard(unsigned char key, int x, int y) {
//    switch (key) {
//    case 'b':
//        if (dirZ != 1) {
//            dirZ = 1;
//            TimerZ = true;
//        }
//        else {
//            dirZ = 0;
//            TimerZ = false;
//        }
//        break;
//    case 'B':
//        if (dirZ != -1) {
//            dirZ = -1;
//            TimerZ = true;
//        }
//        else {
//            dirZ = 0;
//            TimerZ = false;
//        }
//        break;
//    case 'm':
//        if (dirY != 1) {
//            dirY = 1;
//            TimerY = true;
//        }
//        else {
//            dirY = 0;
//            TimerY = false;
//        }
//        break;
//    case 'M':
//        if (dirY != -1) {
//            dirY = -1;
//            TimerY = true;
//        }
//        else {
//            dirY = 0;
//            TimerY = false;
//        }
//        break;
//    case 't':
//        if (dirX != 1) {
//            dirX = 1;
//            TimerX = true;
//        }
//        else {
//            dirX = 0;
//            TimerX = false;
//        }
//        break;
//    case 'T':
//        if (dirX != -1) {
//            dirX = -1;
//            TimerX = true;
//        }
//        else {
//            dirX = 0;
//            TimerX = false;
//        }
//        break;
//    case 'z':
//        cam.translate.z += 0.3f;
//        break;
//    case 'Z':
//        cam.translate.z -= 0.3f;
//        break;
//    case 'x':
//        cam.translate.x += 0.3f;
//        break;
//    case 'X':
//        cam.translate.x -= 0.3f;
//        break;
//    case 'y':
//        cam.rotate.y += 5.0f;
//        break;
//    case 'Y':
//        cam.rotate.y -= 5.0f;
//        break;
//    case 'r':
//    {
//        cam.pre_rotate.y = 5.0f;
//        glm::mat4 temp = glm::mat4(1.0f);
//        glm::vec4 campos_4 = { cam.campos, 1 };
//        temp = glm::rotate(temp, glm::radians(cam.pre_rotate.y), glm::vec3(0.0, 1.0, 0.0));
//        campos_4 = temp * campos_4;
//        cam.campos.x = campos_4.x; cam.campos.y = campos_4.y; cam.campos.z = campos_4.z;
//    }
//    break;
//    case 'R':
//    {
//        cam.pre_rotate.y = -5.0f;
//        glm::mat4 temp = glm::mat4(1.0f);
//        glm::vec4 campos_4 = { cam.campos, 1 };
//        temp = glm::rotate(temp, glm::radians(cam.pre_rotate.y), glm::vec3(0.0, 1.0, 0.0));
//        campos_4 = temp * campos_4;
//        cam.campos.x = campos_4.x; cam.campos.y = campos_4.y; cam.campos.z = campos_4.z;
//    }
//    break;
//    case 'a':
//        CamR = !CamR;
//        cam.pre_rotate.y = 5.0f;
//        break;
//    case 'A':
//        CamR = !CamR;
//        cam.pre_rotate.y = -5.0f;
//        break;
//    case 's':
//    case 'S':
//        dirX = dirY = dirZ = 0;
//        TimerX = TimerY = TimerZ = false;
//        CamR = false;
//        break;
//    case 'c':
//    case 'C':
//        Base.Init();
//        for (int i = 0; i < 4; ++i) {
//            Cubes[i].Init();
//        }
//        cam.Init();
//        cam.campos = { 0.0, 1.0, 5.0 };
//        Cubes[0].pre_scale.y = 0.1;
//        Cubes[0].scale = { 0.3, 1.0, 0.3 };
//        Cubes[1].pre_scale.y = 0.7;
//        Cubes[1].pre_translate.y = 1.0;
//        Cubes[1].scale = { 0.7, 1.0, 0.7 };
//        Cubes[2].pre_scale.y = 2.0;
//        Cubes[2].pre_translate.y = 1.0;
//        Cubes[2].pre_translate.x = 0.3;
//        Cubes[2].scale = { 0.2, 1.0, 0.2 };
//        Cubes[3].pre_scale.y = 2.0;
//        Cubes[3].pre_translate.y = 1.0;
//        Cubes[3].pre_translate.x = -0.3;
//        Cubes[3].scale = { 0.2, 1.0, 0.2 };
//        dirX = dirY = dirZ = 0;
//        TimerX = TimerY = TimerZ = false;
//        CamR = false;
//        break;
//    case 'q':
//    case 'Q':
//        delete[] Cubes;
//        exit(0);
//        break;
//    default:
//        break;
//    }
//    glutPostRedisplay();
//}
//
//void TimerFunc(int value) {
//    if (TimerZ) {
//        Cubes[0].translate.z += (0.05 * dirZ);
//        if (Cubes[0].GetBottomPos().z <= -0.8) {
//            dirZ *= -1;
//        }
//        else if (Cubes[0].GetTopPos().z >= 0.8) {
//            dirZ *= -1;
//        }
//    }
//
//    if (TimerY) {
//        Cubes[1].rotate.y += (5.0 * dirY);
//    }
//
//    if (TimerX) {
//        Cubes[2].rotate.x += (5.0 * dirX);
//        Cubes[3].rotate.x -= (5.0 * dirX);
//        if (Cubes[2].rotate.x >= 90) {
//            dirX = -1;
//        }
//        else if (Cubes[2].rotate.x <= -90) {
//            dirX = 1;
//        }
//    }
//
//    if (CamR) {
//        glm::mat4 temp = glm::mat4(1.0f);
//        glm::vec4 campos_4 = { cam.campos, 1 };
//        temp = glm::rotate(temp, glm::radians(cam.pre_rotate.y), glm::vec3(0.0, 1.0, 0.0));
//        campos_4 = temp * campos_4;
//        cam.campos.x = campos_4.x; cam.campos.y = campos_4.y; cam.campos.z = campos_4.z;
//    }
//    glutTimerFunc(100, TimerFunc, 1);
//
//    glutPostRedisplay();
//}
//
//void Init() {
//    //바닥
//    {
//        Base.vertex.push_back(0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(-0.8);
//        Base.vertex.push_back(0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(0.8);
//        Base.vertex.push_back(-0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(-0.8);
//        Base.vertex.push_back(-0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(-0.8);
//        Base.vertex.push_back(0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(0.8);
//        Base.vertex.push_back(-0.8); Base.vertex.push_back(-0.5); Base.vertex.push_back(0.8);
//
//        for (int i = 0; i < 18; ++i) {
//            Base.color.push_back(0.0);
//        }
//    }
//
//    Cubes = new CubeObject[4];
//    Cubes[0] = CubeObject(1.0, 0.0, 0.0);
//    Cubes[1] = CubeObject(0.0, 1.0, 0.0);
//    Cubes[2] = CubeObject(0.0, 0.0, 1.0);
//    Cubes[3] = CubeObject(0.0, 0.0, 1.0);
//
//
//}