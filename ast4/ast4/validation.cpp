#include "prototype.h"

using namespace std;

int validateName(string name)
{
	int result = VALID;
	int i = 0;
	int position = 0;
	string validName = "abcdefghijklmnopqrstuvwxyz-'. ";

	if (name == "")
	{
		result = EMPTY;
	}
	else if (name.length() > NAME_MAX)
	{
		result = INVALID;
	}
	else if (name.find_first_not_of(validName) != string::npos)
	{
		result = INVALID;
	}
	
	for (i = 0; i < NAME_MAX && result != INVALID && result != EMPTY; i++)
	{
		position = name.find_first_of("-'. ");
			
		if (position != string::npos)
		{
			if (name[position + 1] == '-' || name[position + 1] == '\'' || name[position + 1] == '.' || name[position + 1] == ' ')
			{
				result = INVALID;
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
	int result = VALID;
	string firstValidLetter = "ABCEGHJKLMNPRSTVXY";
	string validLetter = "ABCEGHJKLMNPRSTVWXYZ";

	if (postal == "")
	{
		result = EMPTY;
	}
	else if (postal.length() > POSTAL_MAX)
	{
		result = 1;
	}
	else
	{

		if (firstValidLetter.find(postal[0]) == string::npos)
		{
			result = INVALID;
		}
		else if (isdigit(postal[1]) == false)
		{
			result = INVALID;
		}
		else if (validLetter.find(postal[2]) == string::npos)
		{
			result = INVALID;
		}

		if (postal.length() == POSTAL_MAX && result != INVALID)
		{
			if (postal[3] == ' ')
			{
				postal = postal.substr(4, 3);
			}
			else
			{
				result = INVALID;
			}
		}
		else if (postal.length() == (POSTAL_MAX - 1) && result != INVALID)
		{
			postal = postal.substr(3, 3);
		}

		if (result != INVALID && isdigit(postal[0]) == false)
		{
			result = INVALID;
		}
		else if (result != INVALID && validLetter.find(postal[1]) == string::npos)
		{
			result = INVALID;
		}
		else if (result != INVALID && isdigit(postal[2]) == false)
		{
			result = INVALID;
		}

	}

	return result;
}

int validatePhone(string phone)
{
	return 0;
}
