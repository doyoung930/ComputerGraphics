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
uniform_real_distribution<double> dist_x(-1.0f, 0.95f);
uniform_real_distribution<double> dist_y(-1.0f, 0.95f);
int selectedRectangle = -1; // 선택한 사각형의 인덱스
bool isDragging = false; // 드래그 중인지 여부
GLfloat xOffset, yOffset; // 드래그 시작 시 마우스 클릭 지점과 사각형의 좌측 상단 꼭지점 간의 오프셋

struct Rect {
	GLfloat base_x1, base_y1, base_x2, base_y2;
	GLfloat x1, y1, x2, y2; // 왼쪽 아래와 오른쪽 위 꼭지점 좌표
	GLclampf r, g, b; // 색상
	bool selected = false; // 선택 여부
	GLfloat dx = 0.01f, dy = 0.01f; // 움직임 정보 추가
};

vector<Rect> rects;

GLfloat r = 0.3f, g = 0.3f, b = 0.3f;

bool IsTimerAlive = true;

int maxRectangles = 5;

//// bool 판단 변수
bool a_moveRect = false; // 사각형들의 이동 상태를 나타내는 변수
bool i_key = false;
bool c_key = false;
bool o_key = false;



GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
GLfloat tempx1, tempx2, tempy1, tempy2;

void updateRectangles() {
	static bool reverseDirection = false;

	if (a_moveRect) {
		for (Rect& rect : rects) {
			if (!rect.selected) {
				/*if (reverseDirection) {
					rect.dx = -0.01f;
					rect.dy = -0.01f;
				}
				else {
					rect.dx = 0.01f;
					rect.dy = 0.01f;
				}*/

				// 벽과의 충돌 검사
				if (rect.x1 + rect.dx < -1.0f) {
					// 왼쪽 벽과 충돌한 경우
					rect.dx = fabs(rect.dx); // 반사벡터 설정
				}
				else if (rect.x2 + rect.dx > 1.0f) {
					// 오른쪽 벽과 충돌한 경우
					rect.dx = -fabs(rect.dx); // 반사벡터 설정
				}

				if (rect.y2 + rect.dy < -1.0f) {
					// 아래 벽과 충돌한 경우
					rect.dy = fabs(rect.dy); // 반사벡터 설정
				}
				else if (rect.y1 + rect.dy > 1.0f) {
					// 위 벽과 충돌한 경우
					rect.dy = -fabs(rect.dy); // 반사벡터 설정
				}

				rect.x1 += rect.dx;
				rect.x2 += rect.dx;
				rect.y1 += rect.dy;
				rect.y2 += rect.dy;
			}
		}
	}
}


void updateRectangles2() {
	static bool reverseDirection = false;

	if (i_key) {
		for (Rect& rect : rects) {
			if (!rect.selected) {

				// 벽과의 충돌 검사
				if (rect.x1 + rect.dx < -1.0f) {
					// 왼쪽 벽과 충돌한 경우
					rect.dx = fabs(rect.dx); // 반사벡터 설정
				}
				else if (rect.x2 + rect.dx > 1.0f) {
					// 오른쪽 벽과 충돌한 경우
					rect.dx = -fabs(rect.dx); // 반사벡터 설정
				}

				rect.x1 += rect.dx;
				rect.x2 += rect.dx;
			}
		}
	}
}

// 타이머
void TimerFunction(int value)
{
	if(	a_moveRect)
		updateRectangles();
	else if (i_key)
	{
		updateRectangles2();
	}

	if (c_key)
	{
		for (auto& rect : rects) {
			rect.x1 = (GLclampf)dist(eng);
			rect.y1 = (GLclampf)dist(eng);
		}
	}

	if (o_key)
	{
		for (auto& rect : rects) {
			rect.r = (GLclampf)dist(eng);
			rect.g = (GLclampf)dist(eng);
			rect.b = (GLclampf)dist(eng);
		}
	}
	glutPostRedisplay(); // 화면 재 출력
	if (IsTimerAlive)
		glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void addRectangle_mouse(int m_x, int m_y)
{

	if (rects.size() < maxRectangles) {
		Rect rect;
		rect.x1 = (float)(m_x - 400) / 400 - 0.05f;
		rect.y1 = (float)(300 - m_y) / 300 + 0.05f;
		rect.x2 = rect.x1 + 0.1f;
		rect.y2 = rect.y1 - 0.1f;

		rect.base_x1 = rect.x1;
		rect.base_x2 = rect.x2;
		rect.base_y1 = rect.y1;
		rect.base_y2 = rect.y2;

		rect.r = (GLclampf)dist(eng);
		rect.g = (GLclampf)dist(eng);
		rect.b = (GLclampf)dist(eng);

		rects.push_back(rect);
	}
}


void drawRectangles() {
	for (const Rect& rect : rects) {
		glColor3f(rect.r, rect.g, rect.b);
		glBegin(GL_QUADS);
		glVertex2f(rect.x1, rect.y1);
		glVertex2f(rect.x2, rect.y1);
		glVertex2f(rect.x2, rect.y2);
		glVertex2f(rect.x1, rect.y2);
		glEnd();
	}
}

// 키보드
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		i_key = false;
		if (a_moveRect == false) {
			a_moveRect = true;
			glutTimerFunc(100, TimerFunction, 1);
			IsTimerAlive = true;
		}
		else
		{
			a_moveRect = false;
			glutTimerFunc(100, TimerFunction, 1);

		}
		break;
	case 'i':
		a_moveRect = false;
		if (i_key == false) {
			i_key = true;
			glutTimerFunc(100, TimerFunction, 1);
			IsTimerAlive = true;
		}
		else
		{
			i_key = false;
			glutTimerFunc(100, TimerFunction, 1);

		}
		break;
	case 'c':
		if (c_key == false) {
			c_key = true;
			glutTimerFunc(100, TimerFunction, 1);
			IsTimerAlive = true;
		}
		else
		{
			c_key = false;
			glutTimerFunc(100, TimerFunction, 1);

		}
		break;
	case 'o':
		if (o_key == false) {
			o_key = true;
			glutTimerFunc(100, TimerFunction, 1);
			IsTimerAlive = true;
		}
		else
		{
			o_key = false;
			glutTimerFunc(100, TimerFunction, 1);
			
		}
		break;
	case 's':
		IsTimerAlive = false;
		a_moveRect = false;
		o_key = false;
		c_key = false;
		i_key = false;
		break;
	case 'm':
		for (auto& rect : rects) {
			rect.x1 = rect.base_x1;
			rect.y1 = rect.base_y1;
			rect.x2 = rect.base_x2;
			rect.y2 = rect.base_y2;
		}
		break;
	case 'r':
		rects.clear();
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

//마우스
void Mouse(int button, int state, int m_x, int m_y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		addRectangle_mouse(m_x, m_y);
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

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "“Unable to initialize GLEW”" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);

	glutMainLoop(); // 이벤트 처리 시작 
}