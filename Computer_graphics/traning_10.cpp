#define _CRT_SECURE_NO_WARNINGS //--- ���α׷� �� �տ� ������ ��
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cmath>
// �ʿ��� ��� include ���� �߰��ϼž� �մϴ�~

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
mt19937 gen(seeder());
uniform_real_distribution<double> dist_r(0.0f, 1.0f);
uniform_real_distribution<double> dist_g(0.0f, 1.0f);
uniform_real_distribution<double> dist_b(0.0f, 1.0f);
uniform_real_distribution<double> dist(0.1f, 0.5f);
uniform_real_distribution<double> r_speed(0.05f, 0.1f);
uniform_int_distribution<int> distribution(0, 1);
int r_dir = distribution(gen);
GLdouble bg_r, bg_g, bg_b;


//uniform_real_distribution<int> dist_x(1, 10);
//uniform_real_distribution<int> dist_y(1, 10);
//uniform_real_distribution<int> num(1, 10);

//--- ���� ����
GLuint TriPosVbo[10], TriColorVbo[10];
GLchar* vertexSource, * fragmentSource; //--- �ҽ��ڵ� ���� ����
GLuint vertexShader, fragmentShader; //--- ���̴� ��ü
GLuint shaderProgramID; //--- ���̴� ���α׷�
GLuint LineVbo1, LineVbo2;
GLuint lVbo1[4], lVbo2[4], lVbo3[4];
bool s_TimerAlive = false;		// Ÿ�̸�

int s_spiral_num = 1;		// �����̷� ȸ�� ����
int s_draw_method = 0;	// --- 0 Dot / 1 Line
float centerX = 0.0f;	// ����x
float centerY = 0.0f;	// ����y
bool isMouseClick = false;	// ���콺 Ŭ�� �̺�Ʈ
int currentPointIndex = 0; // -- ���� ���� ����
int currentPointIndex2 = 0; // -- ���� ���� ����
int numPoints= 100;		// �� ����

int draw_sp = 0;
float radius;		//
float angle1 = 0;	// 1 �����̷�
float angle2 = 0;	// 2 �����̷�

// class
struct Dot {
	GLfloat dotpos[3]{};
	GLfloat d_x, d_y, d_z;
	GLclampf r, g, b;
};
vector<Dot> dots[5];
struct Line {
	GLfloat linepos[2][3]{};
	GLfloat l_x, l_y, l_z = 0;
	GLfloat l_x1, l_y1, l_z1;
	GLfloat l_x2, l_y2, l_z2;
	GLfloat l_x3, l_y3, l_z3;
	GLclampf r, g, b;
};
vector<Line> lines[10];
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

// vector
vector<tri> tris;


