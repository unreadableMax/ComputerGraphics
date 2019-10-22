//-------------group members--------------
//	Dennis Becker		3497351
//	Julian Gröger		3542588
//	Amrit  Kaur			3532964
//  Maximilian Legnar	3544557
//-----------------------------------------

// Ex1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//
#include "pch.h"
#include <iostream>
// Assignment1_Q2.cpp : Defines the entry point for the application.
//

#include "String"
#include <vector>
#include <fstream>
using namespace std;

// contains some helpfull functionalities
class Helper {
public:
	static vector<string> split(const string& str, const string& delim)
	{
		vector<string> tokens;
		size_t prev = 0, pos = 0;
		do
		{
			pos = str.find(delim, prev);
			if (pos == string::npos) pos = str.length();
			string token = str.substr(prev, pos - prev);
			if (!token.empty()) tokens.push_back(token);
			prev = pos + delim.length();
		} while (pos < str.length() && prev < str.length());
		return tokens;
	}

	static int GetIntFromUser(string msg) {
		cout << msg;
		int num;
		string input;
		cin >> input;
		try
		{
			num = stoi(input, nullptr);
		}
		catch (const std::exception&)
		{
			cout << "wrong input, try again\n";
			num = Helper::GetIntFromUser(msg);
		}
		return num;
	}

	static float GetFloatFromUser(string msg) {
		cout << msg;
		float num;
		string input;
		cin >> input;
		try
		{
			num = stof(input, nullptr);
		}
		catch (const std::exception&)
		{
			cout << "wrong input, try again\n";
			num = Helper::GetFloatFromUser(msg);
		}

		return num;
	}

};

class Position {
public:
	int X;
	int Y;

	Position() {
		X = 0;
		Y = 0;
	}

	Position(int _x, int _y) {
		X = _x;
		Y = _y;
	}

	string ToString() {
		return std::to_string(X) + ";" + std::to_string(Y);
	}

	bool FromString(string inStr) {
		vector<string> chunks = Helper::split(inStr, ";");
		X = std::stoi(chunks.at(0), nullptr);
		Y = std::stoi(chunks.at(1), nullptr);
		return true;
	}
};

class Mesh {
public:
	int ID;
	int NumberOfVertices;
	Position* Center;
	int NumberOfFaces;
	string Name;
	float Scale;
	Mesh() {
		ID = -1;
		NumberOfVertices = -1;
		Center = NULL;
		NumberOfFaces = -1;
		Name = "";
		Scale = -1;
	}
	Mesh(int _numberOfVertices, Position* _center, int _numberOdFaces, string _name, float _scale) {
		NumberOfVertices = _numberOfVertices;
		Center = _center;
		NumberOfFaces = _numberOdFaces;
		Name = _name;
		Scale = _scale;
	}

	std::string ToString() {
		std::string retValue = "";
		retValue = std::to_string(ID) + "\n" + std::to_string(NumberOfVertices) + "\n" + Center->ToString() + "\n" + std::to_string(this->NumberOfFaces) + "\n" + Name + "\n" + std::to_string(this->Scale) + "\n";
		return retValue;
	}

	std::string ToPresentableString() {
		std::string retValue = "";
		retValue = "ID: " + std::to_string(ID) + "\nNumber of Vertices: " + std::to_string(NumberOfVertices) + "\nCenter(" + Center->ToString() + ")\nNumber of Faces: " + std::to_string(this->NumberOfFaces) + "\nName: " + Name + "\nScale: " + std::to_string(this->Scale) + "\n";
		return retValue;
	}

	bool FromString(string inStr) {
	std:vector<string> props = Helper::split(inStr, "\n");
		if (props.size() != 6) {
			return false;
		}
		else {
			this->ID = std::stoi(props.at(0), nullptr);
			this->NumberOfVertices = std::stoi(props.at(1), nullptr);
			this->Center = new Position();
			if (!this->Center->FromString(props.at(2)))
			{
				return false;
			}
			this->NumberOfFaces = std::stoi(props.at(3), nullptr);
			this->Name = props.at(4);
			this->Scale = std::stof(props.at(5), nullptr);
			return true;
		}
	}
};

class Node
{
public:
	Node* next;
	Mesh* data;
};

class Scene
{
private:
	int id = 1;
	string ToStringRec(Node* nd);
	void addInsertnal(Mesh* obj);
	void printAsc(Node * nd);
public:
	int length;
	Node* tail;
	Scene();
	~Scene();
	void add(Mesh* data);
	Mesh* remove(Mesh* obj);
	Mesh* removeById(int id);
	void print();

	string ToString();
	bool FromString(string inStr);
};

Scene::Scene() {
	this->length = 0;
	this->tail = NULL;
}

Scene::~Scene() {
	std::cout << "LIST DELETED";
}

