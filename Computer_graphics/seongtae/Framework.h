#pragma once
#include "CScene.h"

class CFramework
{
	CScene* scene;

public:
	CFramework();
	virtual ~CFramework();
	void Render();
};