// function
void MouseInput(int m_x, int m_y, double r);
void MouseInputLine(int m_x, int m_y, double r);
void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
void InitBuffer();
char* filetobuf(const char*);
void TriMotion1();
void TimerFunction(int value);
void DrawSpiralLine() {
	glLineWidth(1.0f); // Set the line width as needed

	int numPoints = 100 * s_spiral_num;

	if (s_spiral_num == 1) {
		// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 1.28f;

			glBegin(GL_LINE_STRIP);

			for (int i = 0; i < numPoints; i++) {
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}

			glEnd();
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 0.11f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

			for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
				float radius = 0.005f;
				float angle = -1.7f;

				glBegin(GL_LINE_STRIP);

				for (int i = 0; i < numPoints; i++) {
					float x = centerX2 + radius * cos(angle);
					float y = centerY2 + radius * sin(angle);

					glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
					glVertex2f(x, y);

					radius += 0.0005f;
					angle += 0.05f;
				}

				glEnd();
			}
		}
	}
	if (s_spiral_num == 2) {
		// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 2.73f;

			glBegin(GL_LINE_STRIP);

			for (int i = 0; i < numPoints; i++) {
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}

			glEnd();
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 0.21f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

			for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
				float radius = 0.005f;
				float angle = -0.6f;

				glBegin(GL_LINE_STRIP);

				for (int i = 0; i < numPoints; i++) {
					float x = centerX2 + radius * cos(angle);
					float y = centerY2 + radius * sin(angle);

					glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
					glVertex2f(x, y);

					radius += 0.0005f;
					angle += 0.05f;
				}

				glEnd();
			}
		}
	}
	if (s_spiral_num == 3) {
		// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 3.9f;

			glBegin(GL_LINE_STRIP);

			for (int i = 0; i < numPoints; i++) {
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);
				
				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;

			}

			glEnd();
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 0.31f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

			for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
				float radius = 0.005f;
				float angle = 0.77f;

				glBegin(GL_LINE_STRIP);

				for (int i = 0; i < numPoints; i++) {
					float x = centerX2 + radius * cos(angle);
					float y = centerY2 + radius * sin(angle);

					glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
					glVertex2f(x, y);

					radius += 0.0005f;
					angle += 0.05f;
				}

				glEnd();
			}
		}
	}
	if (s_spiral_num == 4) {
		// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 5.178f;

			glBegin(GL_LINE_STRIP);

			for (int i = 0; i < numPoints; i++) {
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}

			glEnd();
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 0.41f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

			for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
				float radius = 0.005f;
				float angle = 2.04f;

				glBegin(GL_LINE_STRIP);

				for (int i = 0; i < numPoints; i++) {
					float x = centerX2 + radius * cos(angle);
					float y = centerY2 + radius * sin(angle);

					glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
					glVertex2f(x, y);

					radius += 0.0005f;
					angle += 0.05f;
				}

				glEnd();
			}
		}
	}
	if (s_spiral_num == 5) {
		// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 6.5f;

			glBegin(GL_LINE_STRIP);

			for (int i = 0; i < numPoints; i++) {
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}

			glEnd();
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 0.51f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

			for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
				float radius = 0.005f;
				float angle = 3.3f;

				glBegin(GL_LINE_STRIP);

				for (int i = 0; i < numPoints; i++) {
					float x = centerX2 + radius * cos(angle);
					float y = centerY2 + radius * sin(angle);

					glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
					glVertex2f(x, y);

					radius += 0.0005f;
					angle += 0.05f;
				}

				glEnd();
			}
		}
	}
	// Add similar changes for other s_spiral_num cases (2, 3, 4, 5)
}
void DrawSpiralDot() {
	glPointSize(3.0f);

	glBegin(GL_POINTS);


	//numPoints = 1000 * s_spiral_num;
	numPoints = 1000;

	if (s_spiral_num == 1) {
		// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 1.2f;

			for (int i = 0; i < numPoints; i++) {
				
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
				Dot dot;
				dot.d_x = x;
				dot.d_y = y;
				dot.d_z = 0;
				dots[0].push_back(dot);

			}
		}

		glEnd();

		// �� ��° �����̷� �׸���
		glBegin(GL_POINTS);

		float centerX2 = centerX + 0.11f; // �� ��° �����̷��� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
			float radius = 0.005f;
			float angle = -1.7f;

			for (int i = 0; i < numPoints; i++) {
				float x = centerX2 + radius * cos(angle);
				float y = centerY2 + radius * sin(angle);

				glColor3d(0, 0,0);
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
				Dot dot;
				dot.d_x = x;
				dot.d_y = y;
				dot.d_z = 0;
				dots[1].push_back(dot);
			}
		}
	}
	if (s_spiral_num == 2) {
		// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 2.6f;

			for (int i = 0; i < numPoints; i++) {
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
				Dot dot;
				dot.d_x = x;
				dot.d_y = y;
				dot.d_z = 0;
				dots[2].push_back(dot);
			}
		}

		glEnd();

		// �� ��° �����̷� �׸���
		glBegin(GL_POINTS);

		float centerX2 = centerX + 0.21f; // �� ��° �����̷��� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
			float radius = 0.005f;
			float angle = -0.6f;

			for (int i = 0; i < numPoints; i++) {
				float x = centerX2 + radius * cos(angle);
				float y = centerY2 + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
				Dot dot;
				dot.d_x = x;
				dot.d_y = y;
				dot.d_z = 0;
				dots[3].push_back(dot);
			}
		}
	}
	if (s_spiral_num == 3) {
		// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 3.9f;

			for (int i = 0; i < numPoints; i++) {
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}
		}

		glEnd();

		// �� ��° �����̷� �׸���
		glBegin(GL_POINTS);

		float centerX2 = centerX + 0.31f; // �� ��° �����̷��� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
			float radius = 0.005f;
			float angle = 0.7f;

			for (int i = 0; i < numPoints; i++) {
				float x = centerX2 + radius * cos(angle);
				float y = centerY2 + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}
		}
	}
	if (s_spiral_num == 4) {// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 5.1f;

			for (int i = 0; i < numPoints; i++) {
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}
		}

		glEnd();

		// �� ��° �����̷� �׸���
		glBegin(GL_POINTS);

		float centerX2 = centerX + 0.41f; // �� ��° �����̷����� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
			float radius = 0.005f;
			float angle = 2.1f;

			for (int i = 0; i < numPoints; i++) {
				float x = centerX2 + radius * cos(angle);
				float y = centerY2 + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}
		}
	}
	if (s_spiral_num == 5) {// ù ��° �����̷� �׸���
		{
			float radius = 0.005f;
			float angle = 6.5f;

			for (int i = 0; i < numPoints; i++) {
				float x = centerX + radius * cos(angle);
				float y = centerY + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}
		}

		glEnd();

		// �� ��° �����̷� �׸���
		glBegin(GL_POINTS);

		float centerX2 = centerX + 0.51f; // �� ��° �����̷��� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		for (int k = 0; k < 2; k++) { // �� �� �׸��ϴ�
			float radius = 0.005f;
			float angle = 3.3f;

			for (int i = 0; i < numPoints; i++) {
				float x = centerX2 + radius * cos(angle);
				float y = centerY2 + radius * sin(angle);

				glColor3d(dist_r(eng), dist_g(eng), dist_b(eng));
				glVertex2f(x, y);

				radius += 0.0005f;
				angle += 0.05f;
			}
		}
	}
	

	glEnd();
}

