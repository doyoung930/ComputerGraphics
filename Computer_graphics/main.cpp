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

GLclampf r = 1.0f;
GLclampf g = 1.0f;
GLclampf b = 1.0f;

bool IsTimerAlive = true;

#include <iostream>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);

void RandomRGB()
{
	r = (GLclampf)dist(eng);
	g = (GLclampf)dist(eng);
	b = (GLclampf)dist(eng);
}

void TimerFunction(int value)
{
	RandomRGB();
	glutPostRedisplay(); // ȭ�� �� ���
	if (IsTimerAlive)
		glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ���� 
{ //--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 30); // �������� ��ġ ����
	glutInitWindowSize(1280, 720); // �������� ũ�� ����
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

	glutMainLoop(); // �̺�Ʈ ó�� ���� 
} 
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ� 
{ 
	glClearColor( r, g, b, 1.0f ); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

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