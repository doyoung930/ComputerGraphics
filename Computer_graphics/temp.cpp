#define _CRT_SECURE_NO_WARNINGS //--- 프로그램 맨 앞에 선언할 것
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
// 필요한 헤더 include 따로 추가하셔야 합니다~

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

// random
random_device seeder;
const auto seed = seeder.entropy() ? seeder() : time(nullptr);
mt19937 eng(static_cast<mt19937::result_type>(seed));
uniform_real_distribution<double> dist_r(0.0f, 1.0f);
uniform_real_distribution<double> dist_g(0.0f, 1.0f);
uniform_real_distribution<double> dist_b(0.0f, 1.0f);
uniform_real_distribution<double> dist(0.1f, 0.5f);


//uniform_real_distribution<int> dist_x(1, 10);
//uniform_real_distribution<int> dist_y(1, 10);
//uniform_real_distribution<int> num(1, 10);

//--- 전역 변수
GLuint TriPosVbo[10], TriColorVbo[10];
GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint shaderProgramID; //--- 셰이더 프로그램
GLuint LineVbo1, LineVbo2;
GLuint lVbo1[4], lVbo2[4], lVbo3[4];
int s_location = 0;

bool tri_line = true;	// --- true는 삼각형 false는 선

GLuint speed[4]; // -- speed

GLfloat mouse_x, mouse_y;



//---   1 점 2 선 3 삼각형 4 사각형 5 오각형
//		-1 점 -> 선/  -2 선 -> 삼각형 / -3 삼각형 -> 사각형 / -4 사각형 -> 오각형 / -5 오각형 -> 점
// 영역 1
int area1 = 2;
GLfloat areax1 = -0.5;
GLfloat areay1 = 0.5;
// 영역 2
int area2 = 3;
GLfloat areax2 = 0.5;
GLfloat areay2 = 0.5;
// 영역 3
int area3 = 4;
GLfloat areax3 = -0.5;
GLfloat areay3 = -0.5;
// 영역 4
int area4 = 5;
GLfloat areax4 = 0.5;
GLfloat areay4 = -0.5;

bool s_TimerAlive = false;

int timer_num = 0;
int timer_num2 = 0;
int timer_num3 = 0;
int timer_num4 = 0;


// 클래스

struct Dot {

	GLfloat x1, y1, z1;
	GLfloat x2, y2, z2;
	GLfloat x3, y3, z3;
	GLfloat x4, y4, z4;
	GLfloat x5, y5, z5;

	GLfloat r, g, b;

};
vector<Dot> dots;

// 임시저장 변수
Dot temp_dot;
Dot temp_dot2;

Dot c2_temp_dot;
Dot c2_temp_dot2;

Dot c3_temp_dot;
Dot c3_temp_dot2;

Dot c4_temp_dot;
Dot c4_temp_dot2;

// 점 선 삼각형 사각형 오각형 init 값
Dot s_dot;
Dot s_line;
Dot s_tri;
Dot s_rec;
Dot s_pen;

// function
void InitDot();
void MouseInput(int m_x, int m_y, double r);
void MouseInputLine(int m_x, int m_y, double r);
void InitLine();
void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void InitBuffer();
char* filetobuf(const char*);
void TimerFunction(int value);

void draw_temp();
// change
void chane_Dot_Line();
void chane_Line_Tri();
void chane_Tri_Rec();
void chane_Rec_Pen();
void chane_Pen_Dot();

//--- Init
void InitDot() {
	Dot dot;

	dot.x1 = 0;
	dot.y1 = 0;
	dot.z1 = 0;

	dot.x2 = 0;
	dot.y2 = 0;
	dot.z2 = 0;

	dot.x3 = 0;
	dot.y3 = 0;
	dot.z3 = 0;

	dot.x4 = 0;
	dot.y4 = 0;
	dot.z4 = 0;

	dot.x5 = 0;
	dot.y5 = 0;
	dot.z5 = 0;

	dot.r = 0;
	dot.g = 0;
	dot.b = 0;


	// 점 좌표 저장
	s_dot = dot;
	dots.push_back(dot);
}
void InitLine() {
	Dot dot;

	dot.x1 = 0.0;
	dot.y1 = 0.0;
	dot.z1 = 0;

	dot.x2 = 0.3;
	dot.y2 = 0.3;
	dot.z2 = 0;

	dot.x3 = 0.0;
	dot.y3 = 0.0;
	dot.z3 = 0;

	dot.x4 = -0.3;
	dot.y4 = -0.3;
	dot.z4 = 0;

	dot.x5 = 0.3;
	dot.y5 = 0.3;
	dot.z5 = 0;

	dot.r = 0;
	dot.g = 0;
	dot.b = 0;

	temp_dot = dot;
	s_line = dot;
	// 점 좌표 저장
	dots.push_back(dot);
}
void InitTri() {
	Dot dot;


	dot.x1 = 0;
	dot.y1 = 0.3;
	dot.z1 = 0;

	dot.x2 = -0.3;
	dot.y2 = -0.3;
	dot.z2 = 0;

	dot.x3 = 0.3;
	dot.y3 = -0.3;
	dot.z3 = 0;

	dot.x4 = 0;
	dot.y4 = 0;
	dot.z4 = 0;

	dot.x5 = 0;
	dot.y5 = 0;
	dot.z5 = 0;

	dot.r = 0;
	dot.g = 0;
	dot.b = 0;

	s_tri = dot;
	// 점 좌표 저장
	dots.push_back(dot);
}
void InitRec() {
	Dot dot;

	dot.x1 = 0.3;
	dot.y1 = 0.3;
	dot.z1 = 0;

	dot.x2 = -0.3;
	dot.y2 = -0.3;
	dot.z2 = 0;

	dot.x3 = 0.3;
	dot.y3 = -0.3;
	dot.z3 = 0;

	dot.x4 = -0.3;
	dot.y4 = -0.3;
	dot.z4 = 0;

	dot.x5 = -0.3;
	dot.y5 = 0.3;
	dot.z5 = 0;

	dot.r = 0;
	dot.g = 0;
	dot.b = 0;

	s_rec = dot;
	// 점 좌표 저장
	dots.push_back(dot);
}
void InitPen() {
	Dot dot;

	// 다섯 개의 꼭지점 설정
	// 첫 번째 꼭지점
	dot.x1 = 0.0f;
	dot.y1 = 0.5f;
	dot.z1 = 0.0f;

	// 두 번째 꼭지점
	dot.x2 = 0.4755f;
	dot.y2 = 0.1545f;
	dot.z2 = 0.0f;

	// 세 번째 꼭지점
	dot.x3 = 0.2939f;
	dot.y3 = -0.4045f;
	dot.z3 = 0.0f;

	// 네 번째 꼭지점
	dot.x4 = -0.2939f;
	dot.y4 = -0.4045f;
	dot.z4 = 0.0f;

	// 다섯 번째 꼭지점 (마지막 점)
	dot.x5 = -0.4755f;
	dot.y5 = 0.1545f;
	dot.z5 = 0.0f;

	dot.r = 0;
	dot.g = 0;
	dot.b = 0;

	s_pen = dot;
	// 점 좌표 저장
	dots.push_back(dot);
}


