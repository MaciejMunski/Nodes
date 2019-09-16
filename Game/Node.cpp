#include "Node.h"
#include <iostream>

Node::Node(int id)
{
	this->id = id;
	this->info = "";
	this->end = false;
}

Node::Node(int id, string info, bool isEnd)
{
	this->id = id;
	this->info = info;
	this->end = isEnd;
}

void Node::connect(string text, Node* destination)
{
	choices.addBack(Choice{ text, destination });
}

bool Node::isEnd()
{
	return end;
}

void Node::print()
{
	cout << info << endl<<endl;
	for (int i = 0; i < choices.getSize(); i++) {
		Choice c = choices.get(i);
		cout << i << ": " << c.text << endl;
	}
}

Node* Node::move(int choiceId)
{
	if (choiceId >= 0 && choiceId < choices.getSize()) {
		return choices.get(choiceId).node;
	}
	else {
		return nullptr;
	}
}

void Node::setParameters(string info, bool isEnd)
{
	this->info = info;
	this->end = isEnd;
}

int Node::getId()
{
	return id;
}
 