void DrawSpiralDot1(){


	if (s_spiral_num == 1) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				radius += 0.0005f;
				angle1 += 0.05f;
				Dot dot;
				dot.d_x = centerX + radius * cos(angle1);
				dot.d_y = centerY + radius * sin(angle1);
				dot.d_z = 0;
				dots[0].push_back(dot);
				currentPointIndex++;
			}
		}
		// �� ��° �����̷� �׸���
		float centerX2 = centerX + 0.21f; // �� ��° �����̷��� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		 { 
			if (currentPointIndex2 < numPoints) {
				radius += 0.0005f;
				angle2 += 0.05f;
				Dot dot;
				dot.d_x = centerX2 + radius * cos(angle2);
				dot.d_y = centerY2 + radius * sin(angle2);
				dot.d_z = 0;
				dots[0].push_back(dot);
				currentPointIndex2++;
			}
		}
	}
}
void DrawSpiralDot2(){


	if (s_spiral_num == 2) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				float x = centerX + radius * cos(angle1);
				float y = centerY  + radius * sin(angle1);

				radius += 0.0005f;
				angle1 += 0.05f;
				Dot dot;
				dot.d_x = x;
				dot.d_y = y;
				dot.d_z = 0;
				currentPointIndex++;
				dots[1].push_back(dot);
			}
		}


		float centerX2 = centerX + 0.41f; // �� ��° �����̷��� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		if (currentPointIndex2 < numPoints) {
				float x = centerX2 + radius * cos(angle2);
				float y = centerY2 + radius * sin(angle2);

				radius += 0.0005f;
				angle2 += 0.05f;
				Dot dot;
				dot.d_x = x;
				dot.d_y = y;
				dot.d_z = 0;
				currentPointIndex2++;
				dots[1].push_back(dot);
		}
		
	}
}
void DrawSpiralDot3(){
	
	if (s_spiral_num == 3) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				float x = centerX + radius * cos(angle1);
				float y = centerY + 0.02 + radius * sin(angle1);

				radius += 0.0005f;
				angle1 += 0.05f;
				Dot dot;
				dot.d_x = x;
				dot.d_y = y;
				dot.d_z = 0;
				currentPointIndex++;
				dots[2].push_back(dot);
			}
		}


		float centerX2 = centerX + 0.61f; // �� ��° �����̷��� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		if (currentPointIndex2 < numPoints) {
			float x = centerX2 + radius * cos(angle2);
			float y = centerY2 + radius * sin(angle2);

			radius += 0.0005f;
			angle2 += 0.05f;
			Dot dot;
			dot.d_x = x;
			dot.d_y = y;
			dot.d_z = 0;
			currentPointIndex2++;
			dots[2].push_back(dot);
		}
		}
}
void DrawSpiralDot4(){
	if (s_spiral_num == 4) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				float x = centerX + radius * cos(angle1);
				float y = centerY  + radius * sin(angle1);

				radius += 0.0005f;
				angle1 += 0.05f;
				Dot dot;
				dot.d_x = x;
				dot.d_y = y;
				dot.d_z = 0;
				currentPointIndex++;
				dots[3].push_back(dot);
			}
		}


		float centerX2 = centerX + 0.81f; // �� ��° �����̷��� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		if (currentPointIndex2 < numPoints) {
			float x = centerX2 + radius * cos(angle2);
			float y = centerY2 + radius * sin(angle2);

			radius += 0.0005f;
			angle2 += 0.05f;
			Dot dot;
			dot.d_x = x;
			dot.d_y = y;
			dot.d_z = 0;
			currentPointIndex2++;
			dots[3].push_back(dot);
		}
	}
}
void DrawSpiralDot5(){
	if (s_spiral_num == 5) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				float x = centerX + radius * cos(angle1);
				float y = centerY + 0.02 + radius * sin(angle1);

				radius += 0.0005f;
				angle1 += 0.05f;
				Dot dot;
				dot.d_x = x;
				dot.d_y = y;
				dot.d_z = 0;
				currentPointIndex++;
				dots[4].push_back(dot);
			}
		}


		float centerX2 = centerX + 1.01f; // �� ��° �����̷��� ���� X ��ǥ
		float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ

		if (currentPointIndex2 < numPoints) {
			float x = centerX2 + radius * cos(angle2);
			float y = centerY2 + radius * sin(angle2);

			radius += 0.0005f;
			angle2 += 0.05f;
			Dot dot;
			dot.d_x = x;
			dot.d_y = y;
			dot.d_z = 0;
			currentPointIndex2++;
			dots[4].push_back(dot);
		}
	}
}

