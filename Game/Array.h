#pragma once

#include <iostream>
using namespace std;

template<typename T>
class Array {
	T* data; //wsk na tablice z danymi
	int size; //ilosc elementow tab ktorych uzywamy
	int capacity; //calkowita pojemnosc tablicy

	//metoda prywatna
	//przealokowuje pamiec, rozszerzajac tablice 'data' x2 i zmieniajac odpowiednio 'capacity'
	/*
	{4,5,3}
	{ ,4,5,3, , }
	*/
	void realloc(int newcapacity, int offset = 0) {
		//O(capacity)
		if (data == nullptr) {
			//O(1)
			capacity = 10;
			data = new T[capacity]{};
		}
		else {
			//O(capacity)
			T* t = new T[newcapacity]{};
			for (int i = 0; i < capacity; i++) {
				t[i + offset] = data[i];
			}
			delete[] data;
			data = t;
			capacity = newcapacity;
		}
	}

public:
	//konstruktor domyœlny / bezparametrowy
	Array() {
		data = nullptr;
		size = 0;
		capacity = 0;
	}

	Array(int capacity) {
		this->data = new T[capacity]{};
		this->size = 0;
		this->capacity = capacity;
	}

	void addBack(T value) {
		if (size == capacity) {
			realloc(capacity*2);
		}
		//{2,3,2,5} size=4, cap=4, value=7
		//{2,3,2,5, , , , }
		//{2,3,2,5,7, , , }
		data[size] = value;
		size++;
		//z³o¿onoœæ O(1)
	}

	void resize(int newsize) {
		if (newsize > size) {
			if (newsize > capacity) {
				realloc(newsize);
			}
			size = newsize;
		}
	}

	void clear() {
		//{4,5,@, } size=2, cap=4
		//clear -> size=0
		//{@4,5, , }
		size = 0;
	}

	/*void prepareAdd() {
		if (size == capacity) {
			realloc();
		}
	}

	void doAdd(T value) {
		data[size] = value;
		size++;
	}*/

	void print() {
		//O(size)
		for (int i = 0; i < size; i++) {
			cout << data[i] << " ";
		}
		cout << endl;
	}

	void fill(T value) {
		//O(size)
		for (int i = 0; i < size; i++) {
			data[i] = value;
		}
	}

	int count(T value) {
		int n = 0;
		for (int i = 0; i < size; i++) {
			if (data[i] == value)
				n++;
		}
		return n;
	}



	/*
	mamy jeszcze miejsce w tab
	{1,3,5, , } value=0
	{ ,1,3,5, }
	{0,1,3,5, }
	nie mamy (1)
	{6,5,7,8}
	{6,5,7,8, , , , }
	{ ,6,5,7,8, , , }
	{0,6,5,7,8, , , }
	<8>
	1,9,5,7,0,8

	3,3,3,3


	*/
	void addFront(T value) {
		if (size == capacity) {
			realloc(capacity*2, 1);
		}
		else {
			for (int i = size - 1; i >= 0; i--) {
				data[i + 1] = data[i];
			}
		}
		data[0] = value;
		size++;

		//z³o¿onoœæ O(size)
	}

	//przesuwa o 1 miejce w prawo
	//{1,4,5,6} -> {6,1,4,5}
/*

*/
	void rotateRight() {
		T a = data[size - 1];
		for (int i = size - 2; i >= 0; i--) {
			data[i + 1] = data[i];
		}
		data[0] = a;
	}

	void rotateLeft() {
		T a = data[0];
		for (int i = 1; i < size; i++) {
			data[i - 1] = data[i];
		}
		data[size - 1] = a;
	}

	void popBack() {
		//nie musimy przealokowywac tablicy przy usuwaniu elementow
		//{8,9,0,0,1| , , }
		//popBack
		//{8,9,0,0|1, , , }
		//add 9
		//{8,9,0,0,9| , , }
		//popBack x3
		//{8,9|0,0,9, , , }
		//add 7
		//{8,9,7|0,9, , , }
		if (size > 0) {
			size--;
		}
	}

	T get(int i) {
		return data[i];
	}

	T& at(int i) {
		return data[i];
	}

	void set(int i, T value) {
		data[i] = value;
	}

	int getSize() {
		return size;
	}
};
