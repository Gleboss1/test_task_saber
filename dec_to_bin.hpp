//task 1
#include "math.h"
#include <stack>

using namespace std;

void printBin(int decValue)
{
	stack <int> buffer;
	const bool sign = decValue < 0 ? 0 : 1;
	cout << "decimal " << decValue << " in binary = ";

	if (decValue == 0)
	{
		cout << 0 << endl;
		return;
	}

	while (decValue != 0)
	{
		buffer.push(abs(decValue % 2));
		decValue /= 2;
	}

	if (!sign) cout << "-";

	while (!buffer.empty())
	{
		cout << buffer.top();
		buffer.pop();
	}
	cout << endl;
}