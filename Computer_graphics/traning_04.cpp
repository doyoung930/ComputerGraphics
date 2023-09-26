#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <C:\Computer_graphics\Computer_graphics\glfw/glfw3.h>

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

};

vector<Rect> rects;

GLfloat r = 0.3f, g = 0.3f, b = 0.3f;

bool IsTimerAlive = true;

int maxRectangles = 5;
bool a_moveRect = false; // 사각형들의 이동 상태를 나타내는 변수

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
GLfloat tempx1, tempx2, tempy1, tempy2;


void updateRectangles()
{
	static bool reverseDirection = false;

	if (a_moveRect) {
		for (Rect& rect : rects) {
			if (!rect.selected) {
				GLfloat dx = 0.01f;
				GLfloat dy = 0.01f;

				if (reverseDirection) {
					dx = -dx;
					dy = -dy;
				}

				if (rect.x1 + dx < -1.0f || rect.x2 + dx > 1.0f) {
					reverseDirection = !reverseDirection;
					dx = -dx;
				}
				if (rect.y1 + dy < -1.0f || rect.y2 + dy > 1.0f) {
					reverseDirection = !reverseDirection;
					dy = -dy;
				}

				rect.x1 += dx;
				rect.x2 += dx;
				rect.y1 += dy;
				rect.y2 += dy;
			}
		}
	}
}
// 타이머
void TimerFunction(int value)
{
	updateRectangles();
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
		if (a_moveRect == false) {
			a_moveRect = true;
			glutTimerFunc(100, TimerFunction, 1);
			IsTimerAlive = true;
		}
		else
		{
			a_moveRect = false;
			glutTimerFunc(100, TimerFunction, 1);
			IsTimerAlive = false;
		}
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