#include "prototype.h"

using namespace std;

/*
	Function: validateName
	Description: Function used to validate the name specified by the user.
	Parameters: name - input passed in from the user
	Returns: result - whether the string is empty, valid, or invalid.
*/
int validateName(string name)
{
	int result = VALID;
	int i = 0;
	int position = 0;
	string validName = "abcdefghijklmnopqrstuvwxyz-'. ";
	locale loc;

	//used to convert the string passed in to lower case
	for (i = 0; i < name.length(); i++)
	{
		try
		{
			name[i] = tolower(name[i], loc);
		}
		catch (exception& e)
		{
		}
	}

	if (name == "")
	{
		result = EMPTY;
	}
	else if (name.length() > NAME_MAX)
	{
		result = INVALID;
	}
	//checks if there is any instance of an invalid character in the name string
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
	int result = VALID;

	if (city == "")
	{
		// Field can be skipped if the first character is a character return.
		return EMPTY;
	}
	else if (city.length() > CITY_MAX)
	{
		// Too long
		result = INVALID;
	}
	else
	{
		// test each character
		for (unsigned int i = 0; i < city.length(); i++)
		{
			char chr = city.at(i);
			if (chr == ' ')
			{
				// Space
				if (i == 0)
				{
					// CANNOT start with this
					result = INVALID;
				}
				else if (city.at(i - 1) == ' ')
				{
					// CANNOT have two in a row
					result = INVALID;
				}
			}
			else if (chr == '-')
			{
				// Dash
				if (i == 0)
				{
					// CANNOT start with this
					result = INVALID;
				}
			}
			else if (chr == '.')
			{
				// Dot
				if (i == 0)
				{
					// CANNOT start with this
					result = INVALID;
				}
			}
			else if (chr >= 'A' && chr <= 'Z')
			{
				// Upper case, valid
			}
			else if (chr >= 'a' && chr <= 'z')
			{
				// Lower case, valid
			}
			else
			{
				// INVALID character
				result = INVALID;
			}
		}
	}

	return result;
}

int validateProvince(string province)
{
	int result = INVALID;
	char *kAllowedProvinces[] = ALLOWED_PROVINCES;

	if (province == "")
	{
		// Field can be skipped if first character is a character return.
		result = EMPTY;
	}
	else if (province.length() > PROVINCE_MAX)
	{
		result = INVALID;
	}
	else
	{
		// Check against the known list
		int i = 0;
		const char *str = kAllowedProvinces[i];
		while (str != NULL)
		{
			if (_stricmp(province.c_str(), str) == 0)
			{
				result = VALID;
				break;
			}

			str = kAllowedProvinces[++i];
		}
	}
	return result;
}

/*
	Function: validatePostal
	Description: Function used to validate the postal code specified by the user.
	Parameters: postal - input passed in from the user
	Returns: result - whether the string is empty, valid, or invalid.
*/
int validatePostal(string postal)
{
	int result = VALID;
	string firstValidLetter = "ABCEGHJKLMNPRSTVXY";
	string validLetter = "ABCEGHJKLMNPRSTVWXYZ";
	locale loc;

	//used to convert the string passed in to upper case
	for (int i = 0; i < postal.length(); i++)
	{
		try
		{
			postal[i] = toupper(postal[i], loc);
		}
		catch (exception& e)
		{
		}
	}

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
		//check against the valid letters for a postal code.
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
	int result = VALID;
	int i = 0;
	string validPhone = "1234567890-. ";
	string validPhoneChars = "-. ";

	if (phone == "")
	{
		result = EMPTY;
	}
	else if (phone.length() > PHONE_MAX)
	{
		result = INVALID;
	}
	else if (phone.find_first_not_of(validPhone) != string::npos)
	{
		result = INVALID;
	}
	else
	{
		for (i = 0; i < PHONE_MAX; i++)
		{
			if (isdigit(phone[i]) == false)
			{
				if (isdigit(phone[3]) == false)
				{
					if (validPhoneChars.find(phone[3]) == string::npos)
					{
						result = INVALID;
					}
					else if ((isdigit(phone[7]) == false))
					{
						if (validPhoneChars.find(phone[7]) == string::npos)
						{
							result = INVALID;
						}
					}
				}
				
			}

		}
		
	}

	return result;

}
