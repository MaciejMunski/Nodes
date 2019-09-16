#pragma once

#include <string>
#include "Array.h"

using namespace std;

class Node;

struct Choice {
	string text; //linia tekstu, który wyœwietli siê jako opcja do wybrania w danym momencie
	Node* node; //wêze³ (punkt rozgrywki) do którego przemieœcimy siê wybieraj¹c
};

class Node {
	int id;
	bool end;
	string info; //tekst ktory wyswietli siê jako opis aktualnej sytuacji
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
