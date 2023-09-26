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

GLfloat minX = 0.0f;
GLfloat minY = 0.0f;
GLfloat maxX = 800.0f;
GLfloat maxY = 600.0f;

// �簢�� ��ǥ
GLfloat pos1_x = 0;
GLfloat pos1_y = 0;
GLfloat pos2_x = 1;
GLfloat pos2_y = 1;


GLfloat r1_pos1_x = 0;
GLfloat r1_pos1_y = 0;
GLfloat r1_pos2_x = 1.0f;
GLfloat r1_pos2_y = 1.0f;

GLfloat r2_pos1_x = 0;
GLfloat r2_pos1_y = 0;
GLfloat r2_pos2_x = -1.0f;
GLfloat r2_pos2_y = -1.0f;

GLfloat r3_pos1_x = 0;
GLfloat r3_pos1_y = 0;
GLfloat r3_pos2_x = 1.0f;
GLfloat r3_pos2_y = -1.0f;

GLfloat r4_pos1_x = 0;
GLfloat r4_pos1_y = 0;
GLfloat r4_pos2_x = -1;
GLfloat r4_pos2_y = 1;
// ��
GLclampf r = 1.0f;
GLclampf g = 1.0f;
GLclampf b = 1.0f;


GLclampf i1_r = 0.0f;
GLclampf i1_g = 1.0f;
GLclampf i1_b = 1.0f;

GLclampf i2_r = 1.0f;
GLclampf i2_g = 0.0f;
GLclampf i2_b = 1.0f;
		 
GLclampf i3_r = 0.0f;
GLclampf i3_g = 0.0f;
GLclampf i3_b = 1.0f;
		
GLclampf i4_r = 0.0f;
GLclampf i4_g = 1.0f;
GLclampf i4_b = 0.0f;
bool IsTimerAlive = true;

#include <iostream>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);

// ����
void RandomRGB(){
	r = (GLclampf)dist(eng);
	g = (GLclampf)dist(eng);
	b = (GLclampf)dist(eng);
}
void RandomRGB1() {
	i1_r = (GLclampf)dist(eng);
	i1_g = (GLclampf)dist(eng);
	i1_b = (GLclampf)dist(eng);
}
void RandomRGB2() {
	i2_r = (GLclampf)dist(eng);
	i2_g = (GLclampf)dist(eng);
	i2_b = (GLclampf)dist(eng);
}
void RandomRGB3() {
	i3_r = (GLclampf)dist(eng);
	i3_g = (GLclampf)dist(eng);
	i3_b = (GLclampf)dist(eng);
}
void RandomRGB4() {
	i4_r = (GLclampf)dist(eng);
	i4_g = (GLclampf)dist(eng);
	i4_b = (GLclampf)dist(eng);
}

void reduceRect1()
{
	r1_pos1_x = r1_pos1_x	+ 0.1f;
	r1_pos1_y = r1_pos1_y	+ 0.1f;
	r1_pos2_x = r1_pos2_x	- 0.1f;
	r1_pos2_y = r1_pos2_y	- 0.1f;

}
void reduceRect2()
{
	r2_pos1_x = r2_pos1_x	-0.1f;
	r2_pos1_y = r2_pos1_y	-0.1f;
	r2_pos2_x = r2_pos2_x	+0.1f;
	r2_pos2_y = r2_pos2_y	+0.1f;
}void reduceRect3()
{
	r3_pos1_x = r3_pos1_x	+ 0.1f;
	r3_pos1_y = r3_pos1_y	- 0.1f;
	r3_pos2_x = r3_pos2_x	- 0.1f;
	r3_pos2_y = r3_pos2_y	+ 0.1f;
}void reduceRect4()
{
	r4_pos1_x = r4_pos1_x	- 0.1f;
	r4_pos1_y = r4_pos1_y	+ 0.1f;
	r4_pos2_x = r4_pos2_x	+ 0.1f;
	r4_pos2_y = r4_pos2_y	- 0.1f;
	
}

void bigRect1()
{
	r1_pos1_x = r1_pos1_x - 0.1f;
	r1_pos1_y = r1_pos1_y - 0.1f;
	r1_pos2_x = r1_pos2_x + 0.1f;
	r1_pos2_y = r1_pos2_y + 0.1f;

}
void bigRect2()
{
	r2_pos1_x = r2_pos1_x + 0.1f;
	r2_pos1_y = r2_pos1_y + 0.1f;
	r2_pos2_x = r2_pos2_x - 0.1f;
	r2_pos2_y = r2_pos2_y - 0.1f;
}void bigRect3()
{
	r3_pos1_x = r3_pos1_x - 0.1f;
	r3_pos1_y = r3_pos1_y + 0.1f;
	r3_pos2_x = r3_pos2_x + 0.1f;
	r3_pos2_y = r3_pos2_y - 0.1f;
}void bigRect4()
{
	r4_pos1_x = r4_pos1_x + 0.1f;
	r4_pos1_y = r4_pos1_y - 0.1f;
	r4_pos2_x = r4_pos2_x - 0.1f;
	r4_pos2_y = r4_pos2_y + 0.1f;

}

