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
	bool selected = false; // ���� ����

};

vector<Rect> rects;

GLfloat r = 0.3f, g=0.3f, b=0.3f;

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
		rects.push_back(rect);
	}
}

void drawRectangles() {
	for (const Rect& rect : rects) {
		if (rect.selected) {
			glColor3f(1.0f, 0.0f, 0.0f); // ���õ� �簢���� ���������� ǥ��
		}
		else {
			glColor3f(rect.r, rect.g, rect.b);
		}
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
		addRandomRectangle();
		break;
	}
	glutPostRedisplay();
}

//���콺
void Mouse(int button, int state, int m_x, int m_y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{///cout << endl;
		//cout << endl;
		//cout << "���콺 ��ǥ		: " << m_x << "\t\t" << m_y << endl;
		//// ���� �ٲ�ߵ�!
		for (int i = 4; -1 < i ; --i) {
			Rect& rect = rects[i];

			//cout << rect.x1 << " " << rect.y1 << endl;
			if (rect.x1 < 0) {
				tempx1 = 400 + rect.x1 * 400;
			}
			else  {
				tempx1 = 400 + rect.x1 * 400;
			}

			if (rect.y1 < 0) {
				tempy1 = 300 - rect.y1 * 300;
			}
			else  {
				tempy1 = 300 - rect.y1 * 300 ;
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
			else  {
				tempy2 = 300 - rect.y2 * 300 ;
			}
		
			if ((tempx1 < m_x && m_x < tempx2)
				&& (tempy1 < m_y && m_y < tempy2))
			{
				selectedRectangle = i;
				xOffset = tempx1 - m_x ;
				yOffset = tempy1 - m_y ;
				isDragging = true;
				//rect.selected = true;
				break;
			}
		}

	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		isDragging = false;
		selectedRectangle = -1;
		if (selectedRectangle >= 0) {
			//rects[selectedRectangle].selected = false;
	
		}
	}
}


void Motion(int x, int y)
{
	//for (auto& a : rects) {
	//	if (a.selected == true) {
	//		// �巡�� ���� �� �簢���� �̵�
	//		
	//		Rect& rect = rects[selectedRectangle];
	//		if (rect.x1 < 0) {
	//			tempx1 = 400 + rect.x1 * 400;
	//		}
	//		else {
	//			tempx1 = 400 + rect.x1 * 400;
	//		}
	//		if (rect.y1 < 0) {
	//			tempy1 = 300 - rect.y1 * 300;
	//		}
	//		else {
	//			tempy1 = 300 - rect.y1 * 300;
	//		}
	//		if (rect.x2 < 0) {
	//			tempx2 = 400 + rect.x2 * 400;
	//		}
	//		else {
	//			tempx2 = 400 + rect.x2 * 400;
	//		}
	//		if (rect.y2 < 0) {
	//			tempy2 = 300 - rect.y2 * 300;
	//		}
	//		else {
	//			tempy2 = 300 - rect.y2 * 300;
	//		}
	//	}
	//}
	if (isDragging && selectedRectangle >= 0) {

		// �巡�� ���� �� �簢���� �̵�
		Rect& rect = rects[selectedRectangle];
		


		GLfloat newX1 = ((x + xOffset) - 400) / 400;
		GLfloat newY1 = (300 - (y + yOffset)) / 300;
		GLfloat newX2 = newX1 + (rect.x2 - rect.x1);
		GLfloat newY2 = newY1 + (rect.y2 - rect.y1);

		rect.x1 = newX1;
		rect.y1 = newY1;
		rect.x2 = newX2;
		rect.y2 = newY2;
		glClearColor(r, g, b, 1.0f); // �������� ��blue�� �� ����
		glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
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