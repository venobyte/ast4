/*
	User Input Validation
	Authors: Oliver Sousa, Aric Vogel, Joshua Medeiros, Kyle Eaton
	Date: 03-13-15
	Description: To validate user input and display the input information to the user.
*/

#include "prototype.h"
#include <conio.h>

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

	int result = INVALID;
	int end = 0;
	int i = 0;
	int j = 0;

	locale loc;
	string input;

	cout << "Logo\n";

	while (end == 0 && i != 10)
	{
		while (result == INVALID)
		{

			cout << "Enter name : \n";
			getline(cin, input);

			result = validateName(input);

			if (result == EMPTY)
			{
				end = 1;
			}
			else if (result == INVALID)
			{
				cout << "The name you entered is invalid. (Press enter if you wish to finish input)\n";
			}
			else if (result == VALID)
			{
				infos[i].name.assign(input);
			}
		}

		result = INVALID;

		if (end == 0)
		{

			while (result == INVALID)
			{
				cout << "Enter street address : \n";
				getline(cin, input);

				result = validateStreet(input);

				if (result == EMPTY)
				{
					infos[i].street.assign("");
				}
				else if (result == INVALID)
				{
					cout << "The street you entered is invalid. (Press enter if you wish to skip)\n";
				}
				else if (result == VALID)
				{
					infos[i].street.assign(input);
				}
			}

			result = INVALID;

			while (result == INVALID)
			{
				cout << "Enter city : \n";
				getline(cin, input);

				result = validateCity(input);

				if (result == EMPTY)
				{
					infos[i].city.assign("");
				}
				else if (result == INVALID)
				{
					cout << "The city you entered is invalid. (Press enter if you wish to skip)\n";
				}
				else if (result == VALID)
				{
					infos[i].city.assign(input);
				}
			}

			result = INVALID;

			while (result == INVALID)
			{
				cout << "Enter province : \n";
				getline(cin, input);

				result = validateProvince(input);

				if (result == EMPTY)
				{
					infos[i].province.assign("");
				}
				else if (result == INVALID)
				{
					cout << "The province you entered is invalid. (Press enter if you wish to skip)\n";
				}
				else if (result == VALID)
				{
					//this will change the province to upper case.
					for (j = 0; j < input.length(); j++)
					{
						input[j] = toupper(input[j], loc);
					}

					infos[i].province.assign(input);
				}
			}

			result = INVALID;

			while (result == INVALID)
			{
				cout << "Enter postal code : \n";
				getline(cin, input);

				result = validatePostal(input);

				if (result == EMPTY)
				{
					infos[i].postal.assign("");
				}
				else if (result == INVALID)
				{
					cout << "The postal code you entered is invalid. (Press enter if you wish to skip)\n";
				}
				else if (result == VALID)
				{

					//this will change the postal code to upper case.
					for (j = 0; j < input.length(); j++)
					{
						input[j] = toupper(input[j], loc);
					}

					infos[i].postal.assign(input);
				}
			}

			result = INVALID;

			while (result == INVALID)
			{
				cout << "Enter phone number : \n";
				getline(cin, input);

				result = validatePhone(input);

				if (result == EMPTY)
				{
					infos[i].phone.assign("");
				}
				else if (result == INVALID)
				{
					cout << "The phone number entered is invalid. (Press enter if you wish to skip)\n";
				}
				else if (result == VALID)
				{
					infos[i].phone.assign(input);
				}
			}

			result = INVALID;

			i++;
		}

	}

	end = i;
	cout << string(50, '\n');

	if (infos[0].name == "")
	{
		cout << "There are no entries\n";
	}
	else
	{
		while (result == INVALID)
		{

			for (i = 0; i != end && result == INVALID; i++)
			{
				if (result == INVALID)
				{
					try
					{
						cout << infos[i].name << "\n";
						cout << infos[i].street << "\n";
						cout << infos[i].city << ", ";
						cout << infos[i].province << ", ";
						cout << infos[i].postal << "\n";
						cout << infos[i].phone << "\n";
						cout << "++++++++++++" << "\n\n";
					}
					catch (exception& e)
					{
					}
				}

				//this will paginate the output, limiting to 3 entries on the page at a time.
				if (i == 2 || i == 5 || i == 8 || i == (end - 1))
				{
					cout << "Press any button to cycle through entries or press ESC to exit\n";

					j = _getch();

					//if the user enters escape this will end the program
					if (j == ESC)
					{
						result = VALID;
						i = end;
					}
					else
					{
						//trying to avoid the use of system.
						cout << string(50, '\n');
					}
				}
			}

		}
	}

	return 0;
}