//--- Draw

// 영역 1 그림 그리기 
void DrawDot1() {
	glPointSize(5.0f);
	// 다각형 그리기
	glBegin(GL_POINTS);
	glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
	glVertex2f(dots[0].x1 + areax1, dots[0].y1 + areay1);
	glVertex2f(dots[0].x2 + areax1, dots[0].y2 + areay1);
	glVertex2f(dots[0].x3 + areax1, dots[0].y3 + areay1);
	glVertex2f(dots[0].x4 + areax1, dots[0].y4 + areay1);
	glVertex2f(dots[0].x5 + areax1, dots[0].y5 + areay1);


	glEnd();
}
void DrawLine1() {
	glLineWidth(3.0f);
	// 다각형 그리기
	glBegin(GL_LINES);

	glVertex2f(dots[1].x1 + areax1, dots[1].y1 + areay1);
	glVertex2f(dots[1].x2 + areax1, dots[1].y2 + areay1);


	glVertex2f(dots[1].x3 + areax1, dots[1].y3 + areay1);
	glVertex2f(dots[1].x4 + areax1, dots[1].y4 + areay1);
	glVertex2f(dots[1].x5 + areax1, dots[1].y5 + areay1);


	glEnd();
}
void DrawTri1() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[2].x1 + areax1, dots[2].y1 + areay1);
	glVertex2f(dots[2].x2 + areax1, dots[2].y2 + areay1);
	glVertex2f(dots[2].x3 + areax1, dots[2].y3 + areay1);
	glVertex2f(dots[2].x4 + areax1, dots[2].y4 + areay1);
	glVertex2f(dots[2].x5 + areax1, dots[2].y5 + areay1);


	glEnd();
}
void DrawRec1() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[3].x1 + areax1, dots[3].y1 + areay1);
	glVertex2f(dots[3].x2 + areax1, dots[3].y2 + areay1);
	glVertex2f(dots[3].x3 + areax1, dots[3].y3 + areay1);
	glVertex2f(dots[3].x4 + areax1, dots[3].y4 + areay1);
	glVertex2f(dots[3].x5 + areax1, dots[3].y5 + areay1);


	glEnd();
}
void DrawPen1() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[4].x1 + areax1, dots[4].y1 + areay1);
	glVertex2f(dots[4].x2 + areax1, dots[4].y2 + areay1);
	glVertex2f(dots[4].x3 + areax1, dots[4].y3 + areay1);
	glVertex2f(dots[4].x4 + areax1, dots[4].y4 + areay1);
	glVertex2f(dots[4].x5 + areax1, dots[4].y5 + areay1);



	glEnd();
}

// --- 영역 2 그리기
void DrawDot2() {
	glPointSize(5.0f);
	// 다각형 그리기
	glBegin(GL_POINTS);

	glVertex2f(dots[0].x1 + areax2, dots[0].y1 + areay2);
	glVertex2f(dots[0].x2 + areax2, dots[0].y2 + areay2);
	glVertex2f(dots[0].x3 + areax2, dots[0].y3 + areay2);
	glVertex2f(dots[0].x4 + areax2, dots[0].y4 + areay2);
	glVertex2f(dots[0].x5 + areax2, dots[0].y5 + areay2);


	glEnd();
}
void DrawLine2() {
	glLineWidth(3.0f);
	// 다각형 그리기
	glBegin(GL_LINES);

	glVertex2f(dots[1].x1 + areax2, dots[1].y1 + areay2);
	glVertex2f(dots[1].x2 + areax2, dots[1].y2 + areay2);
	glVertex2f(dots[1].x3 + areax2, dots[1].y3 + areay2);
	glVertex2f(dots[1].x4 + areax2, dots[1].y4 + areay2);
	glVertex2f(dots[1].x5 + areax2, dots[1].y5 + areay2);


	glEnd();
}
void DrawTri2() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[2].x1 + areax2, dots[2].y1 + areay2);
	glVertex2f(dots[2].x2 + areax2, dots[2].y2 + areay2);
	glVertex2f(dots[2].x3 + areax2, dots[2].y3 + areay2);
	glVertex2f(dots[2].x4 + areax2, dots[2].y4 + areay2);
	glVertex2f(dots[2].x5 + areax2, dots[2].y5 + areay2);


	glEnd();
}
void DrawRec2() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[3].x1 + areax2, dots[3].y1 + areay2);
	glVertex2f(dots[3].x2 + areax2, dots[3].y2 + areay2);
	glVertex2f(dots[3].x3 + areax2, dots[3].y3 + areay2);
	glVertex2f(dots[3].x4 + areax2, dots[3].y4 + areay2);
	glVertex2f(dots[3].x5 + areax2, dots[3].y5 + areay2);


	glEnd();
}
void DrawPen2() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[4].x1 + areax2, dots[4].y1 + areay2);
	glVertex2f(dots[4].x2 + areax2, dots[4].y2 + areay2);
	glVertex2f(dots[4].x3 + areax2, dots[4].y3 + areay2);
	glVertex2f(dots[4].x4 + areax2, dots[4].y4 + areay2);
	glVertex2f(dots[4].x5 + areax2, dots[4].y5 + areay2);


	glEnd();
}

// --- 영역 3 그리기
void DrawDot3() {
	glPointSize(5.0f);
	// 다각형 그리기
	glBegin(GL_POINTS);

	glVertex2f(dots[0].x1 + areax3, dots[0].y1 + areay3);
	glVertex2f(dots[0].x2 + areax3, dots[0].y2 + areay3);
	glVertex2f(dots[0].x3 + areax3, dots[0].y3 + areay3);
	glVertex2f(dots[0].x4 + areax3, dots[0].y4 + areay3);
	glVertex2f(dots[0].x5 + areax3, dots[0].y5 + areay3);


	glEnd();
}
void DrawLine3() {
	glLineWidth(3.0f);
	// 다각형 그리기
	glBegin(GL_LINES);

	glVertex2f(dots[1].x1 + areax3, dots[1].y1 + areay3);
	glVertex2f(dots[1].x2 + areax3, dots[1].y2 + areay3);
	glVertex2f(dots[1].x3 + areax3, dots[1].y3 + areay3);
	glVertex2f(dots[1].x4 + areax3, dots[1].y4 + areay3);
	glVertex2f(dots[1].x5 + areax3, dots[1].y5 + areay3);


	glEnd();
}
void DrawTri3() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[2].x1 + areax3, dots[2].y1 + areay3);
	glVertex2f(dots[2].x2 + areax3, dots[2].y2 + areay3);
	glVertex2f(dots[2].x3 + areax3, dots[2].y3 + areay3);
	glVertex2f(dots[2].x4 + areax3, dots[2].y4 + areay3);
	glVertex2f(dots[2].x5 + areax3, dots[2].y5 + areay3);


	glEnd();
}
void DrawRec3() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[3].x1 + areax3, dots[3].y1 + areay3);
	glVertex2f(dots[3].x2 + areax3, dots[3].y2 + areay3);
	glVertex2f(dots[3].x3 + areax3, dots[3].y3 + areay3);
	glVertex2f(dots[3].x4 + areax3, dots[3].y4 + areay3);
	glVertex2f(dots[3].x5 + areax3, dots[3].y5 + areay3);


	glEnd();
}
void DrawPen3() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[4].x1 + areax3, dots[4].y1 + areay3);
	glVertex2f(dots[4].x2 + areax3, dots[4].y2 + areay3);
	glVertex2f(dots[4].x3 + areax3, dots[4].y3 + areay3);
	glVertex2f(dots[4].x4 + areax3, dots[4].y4 + areay3);
	glVertex2f(dots[4].x5 + areax3, dots[4].y5 + areay3);


	glEnd();
}

