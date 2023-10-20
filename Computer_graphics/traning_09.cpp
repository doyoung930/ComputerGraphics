#define _CRT_SECURE_NO_WARNINGS //--- 프로그램 맨 앞에 선언할 것
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
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
uniform_real_distribution<double> r_speed(0.05f, 0.1f);


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
bool s_TimerAlive = false;

int s_location = 0;

bool tri_line = true;	// --- true는 삼각형 false는 선

int s_motion = 0; //

float tempx = 0;
float tempy = -1.0;

int tri_dir_draw = 0; // 0 bottom 1 top 2 left 3 right

// class
struct tri {
	
	GLfloat base_x;
	GLfloat base_y;
	
	GLfloat tripos[3][3];
	GLfloat	t_x1, t_y1, t_z1;
	GLfloat t_x2, t_y2, t_z2;
	GLfloat t_x3, t_y3, t_z3;
	GLclampf r, g, b;
	GLclampf r2, g2, b2;
	GLclampf r3, g3, b3;

	GLfloat t_dirx;
	GLfloat t_diry;

	GLfloat t_speedx;
	GLfloat t_speedy;

	int tri_draw = 0; // 0 bottom 1 top 2 right 3 left

	bool t_motion2_dir = true;
	int t_motion3_dir = 0;
	int t_motion4_dir = 0;
	int count = 0;


	bool select = false;
};

struct Line {
	GLfloat linepos1[2][3];
	GLfloat linepos2[2][3];
	GLfloat linepos3[2][3];

	GLfloat	l_x1, l_y1, l_z1;
	GLfloat l_x2, l_y2, l_z2;
	GLfloat l_x3, l_y3, l_z3;

	GLclampf r, g, b;
	GLclampf r2, g2, b2;
	GLclampf r3, g3, b3;

	GLfloat t_dirx;
	GLfloat t_diry;

	bool select = false;
};

// vector
vector<tri> tris;
vector<Line> lines;

// function
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
void TriMotion1();
void TimerFunction(int value);

void InitTri() {


	for (int i = 0; i < 4; i++) {
		tri Tri;
		if (i == 0) {
			Tri.base_x = -0.7;
			Tri.t_dirx = Tri.base_x;
			Tri.base_y = -1.0; Tri.t_diry = Tri.base_y;
		}
		else if (i == 1) {
			Tri.base_x = 0.7;
			Tri.t_dirx = Tri.base_x;
			Tri.base_y = -1.0; Tri.t_diry = Tri.base_y;

		}
		else if (i == 2) {
			Tri.base_x = -0.3;
			Tri.t_dirx = Tri.base_x;
			Tri.base_y = -1.0; Tri.t_diry = Tri.base_y;
		}
		else if (i == 3) {
			Tri.base_x = 0.3;
			Tri.t_dirx = Tri.base_x;
			Tri.base_y = -1.0;
			Tri.t_diry = Tri.base_y;
		}
		
		Tri.t_x1 = Tri.base_x;
		Tri.t_y1 = Tri.base_y + 0.1;
		Tri.t_z1 = 0.0f;

		Tri.t_x2 = Tri.base_x - 0.05;
		Tri.t_y2 = Tri.base_y;
		Tri.t_z2 = 0.0f;

		Tri.t_x3 = Tri.base_x + 0.05;
		Tri.t_y3 = Tri.base_y;
		Tri.t_z3 = 0.0f;

		Tri.tripos[0][0] = Tri.t_x1;
		Tri.tripos[0][1] = Tri.t_y1;
		Tri.tripos[0][2] = Tri.t_z1;
		Tri.tripos[1][0] = Tri.t_x2;
		Tri.tripos[1][1] = Tri.t_y2;
		Tri.tripos[1][2] = Tri.t_z2;
		Tri.tripos[2][0] = Tri.t_x3;
		Tri.tripos[2][1] = Tri.t_y3;
		Tri.tripos[2][2] = Tri.t_z3;

		Tri.r = dist_r(eng);
		Tri.g = dist_g(eng);
		Tri.b = dist_b(eng);

		Tri.r2 = dist_r(eng);
		Tri.g2 = dist_g(eng);
		Tri.b2 = dist_b(eng);

		Tri.r3 = dist_r(eng);
		Tri.g3 = dist_g(eng);
		Tri.b3 = dist_b(eng);

		Tri.select = true;

		Tri.t_speedx = r_speed(eng);
		Tri.t_speedy = Tri.t_speedx;

		tris.push_back(Tri);
	}
}

