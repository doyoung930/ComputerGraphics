#include "CCube.h"

CCube::CCube() : CObject()
{
	
}

CCube::CCube(GLfloat halfLength, float r, float g, float b)
{
}

CCube::CCube(vector<GLfloat>& vertex, vector<GLfloat>& color) : CObject(vertex, color)
{
}

CCube::~CCube()
{
}
