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
int selectedRectangle = -1; // ������ �簢���� �ε���
bool isDragging = false; // �巡�� ������ ����
GLfloat xOffset, yOffset; // �巡�� ���� �� ���콺 Ŭ�� ������ �簢���� ���� ��� ������ ���� ������

struct Rect {
	GLfloat x1, y1, x2, y2; // ���� �Ʒ��� ������ �� ������ ��ǥ
	GLclampf r, g, b; // ����
	bool live = false;
	bool selected = false; // ���� ����

};

struct Rect_erase {
	GLfloat x1, y1, x2, y2; // ���� �Ʒ��� ������ �� ������ ��ǥ
	GLclampf r, g, b; // ����
	bool selected = false; // ���� ����
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
// Ÿ�̸�
void TimerFunction(int value)
{
	//RandomRGB();
	glutPostRedisplay(); // ȭ�� �� ���
	if (IsTimerAlive)
		glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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

// Ű����
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		break;
	}
	glutPostRedisplay();
}

//���콺
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

		// �巡�� ���� �� �簢���� �̵�
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
				// ������ �浹 �˻�
				
			}

		glClearColor(r, g, b, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT);
		drawRectangles();
		glutSwapBuffers(); // ȭ�鿡 ����ϱ�
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
	for (int i = 0; i < 40; i++)
		addRandomRectangle();

	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "��Unable to initialize GLEW��" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		//std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}