// --- 영역 4 그리기
void DrawDot4() {
	glPointSize(5.0f);
	// 다각형 그리기
	glBegin(GL_POINTS);

	glVertex2f(dots[0].x1 + areax4, dots[0].y1 + areay4);
	glVertex2f(dots[0].x2 + areax4, dots[0].y2 + areay4);
	glVertex2f(dots[0].x3 + areax4, dots[0].y3 + areay4);
	glVertex2f(dots[0].x4 + areax4, dots[0].y4 + areay4);
	glVertex2f(dots[0].x5 + areax4, dots[0].y5 + areay4);


	glEnd();
}
void DrawLine4() {
	glLineWidth(3.0f);
	// 다각형 그리기
	glBegin(GL_LINES);

	glVertex2f(dots[1].x1 + areax4, dots[1].y1 + areay4);
	glVertex2f(dots[1].x2 + areax4, dots[1].y2 + areay4);

	glVertex2f(dots[1].x3 + areax4, dots[1].y3 + areay4);
	glVertex2f(dots[1].x4 + areax4, dots[1].y4 + areay4);
	glVertex2f(dots[1].x5 + areax4, dots[1].y5 + areay4);


	glEnd();
}
void DrawTri4() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[2].x1 + areax4, dots[2].y1 + areay4);
	glVertex2f(dots[2].x2 + areax4, dots[2].y2 + areay4);
	glVertex2f(dots[2].x3 + areax4, dots[2].y3 + areay4);
	glVertex2f(dots[2].x4 + areax4, dots[2].y4 + areay4);
	glVertex2f(dots[2].x5 + areax4, dots[2].y5 + areay4);


	glEnd();
}
void DrawRec4() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[3].x1 + areax4, dots[3].y1 + areay4);
	glVertex2f(dots[3].x2 + areax4, dots[3].y2 + areay4);
	glVertex2f(dots[3].x3 + areax4, dots[3].y3 + areay4);
	glVertex2f(dots[3].x4 + areax4, dots[3].y4 + areay4);
	glVertex2f(dots[3].x5 + areax4, dots[3].y5 + areay4);


	glEnd();
}
void DrawPen4() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(dots[4].x1 + areax4, dots[4].y1 + areay4);
	glVertex2f(dots[4].x2 + areax4, dots[4].y2 + areay4);
	glVertex2f(dots[4].x3 + areax4, dots[4].y3 + areay4);
	glVertex2f(dots[4].x4 + areax4, dots[4].y4 + areay4);
	glVertex2f(dots[4].x5 + areax4, dots[4].y5 + areay4);


	glEnd();
}
// --- change
void change_area1() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	temp_dot.x1 += (temp_dot.x1 - temp_dot2.x1) / 100;
	temp_dot.x2 += (temp_dot.x2 - temp_dot2.x2) / 100;
	temp_dot.x3 += (temp_dot.x3 - temp_dot2.x3) / 100;
	temp_dot.x4 += (temp_dot.x4 - temp_dot2.x4) / 100;
	temp_dot.x5 += (temp_dot.x5 - temp_dot2.x5) / 100;
	temp_dot.y1 += (temp_dot.y1 - temp_dot2.y1) / 100;
	temp_dot.y2 += (temp_dot.y2 - temp_dot2.y2) / 100;
	temp_dot.y3 += (temp_dot.y3 - temp_dot2.y3) / 100;
	temp_dot.y4 += (temp_dot.y4 - temp_dot2.y4) / 100;
	temp_dot.y5 += (temp_dot.y5 - temp_dot2.y5) / 100;

}
void change_area1_t() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	temp_dot.x1 += (s_tri.x1 - s_line.x1) / 100;
	temp_dot.x2 += (s_tri.x2 - s_line.x2) / 100;
	temp_dot.x3 += (s_tri.x3 - s_line.x3) / 100;
	temp_dot.x4 += (s_tri.x4 - s_line.x4) / 100;
	temp_dot.x5 += (s_tri.x5 - s_line.x5) / 100;
	temp_dot.y1 += (s_tri.y1 - s_line.y1) / 100;
	temp_dot.y2 += (s_tri.y2 - s_line.y2) / 100;
	temp_dot.y3 += (s_tri.y3 - s_line.y3) / 100;
	temp_dot.y4 += (s_tri.y4 - s_line.y4) / 100;
	temp_dot.y5 += (s_tri.y5 - s_line.y5) / 100;

}
void change_area1_r() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	temp_dot.x1 += (s_rec.x1 - s_tri.x1) / 100;
	temp_dot.x2 += (s_rec.x2 - s_tri.x2) / 100;
	temp_dot.x3 += (s_rec.x3 - s_tri.x3) / 100;
	temp_dot.x4 += (s_rec.x4 - s_tri.x4) / 100;
	temp_dot.x5 += (s_rec.x5 - s_tri.x5) / 100;
	temp_dot.y1 += (s_rec.y1 - s_tri.y1) / 100;
	temp_dot.y2 += (s_rec.y2 - s_tri.y2) / 100;
	temp_dot.y3 += (s_rec.y3 - s_tri.y3) / 100;
	temp_dot.y4 += (s_rec.y4 - s_tri.y4) / 100;
	temp_dot.y5 += (s_rec.y5 - s_tri.y5) / 100;

}
void change_area1_p() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	temp_dot.x1 += (s_pen.x1 - s_rec.x1) / 100;
	temp_dot.x2 += (s_pen.x2 - s_rec.x2) / 100;
	temp_dot.x3 += (s_pen.x3 - s_rec.x3) / 100;
	temp_dot.x4 += (s_pen.x4 - s_rec.x4) / 100;
	temp_dot.x5 += (s_pen.x5 - s_rec.x5) / 100;
	temp_dot.y1 += (s_pen.y1 - s_rec.y1) / 100;
	temp_dot.y2 += (s_pen.y2 - s_rec.y2) / 100;
	temp_dot.y3 += (s_pen.y3 - s_rec.y3) / 100;
	temp_dot.y4 += (s_pen.y4 - s_rec.y4) / 100;
	temp_dot.y5 += (s_pen.y5 - s_rec.y5) / 100;

}
void change_area1_d() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	temp_dot.x1 -= (s_pen.x1 - s_dot.x1) / 100;
	temp_dot.x2 -= (s_pen.x2 - s_dot.x2) / 100;
	temp_dot.x3 -= (s_pen.x3 - s_dot.x3) / 100;
	temp_dot.x4 -= (s_pen.x4 - s_dot.x4) / 100;
	temp_dot.x5 -= (s_pen.x5 - s_dot.x5) / 100;
	temp_dot.y1 -= (s_pen.y1 - s_dot.y1) / 100;
	temp_dot.y2 -= (s_pen.y2 - s_dot.y2) / 100;
	temp_dot.y3 -= (s_pen.y3 - s_dot.y3) / 100;
	temp_dot.y4 -= (s_pen.y4 - s_dot.y4) / 100;
	temp_dot.y5 -= (s_pen.y5 - s_dot.y5) / 100;

}