void InitLine() {

	for (int i = 0; i < 4; i++) {
		Line line;
		if (i == 0) {
			tempx = -0.7;
			tempy = -1.0;
		}
		else if (i == 1) {
			tempx = 0.7;
			tempy = -1.0;
		}
		else if (i == 2) {
			tempx = -0.3;
			tempy = -1.0;
		}
		else if (i == 3) {
			tempx = 0.3;
			tempy = -1.0;
		}

		line.l_x1 = tempx;
		line.l_y1 = tempy + 0.1f;
		line.l_z1 = 0.0f;

		line.l_x2 = tempx - 0.05;
		line.l_y2 = tempy;
		line.l_z2 = 0.0f;

		line.l_x3 = tempx + 0.05;
		line.l_y3 = tempy;
		line.l_z3 = 0.0f;

		line.linepos1[0][0] = line.l_x1;
		line.linepos1[0][1] = line.l_y1;
		line.linepos1[0][2] = 0.0f;
		line.linepos1[1][0] = line.l_x2;
		line.linepos1[1][1] = line.l_y2;
		line.linepos1[1][2] = 0.0f;

		line.linepos2[0][0] = line.l_x1;
		line.linepos2[0][1] = line.l_y1;
		line.linepos2[0][2] = 0.0f;
		line.linepos2[1][0] = line.l_x3;
		line.linepos2[1][1] = line.l_y3;
		line.linepos2[1][2] = 0.0f;

		line.linepos3[0][0] = line.l_x2;
		line.linepos3[0][1] = line.l_y2;
		line.linepos3[0][2] = 0.0f;
		line.linepos3[1][0] = line.l_x3;
		line.linepos3[1][1] = line.l_y3;
		line.linepos3[1][2] = 0.0f;

		line.r = dist_r(eng);
		line.g = dist_g(eng);
		line.b = dist_b(eng);

		line.r2 = dist_r(eng);
		line.g2 = dist_g(eng);
		line.b2 = dist_b(eng);

		line.r3 = dist_r(eng);
		line.g3 = dist_g(eng);
		line.b3 = dist_b(eng);

		line.select = true;

		lines.push_back(line);
	}
}

void MouseInput(int m_x, int m_y, double r) {
	float tempx;
	float tempy;
	tempx = ((float)m_x - 400) / 400;
	tempy = (300 - (float)m_y) / 300;


	tris[s_location - 1].t_x1 = tempx;
	tris[s_location - 1].t_y1 = tempy + 0.2 * r;
	tris[s_location - 1].t_z1 = 0.0f;

	tris[s_location - 1].t_x2 = tempx - 0.1 * r;
	tris[s_location - 1].t_y2 = tempy;
	tris[s_location - 1].t_z2 = 0.0f;

	tris[s_location - 1].t_x3 = tempx + 0.1 * r;
	tris[s_location - 1].t_y3 = tempy ;
	tris[s_location - 1].t_z3 = 0.0f;

	tris[s_location - 1].tripos[0][0] = tempx;
	tris[s_location - 1].tripos[0][1] = tempy + 0.2 *r;
	tris[s_location - 1].tripos[0][2] = 0.0f;
	tris[s_location - 1].tripos[1][0] = tempx - 0.1 * r;
	tris[s_location - 1].tripos[1][1] = tempy ;
	tris[s_location - 1].tripos[1][2] = 0.0f;
	tris[s_location - 1].tripos[2][0] = tempx + 0.1 * r;
	tris[s_location - 1].tripos[2][1] = tempy ;
	tris[s_location - 1].tripos[2][2] = 0.0f;

	tris[s_location - 1].r = dist_r(eng);
	tris[s_location - 1].g = dist_g(eng);
	tris[s_location - 1].b = dist_b(eng);

	tris[s_location - 1].r2 = dist_r(eng);
	tris[s_location - 1].g2 = dist_g(eng);
	tris[s_location - 1].b2 = dist_b(eng);

	tris[s_location - 1].r3 = dist_r(eng);
	tris[s_location - 1].g3 = dist_g(eng);
	tris[s_location - 1].b3 = dist_b(eng);

	tris[s_location - 1].select = true;
}

