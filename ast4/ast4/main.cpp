#include "prototype.h"

using namespace std;

int main(void)
{
	struct info{
		string name;
		string street;
		string city;
		string province;
		string postal;
		string phone;
	};

	struct info infos[10];

	string input;
	cout << "Logo\n";
	cout << "Enter Name\n:";

	cin >> input;

	validateName(input);

	return 0;
}