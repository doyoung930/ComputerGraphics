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
int selectedRectangle = -1; // ������ �簢���� �ε���
bool isDragging = false; // �巡�� ������ ����
GLfloat xOffset, yOffset; // �巡�� ���� �� ���콺 Ŭ�� ������ �簢���� ���� ��� ������ ���� ������

struct Rect {
	GLfloat base_x1, base_y1, base_x2, base_y2;
	GLfloat x1, y1, x2, y2; // ���� �Ʒ��� ������ �� ������ ��ǥ
	GLclampf r, g, b; // ����
	bool selected = false; // ���� ����
	GLfloat dx = 0.01f, dy = 0.01f; // ������ ���� �߰�
};

vector<Rect> rects;

GLfloat r = 0.3f, g = 0.3f, b = 0.3f;

bool IsTimerAlive = true;

int maxRectangles = 5;

//// bool �Ǵ� ����
bool a_moveRect = false; // �簢������ �̵� ���¸� ��Ÿ���� ����
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

				// ������ �浹 �˻�
				if (rect.x1 + rect.dx < -1.0f) {
					// ���� ���� �浹�� ���
					rect.dx = fabs(rect.dx); // �ݻ纤�� ����
				}
				else if (rect.x2 + rect.dx > 1.0f) {
					// ������ ���� �浹�� ���
					rect.dx = -fabs(rect.dx); // �ݻ纤�� ����
				}

				if (rect.y2 + rect.dy < -1.0f) {
					// �Ʒ� ���� �浹�� ���
					rect.dy = fabs(rect.dy); // �ݻ纤�� ����
				}
				else if (rect.y1 + rect.dy > 1.0f) {
					// �� ���� �浹�� ���
					rect.dy = -fabs(rect.dy); // �ݻ纤�� ����
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

				// ������ �浹 �˻�
				if (rect.x1 + rect.dx < -1.0f) {
					// ���� ���� �浹�� ���
					rect.dx = fabs(rect.dx); // �ݻ纤�� ����
				}
				else if (rect.x2 + rect.dx > 1.0f) {
					// ������ ���� �浹�� ���
					rect.dx = -fabs(rect.dx); // �ݻ纤�� ����
				}

				rect.x1 += rect.dx;
				rect.x2 += rect.dx;
			}
		}
	}
}

// Ÿ�̸�
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
	glutPostRedisplay(); // ȭ�� �� ���
	if (IsTimerAlive)
		glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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

// Ű����
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

//���콺
void Mouse(int button, int state, int m_x, int m_y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		addRectangle_mouse(m_x, m_y);
	}

}

GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(r, g, b, 1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.

	drawRectangles();

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 30); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Doyoung"); // ������ ����(������ �̸�)

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "��Unable to initialize GLEW��" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}