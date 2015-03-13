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

	/* Name */
	cout << "Enter Name\n:";

	cin >> input;

	validateName(input);

	/* Street */

	/* City */
	do
	{
		// Input
		cout << "City\n:";
		cin >> input;

		// Validation
		if (validateCity(input) != VALID)
		{
			char resp = '\0';
			cout << "City not valid!\n";
			cout << "Skip <y/n>? ";
			resp = _getch();
			if (resp == 'y' || resp == 'Y')
			{
				// Skip it
				break;
			}

			// Otherwise we loop back
		}
		else
		{
			// Input is good
			break;
		}
	} while (1);

	/* Province */

	/* Postal Code */

	/* Phone Number */

	return 0;
}