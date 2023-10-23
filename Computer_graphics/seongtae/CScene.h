#pragma once
#include "CCube.h"

class CScene
{	
	GLuint s_program;
	CObject** objects;
    GLuint make_vertexShader(string filename);
    GLuint make_fragmentShader(string filename);
	void InitShader(string vertex, string frag);
	const string filetobuf(const char* file);

public:
	CScene();
	virtual ~CScene();
	void Init();
	virtual void Render();
};

