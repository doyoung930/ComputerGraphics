#define _CRT_SECURE_NO_WARNINGS //--- 프로그램 맨 앞에 선언할 것
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
// 필요한 헤더 include 따로 추가하셔야 합니다~

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

//--- 메인 함수
GLuint vao, vbo[2];
GLuint DotPosVbo[10], DotColorVbo[10];
GLuint LinePosVbo[10], LineColorVbo[10];
GLuint TriPosVbo[10], TriColorVbo[10];
GLuint EilPosVbo[10], EilColorVbo[10];
GLuint EilPosVbo2[10], EilColorVbo2[10];

GLchar* vertexSource, * fragmentSource; //--- 소스코드 저장 변수
GLuint vertexShader, fragmentShader; //--- 세이더 객체
GLuint shaderProgramID; //--- 셰이더 프로그램


// 도형 모양, 초기값 점
int shape = 1; // 1점 2선 3삼각형 4사각형

// 저장할 곳
struct dot {
	GLfloat dotpos[3];
	GLfloat d_x, d_y, d_z;
	GLclampf r, g, b;
	bool select = false;
};

struct line {
	GLfloat linepos[2][3];
	GLfloat l_x1, l_y1, l_z1;
	GLfloat l_x2, l_y2, l_z2;
	GLclampf r, g, b;
	bool select = false;
};

struct tri {
	GLfloat tripos[3][3];
	GLfloat	t_x1, t_y1, t_z1;
	GLfloat t_x2, t_y2, t_z2;
	GLfloat t_x3, t_y3, t_z3;
	GLclampf r, g, b;
	bool select = false;
};

struct eil {
	GLfloat eilpos[6][3];

	GLfloat racpos[4][3];


	GLfloat e_x1, e_y1, e_z1;
	GLfloat e_x2, e_y2, e_z2;
	GLfloat e_x3, e_y3, e_z3;
	GLfloat e_x4, e_y4, e_z4;
	GLfloat e_x5, e_y5, e_z5;
	GLfloat e_x6, e_y6, e_z6;
	GLclampf r, g, b;
	bool select = false;
};

// 점
vector<dot> dots;
// 선
vector<line> lines;
// 삼각형
vector<tri> tris;
// 사각형
vector<eil> eils;

void make_shaderProgram();
void make_vertexShaders();
void make_fragmentShaders();
GLvoid drawScene();
GLvoid Reshape(int w, int h);

void InitBuffer();
char* filetobuf(const char*);

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
		shape = 1;
		break;
	case 'l':
		shape = 2;
		break;
	case 't':
		shape = 3;
		break;
	case 'r':
		shape = 4;
		break;
	case 'w':
		for (int i = 0; i < dots.size(); i++)
		{
			dots[i].dotpos[1] += 0.01;
		}
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i].linepos[0][1] += 0.01;
			lines[i].linepos[1][1] += 0.01;
			
		}
		for (int i = 0; i < tris.size(); i++)
		{
			tris[i].tripos[0][1] += 0.01;
			tris[i].tripos[1][1] += 0.01;
			tris[i].tripos[2][1] += 0.01;
		}
		for (int i = 0; i < eils.size(); i++)
		{
			eils[i].e_y1 += 0.01;
			eils[i].e_y2 += 0.01;
			eils[i].e_y3 += 0.01;
			eils[i].e_y4 += 0.01;
			eils[i].e_y5 += 0.01;
			eils[i].e_y6 += 0.01;
		}
		break;
	case 'a':
		for (int i = 0; i < dots.size(); i++)
		{
			dots[i].dotpos[0] -= 0.01;
		}
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i].linepos[0][0] -= 0.01;
			lines[i].linepos[1][0] -= 0.01;

		}
		for (int i = 0; i < tris.size(); i++)
		{
			tris[i].tripos[0][0] -= 0.01;
			tris[i].tripos[1][0] -= 0.01;
			tris[i].tripos[2][0] -= 0.01;
		}for (int i = 0; i < eils.size(); i++)
		{
			eils[i].e_x1 -= 0.01;
			eils[i].e_x2 -= 0.01;
			eils[i].e_x3 -= 0.01;
			eils[i].e_x4 -= 0.01;
			eils[i].e_x5 -= 0.01;
			eils[i].e_x6 -= 0.01;
		}
		break;
	case 's':
		for (int i = 0; i < dots.size(); i++)
		{
			dots[i].dotpos[1] -= 0.01;
		}
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i].linepos[0][1] -= 0.01;
			lines[i].linepos[1][1] -= 0.01;

		}
		for (int i = 0; i < tris.size(); i++)
		{
			tris[i].tripos[0][1] -= 0.01;
			tris[i].tripos[1][1] -= 0.01;
			tris[i].tripos[2][1] -= 0.01;
		}
		for (int i = 0; i < eils.size(); i++)
		{
			eils[i].e_y1 -= 0.01;
			eils[i].e_y2 -= 0.01;
			eils[i].e_y3 -= 0.01;
			eils[i].e_y4 -= 0.01;
			eils[i].e_y5 -= 0.01;
			eils[i].e_y6 -= 0.01;
		}
		break;
	case 'd':
		for (int i = 0; i < dots.size(); i++)
		{
			dots[i].dotpos[0] += 0.01;
		}
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i].linepos[0][0] += 0.01;
			lines[i].linepos[1][0] += 0.01;

		}
		for (int i = 0; i < tris.size(); i++)
		{
			tris[i].tripos[0][0] += 0.01;
			tris[i].tripos[1][0] += 0.01;
			tris[i].tripos[2][0] += 0.01;
		}
		for (int i = 0; i < eils.size(); i++)
		{
			eils[i].e_x1 += 0.01;
			eils[i].e_x2 += 0.01;
			eils[i].e_x3 += 0.01;
			eils[i].e_x4 += 0.01;
			eils[i].e_x5 += 0.01;
			eils[i].e_x6 += 0.01;
		}
		break;
	case 'c':
		dots.clear();
		lines.clear();
		tris.clear();
		eils.clear();
		break;
	}
	glutPostRedisplay();
}