void MouseInputLine(int m_x, int m_y, double r) {

	float tempx;
	float tempy;
	tempx = ((float)m_x - 400) / 400;
	tempy = (300 - (float)m_y) / 300;


	lines[s_location - 1].l_x1 = tempx;
	lines[s_location - 1].l_y1 = tempy + 0.2 * r;
	lines[s_location - 1].l_z1 = 0.0f;

	lines[s_location - 1].l_x2 = tempx - 0.1 * r;
	lines[s_location - 1].l_y2 = tempy - 0.1 * r;
	lines[s_location - 1].l_z2 = 0.0f;

	lines[s_location - 1].l_x3 = tempx + 0.1 * r;
	lines[s_location - 1].l_y3 = tempy - 0.1 * r;
	lines[s_location - 1].l_z3 = 0.0f;

	lines[s_location - 1].linepos1[0][0] = tempx;
	lines[s_location - 1].linepos1[0][1] = tempy + 0.2 * r;
	lines[s_location - 1].linepos1[0][2] = 0.0f;
	lines[s_location - 1].linepos1[1][0] = tempx - 0.1 * r;
	lines[s_location - 1].linepos1[1][1] = tempy;
	lines[s_location - 1].linepos1[1][2] = 0.0f;

	lines[s_location - 1].linepos2[0][0] = tempx - 0.1 * r;
	lines[s_location - 1].linepos2[0][1] = tempy ;
	lines[s_location - 1].linepos2[0][2] = 0.0f;
	lines[s_location - 1].linepos2[1][0] = tempx + 0.1 * r;
	lines[s_location - 1].linepos2[1][1] = tempy ;
	lines[s_location - 1].linepos2[1][2] = 0.0f;

	lines[s_location - 1].linepos3[0][0] = tempx + 0.1 * r;
	lines[s_location - 1].linepos3[0][1] = tempy;
	lines[s_location - 1].linepos3[0][2] = 0.0f;
	lines[s_location - 1].linepos3[1][0] = tempx;
	lines[s_location - 1].linepos3[1][1] = tempy + 0.2 * r;
	lines[s_location - 1].linepos3[1][2] = 0.0f;

	lines[s_location - 1].r = dist_r(eng);
	lines[s_location - 1].g = dist_g(eng);
	lines[s_location - 1].b = dist_b(eng);

	lines[s_location - 1].r2 = dist_r(eng);
	lines[s_location - 1].g2 = dist_g(eng);
	lines[s_location - 1].b2 = dist_b(eng);

	lines[s_location - 1].r3 = dist_r(eng);
	lines[s_location - 1].g3 = dist_g(eng);
	lines[s_location - 1].b3 = dist_b(eng);

	lines[s_location - 1].select = true;
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

void DrawTri() {
	for (int i = 0; i < 4; i++) {

		tris[i].t_x1 = tris[i].t_dirx;
		tris[i].t_y1 = tris[i].t_diry + 0.1;
		tris[i].t_z1 = 0.0f;

		tris[i].t_x2 = tris[i].t_dirx - 0.05;
		tris[i].t_y2 = tris[i].t_diry;
		tris[i].t_z2 = 0.0f;

		tris[i].t_x3 = tris[i].t_dirx + 0.05;
		tris[i].t_y3 = tris[i].t_diry;
		tris[i].t_z3 = 0.0f;

		tris[i].tripos[0][0] = tris[i].t_x1;
		tris[i].tripos[0][1] = tris[i].t_y1;
		tris[i].tripos[0][2] = tris[i].t_z1;
		tris[i].tripos[1][0] = tris[i].t_x2;
		tris[i].tripos[1][1] = tris[i].t_y2;
		tris[i].tripos[1][2] = tris[i].t_z2;
		tris[i].tripos[2][0] = tris[i].t_x3;
		tris[i].tripos[2][1] = tris[i].t_y3;
		tris[i].tripos[2][2] = tris[i].t_z3;

		tris[i].r = dist_r(eng);
		tris[i].g = dist_g(eng);
		tris[i].b = dist_b(eng);

		tris[i].r2 = dist_r(eng);
		tris[i].g2 = dist_g(eng);
		tris[i].b2 = dist_b(eng);

		tris[i].r3 = dist_r(eng);
		tris[i].g3 = dist_g(eng);
		tris[i].b3 = dist_b(eng);

		tris[i].select = true;

	}
}

void DrawTri_bottom(int i) {

		tris[i].t_x1 = tris[i].t_dirx;
		tris[i].t_y1 = tris[i].t_diry + 0.1;
		tris[i].t_z1 = 0.0f;

		tris[i].t_x2 = tris[i].t_dirx - 0.05;
		tris[i].t_y2 = tris[i].t_diry;
		tris[i].t_z2 = 0.0f;

		tris[i].t_x3 = tris[i].t_dirx + 0.05;
		tris[i].t_y3 = tris[i].t_diry;
		tris[i].t_z3 = 0.0f;

		tris[i].tripos[0][0] = tris[i].t_x1;
		tris[i].tripos[0][1] = tris[i].t_y1;
		tris[i].tripos[0][2] = tris[i].t_z1;
		tris[i].tripos[1][0] = tris[i].t_x2;
		tris[i].tripos[1][1] = tris[i].t_y2;
		tris[i].tripos[1][2] = tris[i].t_z2;
		tris[i].tripos[2][0] = tris[i].t_x3;
		tris[i].tripos[2][1] = tris[i].t_y3;
		tris[i].tripos[2][2] = tris[i].t_z3;

		tris[i].r = dist_r(eng);
		tris[i].g = dist_g(eng);
		tris[i].b = dist_b(eng);

		tris[i].r2 = dist_r(eng);
		tris[i].g2 = dist_g(eng);
		tris[i].b2 = dist_b(eng);

		tris[i].r3 = dist_r(eng);
		tris[i].g3 = dist_g(eng);
		tris[i].b3 = dist_b(eng);

		tris[i].select = true;


}
void DrawTri_left(int i)
{

		tris[i].t_x1 = tris[i].t_dirx - 0.1;
		tris[i].t_y1 = tris[i].t_diry;
		tris[i].t_z1 = 0.0f;

		tris[i].t_x2 = tris[i].t_dirx;
		tris[i].t_y2 = tris[i].t_diry - 0.05;
		tris[i].t_z2 = 0.0f;

		tris[i].t_x3 = tris[i].t_dirx;
		tris[i].t_y3 = tris[i].t_diry + 0.05;
		tris[i].t_z3 = 0.0f;

		tris[i].tripos[0][0] = tris[i].t_x1;
		tris[i].tripos[0][1] = tris[i].t_y1;
		tris[i].tripos[0][2] = tris[i].t_z1;
		tris[i].tripos[1][0] = tris[i].t_x2;
		tris[i].tripos[1][1] = tris[i].t_y2;
		tris[i].tripos[1][2] = tris[i].t_z2;
		tris[i].tripos[2][0] = tris[i].t_x3;
		tris[i].tripos[2][1] = tris[i].t_y3;
		tris[i].tripos[2][2] = tris[i].t_z3;

		tris[i].r = dist_r(eng);
		tris[i].g = dist_g(eng);
		tris[i].b = dist_b(eng);

		tris[i].r2 = dist_r(eng);
		tris[i].g2 = dist_g(eng);
		tris[i].b2 = dist_b(eng);

		tris[i].r3 = dist_r(eng);
		tris[i].g3 = dist_g(eng);
		tris[i].b3 = dist_b(eng);

		tris[i].select = true;


}
void DrawTri_right(int i)
{

		tris[i].t_x1 = tris[i].t_dirx + 0.1;
		tris[i].t_y1 = tris[i].t_diry ;
		tris[i].t_z1 = 0.0f;

		tris[i].t_x2 = tris[i].t_dirx ;
		tris[i].t_y2 = tris[i].t_diry - 0.05;
		tris[i].t_z2 = 0.0f;

		tris[i].t_x3 = tris[i].t_dirx ;
		tris[i].t_y3 = tris[i].t_diry + 0.05;
		tris[i].t_z3 = 0.0f;

		tris[i].tripos[0][0] = tris[i].t_x1;
		tris[i].tripos[0][1] = tris[i].t_y1;
		tris[i].tripos[0][2] = tris[i].t_z1;
		tris[i].tripos[1][0] = tris[i].t_x2;
		tris[i].tripos[1][1] = tris[i].t_y2;
		tris[i].tripos[1][2] = tris[i].t_z2;
		tris[i].tripos[2][0] = tris[i].t_x3;
		tris[i].tripos[2][1] = tris[i].t_y3;
		tris[i].tripos[2][2] = tris[i].t_z3;

		tris[i].r = dist_r(eng);
		tris[i].g = dist_g(eng);
		tris[i].b = dist_b(eng);

		tris[i].r2 = dist_r(eng);
		tris[i].g2 = dist_g(eng);
		tris[i].b2 = dist_b(eng);

		tris[i].r3 = dist_r(eng);
		tris[i].g3 = dist_g(eng);
		tris[i].b3 = dist_b(eng);

		tris[i].select = true;


}
void DrawTri_top(int i)
{

		tris[i].t_x1 = tris[i].t_dirx;
		tris[i].t_y1 = tris[i].t_diry - 0.1;
		tris[i].t_z1 = 0.0f;

		tris[i].t_x2 = tris[i].t_dirx - 0.05;
		tris[i].t_y2 = tris[i].t_diry;
		tris[i].t_z2 = 0.0f;

		tris[i].t_x3 = tris[i].t_dirx + 0.05;
		tris[i].t_y3 = tris[i].t_diry;
		tris[i].t_z3 = 0.0f;

		tris[i].tripos[0][0] = tris[i].t_x1;
		tris[i].tripos[0][1] = tris[i].t_y1;
		tris[i].tripos[0][2] = tris[i].t_z1;
		tris[i].tripos[1][0] = tris[i].t_x2;
		tris[i].tripos[1][1] = tris[i].t_y2;
		tris[i].tripos[1][2] = tris[i].t_z2;
		tris[i].tripos[2][0] = tris[i].t_x3;
		tris[i].tripos[2][1] = tris[i].t_y3;
		tris[i].tripos[2][2] = tris[i].t_z3;

		tris[i].r = dist_r(eng);
		tris[i].g = dist_g(eng);
		tris[i].b = dist_b(eng);

		tris[i].r2 = dist_r(eng);
		tris[i].g2 = dist_g(eng);
		tris[i].b2 = dist_b(eng);

		tris[i].r3 = dist_r(eng);
		tris[i].g3 = dist_g(eng);
		tris[i].b3 = dist_b(eng);

		tris[i].select = true;

}


void TriMotion1() {
	for (int i = 0; i < 4; i++) {
		tris[i].t_dirx = tris[i].t_dirx + tris[i].t_speedx;
		tris[i].t_diry = tris[i].t_diry + tris[i].t_speedy;
		
	}
}
void TriMotion2() {
	for (int i = 0; i < 4; i++) {
		if (tris[i].count == 5) {
			tris[i].count = 0;
			tris[i].t_motion2_dir = true;
		}
		if(tris[i].t_motion2_dir)
			tris[i].t_dirx = tris[i].t_dirx + tris[i].t_speedx;
		else {
			tris[i].t_diry = tris[i].t_diry + tris[i].t_speedy;
			tris[i].count++;
		}
	}
}
void TriMotion3() {
	for (int i = 0; i < 4; i++) {
		if (tris[i].t_motion3_dir == 0)
			tris[i].t_dirx = tris[i].t_dirx - tris[i].t_speedx;
		else if (tris[i].t_motion3_dir == 1)
			tris[i].t_diry = tris[i].t_diry - tris[i].t_speedy;
		else if (tris[i].t_motion3_dir == 2)
			tris[i].t_dirx = tris[i].t_dirx + tris[i].t_speedx;
		else if (tris[i].t_motion3_dir == 3)
			tris[i].t_diry = tris[i].t_diry + tris[i].t_speedy;
		else if (tris[i].t_motion3_dir == 4)
			tris[i].t_dirx = tris[i].t_dirx - tris[i].t_speedx;
		else if (tris[i].t_motion3_dir == 5)
			tris[i].t_diry = tris[i].t_diry - tris[i].t_speedy;
		else if (tris[i].t_motion3_dir == 6)
			tris[i].t_dirx = tris[i].t_dirx + tris[i].t_speedx;
		else if (tris[i].t_motion3_dir == 7)
			tris[i].t_diry = tris[i].t_diry + tris[i].t_speedy;
		else if (tris[i].t_motion3_dir == 8)
			tris[i].t_dirx = tris[i].t_dirx - tris[i].t_speedx;
		else if (tris[i].t_motion3_dir == 9)
			tris[i].t_diry = tris[i].t_diry - tris[i].t_speedy;
		else if (tris[i].t_motion3_dir == 10)
			tris[i].t_dirx = tris[i].t_dirx + tris[i].t_speedx;
		else if (tris[i].t_motion3_dir == 11)
			tris[i].t_diry = tris[i].t_diry + tris[i].t_speedy;
	}
}
void TriMotion4() {
	static float radius = 0.0f; // 초기 반지름을 0으로 설정합니다.
	static float angle = 0.0f; // 초기 반지름을 0으로 설정합니다.
	const float maxRadius = 0.9f; // 원의 최대 반지름
	const float rotationSpeed = 0.1f; // 회전 속도 조절

	for (int i = 0; i < 4; i++) {
		// 중심 좌표를 설정
		float centerX = 0.0f;
		float centerY = 0.0f;

		// 각 삼각형의 위치를 계산 (중심에서 바깥으로 이동)
		float radius = maxRadius * (angle / (2 * M_PI)); // 증가하는 반지름 계산
		float x = centerX + radius * cos(angle); // 마이너스 추가
		float y = centerY + radius * sin(angle); // 마이너스 추가

		// 각 삼각형의 위치 및 방향 설정
		tris[i].t_dirx = x;
		tris[i].t_diry = y;

		// 각 삼각형의 그림자 표현을 계산
		tris[i].t_x1 = x;
		tris[i].t_y1 = y + 0.1;
		tris[i].t_z1 = 0.0f;

		tris[i].t_x2 = x - 0.05;
		tris[i].t_y2 = y;
		tris[i].t_z2 = 0.0f;

		tris[i].t_x3 = x + 0.05;
		tris[i].t_y3 = y;
		tris[i].t_z3 = 0.0f;

		// 다음 각도를 계산
		angle += rotationSpeed;

		// 원 슌 스파이럴 패턴의 끝 지점에서 시작점으로 돌아갑니다.
		if (angle >= 2 * M_PI) {
			angle = 0.0f;
		}
	}
}
void AABB() {
	for (tri& Tri : tris) {
		// 벽과의 충돌 검사
		if (Tri.t_dirx + Tri.t_speedx < -1.0f) {
			// 왼쪽 벽과 충돌한 경우
			Tri.t_speedx = fabs(Tri.t_speedx); // 반사벡터 설정
			Tri.tri_draw = 3;
		}
		else if (Tri.t_dirx + Tri.t_speedx > 1.0f) {
			// 오른쪽 벽과 충돌한 경우
			Tri.t_speedx = -fabs(Tri.t_speedx); // 반사벡터 설정
			Tri.tri_draw = 2;
		}

		if (Tri.t_diry + Tri.t_speedy < -1.0f) {
			// 아래 벽과 충돌한 경우
			Tri.t_speedy = fabs(Tri.t_speedy); // 반사벡터 설정
			Tri.tri_draw = 0;
		}
		else if (Tri.t_diry + Tri.t_speedy > 1.0f) {
			// 위 벽과 충돌한 경우
			Tri.t_speedy = -fabs(Tri.t_speedy); // 반사벡터 설정
			Tri.tri_draw = 1;
		}
	}
	
}
void AABB2() {
	for (tri& Tri : tris) {
		// 벽과의 충돌 검사
		if (Tri.t_dirx + Tri.t_speedx < -1.0f) {
			// 왼쪽 벽과 충돌한 경우
			Tri.t_speedx = fabs(Tri.t_speedx); // 반사벡터 설정
			Tri.tri_draw = 3;
			Tri.t_motion2_dir = false;
			
		}
		else if (Tri.t_dirx + Tri.t_speedx > 1.0f) {
			// 오른쪽 벽과 충돌한 경우
			Tri.t_speedx = -fabs(Tri.t_speedx); // 반사벡터 설정
			Tri.tri_draw = 2;
			Tri.t_motion2_dir = false;
		}

		if (Tri.t_diry + Tri.t_speedy < -1.0f) {
			// 아래 벽과 충돌한 경우
			Tri.t_speedy = fabs(Tri.t_speedy); // 반사벡터 설정
			
		}
		else if (Tri.t_diry + Tri.t_speedy > 1.0f) {
			// 위 벽과 충돌한 경우
			Tri.t_speedy = -fabs(Tri.t_speedy); // 반사벡터 설정
			
		}
	}

}
void AABB3() {
	for (tri& Tri : tris) {
		if (Tri.t_motion3_dir == 0) {
			if (Tri.t_dirx - Tri.t_speedx < -1.0f) {
				Tri.tri_draw = 3;
				Tri.t_motion3_dir = 1;
				Tri.t_dirx = -0.95f;
			}
		}
		else if (Tri.t_motion3_dir == 1) {
			if (Tri.t_diry - Tri.t_speedy < -1.0f) {
				Tri.tri_draw = 0;
				Tri.t_motion3_dir = 2;
				Tri.t_diry = -0.95f;
			}
		}
		else if (Tri.t_motion3_dir == 2) {
			if (Tri.t_dirx + Tri.t_speedx > 1.0f) {
				Tri.tri_draw = 2;
				Tri.t_motion3_dir = 3;
				Tri.t_dirx = 0.95f;
			}
		}
		else if (Tri.t_motion3_dir == 3) {
			if (Tri.t_diry + Tri.t_speedy > 0.75f) {
				Tri.tri_draw = 1;
				Tri.t_motion3_dir = 4;
				Tri.t_diry = 0.7f;
			}
		}
		else if (Tri.t_motion3_dir == 4) {
			if (Tri.t_dirx - Tri.t_speedx < -0.75f) {
				Tri.tri_draw = 3;
				Tri.t_motion3_dir = 5;
				Tri.t_dirx = -0.7f;
			}
		}
		else if (Tri.t_motion3_dir == 5) {
			if (Tri.t_diry - Tri.t_speedy < -0.75f) {
				Tri.tri_draw = 0;
				Tri.t_motion3_dir = 6;
				Tri.t_diry = -0.7f;
			}
		}
		else if (Tri.t_motion3_dir == 6) {
			if (Tri.t_dirx - Tri.t_speedx > 0.75f) {
				Tri.tri_draw = 2;
				Tri.t_motion3_dir = 7;
				Tri.t_dirx = 0.7f;
			}
		}
		else if (Tri.t_motion3_dir == 7) {
			if (Tri.t_diry - Tri.t_speedy > 0.5f) {
				Tri.tri_draw = 1;
				Tri.t_motion3_dir = 8;
				Tri.t_diry = 0.5f;
			}
		}
		else if (Tri.t_motion3_dir == 8) {
			if (Tri.t_dirx - Tri.t_speedx < -0.5f) {
				Tri.tri_draw = 3;
				Tri.t_motion3_dir = 9;
				Tri.t_dirx = -0.5f;
			}
		}
		else if (Tri.t_motion3_dir == 9) {
			if (Tri.t_diry - Tri.t_speedy < -0.5f) {
				Tri.tri_draw = 0;
				Tri.t_motion3_dir = 10;
				Tri.t_diry = -0.5f;
			}
		}
		else if (Tri.t_motion3_dir == 10) {
			if (Tri.t_dirx - Tri.t_speedx > 0.0f) {
				Tri.tri_draw = 2;
				Tri.t_motion3_dir = 11;
				Tri.t_dirx = 0.0f;
			}
		}
		else if (Tri.t_motion3_dir == 11) {
			if (Tri.t_diry - Tri.t_speedy > 0.0f) {
				Tri.tri_draw = 1;
				Tri.t_motion3_dir = 12;
				Tri.t_diry = 0.0f;
			}
		}
	}

}

void AABB4() {
	
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		tri_line = true;
		break;
	case 'b':
		tri_line = false;
		break;
	case '1':

		s_motion = 1;
		if(s_TimerAlive == false)
			glutTimerFunc(100, TimerFunction, 1);
		s_TimerAlive = true;
		break;
	case '2':

		s_motion = 2;
		if (s_TimerAlive == false)
			glutTimerFunc(100, TimerFunction, 1);
		s_TimerAlive = true;
		break;
	case '3':
		s_motion = 3;
		for (tri& Tri : tris) {
			Tri.tri_draw = 1;
			Tri.t_dirx = 1.0f - 0.05f;
			Tri.t_diry = 1.0f - 0.1;
			Tri.t_speedx = fabs(Tri.t_speedx);
			Tri.t_speedy = fabs(Tri.t_speedy);
			Tri.t_motion3_dir = 0;
		}
		if (s_TimerAlive == false)
			glutTimerFunc(100, TimerFunction, 1);
		s_TimerAlive = true;
		break;
	case '4':
		s_motion = 4;
		for (tri& Tri : tris) {
			Tri.tri_draw = 1;
			Tri.t_dirx = 0;
			Tri.t_diry = 0;
			Tri.t_speedx = fabs(Tri.t_speedx);
			Tri.t_speedy = fabs(Tri.t_speedy);
			Tri.t_motion4_dir = 0;
		}
		if (s_TimerAlive == false)
			glutTimerFunc(100, TimerFunction, 1);
		s_TimerAlive = true;
		break;
	case 'p':
		s_TimerAlive = false;
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
}

void TimerFunction(int value)
{
	if (s_motion == 1){
		TriMotion1();
		AABB();
	}
	if (s_motion == 2) {
		TriMotion2();
		AABB2();
	}
	if (s_motion == 3) {
		TriMotion3();
			AABB3();
	}
	if (s_motion == 4) {
		TriMotion4();
	}
	for (int i = 0; i < 4; i++) {
		if (tris[i].tri_draw == 0) 	DrawTri_bottom(i);
		else if (tris[i].tri_draw == 1) DrawTri_top(i);
		else if (tris[i].tri_draw == 2)  DrawTri_left(i);
		else if (tris[i].tri_draw == 3)  DrawTri_right(i);
	}
	drawScene();
	glutPostRedisplay(); // 화면 재 출력
	
	
	if (s_TimerAlive)
		glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

GLvoid drawScene()
{

	//--- 변경된 배경색 설정
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(shaderProgramID);
	

	if (tri_line == true) {
		for (int i = 0; i < tris.size(); i++)
		{


			const GLfloat tripos[3][3] = { //--- 삼각형 위치 값
			{tris[i].t_x1, tris[i].t_y1, 0.0},
			{tris[i].t_x2, tris[i].t_y2, 0.0},
			{tris[i].t_x3, tris[i].t_y3, 0.0} };
			const GLfloat tricolor[3][3] = { //--- 삼각형 꼭지점 색상
			{ tris[i].r, tris[i].g,tris[i].b}, {tris[i].r2, tris[i].g2,tris[i].b2}, {tris[i].r3, tris[i].g3,tris[i].b3} };

			glGenBuffers(1, &TriPosVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, TriPosVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(tris[i].tripos) * tris.size(), tris[i].tripos, GL_STATIC_DRAW);
			glGenBuffers(1, &TriColorVbo[i]);
			glBindBuffer(GL_ARRAY_BUFFER, TriColorVbo[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(tricolor) * tris.size(), tricolor, GL_STATIC_DRAW);

			// Location 번호 저장
			int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
			int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

			glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
			glEnableVertexAttribArray(ColorLocation);

			{
				glBindBuffer(GL_ARRAY_BUFFER, TriPosVbo[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			{
				glBindBuffer(GL_ARRAY_BUFFER, TriColorVbo[i]); // VBO Bind
				glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			glDrawArrays(GL_TRIANGLES, 0, 3); // 설정대로 출력
			glDisableVertexAttribArray(PosLocation);	// Disable 필수!
			glDisableVertexAttribArray(ColorLocation);
		}
	}
	else {
		for (int i = 0; i < lines.size(); i++) {
			const GLfloat linepos[2][3] = { //--- 삼각형 위치 값
				{lines[i].linepos1[0][0], lines[i].linepos1[0][1], 0.0},
				{lines[i].linepos1[1][0], lines[i].linepos1[1][1], 0.0} };
			const GLfloat linepos2[2][3] = { //--- 삼각형 위치 값
				{lines[i].linepos2[0][0], lines[i].linepos2[0][1], 0.0},
				{lines[i].linepos2[1][0], lines[i].linepos2[1][1], 0.0} };
			const GLfloat linepos3[2][3] = { //--- 삼각형 위치 값
				{lines[i].linepos3[0][0], lines[i].linepos3[0][1], 0.0},
				{lines[i].linepos3[1][0], lines[i].linepos3[1][1], 0.0} };


			glGenBuffers(1, &lVbo1[i]);
			glBindBuffer(GL_ARRAY_BUFFER, lVbo1[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(linepos), linepos, GL_STATIC_DRAW);

			// Location 번호 저장
			int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
			int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

			glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미

			{
				glBindBuffer(GL_ARRAY_BUFFER, lVbo1[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			glLineWidth(3);
			glDrawArrays(GL_LINES, 0, 2); // 설정대로 출력
			glDisableVertexAttribArray(PosLocation);	// Disable 필수!


			glGenBuffers(1, &lVbo2[i]);
			glBindBuffer(GL_ARRAY_BUFFER, lVbo2[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(linepos2), linepos2, GL_STATIC_DRAW);

			glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미

			{
				glBindBuffer(GL_ARRAY_BUFFER, lVbo2[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			glLineWidth(3);
			glDrawArrays(GL_LINES, 0, 2); // 설정대로 출력
			glDisableVertexAttribArray(PosLocation);	// Disable 필수!

			glGenBuffers(1, &lVbo3[i]);
			glBindBuffer(GL_ARRAY_BUFFER, lVbo3[i]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(linepos3), linepos3, GL_STATIC_DRAW);

			glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미

			{
				glBindBuffer(GL_ARRAY_BUFFER, lVbo3[i]); // VBO Bind
				glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
			}
			glLineWidth(3);
			glDrawArrays(GL_LINES, 0, 2); // 설정대로 출력
			glDisableVertexAttribArray(PosLocation);	// Disable 필수!
		}
	}
	glutSwapBuffers(); //--- 화면에 출력하기
}

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

void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;

	InitTri();
	InitLine();

	glewInit();
	make_shaderProgram();


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);

	glutMainLoop();
}
