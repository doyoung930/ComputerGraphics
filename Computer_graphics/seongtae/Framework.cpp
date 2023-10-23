#include "Framework.h"

CFramework::CFramework()
{
	scene = new CScene();
	scene->Init();
}

CFramework::~CFramework()
{
	delete scene;
}

void CFramework::Render()
{
	scene->Render();
}
