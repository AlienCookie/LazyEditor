#include "stdafx.h"
#include "sceneLoad.h"


int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	
	return 0;
}

sceneLoad::sceneLoad()
{
	sqlite3_open("C:\sqlite3\myDB.db", &dataBase);
	char *zErrMsg = 0;


	string create = "CREATE TABLE IF NOT EXISTS scene (properties text);";
	sqlite3_exec(dataBase, create.c_str(), callback, 0, &zErrMsg);

	create = "CREATE TABLE IF NOT EXISTS vertices (VERTEX TEXT);";

	sqlite3_exec(dataBase, create.c_str(), callback, 0, &zErrMsg);

	create = "CREATE TABLE IF NOT EXISTS poligons (VERTEX TEXT);";

	sqlite3_exec(dataBase, create.c_str(), callback, 0, &zErrMsg);

	/*	if (error)
		sqlite3_close(db);*/

	//
}


int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
	Records* records = static_cast<Records*>(p_data);
	try {
		records->emplace_back(p_fields, p_fields + num_fields);
	}
	catch (...) {
		// abort select on failure, don't let exception propogate thru sqlite3 call-stack 
		return 1;
	}
	return 0;
}

Records sceneLoad::select_stmt(const char* stmt)
{
	Records records;
	char *errmsg;
	int ret = sqlite3_exec(dataBase, stmt, select_callback, &records, &errmsg);
	if (ret != SQLITE_OK) {
		//std::cerr << "Error in select statement " << stmt << "["<< errmsg << "]\n";
	}
	else {
		//std::cerr << records.size() << " records returned.\n";
	}

	return records;
}




//call
void sceneLoad::proper()
{
	records = select_stmt("SELECT * from scene");

	float x, y, z;
	string buff;
	std::string::size_type sz;     // alias of size_t
	vertices.resize(records.size());
	for (int i = 0; i < records.size(); i++)
	{
		buff = records[i][0];
		for (int k = 0; k < 4; k++)
		{
			x = stof(buff, &sz);
			buff = buff.substr(sz);
			y = stof(buff, &sz);
			buff = buff.substr(sz);
			z = stof(buff, &sz);
			buff = buff.substr(sz);

			vertices[i].push_back(vec(x, y, z));
		}
	}
}

void sceneLoad::vertic()
{
	records = select_stmt("SELECT * from vertices");

	float x, y, z;
	string buff;
	std::string::size_type sz;     // alias of size_t
	for (int i = 0; i < records.size(); i++)
	{
		buff = records[i][0];
		while (buff != " " && buff.size()>0)
		{
			x = stof(buff, &sz);
			buff = buff.substr(sz);
			y = stof(buff, &sz);
			buff = buff.substr(sz);
			z = stof(buff, &sz);
			buff = buff.substr(sz);

			vertices[i].push_back(vec(x, y, z));
		}
	}
}

void sceneLoad::polig()
{
	records = select_stmt("SELECT * from poligons");

	float x, y, z;
	string buff;
	std::string::size_type sz;     // alias of size_t   // alias of size_t
	poligon.resize(records.size());
	for (int i = 0; i < records.size(); i++)
	{
		buff = records[i][0];
		while (buff != " " && buff.size()>0)
		{
			x = stof(buff, &sz);
			buff = buff.substr(sz);
			y = stof(buff, &sz);
			buff = buff.substr(sz);
			z = stof(buff, &sz);
			buff = buff.substr(sz);

			poligon[i].push_back(vec(x, y, z));
		}
	}
}

vector<vector<vec>> sceneLoad::getVertices()
{
	return vertices;
}

vector<vector<vec>> sceneLoad::getPoligons()
{
	return poligon;
}

void sceneLoad::loading()
{
	
	proper();

	vertic();

	polig();

	
}

void sceneLoad::savingScene(vector<Model*> models)
{
	std::string query;// = "INSERT INTO myDB VALUES";

	sqlite3_exec(dataBase, "DELETE FROM scene;", select_callback, &records, 0);
	sqlite3_exec(dataBase, "DELETE FROM vertices;", select_callback, &records, 0);
	sqlite3_exec(dataBase, "DELETE FROM poligons;", select_callback, &records, 0);

	for (int i = 0; i < models.size(); i++)
	{
		query =
			"INSERT INTO scene (properties) VALUES ('"
			+ to_string(models[i]->getPosition().x) + " "
			+ to_string(models[i]->getPosition().y) + " "
			+ to_string(models[i]->getPosition().z) + " "
			+ to_string(models[i]->getScale().x) + " "
			+ to_string(models[i]->getScale().y) + " "
			+ to_string(models[i]->getScale().z) + " "
			+ to_string(models[i]->getColor().x) + " "
			+ to_string(models[i]->getColor().y) + " "
			+ to_string(models[i]->getColor().z) + " "
			+ to_string(models[i]->getAngle().x) + " "
			+ to_string(models[i]->getAngle().y) + " "
			+ to_string(models[i]->getAngle().z)  + "');";
		
		sqlite3_exec(dataBase, query.c_str(), callback, 0, 0);
		
		vector<vec> ver = models[i]->getVertices();
		string vert = "INSERT INTO vertices (VERTEX) VALUES ('";
		for (int j = 0; j < ver.size(); j++)
		{
			vert += to_string(ver[j].x) + " "
				+ to_string(ver[j].y) + " "
				+ to_string(ver[j].z) + " ";
		}
		vert += "');";
		sqlite3_exec(dataBase, vert.c_str(), callback, 0, 0);

		vector<vec> pol = models[i]->getPoligons();
		string polig = "INSERT INTO poligons (VERTEX) VALUES ('";
		for (int j = 0; j < pol.size(); j++)
		{
			polig += to_string(pol[j].x) + " "
				+ to_string(pol[j].y) + " "
				+ to_string(pol[j].z) + " ";
		}
		polig += "');";

		sqlite3_exec(dataBase, polig.c_str(), callback, 0, 0);

	}
	
//	sqlite3_close(dataBase);
}

sceneLoad::~sceneLoad()
{
}