void change_area2() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c2_temp_dot.x1 += (c2_temp_dot.x1 - c2_temp_dot2.x1) / 100;
	c2_temp_dot.x2 += (c2_temp_dot.x2 - c2_temp_dot2.x2) / 100;
	c2_temp_dot.x3 += (c2_temp_dot.x3 - c2_temp_dot2.x3) / 100;
	c2_temp_dot.x4 += (c2_temp_dot.x4 - c2_temp_dot2.x4) / 100;
	c2_temp_dot.x5 += (c2_temp_dot.x5 - c2_temp_dot2.x5) / 100;
	c2_temp_dot.y1 += (c2_temp_dot.y1 - c2_temp_dot2.y1) / 100;
	c2_temp_dot.y2 += (c2_temp_dot.y2 - c2_temp_dot2.y2) / 100;
	c2_temp_dot.y3 += (c2_temp_dot.y3 - c2_temp_dot2.y3) / 100;
	c2_temp_dot.y4 += (c2_temp_dot.y4 - c2_temp_dot2.y4) / 100;
	c2_temp_dot.y5 += (c2_temp_dot.y5 - c2_temp_dot2.y5) / 100;

}
void change_area2_t() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c2_temp_dot.x1 += (s_tri.x1 - s_line.x1) / 100;
	c2_temp_dot.x2 += (s_tri.x2 - s_line.x2) / 100;
	c2_temp_dot.x3 += (s_tri.x3 - s_line.x3) / 100;
	c2_temp_dot.x4 += (s_tri.x4 - s_line.x4) / 100;
	c2_temp_dot.x5 += (s_tri.x5 - s_line.x5) / 100;
	c2_temp_dot.y1 += (s_tri.y1 - s_line.y1) / 100;
	c2_temp_dot.y2 += (s_tri.y2 - s_line.y2) / 100;
	c2_temp_dot.y3 += (s_tri.y3 - s_line.y3) / 100;
	c2_temp_dot.y4 += (s_tri.y4 - s_line.y4) / 100;
	c2_temp_dot.y5 += (s_tri.y5 - s_line.y5) / 100;

}
void change_area2_r() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c2_temp_dot.x1 += (s_rec.x1 - s_tri.x1) / 100;
	c2_temp_dot.x2 += (s_rec.x2 - s_tri.x2) / 100;
	c2_temp_dot.x3 += (s_rec.x3 - s_tri.x3) / 100;
	c2_temp_dot.x4 += (s_rec.x4 - s_tri.x4) / 100;
	c2_temp_dot.x5 += (s_rec.x5 - s_tri.x5) / 100;
	c2_temp_dot.y1 += (s_rec.y1 - s_tri.y1) / 100;
	c2_temp_dot.y2 += (s_rec.y2 - s_tri.y2) / 100;
	c2_temp_dot.y3 += (s_rec.y3 - s_tri.y3) / 100;
	c2_temp_dot.y4 += (s_rec.y4 - s_tri.y4) / 100;
	c2_temp_dot.y5 += (s_rec.y5 - s_tri.y5) / 100;

}
void change_area2_p() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c2_temp_dot.x1 += (s_pen.x1 - s_rec.x1) / 100;
	c2_temp_dot.x2 += (s_pen.x2 - s_rec.x2) / 100;
	c2_temp_dot.x3 += (s_pen.x3 - s_rec.x3) / 100;
	c2_temp_dot.x4 += (s_pen.x4 - s_rec.x4) / 100;
	c2_temp_dot.x5 += (s_pen.x5 - s_rec.x5) / 100;
	c2_temp_dot.y1 += (s_pen.y1 - s_rec.y1) / 100;
	c2_temp_dot.y2 += (s_pen.y2 - s_rec.y2) / 100;
	c2_temp_dot.y3 += (s_pen.y3 - s_rec.y3) / 100;
	c2_temp_dot.y4 += (s_pen.y4 - s_rec.y4) / 100;
	c2_temp_dot.y5 += (s_pen.y5 - s_rec.y5) / 100;

}
void change_area2_d() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c2_temp_dot.x1 -= (s_pen.x1 - s_dot.x1) / 100;
	c2_temp_dot.x2 -= (s_pen.x2 - s_dot.x2) / 100;
	c2_temp_dot.x3 -= (s_pen.x3 - s_dot.x3) / 100;
	c2_temp_dot.x4 -= (s_pen.x4 - s_dot.x4) / 100;
	c2_temp_dot.x5 -= (s_pen.x5 - s_dot.x5) / 100;
	c2_temp_dot.y1 -= (s_pen.y1 - s_dot.y1) / 100;
	c2_temp_dot.y2 -= (s_pen.y2 - s_dot.y2) / 100;
	c2_temp_dot.y3 -= (s_pen.y3 - s_dot.y3) / 100;
	c2_temp_dot.y4 -= (s_pen.y4 - s_dot.y4) / 100;
	c2_temp_dot.y5 -= (s_pen.y5 - s_dot.y5) / 100;

}

