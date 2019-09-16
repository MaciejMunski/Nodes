#pragma once

#include "Node.h"

class Game {
	Array<Node*> nodes; //MM wezly przechowywae na zasadzie wsaznikow na nowy obiekt
	Node* begin;
	Node* current;
	string worldFilename;

	void initialize(string filename);
	void save(); //robi save do pliku podanego przez usera
	void save(string savename); //robi save do konkretnego pliku
	void printMenu();
	bool Load();
	void NewGame();
	void Exit();
	bool menuChoice();
	void autoSave();
	void reset();
public:
	void run();
};