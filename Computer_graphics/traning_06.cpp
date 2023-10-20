#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#include "vec2.h"

#include <iostream>
#include <random>

using namespace std;

random_device seeder;
const auto seed = seeder.entropy() ? seeder() : time(nullptr);
mt19937 eng(static_cast<mt19937::result_type>(seed));
uniform_real_distribution<double> dist(0.0f, 1.0f);
uniform_real_distribution<double> dist_x(-0.6f, 0.6f);
uniform_real_distribution<double> dist_y(-0.7f,  1.0f);

random_device rd;
mt19937 gen(rd());  // 난수 생성 엔진을 초기화합니다.
uniform_int_distribution<int> distribution(1, 100);  // 1부터 3 사이의 균일한 분포를 생성합니다.

GLfloat tempx1, tempx2, tempy1, tempy2;


bool set_move = false;

int select_number = -1;

struct Rect {
	GLfloat x1, y1, x2, y2; // 왼쪽 아래와 오른쪽 위 꼭지점 좌표
	GLclampf r, g, b; // 색상
	bool selected = false; // 선택 여부
	int num;
	bool ooo = false;

	GLfloat s1_x1;
	GLfloat s1_x2;
	GLfloat s1_y1;
	GLfloat s1_y2;


	GLfloat s2_x1;
	GLfloat s2_x2;
	GLfloat s2_y1;
	GLfloat s2_y2;

	GLfloat s3_x1;
	GLfloat s3_x2;
	GLfloat s3_y1;
	GLfloat s3_y2;

	GLfloat s4_x1;
	GLfloat s4_x2;
	GLfloat s4_y1;
	GLfloat s4_y2;

	GLfloat s5_x1;
	GLfloat s5_x2;
	GLfloat s5_y1;
	GLfloat s5_y2;


	GLfloat s6_x1;
	GLfloat s6_x2;
	GLfloat s6_y1;
	GLfloat s6_y2;

	GLfloat s7_x1;
	GLfloat s7_x2;
	GLfloat s7_y1;
	GLfloat s7_y2;

	GLfloat s8_x1;
	GLfloat s8_x2;
	GLfloat s8_y1;
	GLfloat s8_y2;

};

vector<Rect> rects;

GLfloat r = 0.3f, g = 0.3f, b = 0.3f;

bool IsTimerAlive = true;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);