void change_area3() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c3_temp_dot.x1 += (c3_temp_dot.x1 - c3_temp_dot2.x1) / 100;
	c3_temp_dot.x2 += (c3_temp_dot.x2 - c3_temp_dot2.x2) / 100;
	c3_temp_dot.x3 += (c3_temp_dot.x3 - c3_temp_dot2.x3) / 100;
	c3_temp_dot.x4 += (c3_temp_dot.x4 - c3_temp_dot2.x4) / 100;
	c3_temp_dot.x5 += (c3_temp_dot.x5 - c3_temp_dot2.x5) / 100;
	c3_temp_dot.y1 += (c3_temp_dot.y1 - c3_temp_dot2.y1) / 100;
	c3_temp_dot.y2 += (c3_temp_dot.y2 - c3_temp_dot2.y2) / 100;
	c3_temp_dot.y3 += (c3_temp_dot.y3 - c3_temp_dot2.y3) / 100;
	c3_temp_dot.y4 += (c3_temp_dot.y4 - c3_temp_dot2.y4) / 100;
	c3_temp_dot.y5 += (c3_temp_dot.y5 - c3_temp_dot2.y5) / 100;

}
void change_area3_t() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c3_temp_dot.x1 += (s_tri.x1 - s_line.x1) / 100;
	c3_temp_dot.x2 += (s_tri.x2 - s_line.x2) / 100;
	c3_temp_dot.x3 += (s_tri.x3 - s_line.x3) / 100;
	c3_temp_dot.x4 += (s_tri.x4 - s_line.x4) / 100;
	c3_temp_dot.x5 += (s_tri.x5 - s_line.x5) / 100;
	c3_temp_dot.y1 += (s_tri.y1 - s_line.y1) / 100;
	c3_temp_dot.y2 += (s_tri.y2 - s_line.y2) / 100;
	c3_temp_dot.y3 += (s_tri.y3 - s_line.y3) / 100;
	c3_temp_dot.y4 += (s_tri.y4 - s_line.y4) / 100;
	c3_temp_dot.y5 += (s_tri.y5 - s_line.y5) / 100;

}
void change_area3_r() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c3_temp_dot.x1 += (s_rec.x1 - s_tri.x1) / 100;
	c3_temp_dot.x2 += (s_rec.x2 - s_tri.x2) / 100;
	c3_temp_dot.x3 += (s_rec.x3 - s_tri.x3) / 100;
	c3_temp_dot.x4 += (s_rec.x4 - s_tri.x4) / 100;
	c3_temp_dot.x5 += (s_rec.x5 - s_tri.x5) / 100;
	c3_temp_dot.y1 += (s_rec.y1 - s_tri.y1) / 100;
	c3_temp_dot.y2 += (s_rec.y2 - s_tri.y2) / 100;
	c3_temp_dot.y3 += (s_rec.y3 - s_tri.y3) / 100;
	c3_temp_dot.y4 += (s_rec.y4 - s_tri.y4) / 100;
	c3_temp_dot.y5 += (s_rec.y5 - s_tri.y5) / 100;

}
void change_area3_p() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c3_temp_dot.x1 += (s_pen.x1 - s_rec.x1) / 100;
	c3_temp_dot.x2 += (s_pen.x2 - s_rec.x2) / 100;
	c3_temp_dot.x3 += (s_pen.x3 - s_rec.x3) / 100;
	c3_temp_dot.x4 += (s_pen.x4 - s_rec.x4) / 100;
	c3_temp_dot.x5 += (s_pen.x5 - s_rec.x5) / 100;
	c3_temp_dot.y1 += (s_pen.y1 - s_rec.y1) / 100;
	c3_temp_dot.y2 += (s_pen.y2 - s_rec.y2) / 100;
	c3_temp_dot.y3 += (s_pen.y3 - s_rec.y3) / 100;
	c3_temp_dot.y4 += (s_pen.y4 - s_rec.y4) / 100;
	c3_temp_dot.y5 += (s_pen.y5 - s_rec.y5) / 100;

}
void change_area3_d() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c3_temp_dot.x1 -= (s_pen.x1 - s_dot.x1) / 100;
	c3_temp_dot.x2 -= (s_pen.x2 - s_dot.x2) / 100;
	c3_temp_dot.x3 -= (s_pen.x3 - s_dot.x3) / 100;
	c3_temp_dot.x4 -= (s_pen.x4 - s_dot.x4) / 100;
	c3_temp_dot.x5 -= (s_pen.x5 - s_dot.x5) / 100;
	c3_temp_dot.y1 -= (s_pen.y1 - s_dot.y1) / 100;
	c3_temp_dot.y2 -= (s_pen.y2 - s_dot.y2) / 100;
	c3_temp_dot.y3 -= (s_pen.y3 - s_dot.y3) / 100;
	c3_temp_dot.y4 -= (s_pen.y4 - s_dot.y4) / 100;
	c3_temp_dot.y5 -= (s_pen.y5 - s_dot.y5) / 100;

}

void change_area4() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c4_temp_dot.x1 += (c4_temp_dot.x1 - c4_temp_dot2.x1) / 100;
	c4_temp_dot.x2 += (c4_temp_dot.x2 - c4_temp_dot2.x2) / 100;
	c4_temp_dot.x3 += (c4_temp_dot.x3 - c4_temp_dot2.x3) / 100;
	c4_temp_dot.x4 += (c4_temp_dot.x4 - c4_temp_dot2.x4) / 100;
	c4_temp_dot.x5 += (c4_temp_dot.x5 - c4_temp_dot2.x5) / 100;
	c4_temp_dot.y1 += (c4_temp_dot.y1 - c4_temp_dot2.y1) / 100;
	c4_temp_dot.y2 += (c4_temp_dot.y2 - c4_temp_dot2.y2) / 100;
	c4_temp_dot.y3 += (c4_temp_dot.y3 - c4_temp_dot2.y3) / 100;
	c4_temp_dot.y4 += (c4_temp_dot.y4 - c4_temp_dot2.y4) / 100;
	c4_temp_dot.y5 += (c4_temp_dot.y5 - c4_temp_dot2.y5) / 100;

}
void change_area4_t() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c4_temp_dot.x1 += (s_tri.x1 - s_line.x1) / 100;
	c4_temp_dot.x2 += (s_tri.x2 - s_line.x2) / 100;
	c4_temp_dot.x3 += (s_tri.x3 - s_line.x3) / 100;
	c4_temp_dot.x4 += (s_tri.x4 - s_line.x4) / 100;
	c4_temp_dot.x5 += (s_tri.x5 - s_line.x5) / 100;
	c4_temp_dot.y1 += (s_tri.y1 - s_line.y1) / 100;
	c4_temp_dot.y2 += (s_tri.y2 - s_line.y2) / 100;
	c4_temp_dot.y3 += (s_tri.y3 - s_line.y3) / 100;
	c4_temp_dot.y4 += (s_tri.y4 - s_line.y4) / 100;
	c4_temp_dot.y5 += (s_tri.y5 - s_line.y5) / 100;

}
void change_area4_r() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c4_temp_dot.x1 += (s_rec.x1 - s_tri.x1) / 100;
	c4_temp_dot.x2 += (s_rec.x2 - s_tri.x2) / 100;
	c4_temp_dot.x3 += (s_rec.x3 - s_tri.x3) / 100;
	c4_temp_dot.x4 += (s_rec.x4 - s_tri.x4) / 100;
	c4_temp_dot.x5 += (s_rec.x5 - s_tri.x5) / 100;
	c4_temp_dot.y1 += (s_rec.y1 - s_tri.y1) / 100;
	c4_temp_dot.y2 += (s_rec.y2 - s_tri.y2) / 100;
	c4_temp_dot.y3 += (s_rec.y3 - s_tri.y3) / 100;
	c4_temp_dot.y4 += (s_rec.y4 - s_tri.y4) / 100;
	c4_temp_dot.y5 += (s_rec.y5 - s_tri.y5) / 100;

}
void change_area4_p() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c4_temp_dot.x1 += (s_pen.x1 - s_rec.x1) / 100;
	c4_temp_dot.x2 += (s_pen.x2 - s_rec.x2) / 100;
	c4_temp_dot.x3 += (s_pen.x3 - s_rec.x3) / 100;
	c4_temp_dot.x4 += (s_pen.x4 - s_rec.x4) / 100;
	c4_temp_dot.x5 += (s_pen.x5 - s_rec.x5) / 100;
	c4_temp_dot.y1 += (s_pen.y1 - s_rec.y1) / 100;
	c4_temp_dot.y2 += (s_pen.y2 - s_rec.y2) / 100;
	c4_temp_dot.y3 += (s_pen.y3 - s_rec.y3) / 100;
	c4_temp_dot.y4 += (s_pen.y4 - s_rec.y4) / 100;
	c4_temp_dot.y5 += (s_pen.y5 - s_rec.y5) / 100;

}
void change_area4_d() {

	// 임시 변수에 저장하여 그리기 다 그리면 임시변수 삭제 및 원래 변수로 바꾸기

	c4_temp_dot.x1 -= (s_pen.x1 - s_dot.x1) / 100;
	c4_temp_dot.x2 -= (s_pen.x2 - s_dot.x2) / 100;
	c4_temp_dot.x3 -= (s_pen.x3 - s_dot.x3) / 100;
	c4_temp_dot.x4 -= (s_pen.x4 - s_dot.x4) / 100;
	c4_temp_dot.x5 -= (s_pen.x5 - s_dot.x5) / 100;
	c4_temp_dot.y1 -= (s_pen.y1 - s_dot.y1) / 100;
	c4_temp_dot.y2 -= (s_pen.y2 - s_dot.y2) / 100;
	c4_temp_dot.y3 -= (s_pen.y3 - s_dot.y3) / 100;
	c4_temp_dot.y4 -= (s_pen.y4 - s_dot.y4) / 100;
	c4_temp_dot.y5 -= (s_pen.y5 - s_dot.y5) / 100;

}

