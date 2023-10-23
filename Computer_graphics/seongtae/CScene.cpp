#include "CScene.h"

CScene::CScene()
{
	objects = new CObject * [10];
    InitShader("vertex23.glsl", "fragment23.glsl");
}

CScene::~CScene()
{
	for (int i = 0; i < 10; ++i) {
		delete objects[i];
	}
	delete[] objects;
}

void CScene::Init()
{

    vector<GLfloat> vertex, color;
    {
        //뒷면
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);

        //아래
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);

        //위
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);

        //앞면
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);

        //왼쪽
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(-0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(-0.5); vertex.push_back(0.5); vertex.push_back(0.5);

        //오른쪽
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);
        vertex.push_back(0.5); vertex.push_back(-0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(-0.5);
        vertex.push_back(0.5); vertex.push_back(0.5); vertex.push_back(0.5);

        for (int i = 0; i < 36; ++i) {
            color.push_back(1.0); color.push_back(0.0); color.push_back(0.0);
        }
    }

    objects[0] = new CCube(vertex, color);
}

void CScene::Render()
{
	objects[0]->Render(s_program);
}

void CScene::InitShader(string vertex, string frag) {
    GLuint vertexShader = make_vertexShader(vertex);
    GLuint fragmentShader = make_fragmentShader(frag);

    s_program = glCreateProgram();
    glAttachShader(s_program, vertexShader);
    glAttachShader(s_program, fragmentShader);
    glLinkProgram(s_program);
    //  checkCompileErrors(s_program, "PROGRAM");

        //--- 세이더 삭제하기
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //--- Shader Program 사용하기
    glUseProgram(s_program);
}

const string CScene::filetobuf(const char* file)
{
    string content = "";
    string line = "";
    ifstream in(file, ios::in);

    while (!in.eof()) {
        getline(in, line);
        content.append(line + "\n");
    }

    in.close();
    return content;
}

GLuint CScene::make_fragmentShader(string filename) {
    string fragmentsource;
    GLuint fragmentShader;
    fragmentsource = filetobuf(filename.c_str());

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* raw_str = fragmentsource.c_str();
    glShaderSource(fragmentShader, 1, &raw_str, NULL);
    glCompileShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << endl;
        return 0;
    }
    return fragmentShader;
}

GLuint CScene::make_vertexShader(string filename) {
    string vertexsource;
    GLuint vertexShader;
    vertexsource = filetobuf(filename.c_str());

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* raw_str = vertexsource.c_str();

    glShaderSource(vertexShader, 1, &raw_str, NULL);
    glCompileShader(vertexShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << endl;
        return 0;
    }

    return vertexShader;
}
