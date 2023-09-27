#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>


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
	GLfloat x1, y1, x2, y2; // 왼쪽 아래와 오른쪽 위 꼭지점 좌표
	GLclampf r, g, b; // 색상
	bool live = false;
	bool selected = false; // 선택 여부

};

struct Rect_erase {
	GLfloat x1, y1, x2, y2; // 왼쪽 아래와 오른쪽 위 꼭지점 좌표
	GLclampf r, g, b; // 색상
	bool selected = false; // 선택 여부
	int num = 0;
	bool existence = false;
};

Rect_erase erase = {};

vector<Rect> rects;

GLfloat r = 0.3f, g = 0.3f, b = 0.3f;

bool IsTimerAlive = true;

#include <iostream>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
GLfloat tempx1, tempx2, tempy1, tempy2;
// 타이머
void TimerFunction(int value)
{
	//RandomRGB();
	glutPostRedisplay(); // 화면 재 출력
	if (IsTimerAlive)
		glutTimerFunc(100, TimerFunction, 1); // 타이머함수 재 설정
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

void addRandomRectangle() {
	if (rects.size() < 40) {
		Rect rect;
		rect.x1 = (GLfloat)dist_x(eng);
		rect.y1 = (GLfloat)dist_y(eng);
		rect.x2 = rect.x1 + 0.08f;
		rect.y2 = rect.y1 + 0.08f;
		rect.r = (GLclampf)dist(eng);
		rect.g = (GLclampf)dist(eng);
		rect.b = (GLclampf)dist(eng);
		rect.live = true;
		rect.selected = false;
		rects.push_back(rect);
	}
	if (erase.existence == false)
	{
		erase.r = 0.0f;
		erase.g = 0.0f;
		erase.b = 0.0f;

		
	}

}

void drawRectangles() {
	for (const Rect& rect : rects) {
		if (rect.live == true) {
			glColor3f(rect.r, rect.g, rect.b);
			glBegin(GL_QUADS);
			glVertex2f(rect.x1, rect.y1);
			glVertex2f(rect.x2, rect.y1);
			glVertex2f(rect.x2, rect.y2);
			glVertex2f(rect.x1, rect.y2);
			glEnd();
		}
	}
	if (erase.selected == true)
	{
		glColor3f(erase.r, erase.g, erase.b);
		glBegin(GL_QUADS);
		glVertex2f(erase.x1, erase.y1);
		glVertex2f(erase.x2, erase.y1);
		glVertex2f(erase.x2, erase.y2);
		glVertex2f(erase.x1, erase.y2);
		glEnd();
	}
}

// 키보드
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		break;
	}
	glutPostRedisplay();
}

//마우스
void Mouse(int button, int state, int m_x, int m_y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		tempx1 = m_x - 32 - 4 * erase.num;
		tempy1 = m_y - 32 - 4 * erase.num;
		tempx2 = m_x + 24 + 3 * erase.num;
		tempy2 = m_y + 24 + 3 * erase.num;

		erase.selected = true;

		if ((tempx1 < m_x && m_x < tempx2)
			&& (tempy1 < m_y && m_y < tempy2))
		{
			selectedRectangle = 1;
			xOffset = tempx1 - m_x;
			yOffset = tempy1 - m_y;
			isDragging = true;
		}

		erase.x1 = (tempx1 - 400) / 400;
		erase.y1 = (300 - tempy1) / 300;
		erase.x2 = (tempx2 - 400) / 400;
		erase.y2 = (300 - tempy2) / 300;
		

	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		erase.selected = false;
		isDragging = false;
		selectedRectangle = -1;
	}
}


void Motion(int x, int y)
{
	if (isDragging && selectedRectangle >= 0) {

		// 드래그 중일 때 사각형을 이동
		Rect_erase& rect = erase;

		GLfloat newX1 = x - 32 - 4 * erase.num;
		GLfloat newY1 = y - 32 - 4 * erase.num;
		GLfloat newX2 = x + 24 + 3 * erase.num;
		GLfloat newY2 = y + 24 + 3 * erase.num;

		rect.x1 = newX1;
		rect.y1 = newY1;
		rect.x2 = newX2;
		rect.y2 = newY2;
		

		for (Rect& rect : rects) {
				// 벽과의 충돌 검사
				
			}

		glClearColor(r, g, b, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT);
		drawRectangles();
		glutSwapBuffers(); // 화면에 출력하기
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
	for (int i = 0; i < 40; i++)
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
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	glutMainLoop(); // 이벤트 처리 시작 
}