#include "list.hpp"

void List::pushBack(const string value)
{
	ListNode* newNode = new ListNode();
	newNode->data = value;

	if (count_ == 0)
	{
		setHead_(newNode);
		newNode->next = NULL;
		newNode->prev = NULL;
		newNode->rand = NULL;
	}
	else
	{
		newNode->prev = getTail_();
		getTail_()->next = newNode;
	}

	setTail_(newNode);
	this->count_++;

	//создаем связь rand для полноты картины
	setRand_(newNode);
}

ListNode* List::pushBack_(const string value)
{
	ListNode* newNode = new ListNode();
	newNode->data = value;

	if (count_ == 0)
	{
		setHead_(newNode);
		newNode->next = NULL;
		newNode->prev = NULL;
		newNode->rand = NULL;
	}
	else
	{
		newNode->prev = getTail_();
		getTail_()->next = newNode;
	}

	setTail_(newNode);
	this->count_++;

	return newNode;
}

void List::pushFront(const string value)
{
	ListNode* newNode = new ListNode();
	newNode->data = value;

	if (count_ == 0)
	{
		setTail_(newNode);
		newNode->next = NULL;
		newNode->prev = NULL;
		newNode->rand = NULL;
	}
	else
	{
		newNode->next = getHead_();
		getHead_()->prev = newNode;
	}

	setHead_(newNode);
	this->count_++;

	setRand_(newNode);
}

void List::setRand_(ListNode* node)
{
	ListNode* tempNode = getHead_();
	if (tempNode->next == NULL)
	{
		node->rand = NULL;
		return;
	}

	random_device rd;   //рандомайзер (нормальный)
	mt19937 gen(rd());
	const int randNum = (gen() % getCount()) -1; //randNum = -1 ... count-2

	if (randNum == -1) // -1 означает rand связь NULL
	{
		node->rand = NULL;
		return;
	}

	for (int i = 0; i < randNum; i++)
		tempNode = tempNode->next;
	node->rand = tempNode;
}

// номер узла в листе, начинается с 0
int List::getId_(const ListNode* node)
{
	if (node == NULL) return -1;

	ListNode* tempNode = this->getHead_();
	int id = 0;

	while (tempNode != node)
	{
		if (tempNode == NULL) break;

		id++;
		tempNode = tempNode->next;
	}

	return id;
}

//вывод листа в консоль и данные о rand элементах узлов (для проверки)
void List::printList()
{
	ListNode* tempHead = getHead_();
	cout << "list count: " << this->getCount() << endl;

	while (tempHead != NULL)
	{
		cout << "data: " << tempHead->data;

		if (tempHead->rand == NULL)
			cout << " | rand ref is NULL" << endl;
		else
			cout << " | data rand ref: " << tempHead->rand->data << " | ID: " << this->getId_(tempHead->rand) << endl;

		tempHead = tempHead->next;
	}
}

List::List()
{
	count_ = 0;
	ListNode* root = new ListNode();
	setHead_(root);
	setTail_(root);
}

//Записываем data узла и id узла связи rand, разделяются пробелом. Разные узлы разделяются \n
void List::Serialize(FILE* file)
{
	ListNode* tempHead = getHead_();
	string tempString = "";

	while (tempHead != NULL)
	{
		tempString = tempHead->data; //add data to string
		tempString += ' ' + to_string(getId_(tempHead->rand)) + '\n'; //add ID of random node to file
		fputs(tempString.c_str(), file);

		tempHead = tempHead->next;
	}
}


void List::Deserialize(FILE* file)
{
	string nodeData = "";
	string nodeRandId = "";
	vector <ListNode*> nodes;
	vector <int> nodesRandId;

	//находим кол-во символов в файле
	fseek(file, 0, SEEK_END);
	const size_t size = ftell(file);  
	rewind(file);

	//считываем данные из файла
	char* data = new char[size];
	fread(data, 1, size, file);   

	int counterChar = 0;
	int counterNode = 0;


	while (counterChar < size)
	{
		//считываем data узла
		while (data[counterChar] != ' ')
		{
			nodeData += data[counterChar];
			counterChar++;
		}

		counterChar++;

		//считываем ID узла связи rand
		while (data[counterChar] != '\n')
		{
			nodeRandId += data[counterChar];
			counterChar++;
		}

		counterChar++;

		//восстанавливаем ущел
		nodes.push_back(this->pushBack_(nodeData));
		
		nodesRandId.push_back(stoi(nodeRandId));
		nodeData = "";
		nodeRandId = "";
		counterNode++;
	}

	//восстанавливаем связи rand для каждого узла в соответсивии в ID
	for (int i = 0; i< counterNode; i++)
	{
		if (nodesRandId.at(i) == -1)
			setRand_(nodes.at(i), NULL);
		else 
			setRand_(nodes.at(i), nodes.at(nodesRandId.at(i)));
	}

	delete[] data;
}