// 변하는거 그리기
void DrawTemp1() {
	// 다각형 그리기
	glBegin(GL_LINES);

	glVertex2f(temp_dot.x1 + areax1, temp_dot.y1 + areay1);
	glVertex2f(temp_dot.x2 + areax1, temp_dot.y2 + areay1);
	glVertex2f(temp_dot.x3 + areax1, temp_dot.y3 + areay1);
	glVertex2f(temp_dot.x4 + areax1, temp_dot.y4 + areay1);
	glVertex2f(temp_dot.x5 + areax1, temp_dot.y5 + areay1);


	glEnd();
}
void DrawTemp1_p() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(temp_dot.x1 + areax1, temp_dot.y1 + areay1);
	glVertex2f(temp_dot.x2 + areax1, temp_dot.y2 + areay1);
	glVertex2f(temp_dot.x3 + areax1, temp_dot.y3 + areay1);
	glVertex2f(temp_dot.x4 + areax1, temp_dot.y4 + areay1);
	glVertex2f(temp_dot.x5 + areax1, temp_dot.y5 + areay1);


	glEnd();
}
void DrawTemp1_d() {
	// 다각형 그리기
	glBegin(GL_POINTS);

	glVertex2f(temp_dot.x1 + areax1, temp_dot.y1 + areay1);
	glVertex2f(temp_dot.x2 + areax1, temp_dot.y2 + areay1);
	glVertex2f(temp_dot.x3 + areax1, temp_dot.y3 + areay1);
	glVertex2f(temp_dot.x4 + areax1, temp_dot.y4 + areay1);
	glVertex2f(temp_dot.x5 + areax1, temp_dot.y5 + areay1);


	glEnd();
}

// 변하는거 그리기
void DrawTemp2() {
	// 다각형 그리기
	glBegin(GL_LINES);

	glVertex2f(c2_temp_dot.x1 + areax2, c2_temp_dot.y1 + areay2);
	glVertex2f(c2_temp_dot.x2 + areax2, c2_temp_dot.y2 + areay2);
	glVertex2f(c2_temp_dot.x3 + areax2, c2_temp_dot.y3 + areay2);
	glVertex2f(c2_temp_dot.x4 + areax2, c2_temp_dot.y4 + areay2);
	glVertex2f(c2_temp_dot.x5 + areax2, c2_temp_dot.y5 + areay2);


	glEnd();
}
void DrawTemp2_p() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(c2_temp_dot.x1 + areax2, c2_temp_dot.y1 + areay2);
	glVertex2f(c2_temp_dot.x2 + areax2, c2_temp_dot.y2 + areay2);
	glVertex2f(c2_temp_dot.x3 + areax2, c2_temp_dot.y3 + areay2);
	glVertex2f(c2_temp_dot.x4 + areax2, c2_temp_dot.y4 + areay2);
	glVertex2f(c2_temp_dot.x5 + areax2, c2_temp_dot.y5 + areay2);


	glEnd();
}
void DrawTemp2_d() {
	// 다각형 그리기
	glBegin(GL_POINTS);

	glVertex2f(c2_temp_dot.x1 + areax2, c2_temp_dot.y1 + areay2);
	glVertex2f(c2_temp_dot.x2 + areax2, c2_temp_dot.y2 + areay2);
	glVertex2f(c2_temp_dot.x3 + areax2, c2_temp_dot.y3 + areay2);
	glVertex2f(c2_temp_dot.x4 + areax2, c2_temp_dot.y4 + areay2);
	glVertex2f(c2_temp_dot.x5 + areax2, c2_temp_dot.y5 + areay2);


	glEnd();
}

// 변하는거 그리기
void DrawTemp3() {
	// 다각형 그리기
	glBegin(GL_LINES);

	glVertex2f(c3_temp_dot.x1 + areax3, c3_temp_dot.y1 + areay3);
	glVertex2f(c3_temp_dot.x2 + areax3, c3_temp_dot.y2 + areay3);
	glVertex2f(c3_temp_dot.x3 + areax3, c3_temp_dot.y3 + areay3);
	glVertex2f(c3_temp_dot.x4 + areax3, c3_temp_dot.y4 + areay3);
	glVertex2f(c3_temp_dot.x5 + areax3, c3_temp_dot.y5 + areay3);


	glEnd();
}
void DrawTemp3_p() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(c3_temp_dot.x1 + areax3, c3_temp_dot.y1 + areay3);
	glVertex2f(c3_temp_dot.x2 + areax3, c3_temp_dot.y2 + areay3);
	glVertex2f(c3_temp_dot.x3 + areax3, c3_temp_dot.y3 + areay3);
	glVertex2f(c3_temp_dot.x4 + areax3, c3_temp_dot.y4 + areay3);
	glVertex2f(c3_temp_dot.x5 + areax3, c3_temp_dot.y5 + areay3);


	glEnd();
}
void DrawTemp3_d() {
	// 다각형 그리기
	glBegin(GL_POINTS);

	glVertex2f(c3_temp_dot.x1 + areax3, c3_temp_dot.y1 + areay3);
	glVertex2f(c3_temp_dot.x2 + areax3, c3_temp_dot.y2 + areay3);
	glVertex2f(c3_temp_dot.x3 + areax3, c3_temp_dot.y3 + areay3);
	glVertex2f(c3_temp_dot.x4 + areax3, c3_temp_dot.y4 + areay3);
	glVertex2f(c3_temp_dot.x5 + areax3, c3_temp_dot.y5 + areay3);


	glEnd();
}

