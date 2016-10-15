#pragma once
#include "arcball.h"
//#include "Model.h"
#include "World.h"
#include "Observer.h"
#include "sceneLoad.h"

class COpenGLRender
{
protected:
	int Width, Height;
	vector<Model*> models;
	Observer me;
	World myWorld;
	transform mode;
	Model *selected;
	bool selectAxe;
	bool onObject;
	sceneLoad myScene;
public:
	CPoint cursor;
	float ortho[3];

	COpenGLRender();
	~COpenGLRender();

	bool Init();

	void Render(float FrameTime = 0);
	void Resize(int Width, int Height);
	void Destroy();
	void mouseWheel(short k);
	void setMode(transform _mode);
	void LButtonMove(CPoint pos);
	void RButtonMove(CPoint pos);
	void onSelected();
	void onSave();
	void onLoad();
	void onColor();
	void pickObject(CPoint pos);
	void setSelct(bool _selectedAxe);
	void setOnObject(bool _onObject);
	void draw_scene();
	void addObject(modelType);
};