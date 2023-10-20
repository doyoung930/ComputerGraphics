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
int selectedRectangle = -1; 
bool isDragging = false; 
GLfloat xOffset, yOffset; 
struct Rect {
	GLfloat x1, y1, x2, y2; 
	GLclampf r, g, b; 
	bool live = false;
	bool selected = false; 

};

struct Rect_erase {
	GLfloat x1, y1, x2, y2; 
	GLclampf r, g, b; 
	bool selected = false; 
	int num = 0;
	bool existence = false;
};

struct Rect_col {
	GLfloat left,right,top,bottom;
};
Rect_erase erase = {};

vector<Rect> rects;

GLfloat r = 0.3f, g = 0.3f, b = 0.3f;

bool IsTimerAlive = true;

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
		
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		drawRectangles();
		glutSwapBuffers();
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		erase.selected = false;
		isDragging = false;
		selectedRectangle = -1;
	}
}
bool isAABBCollision(const Rect_col& rect1, const Rect_col& rect2) {

	if (rect1.right < rect2.left || rect1.left > rect2.right) {
		return false; 
	}

	if (rect1.bottom < rect2.top || rect1.top > rect2.bottom) {
		return false; 
	}

	return true;
}

void Motion(int x, int y)
{
	if (isDragging == true) {

		// 드래그 중일 때 사각형을 이동
		Rect_erase& rect_e = erase;

		tempx1 = x - 32 - 4 * erase.num;
		tempy1 = y - 32 - 4 * erase.num;
		tempx2 = x + 24 + 3 * erase.num;
		tempy2 = y + 24 + 3 * erase.num;

		erase.selected = true;


		erase.x1 = (tempx1 - 400) / 400;
		erase.y1 = (300 - tempy1) / 300;
		erase.x2 = (tempx2 - 400) / 400;
		erase.y2 = (300 - tempy2) / 300;
		
		
		
		//cout << erase.num << endl;
		for (Rect& rect : rects) {

			Rect_col rectAABB;
			rectAABB.left = rect.x1;
			rectAABB.right = rect.x2;
			rectAABB.top = rect.y1;
			rectAABB.bottom = rect.y2;

			Rect_col eraseAABB;
			eraseAABB.left = erase.x1;
			eraseAABB.right = erase.x2;
			eraseAABB.bottom = erase.y1;
			eraseAABB.top = erase.y2;

			if (isAABBCollision(eraseAABB, rectAABB)) {
				rect.x1 = 1000;
				rect.y1 = 1000;
				rect.y2 = 1000;
				rect.x2 = 1000;

				rect.live = false;
				rect.selected = false;
				erase.num++;
			}
		}

		glClearColor(r, g, b, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT);
		drawRectangles();
		glutSwapBuffers(); 
	}
}
GLvoid drawScene() 
{
	glClearColor(r, g, b, 1.0f); 
	glClear(GL_COLOR_BUFFER_BIT); 
	
	drawRectangles();

	glutSwapBuffers(); 
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