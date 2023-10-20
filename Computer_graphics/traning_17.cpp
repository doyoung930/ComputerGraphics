//#define _CRT_SECURE_NO_WARNINGS
//#define WinWidth 800
//#define WinHeight 800
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <gl/glew.h>
//#include <gl/freeglut.h>
//#include <gl/freeglut_ext.h>
//
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//using namespace std;
//
//GLvoid drawScene(GLvoid);
//GLvoid Reshape(int w, int h);
//const string filetobuf(const char* file);
//void Convert(int x, int y, float* ox, float* oy);
//void KeyBoard(unsigned char key, int x, int y);
//void TimerFunction(int value);
//void TimerFunction2(int value);
//void TimerFunction3(int value);
//void TimerFunction4(int value);
//void TimerFunction5(int value);
//
//GLuint shaderID;
//GLuint vertexShader;
//GLuint fragmentShader;
//GLuint s_program[6];
//GLuint vao[10], vbo[20];
//
//bool shape{ false };
//bool rotateY{ false }, rotateF{ false }, rotateT{ false }, moveS{ false }, rotateS{ false };
//bool dirF{ false }, dirT{ false }, dirS{ false }, dirTS{ false };
//float rotY{ 0.0f }, rotF{ 0.0f }, rotT{ 0.0f }, rotS{ 0.0f }, sidey{ 0.0f };
//float lineX{ 30.0f }, lineY{ 30.0f }, lineMY{ 0.0f };
//float scale{ 0.4f };
//bool orthoproj{ false }, persproj{ false };
//
//GLfloat LineShape[6][3] = {
//    {-1.0f, 0.0f, 0.0f},
//    {1.0f, 0.0f, 0.0f},
//    {0.0f, -1.0f, 0.0f},
//    {0.0f, 1.0f, 0.0f},
//    {0.0f, 0.0f, -1.0f},
//    {0.0f, 0.0f, 1.0f},
//};
//GLfloat CubeShape[12][3] = {
//    //뒷면
//    //반시계
//  { 0.5f, -0.5f, -0.5f },
//  { -0.5f, -0.5f, -0.5f },
//  { -0.5f, 0.5f, -0.5f },
//
//  { 0.5f, 0.5f, -0.5f },
//  { 0.5f, -0.5f, -0.5f },
//  { -0.5f, 0.5f, -0.5f },
//
//  //시계
//  /* { 0.5f, -0.5f, -0.5f },
//  { -0.5f, -0.5f, -0.5f },
//  { 0.5f, 0.5f, -0.5f },
//
//  { -0.5f, -0.5f, -0.5f },
//  { -0.5f, 0.5f, -0.5f },
//  { 0.5f, 0.5f, -0.5f },*/
//
//    //아래
//    //반시계
//     { -0.5f, -0.5f, 0.5f },
//    { -0.5f, -0.5f, -0.5f },
//    { 0.5f, -0.5f, -0.5f },
//
//    { -0.5f, -0.5f, 0.5f },
//    { 0.5f, -0.5f, -0.5f },
//    { 0.5f, -0.5f, 0.5f },
//
//    //시계
//    /* { -0.5f, -0.5f, 0.5f },
//      { 0.5f, -0.5f, -0.5f },
//    { -0.5f, -0.5f, -0.5f },
//
//    { -0.5f, -0.5f, 0.5f },
//    { 0.5f, -0.5f, 0.5f },
//    { 0.5f, -0.5f, -0.5f },*/
//};
//GLfloat CubeTop[6][3] = {
//    //위
//    //반시계
//    {-0.5f, 0.5f, 0.5f},
//    { 0.5f, 0.5f, 0.5f },
//    { -0.5f, 0.5f, -0.5f },
//    { 0.5f, 0.5f, 0.5f },
//    { 0.5f, 0.5f, -0.5f },
//    { -0.5f, 0.5f, -0.5f },
//
//    //시계
//    /*{-0.5f, 0.5f, 0.5f},
//    { -0.5f, 0.5f, -0.5f },
//    { 0.5f, 0.5f, 0.5f },
//    
//    { 0.5f, 0.5f, 0.5f },
//    { -0.5f, 0.5f, -0.5f },
//    { 0.5f, 0.5f, -0.5f },*/
//    
//};
//GLfloat CubeFront[6][3] = {
//    //앞면
//    //반시계
//    { -0.5f, -0.5f, 0.5f },
//    { 0.5f, -0.5f, 0.5f },
//    {-0.5f, 0.5f, 0.5f},
//    { 0.5f, -0.5f, 0.5f },
//    { 0.5f, 0.5f, 0.5f },
//    {-0.5f, 0.5f, 0.5f},
//    //시계
//   /* { -0.5f, -0.5f, 0.5f },
//    {-0.5f, 0.5f, 0.5f},
//    { 0.5f, -0.5f, 0.5f },
//    
//    { 0.5f, -0.5f, 0.5f },
//    {-0.5f, 0.5f, 0.5f},
//    { 0.5f, 0.5f, 0.5f },*/
//    
//
//};
//GLfloat CubeSide[12][3] = {
//    //왼쪽
//    //반시계
//    { -0.5f, -0.5f, -0.5f },
//    {-0.5f, 0.5f, 0.5f},
//    { -0.5f, 0.5f, -0.5f },
//    { -0.5f, -0.5f, -0.5f },
//    { -0.5f, -0.5f, 0.5f },
//    {-0.5f, 0.5f, 0.5f},
//
//    //시계
//   /* { -0.5f, -0.5f, -0.5f },
//    { -0.5f, 0.5f, -0.5f },
//    {-0.5f, 0.5f, 0.5f},
//    
//    { -0.5f, -0.5f, -0.5f },
//    {-0.5f, 0.5f, 0.5f},
//    { -0.5f, -0.5f, 0.5f },
//    */
//
//  //오른쪽
//  //시계
//    /*{ 0.5f, -0.5f, 0.5f },
//    { 0.5f, 0.5f, 0.5f },
//    { 0.5f, -0.5f, -0.5f },
//    { 0.5f, -0.5f, -0.5f },
//    { 0.5f, 0.5f, 0.5f },
//    { 0.5f, 0.5f, -0.5f },*/
//    
//   //반시계
//  { 0.5f, -0.5f, 0.5f },
//    { 0.5f, -0.5f, -0.5f },
//    { 0.5f, 0.5f, 0.5f },
//    { 0.5f, -0.5f, -0.5f },
//    { 0.5f, 0.5f, -0.5f },
//    { 0.5f, 0.5f, 0.5f },
// 
//};
//GLfloat TetraSide1[3][3] = {
//    //앞면
//    {-0.5, -0.5, 0.5},
//    {0.5, -0.5, 0.5},
//    {0.0, 0.5, 0.0},
//};
//GLfloat TetraSide2[3][3] = {
//    //뒷면
//    {-0.5, -0.5, -0.5},
//    {0.0, 0.5, 0.0},
//    {0.5, -0.5, -0.5},
//};
//GLfloat TetraSide3[3][3] = {
//    //왼쪽
//    {-0.5, -0.5, -0.5},
//    {-0.5, -0.5, 0.5},
//    {0.0, 0.5, 0.0},
//};
//GLfloat TetraSide4[3][3] = {
//    //오른쪽
//    {0.5, -0.5, -0.5},
//    {0.5, -0.5, 0.5},
//    {0.0, 0.5, 0.0},
//};
//GLfloat TetraBase[6][3] = {
//    //바닥
//    {-0.5, -0.5, -0.5},
//    {0.5, -0.5, -0.5},
//    {0.5, -0.5, 0.5},
//
//    {-0.5, -0.5, -0.5},
//    {0.5, -0.5, 0.5},
//    {-0.5, -0.5, 0.5},
//};
//
//GLfloat Linecolors[6][3] = {
//    {1.0f, 0.0f, 0.0f},
//    {1.0f, 0.0f, 0.0f},
//    {0.0f, 1.0f, 0.0f},
//    {0.0f, 1.0f, 0.0f},
//    {0.0f, 0.0f, 1.0f},
//    {0.0f, 0.0f, 1.0f},
//};
//GLfloat Cubecolors[12][3] = {
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//   
//    {0.0, 1.0, 1.0},
//    {0.0, 1.0, 1.0},
//    {0.0, 1.0, 1.0},
//    {0.0, 1.0, 1.0},
//    {0.0, 1.0, 1.0},
//    {0.0, 1.0, 1.0},
//};
//GLfloat Topcolors[6][3] = {
//    {0.0, 1.0, 0.0},
//    {0.0, 1.0, 0.0},
//    {0.0, 1.0, 0.0},
//    {0.0, 1.0, 0.0},
//    {0.0, 1.0, 0.0},
//    {0.0, 1.0, 0.0},
//};
//GLfloat Frontcolors[6][3] = {
//    {1.0, 0.0, 0.0},
//    {1.0, 0.0, 0.0},
//    {1.0, 0.0, 0.0},
//    {1.0, 0.0, 0.0},
//    {1.0, 0.0, 0.0},
//    {1.0, 0.0, 0.0},
//
//};
//GLfloat Sidecolors[12][3] = {
//    {0.0, 0.0, 1.0},
//    {0.0, 0.0, 1.0},
//    {0.0, 0.0, 1.0},
//    {0.0, 0.0, 1.0},
//    {0.0, 0.0, 1.0},
//    {0.0, 0.0, 1.0},
//
//    {1.0, 0.0, 1.0},
//    {1.0, 0.0, 1.0},
//    {1.0, 0.0, 1.0},
//    {1.0, 0.0, 1.0},
//    {1.0, 0.0, 1.0},
//    {1.0, 0.0, 1.0},
//};
//GLfloat Sidecolors1[3][3] = {
//    {1.0, 0.0, 0.0},
//    {1.0, 0.0, 0.0},
//    {1.0, 0.0, 0.0},
//};
//GLfloat Sidecolors2[3][3] = {
//    {0.0, 1.0, 0.0},
//    {0.0, 1.0, 0.0},
//    {0.0, 1.0, 0.0},
//};
//GLfloat Sidecolors3[3][3] = {
//    {0.0, 0.0, 1.0},
//    {0.0, 0.0, 1.0},
//    {0.0, 0.0, 1.0},
//};
//GLfloat Sidecolors4[3][3] = {
//    {1.0, 0.0, 1.0},
//    {1.0, 0.0, 1.0},
//    {1.0, 0.0, 1.0},
//};
//GLfloat Basecolors[6][3] = {
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//    {1.0, 1.0, 0.0},
//};
//
//void make_vertexShader() {
//    string vertexsource;
//    vertexsource = filetobuf("vertex.glsl");
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
//    fragmentsource = filetobuf("fragment.glsl");
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
//    for (int i = 0; i < 10; ++i) {
//        if (i == 0) {
//            glGenVertexArrays(1, &vao[0]); //--- VAO 를 지정하고 할당하기
//
//            glBindVertexArray(vao[0]); //--- VAO를 바인드하기
//
//            glGenBuffers(10, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
//            glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), LineShape, GL_STATIC_DRAW);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
//            glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Linecolors, GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(1);
//        }
//        else if (i == 1) {
//            glGenVertexArrays(1, &vao[1]); //--- VAO 를 지정하고 할당하기
//
//            glBindVertexArray(vao[1]); //--- VAO를 바인드하기
//
//            glGenBuffers(10, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
//            glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), CubeShape, GL_STATIC_DRAW);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
//            glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), Cubecolors, GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(1);
//        }
//        else if (i == 2) {
//            glGenVertexArrays(1, &vao[2]); //--- VAO 를 지정하고 할당하기
//
//            glBindVertexArray(vao[2]); //--- VAO를 바인드하기
//
//            glGenBuffers(10, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);
//            glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), CubeFront, GL_STATIC_DRAW);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);
//            glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Frontcolors, GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(1);
//        }
//        else if (i == 3) {
//            glGenVertexArrays(1, &vao[3]); //--- VAO 를 지정하고 할당하기
//
//            glBindVertexArray(vao[3]); //--- VAO를 바인드하기
//
//            glGenBuffers(10, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);
//            glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), CubeTop, GL_STATIC_DRAW);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);
//            glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Topcolors, GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(1);
//        }
//        else if (i == 4) {
//            glGenVertexArrays(1, &vao[4]); //--- VAO 를 지정하고 할당하기
//
//            glBindVertexArray(vao[4]); //--- VAO를 바인드하기
//
//            glGenBuffers(10, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);
//            glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), CubeSide, GL_STATIC_DRAW);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);
//            glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(GLfloat), Sidecolors, GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(1);
//        }
//        else if (i == 5) {
//            glGenVertexArrays(1, &vao[5]); //--- VAO 를 지정하고 할당하기
//
//            glBindVertexArray(vao[5]); //--- VAO를 바인드하기
//
//            glGenBuffers(20, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);
//            glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), TetraSide1, GL_STATIC_DRAW);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[11]);
//            glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), Sidecolors1, GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(1);
//        }
//        else if (i == 6) {
//            glGenVertexArrays(1, &vao[6]); //--- VAO 를 지정하고 할당하기
//
//            glBindVertexArray(vao[6]); //--- VAO를 바인드하기
//
//            glGenBuffers(20, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[12]);
//            glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), TetraSide2, GL_STATIC_DRAW);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, vbo[13]);
//            glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), Sidecolors2, GL_STATIC_DRAW);
//            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//            glEnableVertexAttribArray(1);
//        }
//        else if (i == 7) {
//        glGenVertexArrays(1, &vao[7]); //--- VAO 를 지정하고 할당하기
//
//        glBindVertexArray(vao[7]); //--- VAO를 바인드하기
//
//        glGenBuffers(20, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//        glBindBuffer(GL_ARRAY_BUFFER, vbo[14]);
//        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), TetraSide3, GL_STATIC_DRAW);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//        glEnableVertexAttribArray(0);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo[15]);
//        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), Sidecolors3, GL_STATIC_DRAW);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//        glEnableVertexAttribArray(1);
//        }
//        else if (i == 8) {
//        glGenVertexArrays(1, &vao[8]); //--- VAO 를 지정하고 할당하기
//
//        glBindVertexArray(vao[8]); //--- VAO를 바인드하기
//
//        glGenBuffers(20, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//        glBindBuffer(GL_ARRAY_BUFFER, vbo[16]);
//        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), TetraSide4, GL_STATIC_DRAW);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//        glEnableVertexAttribArray(0);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo[17]);
//        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), Sidecolors4, GL_STATIC_DRAW);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//        glEnableVertexAttribArray(1);
//        }
//        else if (i == 9) {
//        glGenVertexArrays(1, &vao[9]); //--- VAO 를 지정하고 할당하기
//
//        glBindVertexArray(vao[9]); //--- VAO를 바인드하기
//
//        glGenBuffers(20, vbo); //--- 2개의 VBO를 지정하고 할당하기
//
//        glBindBuffer(GL_ARRAY_BUFFER, vbo[18]);
//        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), TetraBase, GL_STATIC_DRAW);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//        glEnableVertexAttribArray(0);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo[19]);
//        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), Basecolors, GL_STATIC_DRAW);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
//        glEnableVertexAttribArray(1);
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
//    for (int i = 0; i < 6; ++i) {
//        s_program[i] = glCreateProgram();
//        glAttachShader(s_program[i], vertexShader);
//        glAttachShader(s_program[i], fragmentShader);
//        glLinkProgram(s_program[i]);
//        //  checkCompileErrors(s_program, "PROGRAM");
//
//          //--- 세이더 삭제하기
//        glDeleteShader(vertexShader);
//        glDeleteShader(fragmentShader);
//        //--- Shader Program 사용하기
//        glUseProgram(s_program[i]);
//    }
//}
//
//void main(int argc, char** argv)
//{
//    glutInit(&argc, argv); // glut 초기화
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정
//    glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
//    glutInitWindowSize(WinWidth, WinHeight); // 윈도우의 크기 지정
//    glutCreateWindow("Example17"); // 윈도우 생성(윈도우 이름)
//    //--- GLEW 초기화하기
//    glewExperimental = GL_TRUE;
//    glewInit();
//
//    //--- 세이더 읽어와서 세이더 프로그램 만들기
//    InitShader();
//    InitBuffer();
//   
//
//    glutDisplayFunc(drawScene); // 출력 함수의 지정
//    glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
//    glutKeyboardFunc(KeyBoard);
//    glutMainLoop(); // 이벤트 처리 시작 
//}
//
//GLvoid drawScene()
//{    
//    if (persproj) {
//        glClearDepth(1.0f);
//        glDepthFunc(GL_LESS);
//    }
//    else {
//        glClearDepth(0.0f);
//        glDepthFunc(GL_GREATER);
//    }
//    glEnable(GL_DEPTH_TEST);
//
//    glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 5.0f); //EYE
//    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // At
//    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); // Up
//
//    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
//    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
//    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
//
//    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//   
//    //xyz축-------------------------------------------------------------------------------------------
//    glUseProgram(s_program[0]);
//    glm::mat4 TR = glm::mat4(1.0f);
//    glm::mat4 RX = glm::mat4(1.0f);
//    glm::mat4 RY = glm::mat4(1.0f);
//    glm::mat4 view = glm::mat4(1.0f);
//    glm::mat4 projection = glm::mat4(1.0f);
//
//    RX = glm::rotate(RX, glm::radians(lineX), glm::vec3(1.0, 0.0, 0.0));
//    RY = glm::rotate(RY, glm::radians(lineY), glm::vec3(0.0, 1.0, 0.0));
//
//    if (persproj) {
//        view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//        projection = glm::perspective(glm::radians(45.0f), (float)WinWidth / (float)WinHeight, 0.1f, 50.0f);
//    }
//    else if (orthoproj) {
//        view = glm::lookAt(cameraPos, cameraDirection, cameraUp);
//        projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 10.0f, -50.0f); 
//    }
//    TR = RX * RY;
//
//    unsigned int modelLocation = glGetUniformLocation(s_program[0], "modelTransform");
//    unsigned int viewLocation = glGetUniformLocation(s_program[0], "viewTransform");
//    unsigned int projectionLocation = glGetUniformLocation(s_program[0], "projectionTransform");
//
//    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(TR));
//    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
//
//    glBindVertexArray(vao[0]);
//    glDrawArrays(GL_LINES, 0, 6);
//
//    //도형-------------------------------------------------------------------------------------------
//    glUseProgram(s_program[1]);
//    glm::mat4 TR2 = glm::mat4(1.0f);
//    glm::mat4 RY2 = glm::mat4(1.0f);
//    glm::mat4 S2 = glm::mat4(1.0f);
// 
//
//    RY2 = glm::rotate(RY2, glm::radians(rotY), glm::vec3(0.0, 1.0, 0.0));
//    S2 = glm::scale(S2, glm::vec3(scale, scale, scale));
//  
//    TR2 = TR * RY2 * S2;
//
//    unsigned int modelLocation2 = glGetUniformLocation(s_program[1], "modelTransform");
//    unsigned int viewLocation2 = glGetUniformLocation(s_program[1], "viewTransform");
//    unsigned int projectionLocation2 = glGetUniformLocation(s_program[1], "projectionTransform");
//
//    glUniformMatrix4fv(modelLocation2, 1, GL_FALSE, glm::value_ptr(TR2));
//    glUniformMatrix4fv(viewLocation2, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLocation2, 1, GL_FALSE, glm::value_ptr(projection));
//    
//
//    if (shape) {
//        
//    }
//    else {
//        glBindVertexArray(vao[1]);
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glDrawArrays(GL_TRIANGLES, 0, 12);
//    }
//    //앞면------------------------------------------------------------------------------------------------
//    glUseProgram(s_program[2]);
//
//    glm::mat4 MT = glm::mat4(1.0f);
//    glm::mat4 FrontRotate = glm::mat4(1.0f);
//
//    //부고이자스
//    FrontRotate = glm::translate(FrontRotate, glm::vec3(0.0, -0.5, 0.5));
//    FrontRotate = glm::rotate(FrontRotate, glm::radians(rotF), glm::vec3(1.0, 0.0, 0.0));
//    FrontRotate = glm::translate(FrontRotate, glm::vec3(0.0, 0.5, -0.5));
//
//    MT = TR2 * FrontRotate;
//
//    unsigned int modelLocation3 = glGetUniformLocation(s_program[2], "modelTransform");
//    unsigned int viewLocation3 = glGetUniformLocation(s_program[2], "viewTransform");
//    unsigned int projectionLocation3 = glGetUniformLocation(s_program[2], "projectionTransform");
//
//    glUniformMatrix4fv(modelLocation3, 1, GL_FALSE, glm::value_ptr(MT));
//    glUniformMatrix4fv(viewLocation3, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLocation3, 1, GL_FALSE, glm::value_ptr(projection));
//
//    if (shape) {
//
//    }
//    else {
//        glBindVertexArray(vao[2]);
//        
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//    }
//    //윗면--------------------------------------------------------------------------------------------------
//    glUseProgram(s_program[3]);
//    glm::mat4 MT2 = glm::mat4(1.0f);
//    glm::mat4 TopRotate = glm::mat4(1.0f);
//
//    TopRotate = glm::translate(TopRotate, glm::vec3(0.0, 0.5, 0.0));
//    TopRotate = glm::rotate(TopRotate, glm::radians(rotT), glm::vec3(1.0, 0.0, 0.0));
//    TopRotate = glm::translate(TopRotate, glm::vec3(0.0, -0.5, 0.0));
//
//    MT2 = TR2 * TopRotate;
//
//    unsigned int modelLocation4 = glGetUniformLocation(s_program[3], "modelTransform");
//    unsigned int viewLocation4 = glGetUniformLocation(s_program[3], "viewTransform");
//    unsigned int projectionLocation4 = glGetUniformLocation(s_program[3], "projectionTransform");
//
//    glUniformMatrix4fv(modelLocation4, 1, GL_FALSE, glm::value_ptr(MT2));
//    glUniformMatrix4fv(viewLocation4, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLocation4, 1, GL_FALSE, glm::value_ptr(projection));
//
//    if (shape) {
//
//    }
//    else {
//        glBindVertexArray(vao[3]);
//        
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//    }
//    
//    //옆면--------------------------------------------------------------------------------------------------------------
//    glUseProgram(s_program[4]);
//    glm::mat4 MT3 = glm::mat4(1.0f);
//    glm::mat4 SideTrans = glm::mat4(1.0f);
//
//    SideTrans = glm::translate(SideTrans, glm::vec3(0.0, sidey, 0.0));
//
//    MT3 = TR2 * SideTrans;
//
//    unsigned int modelLocation5 = glGetUniformLocation(s_program[4], "modelTransform");
//    unsigned int viewLocation5 = glGetUniformLocation(s_program[4], "viewTransform");
//    unsigned int projectionLocation5 = glGetUniformLocation(s_program[4], "projectionTransform");
//
//    glUniformMatrix4fv(modelLocation5, 1, GL_FALSE, glm::value_ptr(MT3));
//    glUniformMatrix4fv(viewLocation5, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLocation5, 1, GL_FALSE, glm::value_ptr(projection));
//
//    if (shape) {
//
//    }
//    else {
//        glBindVertexArray(vao[4]);
//        
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glDrawArrays(GL_TRIANGLES, 0, 12);
//    }
//    //사각뿔---------------------------------------------------------------------------------------------------------------------
//    glUseProgram(s_program[5]);
//    glm::mat4 MT4 = glm::mat4(1.0f);
//    glm::mat4 MT5 = glm::mat4(1.0f);
//    MT4 = TR2;
//
//    unsigned int modelLocation6 = glGetUniformLocation(s_program[5], "modelTransform");
//    unsigned int viewLocation6 = glGetUniformLocation(s_program[5], "viewTransform");
//    unsigned int projectionLocation6 = glGetUniformLocation(s_program[5], "projectionTransform");
//
//    glUniformMatrix4fv(modelLocation6, 1, GL_FALSE, glm::value_ptr(MT4));
//    glUniformMatrix4fv(viewLocation6, 1, GL_FALSE, glm::value_ptr(view));
//    glUniformMatrix4fv(projectionLocation6, 1, GL_FALSE, glm::value_ptr(projection));
//
//    if (shape) {
//        glBindVertexArray(vao[5]);
//        MT5 = glm::translate(MT5, glm::vec3(0.0, -0.5, 0.5));
//        MT5 = glm::rotate(MT5, glm::radians(rotS), glm::vec3(1.0, 0.0, 0.0));
//        MT5 = glm::translate(MT5, glm::vec3(0.0, 0.5, -0.5));
//        MT4 = TR2 * MT5;
//        modelLocation6 = glGetUniformLocation(s_program[5], "modelTransform");
//        glUniformMatrix4fv(modelLocation6, 1, GL_FALSE, glm::value_ptr(MT4));
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        glBindVertexArray(vao[6]);
//        MT5 = glm::mat4(1.0f);
//        MT5 = glm::translate(MT5, glm::vec3(0.0, -0.5, -0.5));
//        MT5 = glm::rotate(MT5, glm::radians(-rotS), glm::vec3(1.0, 0.0, 0.0));
//        MT5 = glm::translate(MT5, glm::vec3(0.0, 0.5, 0.5));
//        MT4 = TR2 * MT5;
//        modelLocation6 = glGetUniformLocation(s_program[5], "modelTransform");
//        glUniformMatrix4fv(modelLocation6, 1, GL_FALSE, glm::value_ptr(MT4));
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        glBindVertexArray(vao[7]);
//        MT5 = glm::mat4(1.0f);
//        MT5 = glm::translate(MT5, glm::vec3(-0.5, -0.5, 0.0));
//        MT5 = glm::rotate(MT5, glm::radians(rotS), glm::vec3(0.0, 0.0, 1.0));
//        MT5 = glm::translate(MT5, glm::vec3(0.5, 0.5, 0.0));
//        MT4 = TR2 * MT5;
//        modelLocation6 = glGetUniformLocation(s_program[5], "modelTransform");
//        glUniformMatrix4fv(modelLocation6, 1, GL_FALSE, glm::value_ptr(MT4));
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        glBindVertexArray(vao[8]);
//        MT5 = glm::mat4(1.0f);
//        MT5 = glm::translate(MT5, glm::vec3(0.5, -0.5, 0.0));
//        MT5 = glm::rotate(MT5, glm::radians(-rotS), glm::vec3(0.0, 0.0, 1.0));
//        MT5 = glm::translate(MT5, glm::vec3(-0.5, 0.5, 0.0));
//        MT4 = TR2 * MT5;
//        modelLocation6 = glGetUniformLocation(s_program[5], "modelTransform");
//        glUniformMatrix4fv(modelLocation6, 1, GL_FALSE, glm::value_ptr(MT4));
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        glBindVertexArray(vao[9]);
//        MT4 = TR2;
//        modelLocation6 = glGetUniformLocation(s_program[5], "modelTransform");
//        glUniformMatrix4fv(modelLocation6, 1, GL_FALSE, glm::value_ptr(MT4));
//        glPolygonMode(GL_FRONT, GL_FILL);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//    }
//
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
//    case 'y':
//        if (rotateY) {
//            rotateY = false;
//        }
//        else {
//            rotateY = true;
//            glutTimerFunc(100, TimerFunction, 1);
//        }
//        break;
//    case 't':
//    case 'T':
//        if (rotateT) {
//            rotateT = false;
//        }
//        else {
//            rotateT = true;
//            glutTimerFunc(50, TimerFunction3, 1);
//        }
//        break;
//    case 'f':
//        rotateF = true;
//        dirF = false;
//        glutTimerFunc(50, TimerFunction2, 1);
//        break;
//    case 'F':
//        rotateF = true;
//        dirF = true;
//        glutTimerFunc(50, TimerFunction2, 1);
//        break;
//    case '1':
//        moveS = true;
//        dirS = true;
//        glutTimerFunc(50, TimerFunction4, 1);
//        break;
//    case '2':
//        moveS = true;
//        dirS = false;
//        glutTimerFunc(50, TimerFunction4, 1);
//        break;
//    case 'o':
//        rotateS = true;
//        dirTS = false;
//        glutTimerFunc(50, TimerFunction5, 1);
//        break;
//    case 'O':
//        rotateS = true;
//        dirTS = true;
//        glutTimerFunc(50, TimerFunction5, 1);
//        break;
//    case 'c':
//        if (shape) {
//            shape = false;
//        }
//        else {
//            shape = true;
//        }
//        break;
//    case 'p':
//        //직각
//        if (orthoproj) {
//            orthoproj = false;
//        }
//        else {
//            orthoproj = true;
//            persproj = false;
//        }
//        break;
//    case 'P':
//        //원근
//        if (persproj) {
//            persproj = false;
//        }
//        else {
//            persproj = true;
//            orthoproj = false;
//        }
//        break;
//    default:
//        break;
//    }
//    glutPostRedisplay();
//}
//
//void TimerFunction(int value) {
//    rotY += 3.0f;
//    if (rotY >= 360.0f) {
//        rotY = 0.0f;
//    }
//  
//    if (rotateY) {
//        glutTimerFunc(100, TimerFunction, 1);
//    }
//    glutPostRedisplay();
//}
//void TimerFunction2(int value) {
//    if (dirF) {
//        rotF -= 5.0;
//        if (rotF < 0.0) {
//            rotateF = false;
//            rotF = 0.0;
//            return;
//        }    
//    }
//    else {
//        rotF += 5.0;
//        if (rotF > 90.0) {
//            rotateF = false;
//            rotF = 90.0;
//            return;
//        }
//    }
//    if (rotateF) {
//        glutTimerFunc(50, TimerFunction2, 1);
//    }
//    glutPostRedisplay();
//}
//void TimerFunction3(int value) {
//    rotT += 5.0;
//
//    if (rotateT) {
//        glutTimerFunc(50, TimerFunction3, 1);
//    }
//    glutPostRedisplay();
//}
//void TimerFunction4(int value) {
//    if (dirS) {
//        if (sidey >= 0.3) {
//            moveS = false;
//        }
//        sidey += 0.05;
//    }
//    else {
//        sidey -= 0.05;
//        if (sidey <= 0.0) {
//            moveS = false;
//            sidey = 0.0;
//        }
//    }
//    if (moveS) {
//        glutTimerFunc(50, TimerFunction4, 1);
//    }
//    glutPostRedisplay();
//}
//void TimerFunction5(int value) {
//    if (dirTS) {
//        rotS -= 5.0;
//        if (rotS < 0) {
//            rotS = 0;
//            rotateS = false;
//            glutPostRedisplay();
//            return;
//        }
//    }
//    else {
//        rotS += 5.0;
//        if (rotS > 235) {
//            rotS = 233;
//            rotateS = false;
//            glutPostRedisplay();
//            return;
//        }
//    }
//
//    if (rotateS) {
//        glutTimerFunc(50, TimerFunction5, 1);
//    }
//    glutPostRedisplay();
//}