void DrawSpiralLine1() {
	if (s_spiral_num == 1) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				float x = centerX + radius * cos(angle1);
				float y = centerY + radius * sin(angle1);


				radius += 0.0005f;
				angle1 += 0.05f;

				float x1 = centerX + radius * cos(angle1);
				float y1 = centerY + radius * sin(angle1);

				Line line;
				line.l_x = x;
				line.l_y = y;
				line.l_x1 = x1;
				line.l_y1 = y1;


				lines[0].push_back(line);
				currentPointIndex++;
			}
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 0.21f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ


			if (currentPointIndex2 < numPoints) {
				float x = centerX2 + radius * cos(angle2);
				float y = centerY2 + radius * sin(angle2);


				radius += 0.0005f;
				angle2 += 0.05f;
				float x1 = centerX2 + radius * cos(angle2);
				float y1 = centerY2 + radius * sin(angle2);

				Line line;
				line.l_x2 = x;
				line.l_y2 = y;
				line.l_x3 = x1;
				line.l_y3 = y1;
				lines[1].push_back(line);
				currentPointIndex2++;
			}

			
			
		}
	}
}
void DrawSpiralLine2() {
	if (s_spiral_num ==2) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				float x = centerX + radius * cos(angle1);
				float y = centerY + radius * sin(angle1);


				radius += 0.0005f;
				angle1 += 0.05f;

				float x1 = centerX + radius * cos(angle1);
				float y1 = centerY + radius * sin(angle1);

				Line line;
				line.l_x = x;
				line.l_y = y;
				line.l_x1 = x1;
				line.l_y1 = y1;


				lines[2].push_back(line);
				currentPointIndex++;
			}
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 0.41f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ


			if (currentPointIndex2 < numPoints) {
				float x = centerX2 + radius * cos(angle2);
				float y = centerY2 + radius * sin(angle2);


				radius += 0.0005f;
				angle2 += 0.05f;
				float x1 = centerX2 + radius * cos(angle2);
				float y1 = centerY2 + radius * sin(angle2);

				Line line;
				line.l_x2 = x;
				line.l_y2 = y;
				line.l_x3 = x1;
				line.l_y3 = y1;
				lines[3].push_back(line);
				currentPointIndex2++;
			}



		}
	}
}
void DrawSpiralLine3() {
	if (s_spiral_num == 3) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				float x = centerX + radius * cos(angle1);
				float y = centerY + radius * sin(angle1);


				radius += 0.0005f;
				angle1 += 0.05f;

				float x1 = centerX + radius * cos(angle1);
				float y1 = centerY + radius * sin(angle1);

				Line line;
				line.l_x = x;
				line.l_y = y;
				line.l_x1 = x1;
				line.l_y1 = y1;


				lines[4].push_back(line);
				currentPointIndex++;
			}
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 0.61f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ


			if (currentPointIndex2 < numPoints) {
				float x = centerX2 + radius * cos(angle2);
				float y = centerY2 + radius * sin(angle2);


				radius += 0.0005f;
				angle2 += 0.05f;
				float x1 = centerX2 + radius * cos(angle2);
				float y1 = centerY2 + radius * sin(angle2);

				Line line;
				line.l_x2 = x;
				line.l_y2 = y;
				line.l_x3 = x1;
				line.l_y3 = y1;
				lines[5].push_back(line);
				currentPointIndex2++;
			}



		}
	}
}
void DrawSpiralLine4() {
	if (s_spiral_num == 4) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				float x = centerX + radius * cos(angle1);
				float y = centerY + radius * sin(angle1);


				radius += 0.0005f;
				angle1 += 0.05f;

				float x1 = centerX + radius * cos(angle1);
				float y1 = centerY + radius * sin(angle1);

				Line line;
				line.l_x = x;
				line.l_y = y;
				line.l_x1 = x1;
				line.l_y1 = y1;


				lines[6].push_back(line);
				currentPointIndex++;
			}
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 0.81f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ


			if (currentPointIndex2 < numPoints) {
				float x = centerX2 + radius * cos(angle2);
				float y = centerY2 + radius * sin(angle2);


				radius += 0.0005f;
				angle2 += 0.05f;
				float x1 = centerX2 + radius * cos(angle2);
				float y1 = centerY2 + radius * sin(angle2);

				Line line;
				line.l_x2 = x;
				line.l_y2 = y;
				line.l_x3 = x1;
				line.l_y3 = y1;
				lines[7].push_back(line);
				currentPointIndex2++;
			}



		}
	}
}
void DrawSpiralLine5() {
	if (s_spiral_num == 5) {
		// ù ��° �����̷� �׸���
		{
			if (currentPointIndex < numPoints) {
				float x = centerX + radius * cos(angle1);
				float y = centerY + radius * sin(angle1);


				radius += 0.0005f;
				angle1 += 0.05f;

				float x1 = centerX + radius * cos(angle1);
				float y1 = centerY + radius * sin(angle1);

				Line line;
				line.l_x = x;
				line.l_y = y;
				line.l_x1 = x1;
				line.l_y1 = y1;


				lines[8].push_back(line);
				currentPointIndex++;
			}
		}

		// �� ��° �����̷� �׸���
		{
			float centerX2 = centerX + 1.01f; // �� ��° �����̷��� ���� X ��ǥ
			float centerY2 = centerY; // �� ��° �����̷��� ���� Y ��ǥ


			if (currentPointIndex2 < numPoints) {
				float x = centerX2 + radius * cos(angle2);
				float y = centerY2 + radius * sin(angle2);


				radius += 0.0005f;
				angle2 += 0.05f;
				float x1 = centerX2 + radius * cos(angle2);
				float y1 = centerY2 + radius * sin(angle2);

				Line line;
				line.l_x2 = x;
				line.l_y2 = y;
				line.l_x3 = x1;
				line.l_y3 = y1;
				lines[9].push_back(line);
				currentPointIndex2++;
			}



		}
	}
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
		
		break;
	case 'l':
		
		break;
	case '1': 
		for (auto& dot : dots)
			dot.clear();
		for (auto& line : lines)
			line.clear();
		s_spiral_num = 1; break;

	case '2': 
		for (auto& dot : dots)
			dot.clear();	
		for (auto& line : lines)
			line.clear();
		s_spiral_num = 2; break;

	case '3': 
		for (auto& dot : dots)
			dot.clear();
		for (auto& line : lines)
			line.clear(); 
		s_spiral_num = 3; break;

	case '4': 
		for (auto& dot : dots)
			dot.clear();
		for (auto& line : lines)
			line.clear(); 
		s_spiral_num = 4; break;

	case '5': 
		for (auto& dot : dots)
			dot.clear();
		for (auto& line : lines)
			line.clear(); 
		s_spiral_num = 5; break;
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
		for (auto& dot : dots)
			dot.clear();
		for (auto& line : lines)
			line.clear();
		if (s_TimerAlive == false)
			glutTimerFunc(10, TimerFunction, 1);
		// Ŭ���� ��ġ�� �߽����� ����
		centerX = (float)(m_x - 400) / 400;
		centerY = (float)(300 - m_y) / 300;

		isMouseClick = true;
		s_TimerAlive = true;
		bg_r = dist_r(eng);
		bg_g = dist_g(eng);
		bg_b = dist_b(eng);

		currentPointIndex = 0;
		currentPointIndex2 = 0;
		draw_sp = 0;
		numPoints = 100 * s_spiral_num;

		if (s_spiral_num == 1) {
			radius = 0.005f;
			angle1 = 1.2f;
			angle2 = -1.7f;
		}
		if (s_spiral_num == 2) {
			radius = 0.005f;
			angle1 = 2.6f;
			angle2 = -0.6f;
		}
		if (s_spiral_num == 3) {
			radius = 0.005f;
			angle1 = 3.9f;
			angle2 = 0.7f;
		}
		if (s_spiral_num == 4) {
			radius = 0.005f;
			angle1 = 5.1f;
			angle2 = 2.1f;
		}
		if (s_spiral_num == 5) {
			radius = 0.005f;
			angle1 = 6.5f;
			angle2 = 3.3f;
		}
	
	}
}

