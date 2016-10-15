#include "stdafx.h"
#include "OpenGL.h"

static float aspect_ratio = 1.0f;

void COpenGLRender::draw_scene()
{

	for (int i = 0; i < models.size(); i++)
		models[i]->draw();

	myWorld.draw();
	onSelected();
	me.show();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0f, aspect_ratio, 1.0f, 70.0f);
	me.show();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

COpenGLRender::COpenGLRender()
{
	selected = nullptr;
	selectAxe = false;
	onObject = false;
}

COpenGLRender::~COpenGLRender()
{
}

void Lightning()
{
	GLfloat light1_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
	GLfloat light1_diffuse[] = { 0.6f, .6f, 0.6f, 1.0f };
	GLfloat light1_position[] = { -20.0f, 50.0f, -10.0f, 0.0f };
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
}

bool COpenGLRender::Init()
{
	glClearColor(0.4, 0.3, 0.1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glOrtho(-400, 400, -400, 400, -400, 400);

	// Set up OpenGL lights
	Lightning();

	// Enable alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable depth
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	myWorld = World(30);
	me = Observer(vec(15.0, 3.0, 2.0));
	mode = Scale;
	return true;
}

void COpenGLRender::Render(float FrameTime)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	draw_scene();
}

void COpenGLRender::Resize(int Width, int Height)
{
	this->Width = Width;
	this->Height = Height;
	aspect_ratio = (float)Width / (float)Height;
	glViewport(0, 0, Width, Height);
}

void COpenGLRender::Destroy()
{
}

void COpenGLRender::mouseWheel(short k)
{
	me.changeDistance(k/200.0);
}

void COpenGLRender::setMode(transform _mode)
{
	this->mode = _mode;
}

void COpenGLRender::LButtonMove(CPoint pos)
{
	POINT shift;
	shift.x = pos.x - cursor.x;
	shift.y = pos.y - cursor.y;
	if (selectAxe)
	{
		switch (mode)
		{
		case Move:
			me.moving(shift, selected);
			break;
		case Scale:
			me.scaling(shift, selected);
			break;
		case Rotate:
			me.rotating(shift, selected);
			break;
		case Color:
			me.colorChange(shift, selected);
			break;
		}
	}
	else if (onObject)
		me.freeMoving(shift, selected);
	else me.applyRotate(shift);

}

void COpenGLRender::RButtonMove(CPoint pos)
{
	POINT shift;
	shift.x = pos.x - cursor.x;
	shift.y = pos.y - cursor.y;
	me.applyShift(shift);
}

void COpenGLRender::onSelected()
{
	/*if (selected ) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_FOG);
		glDisable(GL_LIGHTING);

		glPushMatrix();

		for (int i = 0; i < models.size(); i++)
			models[i]->draw();
		GLdouble selBox[6][3];
		glPopMatrix();
		GLdouble modelMatrix[16], projectionMatrix[16];
		GLint viewPort[4];
		glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
		glGetIntegerv(GL_VIEWPORT, viewPort);
#pragma region array
		gluProject(
			selected->getBox()[0].x + selected->getPosition().x,
			selected->getBox()[0].y + selected->getPosition().y,
			selected->getBox()[0].z + selected->getPosition().z,
			modelMatrix,
			projectionMatrix,
			viewPort,
			&selBox[0][0],
			&selBox[0][1],
			&selBox[0][2]);
		gluProject(
			selected->getBox()[1].x + selected->getPosition().x,
			selected->getBox()[1].y + selected->getPosition().y,
			selected->getBox()[1].z + selected->getPosition().z,
			modelMatrix,
			projectionMatrix,
			viewPort,
			&selBox[1][0],
			&selBox[1][1],
			&selBox[1][2]);

		gluProject(
			selected->getBox()[2].x + selected->getPosition().x,
			selected->getBox()[2].y + selected->getPosition().y,
			selected->getBox()[2].z + selected->getPosition().z,
			modelMatrix,
			projectionMatrix,
			viewPort,
			&selBox[2][0],
			&selBox[2][1],
			&selBox[2][2]);

		gluProject(
			selected->getBox()[3].x + selected->getPosition().x,
			selected->getBox()[3].y + selected->getPosition().y,
			selected->getBox()[3].z + selected->getPosition().z,
			modelMatrix,
			projectionMatrix,
			viewPort,
			&selBox[3][0],
			&selBox[3][1],
			&selBox[3][2]);
		gluProject(
			selected->getBox()[4].x + selected->getPosition().x,
			selected->getBox()[4].y + selected->getPosition().y,
			selected->getBox()[4].z + selected->getPosition().z,
			modelMatrix,
			projectionMatrix,
			viewPort,
			&selBox[4][0],
			&selBox[4][1],
			&selBox[4][2]);
		gluProject(
			selected->getBox()[5].x + selected->getPosition().x,
			selected->getBox()[5].y + selected->getPosition().y,
			selected->getBox()[5].z + selected->getPosition().z,
			modelMatrix,
			projectionMatrix,
			viewPort,
			&selBox[5][0],
			&selBox[5][1],
			&selBox[5][2]);

#pragma endregion
		GLint leftBottX = viewPort[2], leftBottY = viewPort[3], rightTopX = viewPort[0], rightTopY = viewPort[1];
		for (int i = 0; i < 6; i++)
		{
			if (selBox[i][0] < leftBottX) leftBottX = selBox[i][0];
			if (selBox[i][1] < leftBottY) leftBottY = selBox[i][1];
			if (selBox[i][0] > rightTopX) rightTopX = selBox[i][0];
			if (selBox[i][1] > rightTopY) rightTopY = selBox[i][1];
		}
		gluUnProject(
			leftBottX,
			leftBottY,
			0.9,
			modelMatrix,
			projectionMatrix,
			viewPort,
			&selBox[0][0],
			&selBox[0][1],
			&selBox[0][2]
			);
		gluUnProject(
			rightTopX,
			rightTopY,
			0.9,
			modelMatrix,
			projectionMatrix,
			viewPort,
			&selBox[1][0],
			&selBox[1][1],
			&selBox[1][2]
			);
		glColor3f(0.0, 0.0, 1.0);
		glLineWidth(3.0);
		glBegin(GL_LINE_LOOP);
		glVertex3d(selBox[0][0], selBox[0][1], selBox[0][2]);
		glVertex3d(selBox[1][0], selBox[0][1], selBox[1][2]);
		glVertex3d(selBox[1][0], selBox[1][1], selBox[1][2]);
		glVertex3d(selBox[0][0], selBox[1][1], selBox[0][2]);
		glEnd();
	}
	glEnable(GL_LIGHTING);*/
}

