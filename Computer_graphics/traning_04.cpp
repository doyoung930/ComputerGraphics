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
int selectedRectangle = -1; // ������ �簢���� �ε���
bool isDragging = false; // �巡�� ������ ����
GLfloat xOffset, yOffset; // �巡�� ���� �� ���콺 Ŭ�� ������ �簢���� ���� ��� ������ ���� ������

struct Rect {
	GLfloat base_x1, base_y1, base_x2, base_y2;
	GLfloat x1, y1, x2, y2; // ���� �Ʒ��� ������ �� ������ ��ǥ
	GLclampf r, g, b; // ����
	bool selected = false; // ���� ����

};

vector<Rect> rects;

GLfloat r = 0.3f, g = 0.3f, b = 0.3f;

bool IsTimerAlive = true;

int maxRectangles = 5;
bool a_moveRect = false; // �簢������ �̵� ���¸� ��Ÿ���� ����

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
// Ÿ�̸�
void TimerFunction(int value)
{
	updateRectangles();
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