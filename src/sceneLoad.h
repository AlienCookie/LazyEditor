#pragma once
#include <sqlite3\sqlite3.h>
#include "Model.h"
#include <string>

#pragma comment (lib, "sqlitePrj.lib")


using Record = std::vector<std::string>;
using Records = std::vector<Record>;

class sceneLoad
{
protected:
	sqlite3* dataBase;
	sqlite3_stmt* res;

	const char *errMsg;
	const char *tail;
	vector<vector<vec>> vertices;
	vector<vector<vec>> poligon;
	Records	records;
public:
	sceneLoad();
	Records select_stmt(const char * stmt);
	void proper();
	void vertic();
	void polig();
	vector<vector<vec>> getVertices();
	vector<vector<vec>> getPoligons();
	void loading();
	void savingScene(vector<Model*>);
	~sceneLoad();
};