void Mouse(int button, int state, int m_x, int m_y)
{
	float tempx;
	float tempy;
	tempx =((float)m_x - 400) / 400;
 	tempy = (300 - (float)m_y) / 300;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (dots.size() + lines.size() + tris.size() + eils.size() <10))
	{
		// m_x를 기준으로 도형그리기
		if (shape == 1) {
			dot Dot;
			Dot.d_x =tempx;
			Dot.d_y =tempy;
			Dot.d_z = 0.0f;


			Dot.dotpos[0] =Dot.d_x;
			Dot.dotpos[1] =Dot.d_y;
			Dot.dotpos[2] =Dot.d_z;

			Dot.r = 0.0;
			Dot.g = 1.0;
			Dot.b = 1.0;
			Dot.select = true;
			dots.push_back(Dot);
		}
		else if (shape == 2) {
			line Line;
			Line.l_x1 = tempx;
			Line.l_y1 = tempy;
			Line.l_z1 = 0.0f;
			
			Line.l_x2 =tempx + 0.3;
			Line.l_y2 =tempy + 0.3;
			Line.l_z2 = 0.0f;
			
			Line.linepos[0][0] = Line.l_x1;
			Line.linepos[0][1] = Line.l_y1;
			Line.linepos[0][2] = Line.l_z1;
			Line.linepos[1][0] = Line.l_x2;
			Line.linepos[1][1] = Line.l_y2;
			Line.linepos[1][2] = Line.l_z2;

			Line.r = 0.0;
			Line.g = 1.0;
			Line.b = 1.0;

			Line.select = true;

			lines.push_back(Line);
		}
		else if (shape == 3) {

			tri Tri;
			Tri.t_x1 =tempx;
			Tri.t_y1 =tempy;
			Tri.t_z1 = 0.0f;

			Tri.t_x2 = tempx - 0.1;
			Tri.t_y2 = tempy - 0.1;
			Tri.t_z2 = 0.0f;

			Tri.t_x3 =tempx + 0.1;
			Tri.t_y3 =tempy - 0.1;
			Tri.t_z3 = 0.0f;

			Tri.tripos[0][0] = tempx;
			Tri.tripos[0][1] = tempy;
			Tri.tripos[0][2] =  0.0f;
			Tri.tripos[1][0] =  tempx - 0.1;
			Tri.tripos[1][1] =  tempy - 0.1;
			Tri.tripos[1][2] =  0.0f;
			Tri.tripos[2][0] = tempx + 0.1;
			Tri.tripos[2][1] = tempy - 0.1;
			Tri.tripos[2][2] =  0.0f;

			Tri.r = 0.0;
			Tri.g = 1.0;
			Tri.b = 1.0;

			Tri.select = true;

			tris.push_back(Tri);

		}
		else if (shape == 4) {
			eil Eil;
			Eil.e_x1 = tempx;
			Eil.e_y1 = tempy;
			Eil.e_z1 = 0.0;

			Eil.e_x2 = tempx+0.1;
			Eil.e_y2 = tempy;
			Eil.e_z2 = 0.0;

			Eil.e_x3 = tempx;
			Eil.e_y3 = tempy-0.1;
			Eil.e_z3 = 0.0;

			Eil.e_x4 = tempx + 0.1;
			Eil.e_y4 = tempy - 0.1;
			Eil.e_z4 = 0.0;

			Eil.e_x5 = tempx + 0.1;
			Eil.e_y5 = tempy;
			Eil.e_z5 = 0.0;

			Eil.e_x6 = tempx;
			Eil.e_y6 = tempy - 0.1;
			Eil.e_z6 = 0.0;

			Eil.eilpos[0][0] = Eil.e_x1;
			Eil.eilpos[0][1] = Eil.e_y1;
			Eil.eilpos[0][2] = Eil.e_z1;

			Eil.eilpos[1][0] = Eil.e_x2;
			Eil.eilpos[1][1] = Eil.e_y2;
			Eil.eilpos[1][2] = Eil.e_z2;

			Eil.eilpos[2][0] = Eil.e_x3;
			Eil.eilpos[2][1] = Eil.e_y3;
			Eil.eilpos[2][2] = Eil.e_z3;

			Eil.eilpos[3][0] = Eil.e_x4;
			Eil.eilpos[3][1] = Eil.e_y4;
			Eil.eilpos[3][2] = Eil.e_z4;

			Eil.eilpos[4][0] = Eil.e_x5;
			Eil.eilpos[4][1] = Eil.e_y5;
			Eil.eilpos[4][2] = Eil.e_z5;

			Eil.eilpos[5][0] = Eil.e_x6;
			Eil.eilpos[5][1] = Eil.e_y6;
			Eil.eilpos[5][2] = Eil.e_z6;
			///rac
			Eil.racpos[0][0] = Eil.e_x1;
			Eil.racpos[0][1] = Eil.e_y1;
			Eil.racpos[0][2] = Eil.e_z1;

			Eil.racpos[1][0] = Eil.e_x2;
			Eil.racpos[1][1] = Eil.e_y2;
			Eil.racpos[1][2] = Eil.e_z2;

			Eil.racpos[2][0] = Eil.e_x3;
			Eil.racpos[2][1] = Eil.e_y3;
			Eil.racpos[2][2] = Eil.e_z3;

			Eil.racpos[3][0] = Eil.e_x4;
			Eil.racpos[3][1] = Eil.e_y4;
			Eil.racpos[3][2] = Eil.e_z4;

			Eil.r = 0.0;
			Eil.g = 1.0;
			Eil.b = 1.0;
			Eil.select = true;

			eils.push_back(Eil);
		}
	}
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
	glewInit();
	make_shaderProgram();


	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);

	glutMainLoop();
}

