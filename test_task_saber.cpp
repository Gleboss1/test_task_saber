#include "test_task_saber.hpp"

using namespace std;

void Test1()
{
	cout << "testing task 1:" << endl;
	printBin(56);
	printBin(-5788786);
	printBin(0);
	printBin(-1);
	printBin(1);
	printBin(INT_MAX);
	printBin(INT_MIN);
	cout << endl;
}

void Test2()
{
	char data[] = "AAA BBB AAA";
	RemoveDups(data);
	printf("%s\n", data); // “A B A”

	char data2[] = "";
	RemoveDups(data2);
	printf("%s\n", data2); // “”

	char data3[] = "AAAAAAAAA";
	RemoveDups(data3);
	printf("%s\n", data3); // “A”
}


void Test3()
{
	//создаем тестовый лист
	List list;
	list.pushBack("abc");
	list.pushFront("def");
	list.pushBack("ooo");
	list.pushBack("lol");
	list.pushBack("789");
	list.pushBack("elif");
	list.pushBack("for");
	list.pushFront("gamedev");

	cout << "List 1:" << endl;
	list.printList();

	char path[] = "file";
	FILE* file;

	//serialization
	if ((file = fopen(path, "wb")) == NULL)
	{
		cout << "can't open file for serialization" << endl;
	}

	list.Serialize(file);
	fclose(file);



	//deserialization
	//создаем новый лист и восстанавливаем туда данные из файла
	List list2;
	if ((file = fopen(path, "rb")) == NULL)
	{
		cout << "can't open file for deserialization" << endl;
	}

	list2.Deserialize(file);
	fclose(file);

	cout << "\nList 2:" << endl;
	list2.printList();
}

int main()
{
	//Test1();

	//Test2();

	Test3();

	return 0;
}
