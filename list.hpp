//task 3
#include <vector>
#include <string>
#include <cstdio>
#include <fstream>
#include <random>
#include <iostream>

using namespace std;
// структуру ListNode модифицировать нельзя
struct ListNode {
	ListNode* prev;
	ListNode* next;
	ListNode* rand; // указатель на произвольный элемент данного списка, либо NULL
	std::string data;
};

class List {
public:
	List();

	void Serialize(FILE* file);   // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
	void Deserialize(FILE* file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

	void pushBack(const string value); //добавление элементов
	void pushFront(const string value);
	void printList();	
	int getCount() { return this->count_; }

private:
	ListNode* pushBack_(const string value); //добавление элемента без связи rand
	//ListNode* pushFront_(string value);

	void setRand_(ListNode* node); //присвоение новому узлу случайной связи rand (для тестирования)

	void setHead_(ListNode* newHead) { this->head_ = newHead; }
	void setTail_(ListNode* newTail) { this->tail_ = newTail; }
	void setRand_(ListNode* nodeBase, ListNode* toRand) { nodeBase->rand = toRand; } //установка ссылки rand

	ListNode* getHead_() { return this->head_; }
	ListNode* getTail_() { return this->tail_; }

	int getId_(const ListNode* node); //вспомогательная функция для восстановления связей rand при десериализации


	ListNode* head_;
	ListNode* tail_;
	int count_;
};