GLvoid drawScene()
{

	//--- 변경된 배경색 설정
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//--- 렌더링 파이프라인에 세이더 불러오기
	glUseProgram(shaderProgramID);

	for (int i = 0; i < dots.size(); i++)
	{
		
		const GLfloat dotpos[3] = { //--- 삼각형 위치 값
		dots[i].d_x, dots[i].d_y, 0.0 };
		const GLfloat dotcolor[3] = { //--- 삼각형 꼭지점 색상
		1.0, 0.0, 1.0 };
		glGenBuffers(1, &DotPosVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, DotPosVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(dots[i].dotpos) * dots.size(), dots[i].dotpos, GL_STATIC_DRAW);
		glGenBuffers(1, &DotColorVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, DotColorVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(dotcolor) * dots.size(), dotcolor, GL_STATIC_DRAW);

		// Location 번호 저장
		int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
		int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

		glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
		glEnableVertexAttribArray(ColorLocation);

		{
			glBindBuffer(GL_ARRAY_BUFFER, DotPosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		{
			glBindBuffer(GL_ARRAY_BUFFER, DotColorVbo[i]); // VBO Bind
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		glPointSize(5.0);
		glDrawArrays(GL_POINTS, 0, 1); // 설정대로 출력
		glDisableVertexAttribArray(PosLocation);	// Disable 필수!
		glDisableVertexAttribArray(ColorLocation);
		
	}
	for (int i = 0; i < lines.size(); i++)
	{
		const GLfloat linepos[2][3] = { //--- 삼각형 위치 값
		{lines[i].l_x1, lines[i].l_y1, 0.0},
		{lines[i].l_x2, lines[i].l_y2, 0.0} };
		const GLfloat linecolor[2][3] = { //--- 삼각형 꼭지점 색상
		{ lines[i].r, lines[i].g,lines[i].b}, {1.0, 0.0, 1.0} };
		glGenBuffers(1, &LinePosVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, LinePosVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lines[i].linepos) * lines.size(), lines[i].linepos, GL_STATIC_DRAW);
		glGenBuffers(1, &LineColorVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, LineColorVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(linecolor) * lines.size(), linecolor, GL_STATIC_DRAW);

		// Location 번호 저장
		int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
		int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

		glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
		glEnableVertexAttribArray(ColorLocation);

		{
			glBindBuffer(GL_ARRAY_BUFFER, LinePosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		{
			glBindBuffer(GL_ARRAY_BUFFER, LineColorVbo[i]); // VBO Bind
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		glLineWidth(3);
		glDrawArrays(GL_LINES, 0, 2); // 설정대로 출력
		glDisableVertexAttribArray(PosLocation);	// Disable 필수!
		glDisableVertexAttribArray(ColorLocation);
	}
	for (int i = 0; i < tris.size(); i++)
	{


		const GLfloat tripos[3][3] = { //--- 삼각형 위치 값
		{tris[i].t_x1, tris[i].t_y1, 0.0},
		{tris[i].t_x2, tris[i].t_y2, 0.0},
		{tris[i].t_x3, tris[i].t_y3, 0.0} };
		const GLfloat tricolor[3][3] = { //--- 삼각형 꼭지점 색상
		{ tris[i].r, tris[i].g,tris[i].b}, {1.0, 0.0, 1.0}, {1.0, 0.0, 1.0}};
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
	for (int i = 0; i < eils.size(); i++) {
		const GLfloat eilpos1[3][3] = { //--- 삼각형 위치 값
		{eils[i].e_x1, eils[i].e_y1, 0.0},
		{eils[i].e_x2, eils[i].e_y2, 0.0},
		{eils[i].e_x3, eils[i].e_y3, 0.0} };
		const GLfloat eilpos2[3][3] = {
		{eils[i].e_x4, eils[i].e_y4, 0.0},
		{eils[i].e_x5, eils[i].e_y5, 0.0},
		{eils[i].e_x6, eils[i].e_y6, 0.0} };

		const GLfloat eilcolor[3][3] = { //--- 삼각형 꼭지점 색상
		{ eils[i].r, eils[i].g,eils[i].b}, {1.0, 0.0, 1.0}, {1.0, 0.0, 1.0} };


		glGenBuffers(1, &EilPosVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, EilPosVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(eilpos1)* eils.size(), eilpos1, GL_STATIC_DRAW);
		glGenBuffers(1, &EilColorVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, EilColorVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(eilcolor)* eils.size(), eilcolor, GL_STATIC_DRAW);

		// Location 번호 저장
		int PosLocation = glGetAttribLocation(shaderProgramID, "in_Position"); //	: 0  Shader의 'layout (location = 0)' 부분
		int ColorLocation = glGetAttribLocation(shaderProgramID, "in_Color"); //	: 1

		glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
		glEnableVertexAttribArray(ColorLocation);

		{
			glBindBuffer(GL_ARRAY_BUFFER, EilPosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		{
			glBindBuffer(GL_ARRAY_BUFFER, EilColorVbo[i]); // VBO Bind
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		glDrawArrays(GL_TRIANGLES, 0, 3); // 설정대로 출력

		glGenBuffers(1, &EilPosVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, EilPosVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(eilpos1)* eils.size(), eilpos2, GL_STATIC_DRAW);
		glGenBuffers(1, &EilColorVbo[i]);
		glBindBuffer(GL_ARRAY_BUFFER, EilColorVbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(eilcolor)* eils.size(), eilcolor, GL_STATIC_DRAW);


		glEnableVertexAttribArray(PosLocation); // Enable 필수! 사용하겠단 의미
		glEnableVertexAttribArray(ColorLocation);

		{
			glBindBuffer(GL_ARRAY_BUFFER, EilPosVbo[i]); // VBO Bind
			glVertexAttribPointer(PosLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		{
			glBindBuffer(GL_ARRAY_BUFFER, EilColorVbo[i]); // VBO Bind
			glVertexAttribPointer(ColorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		glDrawArrays(GL_TRIANGLES, 0, 3); // 설정대로 출력
		glDisableVertexAttribArray(PosLocation);	// Disable 필수!
		glDisableVertexAttribArray(ColorLocation);



	}
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