// 타이머
void TimerFunction(int value)
{

	for (auto& rect : rects) {
		if(rect.selected == true)
		{
			if (rect.num == 0) {

				

				rect.s1_x1 -= 0.017f;
				rect.s1_x2 -= 0.02f;
				rect.s1_y1 += 0.001;
				rect.s1_y2 -= 0.001;

				rect.s2_x1-= 0.001;
				rect.s2_x2+= 0.001;
				rect.s2_y1 -= 0.012f;
				rect.s2_y2 -= 0.015f;
				
				rect.s3_x1+= 0.001;
				rect.s3_x2-= 0.001;
				rect.s3_y1 += 0.012f;
				rect.s3_y2 += 0.015f;
				
				rect.s4_x1 += 0.017f;
				rect.s4_x2 += 0.02f;
				rect.s4_y1-= 0.001;
				rect.s4_y2+= 0.001;

				if (rect.s4_x1 - rect.s4_x2 <= 0)
				{
					rect.selected = false;
					rect.x1	= 10000.f;
					rect.x2	= 10000.f;
					rect.y1	= 10000.f;
					rect.y2	= 10000.f;
				
				}
				if (rect.s4_y2 - rect.s4_y1  >= 0)
				{
					rect.selected = false;
					rect.x1 = 10000.f;
					rect.x2 = 10000.f;
					rect.y1 = 10000.f;
					rect.y2 = 10000.f;
				}
			}
			if (rect.num == 1) {
				rect.s1_x1 -= 0.01f;
				rect.s1_x2 -= 0.012f;
				rect.s1_y1-= 0.01f;
				rect.s1_y2-= 0.012f;

				rect.s2_x1+= 0.01f;
				rect.s2_x2+= 0.012f;
				rect.s2_y1 -= 0.01f;
				rect.s2_y2 -= 0.012f;
				
				rect.s3_x1-= 0.01f;
				rect.s3_x2-= 0.012f;
				rect.s3_y1 += 0.01f;
				rect.s3_y2 += 0.012f;
				
				rect.s4_x1 += 0.01f;
				rect.s4_x2 += 0.012f;
				rect.s4_y1+= 0.01f;
				rect.s4_y2+= 0.012f;
				if (rect.s4_x1 - rect.s4_x2 <= 0)
				{
					rect.selected = false;
					rect.x1 = 10000.f;
					rect.x2 = 10000.f;
					rect.y1 = 10000.f;
					rect.y2 = 10000.f;

				}
			}
			if (rect.num == 2) {
				rect.s1_x1 -= 0.017f;
				rect.s1_x2 -= 0.02f;
				rect.s1_y1 += 0.001;
				rect.s1_y2 -= 0.001;

				rect.s2_x1 -= 0.001;
				rect.s2_x2 += 0.001;
				rect.s2_y1 -= 0.012f;
				rect.s2_y2 -= 0.015f;

				rect.s3_x1 += 0.001;
				rect.s3_x2 -= 0.001;
				rect.s3_y1 += 0.012f;
				rect.s3_y2 += 0.015f;

				rect.s4_x1 += 0.017f;
				rect.s4_x2 += 0.02f;
				rect.s4_y1 -= 0.001;
				rect.s4_y2 += 0.001;

				if (rect.s4_x1 - rect.s4_x2 <= 0)
				{
					rect.selected = false;
					rect.x1 = 10000.f;
					rect.x2 = 10000.f;
					rect.y1 = 10000.f;
					rect.y2 = 10000.f;

				}
				if (rect.s4_y2 - rect.s4_y1 >= 0)
				{
					rect.selected = false;
					rect.x1 = 10000.f;
					rect.x2 = 10000.f;
					rect.y1 = 10000.f;
					rect.y2 = 10000.f;
				}

				rect.s5_x1 -= 0.01f;
				rect.s5_x2 -= 0.012f;
				rect.s5_y1 -= 0.01f;
				rect.s5_y2 -= 0.012f;

				rect.s6_x1 += 0.01f;
				rect.s6_x2 += 0.012f;
				rect.s6_y1 -= 0.01f;
				rect.s6_y2 -= 0.012f;

				rect.s7_x1 -= 0.01f;
				rect.s7_x2 -= 0.012f;
				rect.s7_y1 += 0.01f;
				rect.s7_y2 += 0.012f;

				rect.s8_x1 += 0.01f;
				rect.s8_x2 += 0.012f;
				rect.s8_y1 += 0.01f;
				rect.s8_y2 += 0.012f;
				if (rect.s4_x1 - rect.s4_x2 <= 0)
				{
					rect.selected = false;
					rect.x1 = 10000.f;
					rect.x2 = 10000.f;
					rect.y1 = 10000.f;
					rect.y2 = 10000.f;

				}
			}
		}


	}
	glutPostRedisplay(); // 화면 재 출력
	if (IsTimerAlive)
		glutTimerFunc(50, TimerFunction, 1); // 타이머함수 재 설정
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void addRandomRectangle() {
	if (rects.size() < 5) {
		Rect rect;
		rect.x1 = (GLfloat)dist_x(eng);
		rect.y1 = (GLfloat)dist_y(eng);
		rect.x2 = rect.x1 + 0.3f;
		rect.y2 = rect.y1 - 0.3f;

		rect.r = (GLclampf)dist(eng);
		rect.g = (GLclampf)dist(eng);
		rect.b = (GLclampf)dist(eng);
		rect.selected = false;

		
		rect.num = distribution(gen)%3;
		//rect.num = 2;
		
		rects.push_back(rect);
	}
}

void drawRectangles() {
	for (const Rect& rect : rects) {

		if (rect.selected) {
			if (rect.num == 0) {
			

				// 상단 왼쪽 작은 사각형
				// (mid_x, mid_y)를 왼쪽 아래로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s3_x1, rect.s3_y1);
				glVertex2f(rect.s3_x2, rect.s3_y1);
				glVertex2f(rect.s3_x2, rect.s3_y2);
				glVertex2f(rect.s3_x1, rect.s3_y2);
				glEnd();



				// 상단 오른쪽 작은 사각형
				// (mid_x, mid_y)를 오른쪽 아래로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s4_x2, rect.s4_y1);
				glVertex2f(rect.s4_x1, rect.s4_y1);
				glVertex2f(rect.s4_x1, rect.s4_y2);
				glVertex2f(rect.s4_x2, rect.s4_y2);
				glEnd();

				// 하단 왼쪽 작은 사각형
				glColor3f(rect.r, rect.g, rect.b);
				glBegin(GL_QUADS);
				glVertex2f(rect.s1_x1, rect.s1_y2);
				glVertex2f(rect.s1_x2, rect.s1_y2);
				glVertex2f(rect.s1_x2, rect.s1_y1);
				glVertex2f(rect.s1_x1, rect.s1_y1);
				glEnd();

							

				// 하단 오른쪽 작은 사각형
				// (mid_x, mid_y)를 왼쪽 위로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s2_x2, rect.s2_y2);
				glVertex2f(rect.s2_x1, rect.s2_y2);
				glVertex2f(rect.s2_x1, rect.s2_y1);
				glVertex2f(rect.s2_x2, rect.s2_y1);
				glEnd();
				
				
				
			}
			else if (rect.num == 1) {
				// 4등분 상하좌우
				GLfloat mid_x = (rect.x1 + rect.x2) / 2.0f;
				GLfloat mid_y = (rect.y1 + rect.y2) / 2.0f;

				
				// 하단 왼쪽 작은 사각형
				glColor3f(rect.r, rect.g, rect.b);
				glBegin(GL_QUADS);
				glVertex2f(rect.s1_x1, rect.s1_y2);
				glVertex2f(rect.s1_x2, rect.s1_y2);
				glVertex2f(rect.s1_x2, rect.s1_y1);
				glVertex2f(rect.s1_x1, rect.s1_y1);
				glEnd();


				

				// 하단 오른쪽 작은 사각형
				// (mid_x, mid_y)를 왼쪽 위로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s2_x2, rect.s2_y2);
				glVertex2f(rect.s2_x1, rect.s2_y2);
				glVertex2f(rect.s2_x1, rect.s2_y1);
				glVertex2f(rect.s2_x2, rect.s2_y1);
				glEnd();

				
				// 상단 왼쪽 작은 사각형
				// (mid_x, mid_y)를 왼쪽 아래로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s3_x1, rect.s3_y1);
				glVertex2f(rect.s3_x2, rect.s3_y1);
				glVertex2f(rect.s3_x2, rect.s3_y2);
				glVertex2f(rect.s3_x1, rect.s3_y2);
				glEnd();


				
				// 상단 오른쪽 작은 사각형
				// (mid_x, mid_y)를 오른쪽 아래로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s4_x2, rect.s4_y1);
				glVertex2f(rect.s4_x1, rect.s4_y1);
				glVertex2f(rect.s4_x1, rect.s4_y2);
				glVertex2f(rect.s4_x2, rect.s4_y2);
				glEnd();
			}
			else if (rect.num == 2) {
				// 상단 왼쪽 작은 사각형
				// (mid_x, mid_y)를 왼쪽 아래로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s3_x1, rect.s3_y1);
				glVertex2f(rect.s3_x2, rect.s3_y1);
				glVertex2f(rect.s3_x2, rect.s3_y2);
				glVertex2f(rect.s3_x1, rect.s3_y2);
				glEnd();



				// 상단 오른쪽 작은 사각형
				// (mid_x, mid_y)를 오른쪽 아래로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s4_x2, rect.s4_y1);
				glVertex2f(rect.s4_x1, rect.s4_y1);
				glVertex2f(rect.s4_x1, rect.s4_y2);
				glVertex2f(rect.s4_x2, rect.s4_y2);
				glEnd();

				// 하단 왼쪽 작은 사각형
				glColor3f(rect.r, rect.g, rect.b);
				glBegin(GL_QUADS);
				glVertex2f(rect.s1_x1, rect.s1_y2);
				glVertex2f(rect.s1_x2, rect.s1_y2);
				glVertex2f(rect.s1_x2, rect.s1_y1);
				glVertex2f(rect.s1_x1, rect.s1_y1);
				glEnd();



				// 하단 오른쪽 작은 사각형
				// (mid_x, mid_y)를 왼쪽 위로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s2_x2, rect.s2_y2);
				glVertex2f(rect.s2_x1, rect.s2_y2);
				glVertex2f(rect.s2_x1, rect.s2_y1);
				glVertex2f(rect.s2_x2, rect.s2_y1);
				glEnd();

				// 4등분 상하좌우
				GLfloat mid_x = (rect.x1 + rect.x2) / 2.0f;
				GLfloat mid_y = (rect.y1 + rect.y2) / 2.0f;


				// 하단 왼쪽 작은 사각형
				glColor3f(rect.r, rect.g, rect.b);
				glBegin(GL_QUADS);
				glVertex2f(rect.s5_x1, rect.s5_y2);
				glVertex2f(rect.s5_x2, rect.s5_y2);
				glVertex2f(rect.s5_x2, rect.s5_y1);
				glVertex2f(rect.s5_x1, rect.s5_y1);
				glEnd();




				// 하단 오른쪽 작은 사각형
				// (mid_x, mid_y)를 왼쪽 위로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s6_x2, rect.s6_y2);
				glVertex2f(rect.s6_x1, rect.s6_y2);
				glVertex2f(rect.s6_x1, rect.s6_y1);
				glVertex2f(rect.s6_x2, rect.s6_y1);
				glEnd();


				// 상단 왼쪽 작은 사각형
				// (mid_x, mid_y)를 왼쪽 아래로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s7_x1, rect.s7_y1);
				glVertex2f(rect.s7_x2, rect.s7_y1);
				glVertex2f(rect.s7_x2, rect.s7_y2);
				glVertex2f(rect.s7_x1, rect.s7_y2);
				glEnd();



				// 상단 오른쪽 작은 사각형
				// (mid_x, mid_y)를 오른쪽 아래로 설정한 작은 사각형과 같이 사용합니다.
				glBegin(GL_QUADS);
				glVertex2f(rect.s8_x2, rect.s8_y1);
				glVertex2f(rect.s8_x1, rect.s8_y1);
				glVertex2f(rect.s8_x1, rect.s8_y2);
				glVertex2f(rect.s8_x2, rect.s8_y2);
				glEnd();
			}


		}
		else {
			glColor3f(rect.r, rect.g, rect.b);
			glBegin(GL_QUADS);
			glVertex2f(rect.x1, rect.y1);
			glVertex2f(rect.x2, rect.y1);
			glVertex2f(rect.x2, rect.y2);
			glVertex2f(rect.x1, rect.y2);
			glEnd();
		}
	}
}



//마우스
void Mouse(int button, int state, int m_x, int m_y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (set_move == false) {
			set_move = true;
			glutTimerFunc(100, TimerFunction, 1);
			}
		for (int i = 4; -1 < i; --i) {
			Rect& rect = rects[i];


			if (rect.x1 < 0) {
				tempx1 = 400 + rect.x1 * 400;
			}
			else {
				tempx1 = 400 + rect.x1 * 400;
			}

			if (rect.y1 < 0) {
				tempy1 = 300 - rect.y1 * 300;
			}
			else {
				tempy1 = 300 - rect.y1 * 300;
			}

			if (rect.x2 < 0) {
				tempx2 = 400 + rect.x2 * 400;
			}
			else {
				tempx2 = 400 + rect.x2 * 400;
			}

			if (rect.y2 < 0) {
				tempy2 = 300 - rect.y2 * 300;
			}
			else {
				tempy2 = 300 - rect.y2 * 300;
			}

			if ((tempx1 < m_x && m_x < tempx2)
				&& (tempy1 < m_y && m_y < tempy2) && rect.selected == false)
			{

				rect.selected = true;
				if (rect.num == 0 || rect.num == 1) {
					// 4등분 대각선
					GLfloat mid_x = (rect.x1 + rect.x2) / 2.0f;
					GLfloat mid_y = (rect.y1 + rect.y2) / 2.0f;

					rect.s1_x1 = rect.x1;
					rect.s1_x2 = mid_x;
					rect.s1_y1 = rect.y2;
					rect.s1_y2 = mid_y;
					rect.s2_x1 = rect.x2;
					rect.s2_x2 = mid_x;
					rect.s2_y1 = rect.y2;
					rect.s2_y2 = mid_y;
					rect.s3_x1 = rect.x1;
					rect.s3_x2 = mid_x;
					rect.s3_y1 = rect.y1;
					rect.s3_y2 = mid_y;
					rect.s4_x1 = rect.x2;
					rect.s4_x2 = mid_x;
					rect.s4_y1 = rect.y1;
					rect.s4_y2 = mid_y;
				}
				else if (rect.num == 2) {
					// 4등분 대각선
					GLfloat mid_x = (rect.x1 + rect.x2) / 2.0f;
					GLfloat mid_y = (rect.y1 + rect.y2) / 2.0f;

					rect.s1_x1 = rect.x1;
					rect.s1_x2 = mid_x;
					rect.s1_y1 = rect.y2;
					rect.s1_y2 = mid_y;
					rect.s2_x1 = rect.x2;
					rect.s2_x2 = mid_x;
					rect.s2_y1 = rect.y2;
					rect.s2_y2 = mid_y;
					rect.s3_x1 = rect.x1;
					rect.s3_x2 = mid_x;
					rect.s3_y1 = rect.y1;
					rect.s3_y2 = mid_y;
					rect.s4_x1 = rect.x2;
					rect.s4_x2 = mid_x;
					rect.s4_y1 = rect.y1;
					rect.s4_y2 = mid_y;

					rect.s5_x1 = rect.x1;
					rect.s5_x2 = mid_x;
					rect.s5_y1 = rect.y2;
					rect.s5_y2 = mid_y;
					rect.s6_x1 = rect.x2;
					rect.s6_x2 = mid_x;
					rect.s6_y1 = rect.y2;
					rect.s6_y2 = mid_y;
					rect.s7_x1 = rect.x1;
					rect.s7_x2 = mid_x;
					rect.s7_y1 = rect.y1;
					rect.s7_y2 = mid_y;
					rect.s8_x1 = rect.x2;
					rect.s8_x2 = mid_x;
					rect.s8_y1 = rect.y1;
					rect.s8_y2 = mid_y;

				}
				break;
			}
		}

	}
}


GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수 
{
	glClearColor(r, g, b, 1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.

	drawRectangles();

	glutSwapBuffers(); // 화면에 출력하기
}
void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(100, 30); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Doyoung"); // 윈도우 생성(윈도우 이름)

	for(int i= 0 ; i <5 ; i++)
		addRandomRectangle();

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "“Unable to initialize GLEW”" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		//std::cout << "GLEW Initialized\n";
		glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);


	glutMainLoop(); // 이벤트 처리 시작 
}