void TimerFunction(int value)
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (s_draw_method == 0)
	{
		glBegin(GL_POINTS);
		if (s_spiral_num == 1) {
 			DrawSpiralDot1();
		}
		if (s_spiral_num == 2) {
			DrawSpiralDot2();
		}
		if (s_spiral_num == 3) {
			DrawSpiralDot3();
		}
		if (s_spiral_num == 4) {
			DrawSpiralDot4();
		}
		if (s_spiral_num == 5) {
			DrawSpiralDot5();
		}
	}
	else if (s_draw_method == 1)
	{
		if (s_spiral_num == 1) {
			DrawSpiralLine1();
		}
		if (s_spiral_num == 2) {
			DrawSpiralLine2();
		}
		if (s_spiral_num == 3) {
			DrawSpiralLine3();
		}
		if (s_spiral_num == 4) {
			DrawSpiralLine4();
		}
		if (s_spiral_num == 5) {
			DrawSpiralLine5();
		}
	}
	drawScene();
	glutPostRedisplay(); // ȭ�� �� ���


	if (s_TimerAlive)
		glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}


GLvoid drawScene()
{

	//--- ����� ���� ����
	glClearColor(bg_r, bg_g, bg_b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- ������ ���������ο� ���̴� �ҷ�����
	glUseProgram(shaderProgramID);
	
	glLineWidth(1.0f); // Set the line width as needed

	
	if (s_draw_method == 0) {
		for (auto& dot : dots[s_spiral_num - 1])
		{
			glPointSize(3.0f);
			glBegin(GL_POINTS);
			glColor3d(0, 0, 0);
			glVertex2f(dot.d_x, dot.d_y);
			
		}
		glEnd();
	}
	else if (s_draw_method == 1) {
		//DrawSpiralLine();
		if (s_spiral_num == 1) {
			for (auto& line : lines[s_spiral_num - 1])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x, line.l_y);
				glVertex2f(line.l_x1, line.l_y1);


			}
			glEnd();

			for (auto& line : lines[s_spiral_num])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x2, line.l_y2);
				glVertex2f(line.l_x3, line.l_y3);


			}
			glEnd();
		}
		if (s_spiral_num == 2) {
			for (auto& line : lines[2])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x, line.l_y);
				glVertex2f(line.l_x1, line.l_y1);


			}
			glEnd();

			for (auto& line : lines[3])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x2, line.l_y2);
				glVertex2f(line.l_x3, line.l_y3);


			}
			glEnd();
		}
		if (s_spiral_num == 3) {
			for (auto& line : lines[4])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x, line.l_y);
				glVertex2f(line.l_x1, line.l_y1);


			}
			glEnd();

			for (auto& line : lines[5])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x2, line.l_y2);
				glVertex2f(line.l_x3, line.l_y3);


			}
			glEnd();
		}
		if (s_spiral_num == 4) {
			for (auto& line : lines[6])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x, line.l_y);
				glVertex2f(line.l_x1, line.l_y1);


			}
			glEnd();

			for (auto& line : lines[7])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x2, line.l_y2);
				glVertex2f(line.l_x3, line.l_y3);


			}
			glEnd();
		}
		if (s_spiral_num == 5) {
			for (auto& line : lines[8])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x, line.l_y);
				glVertex2f(line.l_x1, line.l_y1);


			}
			glEnd();

			for (auto& line : lines[9])
			{


				glBegin(GL_LINE_STRIP);
				glColor3d(0, 0, 0);
				glVertex2f(line.l_x2, line.l_y2);
				glVertex2f(line.l_x3, line.l_y3);


			}
			glEnd();
		}
		
	}



	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void make_fragmentShaders()
{
	fragmentSource = filetobuf("fragment.glsl");
	//--- �����׸�Ʈ ���̴� ��ü �����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentSource, 0);
	//--- �����׸�Ʈ ���̴� ������
	glCompileShader(fragmentShader);
	//--- �������� ����� ���� ���� ���: ������ ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cout << "ERROR: fragment shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}

void make_shaderProgram()
{
	make_vertexShaders(); //--- ���ؽ� ���̴� �����
	make_fragmentShaders();
	//-- shader Program
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShader);
	glAttachShader(shaderProgramID, fragmentShader);
	glLinkProgram(shaderProgramID);
	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//--- Shader Program ����ϱ�
	glUseProgram(shaderProgramID);
}

void make_vertexShaders()
{
	vertexSource = filetobuf("vertex.glsl");
	//--- ���ؽ� ���̴� ��ü �����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//--- ���̴� �ڵ带 ���̴� ��ü�� �ֱ�
	glShaderSource(vertexShader, 1, (const GLchar**)&vertexSource, 0);
	//--- ���ؽ� ���̴� �������ϱ�
	glCompileShader(vertexShader);
	//--- �������� ����� ���� ���� ���: ���� üũ
	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cout << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
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

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{

	bg_r = dist_r(eng);
	bg_g = dist_g(eng);
	bg_b = dist_b(eng);
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Example1");
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;

	glewInit();
	make_shaderProgram();


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);

	glutMainLoop();
}
