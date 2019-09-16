#pragma once

#include <string>
#include "Array.h"

using namespace std;

class Node;

struct Choice {
	string text; //linia tekstu, kt�ry wy�wietli si� jako opcja do wybrania w danym momencie
	Node* node; //w�ze� (punkt rozgrywki) do kt�rego przemie�cimy si� wybieraj�c
};

class Node {
	int id;
	bool end;
	string info; //tekst ktory wyswietli si� jako opis aktualnej sytuacji
	Array<Choice> choices; //mozliwe wybory
public:
	Node(int id);
	Node(int id, string info, bool isEnd = false);
	void connect(string text, Node* destination);
	bool isEnd();
	void print();
	Node* move(int choiceId);
	void setParameters(string info, bool isEnd = false);
	int getId();
};