// 변하는거 그리기
void DrawTemp4() {
	// 다각형 그리기
	glBegin(GL_LINES);

	glVertex2f(c4_temp_dot.x1 + areax4, c4_temp_dot.y1 + areay4);
	glVertex2f(c4_temp_dot.x2 + areax4, c4_temp_dot.y2 + areay4);
	glVertex2f(c4_temp_dot.x3 + areax4, c4_temp_dot.y3 + areay4);
	glVertex2f(c4_temp_dot.x4 + areax4, c4_temp_dot.y4 + areay4);
	glVertex2f(c4_temp_dot.x5 + areax4, c4_temp_dot.y5 + areay4);


	glEnd();
}
void DrawTemp4_p() {
	// 다각형 그리기
	glBegin(GL_POLYGON);

	glVertex2f(c4_temp_dot.x1 + areax4, c4_temp_dot.y1 + areay4);
	glVertex2f(c4_temp_dot.x2 + areax4, c4_temp_dot.y2 + areay4);
	glVertex2f(c4_temp_dot.x3 + areax4, c4_temp_dot.y3 + areay4);
	glVertex2f(c4_temp_dot.x4 + areax4, c4_temp_dot.y4 + areay4);
	glVertex2f(c4_temp_dot.x5 + areax4, c4_temp_dot.y5 + areay4);


	glEnd();
}
void DrawTemp4_d() {
	// 다각형 그리기
	glBegin(GL_POINTS);

	glVertex2f(c4_temp_dot.x1 + areax4, c4_temp_dot.y1 + areay4);
	glVertex2f(c4_temp_dot.x2 + areax4, c4_temp_dot.y2 + areay4);
	glVertex2f(c4_temp_dot.x3 + areax4, c4_temp_dot.y3 + areay4);
	glVertex2f(c4_temp_dot.x4 + areax4, c4_temp_dot.y4 + areay4);
	glVertex2f(c4_temp_dot.x5 + areax4, c4_temp_dot.y5 + areay4);


	glEnd();
}


void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':
		if (s_TimerAlive == false)
			glutTimerFunc(10, TimerFunction, 1);

		if (area1 == 1) {
			area1 = -1;
			temp_dot = s_dot;
			temp_dot2 = s_line;
		}
		else if (area1 == 2) {
			area1 = -2;
			temp_dot = s_line;
			temp_dot2 = s_tri;
		}
		else if (area1 == 3)
		{
			area1 = -3;
			temp_dot = s_tri;
			temp_dot2 = s_rec;
		}
		else if (area1 == 4)
		{
			area1 = -4;
			temp_dot = s_rec;
			temp_dot2 = s_pen;
		}
		else if (area1 == 5)
		{
			area1 = -5;
			temp_dot = s_pen;
			temp_dot2 = s_dot;
		}


		s_TimerAlive = true;
		break;
	case '2':
		if (s_TimerAlive == false)
			glutTimerFunc(10, TimerFunction, 1);

		if (area2 == 1) {
			area2 = -1;
			c2_temp_dot = s_dot;
			c2_temp_dot2 = s_line;
		}
		else if (area2 == 2) {
			area2 = -2;
			c2_temp_dot = s_line;
			c2_temp_dot2 = s_tri;
		}
		else if (area2 == 3)
		{
			area2 = -3;
			c2_temp_dot = s_tri;
			c2_temp_dot2 = s_rec;
		}
		else if (area2 == 4)
		{
			area2 = -4;
			c2_temp_dot = s_rec;
			c2_temp_dot2 = s_pen;
		}
		else if (area2 == 5)
		{
			area2 = -5;
			c2_temp_dot = s_pen;
			c2_temp_dot2 = s_dot;
		}


		s_TimerAlive = true;
		break;
	case '3':
		if (s_TimerAlive == false)
			glutTimerFunc(10, TimerFunction, 1);

		if (area3 == 1) {
			area3 = -1;
			c3_temp_dot = s_dot;
			c3_temp_dot2 = s_line;
		}
		else if (area3 == 2) {
			area3 = -2;
			c3_temp_dot = s_line;
			c3_temp_dot2 = s_tri;
		}
		else if (area3 == 3)
		{
			area3 = -3;
			c3_temp_dot = s_tri;
			c3_temp_dot2 = s_rec;
		}
		else if (area3 == 4)
		{
			area3 = -4;
			c3_temp_dot = s_rec;
			c3_temp_dot2 = s_pen;
		}
		else if (area3 == 5)
		{
			area3 = -5;
			c3_temp_dot = s_pen;
			c3_temp_dot2 = s_dot;
		}


		s_TimerAlive = true;
		break;
	case '4':
		if (s_TimerAlive == false)
			glutTimerFunc(10, TimerFunction, 1);

		if (area4 == 1) {
			area4 = -1;
			c4_temp_dot = s_dot;
			c4_temp_dot2 = s_line;
		}
		else if (area4 == 2) {
			area4 = -2;
			c4_temp_dot = s_line;
			c4_temp_dot2 = s_tri;
		}
		else if (area4 == 3)
		{
			area4 = -3;
			c4_temp_dot = s_tri;
			c4_temp_dot2 = s_rec;
		}
		else if (area4 == 4)
		{
			area4 = -4;
			c4_temp_dot = s_rec;
			c4_temp_dot2 = s_pen;
		}
		else if (area4 == 5)
		{
			area4 = -5;
			c4_temp_dot = s_pen;
			c4_temp_dot2 = s_dot;
		}


		s_TimerAlive = true;
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int m_x, int m_y)
{
	double num = dist(eng) * 10;
	float tempx;
	float tempy;
	tempx = ((float)m_x - 400) / 400;
	tempy = (300 - (float)m_y) / 300;
	mouse_x = tempx;
	mouse_y = tempy;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (m_x <= 400 && m_y <= 300) {
			s_location = 1;
			cout << "영역 1" << endl;
		}
		else if (m_x > 400 && m_y < 300) {
			s_location = 2;
			cout << "영역 2" << endl;
		}
		else if (m_x < 400 && m_y > 300) {
			s_location = 3; cout << "영역 3" << endl;
		}
		else if (m_x > 400 && m_y > 300) {
			s_location = 4; cout << "영역 4" << endl;
		}
	}
}





void DrawTriByLine() {
	const GLfloat linepos[2][3] = {
		{-1.0, 0.0, 0.0},
		{1.0, 0.0, 0.0} };
	const GLfloat linepos2[2][3] = {
		{0.0, 1.0, 0.0},
		{0.0, -1.0, 0.0} };
	const GLfloat linepos3[2][3] = {
		{0.0, 1.0, 0.0},
		{0.0, -1.0, 0.0} };
}



void BaseLine() {
	const GLfloat linepos[2][3] = { //--- 삼각형 위치 값
		{-1.0, 0.0, 0.0},
		{1.0, 0.0, 0.0} };
	const GLfloat linepos2[2][3] = { //--- 삼각형 위치 값
		{0.0, 1.0, 0.0},
		{0.0, -1.0, 0.0} };


	glGenBuffers(1, &LineVbo1);
	glBindBuffer(GL_ARRAY_BUFFER, LineVbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linepos), linepos, GL_STATIC_DRAW);

	// Location 번호 저장
	int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
	int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미

	{
		glBindBuffer(GL_ARRAY_BUFFER, LineVbo1); // VBO Bind
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	glLineWidth(3);
	glDrawArrays(GL_LINES, 0, 2); // 설정대로 출력
	glDisableVertexAttribArray(PosLocation);	// Disable 필수!


	glGenBuffers(1, &LineVbo2);
	glBindBuffer(GL_ARRAY_BUFFER, LineVbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linepos2), linepos2, GL_STATIC_DRAW);

	glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미

	{
		glBindBuffer(GL_ARRAY_BUFFER, LineVbo2); // VBO Bind
		glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	}
	glLineWidth(3);
	glDrawArrays(GL_LINES, 0, 2); // 설정대로 출력
	glDisableVertexAttribArray(PosLocation);	// Disable 필수!

}

