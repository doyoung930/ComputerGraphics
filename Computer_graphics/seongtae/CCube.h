#pragma once
#include "CObject.h"

class CCube : public CObject
{
public:
	CCube();
	CCube(GLfloat halfLength, float r, float g, float b);
	CCube(vector<GLfloat>& vertex, vector<GLfloat>& color);
	virtual ~CCube();
};

