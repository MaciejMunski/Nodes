#include "Game.h"
#include <fstream>
#include <iostream>

void Game::initialize(string filename)
{
	reset();
	worldFilename = filename;
	ifstream file(filename); // ifstream to klasa obslugujaca plik
	if (file.good()) {
		int id;
		string info;
		int destid;
		string choiceText;
		string line;

		while (getline(file, line)) {
			bool isEnd = (line.back() == '*');//back pobiera ostatni znak w stringu
			id = stoi(line);
			nodes.resize(id + 1);
			Node * n = nodes.get(id);
			if (n == nullptr) {
				n = new Node(id);
				nodes.set(id, n);
			}
			getline(file, info);
			n->setParameters(info, isEnd);

			getline(file, line);
			while (line.empty() == false) {
				int space = line.find_first_of(' ');
				choiceText = line.substr(space + 1);
				string destidStr = line.substr(0, space);
				destid = stoi(destidStr);
				nodes.resize(destid + 1);
				Node * destnode = nodes.get(destid);
				if (destnode == nullptr) {
					destnode = new Node(destid);
					nodes.set(destid, destnode);
				}
				n->connect(choiceText, destnode);
				getline(file, line);
			}
		}
	}
	begin = nodes.get(0);
	current = begin;
}

// Menu glowne pokazujace sie przed rozpoczeciem rozgrywki
void Game::printMenu()
{
	cout <<
		"0: Load\n" <<
		"1: New Game\n" <<
		"2: Exit\n";
}

bool Game::Load()
{
	string fileName;
	cout << "Podaj nazwe zapisu: ";
	cin >> fileName;
	fileName += ".txt";
	ifstream file(fileName, std::ios::app);

	if (file.good()) {
		file >> worldFilename;
		int nodeId;
		file >> nodeId;
		initialize(worldFilename);
		current = nodes.get(nodeId);
		return true;
	}
	else {
		cout << "nie ma takiego pliku" << endl;
		return false;
	}
}

//fstream file;
//string fileName;
//
//file.open(fileName.txt, std::ios::in | std::ios::app)

//string filename;
//cout << "podaj nazwe zapisu";
//cin >> filename;
//if (filename.good()==true) {
//	ifstream file(filename.c_str());
//	file.seekg(0, ios_base::end); //idz na koniec pliku czyli na miejsce w ktorym przerwana zostala gra
//}
//else {
//}


void Game::NewGame()
{
	cout << "podaj nazwe pliku ze swiatem do wczytania: ";
	string filename;
	cin >> filename;
	initialize(filename);
}


bool Game::menuChoice()
{
	printMenu();
	int action;
	do {
		cout << ">> ";
		cin >> action;
		switch (action) {
		case 0:
			Load();
			return true; // zaczynamy rozgrywke

		case 1:
			NewGame();
			return true; // zaczynamy rozgrywke

		case 2:
			return false; // nie zamierzamy zaczynac rozgrywki

		default:
			cout << "Invalid action\n";
		}

	} while (action != 2);
}

void Game::save()
{
	string savename;
	cout << "Podaj nazwe zapisu: ";
	cin >> savename;
	save(savename);
}

void Game::save(string savename)
{
	string filename = savename + ".txt";
	ofstream fout(filename);
	if (fout.good()) {
		fout << worldFilename << endl;
		fout << current->getId();
		fout.close();
	}
	else {
		cout << "Nie udalo sie zapisac gry\n";
	}
}

void Game::autoSave() {
	save("autosave");
}

void Game::reset()
{
	//nodes={*n1,*n2,*n3,*n4},  n1=Node{...},  n2=Node{...}, ... 
	for (int i = 0; i < nodes.getSize(); ++i) {
		//i=0
		Node* n = nodes.get(i);
		//*n=n1
		delete n;
		//n1 ju¿ nie istnieje, ale w nodes na idx 0 pozostaje wartoœæ wsk do pamiêci, w której dotychczas siedzia³ n1
		nodes.set(i, nullptr);
		//nodes={nullptr,*n2,*n3,*n4}
	}
	nodes.clear();
	//nodes={}
}

void Game::run()
{
	bool shouldRunGame = menuChoice();
	if (shouldRunGame) {
		int pass = 0;
		do {
			system("cls"); //clear screen
			current->print();
			char choiceChar;
			cin >> choiceChar;
			if (choiceChar == 's' || choiceChar == 'S') {
				save();
				continue;
			}
			if (choiceChar == 'e') {
				cout << "Bye!";
				return;
			}
			if (choiceChar == 'm') {
				shouldRunGame = menuChoice();
				if (shouldRunGame)
					continue;
				else {
					cout << "Bye!";
					return;
				}
			}
			int choice = choiceChar - '0'; //wyznaczenie wartoœci liczbowej na podstawie znaku cyfry
			Node * next = current->move(choice);
			if (next == nullptr) {
				cout << "Nieprawidlowy wybor" << endl;
			}
			else {
				current = next;
				pass++;
				if (pass == 5) {
					autoSave();
					pass = 0;
				}				
			}
		} while (!current->isEnd());

		system("cls");
		current->print();
		cout << "Koniec gry";
	}
	else {
		cout << "Bye!";
	}
}