void area1_f() {
	if (area1 == -1) {
		change_area1();
		if (timer_num == 70) {
			area1 = 2;
			timer_num = 0;

		}
		else {
			timer_num++;
		}
	}
	else if (area1 == -2) {
		change_area1_t();
		if (timer_num == 100) {
			area1 = 3;
			timer_num = 0;

		}
		else {
			timer_num++;
		}
	}
	else if (area1 == -3) {
		change_area1_r();
		if (timer_num == 100) {
			area1 = 4;
			timer_num = 0;

		}
		else {
			timer_num++;
		}
	}
	else if (area1 == -4) {
		change_area1_p();
		if (timer_num == 100) {
			area1 = 5;
			timer_num = 0;

		}
		else {
			timer_num++;
		}
	}
	else if (area1 == -5) {
		change_area1_d();
		if (timer_num == 100) {
			area1 = 1;
			timer_num = 0;

		}
		else {
			timer_num++;
		}
	}
}
void area2_f() {
	if (area2 == -1) {
		change_area2();
		if (timer_num2 == 70) {
			area2 = 2;
			timer_num2 = 0;

		}
		else {
			timer_num2++;
		}
	}
	else if (area2 == -2) {
		change_area2_t();
		if (timer_num2 == 100) {
			area2 = 3;
			timer_num2 = 0;

		}
		else {
			timer_num2++;
		}
	}
	else if (area2 == -3) {
		change_area2_r();
		if (timer_num2 == 100) {
			area2 = 4;
			timer_num2 = 0;

		}
		else {
			timer_num2++;
		}
	}
	else if (area2 == -4) {
		change_area2_p();
		if (timer_num2 == 100) {
			area2 = 5;
			timer_num2 = 0;

		}
		else {
			timer_num2++;
		}
	}
	else if (area2 == -5) {
		change_area2_d();
		if (timer_num2 == 100) {
			area2 = 1;
			timer_num2 = 0;

		}
		else {
			timer_num2++;
		}
	}
}

void area3_f() {
	if (area3 == -1) {
		change_area3();
		if (timer_num3 == 70) {
			area3 = 2;
			timer_num3 = 0;

		}
		else {
			timer_num3++;
		}
	}
	else if (area3 == -2) {
		change_area3_t();
		if (timer_num3 == 100) {
			area3 = 3;
			timer_num3 = 0;

		}
		else {
			timer_num3++;
		}
	}
	else if (area3 == -3) {
		change_area3_r();
		if (timer_num3 == 100) {
			area3 = 4;
			timer_num3 = 0;

		}
		else {
			timer_num3++;
		}
	}
	else if (area3 == -4) {
		change_area3_p();
		if (timer_num3 == 100) {
			area3 = 5;
			timer_num3 = 0;

		}
		else {
			timer_num3++;
		}
	}
	else if (area3 == -5) {
		change_area3_d();
		if (timer_num3 == 100) {
			area3 = 1;
			timer_num3 = 0;

		}
		else {
			timer_num3++;
		}
	}
}

void area4_f() {
	if (area4 == -1) {
		change_area4();
		if (timer_num4 == 70) {
			area4 = 2;
			timer_num4 = 0;

		}
		else {
			timer_num4++;
		}
	}
	else if (area4 == -2) {
		change_area4_t();
		if (timer_num4 == 100) {
			area4 = 3;
			timer_num4 = 0;

		}
		else {
			timer_num4++;
		}
	}
	else if (area4 == -3) {
		change_area4_r();
		if (timer_num4 == 100) {
			area4 = 4;
			timer_num4 = 0;

		}
		else {
			timer_num4++;
		}
	}
	else if (area4 == -4) {
		change_area4_p();
		if (timer_num4 == 100) {
			area4 = 5;
			timer_num4 = 0;

		}
		else {
			timer_num4++;
		}
	}
	else if (area4 == -5) {
		change_area4_d();
		if (timer_num4 == 100) {
			area4 = 1;
			timer_num4 = 0;

		}
		else {
			timer_num4++;
		}
	}
}
// --- timer
void TimerFunction(int value)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//area1 변환
	area1_f();
	area2_f();
	area3_f();
	area4_f();


	drawScene();
	glutPostRedisplay(); // 화면 재 출력


	if (s_TimerAlive)
		glutTimerFunc(10, TimerFunction, 1); // 타이머함수 재 설정
}


GLvoid drawScene()
{

	//--- 변경된 배경색 설정
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(shaderProgramID);
	BaseLine();

	draw_temp();

	if (area1 == 1)	DrawDot1();
	else if (area1 == 2) DrawLine1();
	else if (area1 == 3)DrawTri1();
	else if (area1 == 4)DrawRec1();
	else if (area1 == 5)DrawPen1();

	if (area2 == 1)DrawDot2();
	else if (area2 == 2)DrawLine2();
	else if (area2 == 3)DrawTri2();
	else if (area2 == 4)DrawRec2();
	else if (area2 == 5)DrawPen2();

	if (area3 == 1)DrawDot3();
	else if (area3 == 2)DrawLine3();
	else if (area3 == 3)DrawTri3();
	else if (area3 == 4)DrawRec3();
	else if (area3 == 5)DrawPen3();

	if (area4 == 1)DrawDot4();
	else if (area4 == 2)DrawLine4();
	else if (area4 == 3)DrawTri4();
	else if (area4 == 4)DrawRec4();
	else if (area4 == 5)DrawPen4();


	glutSwapBuffers(); //--- 화면에 출력하기
}
//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- 프래그먼트 세이더 객체 만들기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- 프래그먼트 세이더 컴파일
	glCompileShader(fragmentShader);
	//--- 컴파일이 제대로 되지 않은 경우: 컴파일 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cout << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

void make_shaderProgram()
{
	make_vertexShaders(); //--- 버텍스 세이더 만들기
	make_fragmentShaders();
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program 사용하기
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- 버텍스 세이더 객체 만들기
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- 세이더 코드를 세이더 객체에 넣기
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- 버텍스 세이더 컴파일하기
	glCompileShader(vertexShader);
	//--- 컴파일이 제대로 되지 않은 경우: 에러 체크
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cout << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer 
}

void draw_temp() {
	if (area1 == -1)
		DrawTemp1();
	else if (area1 == -2 || area1 == -3 || area1 == -4 || area1 == -5)
		DrawTemp1_p();

	if (area2 == -1)
		DrawTemp2();
	else if (area2 == -2 || area2 == -3 || area2 == -4 || area2 == -5)
		DrawTemp2_p();

	if (area3 == -1)
		DrawTemp3();
	else if (area3 == -2 || area3 == -3 || area3 == -4 || area3 == -5)
		DrawTemp3_p();

	if (area4 == -1)
		DrawTemp4();
	else if (area4 == -2 || area4 == -3 || area4 == -4 || area4 == -5)
		DrawTemp4_p();

}

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{

	InitDot();
	InitLine();
	InitTri();
	InitRec();
	InitPen();

	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;




	glewInit();
	make_shaderProgram();


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);

	glutMainLoop();
}