void COpenGLRender::onSave()
{
	myScene.savingScene(models);
}

void COpenGLRender::onLoad()
{
	models.clear();
	myScene.loading();
	vector<vector<vec>> vertt =	myScene.getVertices();
	vector<vector<vec>> poligg = myScene.getPoligons();
	models.resize(vertt.size());
	for (int i = 0; i < models.size(); i++)
	{
		models[i] = new Model(vertt[i], poligg[i]);
	}

}

void COpenGLRender::onColor()
{
	this->mode = Color;
}

void COpenGLRender::pickObject(CPoint pos)
{
	// turn off texturing, lighting and fog
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_FOG);
	glDisable(GL_LIGHTING);

	glPushMatrix();

	for (int i = 0; i < models.size(); i++)
	{
		models[i]->swapColors();
		models[i]->draw();
		models[i]->swapColors();
		
	}


	// get color information from frame buffer
	unsigned char pixel[3];
	glPopMatrix();

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	glReadPixels(pos.x, viewport[3] - pos.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

	unsigned ID = pixel[0] + pixel[1] * 255 + pixel[2] * 255 * 255;

	switch (ID)
	{
	case 65025:
		selected->setAxe(axeX);
		selectAxe = true;
		break;
	case 64770:
		selected->setAxe(axeY);
		selectAxe = true;
		break;
	case 64515:
		selected->setAxe(axeZ);
		selectAxe = true;
		break;
	default:
		for (int i = 0; i < models.size(); i++)
			if (models[i]->getId() == ID)
			{
				onObject = true;
				models[i]->setSelected(true);
				selected = models[i];
			}
			else
				models[i]->setSelected(false);
	}
	glEnable(GL_LIGHTING);

}

void COpenGLRender::setSelct(bool _selectedAxe)
{
	selectAxe = _selectedAxe;
}

void COpenGLRender::setOnObject(bool _onObject)
{
	onObject = _onObject;
}

void COpenGLRender::addObject(modelType _model)
{
	switch (_model)
	{
	case CubeType:
		models.push_back(new Cube(vec(0.0, 1.0, 0.0), 2.0));
		break;
	case PiramidType:
		models.push_back(new Piramid(vec(0.0, 1.0, 0.0), 2.0));
		break;
	}
/*	for (int i = -20; i < 20; i += 4)
		for (int j = -30; j < 30; j += 4)
		{
			models.push_back(new Cube(vec(i, 1.0, j), 1.0));
			models.push_back(new Piramid(vec(i + 2, 1.0, j + 2), 1.0));
		}
	*/
}