// Ÿ�̸�
void TimerFunction(int value)
{
	RandomRGB();
	glutPostRedisplay(); // ȭ�� �� ���
	if (IsTimerAlive)
		glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}



GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{
	glClearColor(r, g, b, 1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glColor3f(i1_r, i1_g, i1_b);


	glRectf(r1_pos1_x, 
		r1_pos1_y, 
		r1_pos2_x, 
		r1_pos2_y);

	glColor3f(i2_r, i2_g, i2_b);
	glRectf(r2_pos1_x,
		r2_pos1_y,
		r2_pos2_x,
		r2_pos2_y);

	glColor3f(i3_r, i3_g, i3_b);
	glRectf(r3_pos1_x,
		r3_pos1_y,
		r3_pos2_x,
		r3_pos2_y);

	glColor3f(i4_r, i4_g, i4_b);
	glRectf(r4_pos1_x,
		r4_pos1_y,
		r4_pos2_x,
		r4_pos2_y);

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

// Ű����
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c':
		r = 0.0f;
		g = 1.0f;
		b = 1.0f;
		break;
	case 'm':
		r = 1.0f;
		g = 0.0f;
		b = 1.0f;
		break;
	case 'y':
		r = 1.0f;
		g = 1.0f;
		b = 0.0f;
		break;
	case 'a':
		RandomRGB();
		break;
	case 'w':
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		break;
	case 'k':
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		break;
	case 't':
		glutTimerFunc(100, TimerFunction, 1);
		IsTimerAlive = true;
		break;
	case 's':
		IsTimerAlive = false;
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
		if (((r1_pos1_x+1.0f)*400 < m_x &&
			(r1_pos2_x+1.0f)*400 > m_x) &&
			((r1_pos1_y - 1.0f) * -300 > m_y &&
			(r1_pos2_y - 1.0f) * -300 < m_y)) {
			RandomRGB1();
			cout << "����1" << endl;
		}
		else if (((r2_pos1_x + 1.0f) * 400 > m_x &&
			(r2_pos2_x + 1.0f) * 400 < m_x) &&
			((r2_pos1_y - 1.0f) * -300 < m_y &&
			(r2_pos2_y - 1.0f) * -300 > m_y)) {
			RandomRGB2();
			cout << "����2" << endl;
		}
		else if (((r3_pos1_x + 1.0f) * 400 < m_x &&
			(r3_pos2_x + 1.0f) * 400 > m_x) &&
			((r3_pos1_y - 1.0f) * -300 < m_y &&
			(r3_pos2_y - 1.0f) * -300 > m_y)) {
			RandomRGB3();
			cout << "����3" << endl;
		}
		else if (((r4_pos1_x + 1.0f) * 400 > m_x &&
			(r4_pos2_x + 1.0f) * 400 < m_x) &&
			((r4_pos1_y - 1.0f) * -300 > m_y &&
			(r4_pos2_y - 1.0f) * -300 < m_y)) {
			RandomRGB4();
			cout << "����4" << endl;
		}
		else {
			RandomRGB();
			cout << "���"<< endl;
		}
		cout << m_x << " , " << m_y << endl;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
		if (((r1_pos1_x + 1.0f) * 400 < m_x &&
			(r1_pos2_x + 1.0f) * 400 > m_x) &&
			((r1_pos1_y - 1.0f) * -300 > m_y &&
				(r1_pos2_y - 1.0f) * -300 < m_y)) {
			reduceRect1();
			cout << "����1" << endl;
		}
		else if (((r2_pos1_x + 1.0f) * 400 > m_x &&
			(r2_pos2_x + 1.0f) * 400 < m_x) &&
			((r2_pos1_y - 1.0f) * -300 < m_y &&
				(r2_pos2_y - 1.0f) * -300 > m_y)) {
			reduceRect2();
			cout << "����2" << endl;
		}
		else if (((r3_pos1_x + 1.0f) * 400 < m_x &&
			(r3_pos2_x + 1.0f) * 400 > m_x) &&
			((r3_pos1_y - 1.0f) * -300 < m_y &&
				(r3_pos2_y - 1.0f) * -300 > m_y)) {
			reduceRect3();
			cout << "����3" << endl;
		}
		else if (((r4_pos1_x + 1.0f) * 400 > m_x &&
			(r4_pos2_x + 1.0f) * 400 < m_x) &&
			((r4_pos1_y - 1.0f) * -300 > m_y &&
				(r4_pos2_y - 1.0f) * -300 < m_y)) {
			reduceRect4();
			cout << "����4" << endl;
		}
		else if ( 400 < m_x && m_x < 800 && 
				0 < m_y && m_y < 300) {
			bigRect1();
			cout << endl;
			cout << "����1" << endl;
		}
		else if (0 < m_x && m_x <400 &&
			300 < m_y && m_y < 600) {
			bigRect2();
			cout << "����2" << endl;
		}
		else if (400 < m_x && m_x < 800 &&
			300 < m_y && m_y <600) {
			bigRect3();
			cout << "����3" << endl;
		}
		else if (0 < m_x && m_x < 400 &&
			0 < m_y && m_y < 300) {
			bigRect4();
			cout << "����4" << endl;
		}

		
	}
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

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
}