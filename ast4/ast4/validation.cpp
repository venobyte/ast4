#include "prototype.h"

using namespace std;

#define NAME_MAX 30
#define EMPTY 2

int validateName(string name)
{
	int result = 0;
	int i = 0;
	int position = 0;
	string validName = "abcdefghijklmnopqrstuvwxyz-'. ";

	if (name == "")
	{
		result = EMPTY;
	}
	else if (name.length() > NAME_MAX)
	{
		result = 1;
	}
	else if (name.find_first_not_of(validName) != string::npos)
	{
		result = 1;
	}
	
	for (i = 0; i < NAME_MAX && result != 1 && result != EMPTY; i++)
	{
		position = name.find_first_of("-'. ");
			
		if (position != string::npos)
		{
			if (name[position + 1] == '-' || name[position + 1] == '\'' || name[position +1] == '.' || name[position +1] == ' ')
			{
				result = 1;
			}
			else
			{
				name = name.substr(position + 1, name.length()-position);
			}
		}
		
	}
	return result;
}


int validateStreet(string street)
{
	return 0;
}

int validateCity(string city)
{
	return 0;
}

int validateProvince(string province)
{
	return 0;
}

int validatePostal(string postal)
{
	return 0;
}

int validatePhone(string phone)
{
	return 0;
}