void Scene::addInsertnal(Mesh* obj) {
	Node* node = new Node();
	node->data = obj;
	node->next = this->tail;
	this->tail = node;

	this->length++;

	int maxId = 0;
	Node* nav = this->tail;
	while (nav)
	{
		if (nav->data->ID > maxId) {
			maxId = nav->data->ID;
		}
		nav = nav->next;
	}
	id = maxId + 1;
}

void Scene::add(Mesh* data) {
	data->ID = id;
	id++;
	addInsertnal(data);
}

Mesh* Scene::remove(Mesh* obj) {
	if (obj == NULL) {
		return false;
	}
	return this->removeById(obj->ID);
}

Mesh* Scene::removeById(int id) {
	Node* navNode = tail;
	Node* prevNode = NULL;
	Node *deletedNode = NULL;
	while (navNode != NULL)
	{
		if (navNode->data->ID == id) {
			//mesh object found now lets delete
			if (prevNode == NULL) {
				tail = navNode->next;
			}
			else {
				prevNode->next = navNode->next;
			}
			deletedNode = navNode;
			return deletedNode->data;
		}
		prevNode = navNode;
		navNode = navNode->next;
	}
	//item to delete not found
	return NULL;
}

void Scene::print() {
	if (this->tail)
		printAsc(this->tail);
	else
		std::cout << "nothing to print" << endl;
}

void Scene::printAsc(Node* nd) {
	if (nd->next != NULL) {
		printAsc(nd->next);
	}
	std::cout << nd->data->ToPresentableString() << std::endl;
}

string Scene::ToString() {
	return ToStringRec(this->tail);
}

string Scene::ToStringRec(Node* nd) {
	string val = "";
	if (nd->next) {
		val = val + this->ToStringRec(nd->next);
		val = val + "\n---\n";
	}
	val = val + nd->data->ToString();
	return val;
}
bool Scene::FromString(string inStr) {
	vector<string> objChunks = Helper::split(inStr, "\n---\n");
	for (string n : objChunks) {
		Mesh* m = new Mesh();
		if (!m->FromString(n)) {
			return false;
		}
		else {
			this->add(m);
		}
	}
	return true;
}


int main()
{
	//try read scene from file if file exists 
	string fileContent="";
	string line;
	ifstream rmyfile("Ex1Q2.txt");
	if (rmyfile.is_open())
	{
		while (getline(rmyfile, line))
		{
			fileContent= fileContent+ line + '\n';
		}
		rmyfile.close();
	}
		
	Scene* lst = new Scene();
	if (fileContent != "") {
		if (!lst->FromString(fileContent)) {
			cout << "Unable to deserialize file content." << std::endl;
		}
	}
	bool doExit = false;
	bool showHelp = true;
	while (!doExit)
	{
		if (showHelp) {
			cout << "Please choose action: " << std::endl;
			cout << "Enter 1 to add mesh object" << std::endl;
			cout << "Enter 2 to remove mesh object" << std::endl;
			cout << "Enter 3 to list existing mesh objects" << std::endl;
			cout << "Enter 4 to exit the program" << std::endl;
			cout << "-----------------------------------" << std::endl;
			showHelp = false;
		}
		else {
			cout << "Press 5 For Help" << std::endl;
		}
		string in_choice;
		cin >> in_choice;

		int choice = -1;
		try
		{
			choice = std::stoi(in_choice, nullptr);
		}
		catch (const std::exception&)
		{
			cin.clear(); // reset failbit
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			choice = -1;
		}

		if (choice == 1) {
			Mesh* m = new Mesh();
			cout << "Enter name of Mesh" << std::endl;
			cin >> m->Name;
			m->NumberOfFaces=  Helper::GetIntFromUser("Enter Number of faces: ");
			m->NumberOfVertices = Helper::GetIntFromUser("Enter Number of vertices: ");
			m->Scale = Helper::GetFloatFromUser("Enter Scale factor: ");
			m->Center = new Position();
			m->Center->X = Helper::GetFloatFromUser("Enter position X of Mesh: ");
			m->Center->Y = Helper::GetFloatFromUser("Enter position Y of Mesh: ");
			lst->add(m);
			cout << "Object added to scene its id is: " << m->ID << std::endl;
		}
		else if (choice == 2) {
			cout << "Enter id of mesh objects to remove" << std::endl;
			int idToRemove = -1;
			cin >> idToRemove;
			Mesh* removedObj = lst->removeById(idToRemove);
			if (removedObj == NULL) {
				cout << "Object with id: " << idToRemove << " not found in the scene." << std::endl;
			}
			else {
				cout << "Object with id: " << idToRemove << " removed from the scene." << std::endl;
				delete removedObj;
			}
		}
		else if (choice == 3) {
			cout << "List of Objects " << std::endl;
			cout << "--------------------- " << std::endl;
			lst->print();
			cout << "--------------------- " << std::endl;
		}
		else if (choice == 4) {
			doExit = true;
		}
		else{
			showHelp = true;
		}
	}

	//Save scene to file
	ofstream myfile;
	myfile.open("Ex1Q2.txt");
	myfile << lst->ToString();
	myfile.close();

	return 0;
}