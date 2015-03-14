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
	//checks to see if the first letter is non-alphabetical
	else if (name[0] == '-' || name[0] == '\'' || name[0] == '.' || name[0] == ' ')
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

/*
Function: validatePhone
Description: Function used to validate the phone number specified by the user.
Parameters: phone - input passed in from the user province - province the user has set
Returns: result - whether the string is empty, valid, or invalid.
*/
int validatePhone(string phone, string province)
{
	int result = VALID;
	int i = 0;
	string validPhone = "1234567890-. ()";
	string validPhoneChars = "-.";
	string areaCode = "   ";
	
	
	//is phone string empty
	if (phone == "")
	{
		//we can skip if phone number is empty
		result = EMPTY;
	}
	//is phone number too long
	else if (phone.length() > PHONE_MAX)
	{
		//too long has to invalid
		result = INVALID;
	}
	//check to make sure everything is valid before we even break it down
	else if (phone.find_first_not_of(validPhone) != string::npos)
	{
		//if something not valid exists in number we dont need to continue
		result = INVALID;
	}

	//is user using brackets for area code
	else if (phone[0] == '(')
	{
		//then lets make sure next three numbers are digits
		for (i = 1; i < 4; i++)
		{
			if (isdigit(phone[i]) == false)
			{
				//the area code is not digits is invalid
				result = INVALID;
			}
			// make sure space is after area code
			else if (isspace(phone[5]) == false)
			{
				result = INVALID;
			}

			//lets make sure that closing bracket is there
			else if (phone[4] != ')')
			{
				

				//we know this part so far is valid lets take the area code
				areaCode = phone.substr(1, 3);

				//next three elements after space should be digits 
				for (i = 0; i < 3; i++)
				{
					//if they are not digits its invalid
					if (isdigit(phone[i + 6]) == false)
					{
						result = INVALID;
					}
				}
				//next digit can contain peroid dash or any number check for number first
				if (isdigit(phone[9]) == false)
				{
					//not a number so make sure its valid
					if (validPhoneChars.find(phone[9]) == string::npos)
					{
						//not valid
						result = INVALID;
					}
					//if we get here we know it is a valid character and we can continue
					else
					{
						//make sure last 4 digits are numbers
						for (i = 0; i < 4; i++)
						{
							//if they are not it is invalid
							if (isdigit(phone[i + 10]) == false)
							{
								result = INVALID;
							}
						}
					}

				}
				//is a number check last 4 elements to make sure all digits
				else
				{
					for (i = 0; i < 4; i++)
					{
						//if they are not it is invalid
						if (isdigit(phone[i + 9]) == false)
						{
							result = INVALID;
						}
					}
				}
			}

		}
	}
	//if we get this far we know the area code is first three numbers
	else
	{
		//seperate area code for validation
		areaCode = phone.substr(0, 3);

		//next number can be a special character or a number
		if (isdigit(phone[3]) == false)
		{
			//not a number lets make sure valid
			if (validPhoneChars.find(phone[3]) == string::npos)
			{
				//not Valid
				result = INVALID;
			}
			//if we get here it is a valid character
			else
			{
				//next three numbers should be digits
				for (i = 0; i < 3; i++)
				{
					if (isdigit(phone[i + 4]) == false)
					{
						//not all digits this is invalid
						result = INVALID;
					}
				}
				//next digit must be a character to match format
				if (validPhoneChars.find(phone[7]) == string::npos)
				{
					//format is  not consistant we cant use this
					result = INVALID;
					
				}


			}
		}
		//is a digit
		else
		{
			printf("stuck\n");


			//rest of numbers up to point must all be digits to follow format
			for (i = 0; i < 7; i++)
			{
				if (isdigit(phone[i + 2]) == false)
				{
					//rest are not digits invalid
					result = INVALID;
				}

			}

			//phone number format is valid

		}

	}

	//Area code handling
if (province == "ON")
	{
		if (areaCode == "226")
		{
		}
		else if (areaCode == "249")
		{
		}
		else if (areaCode == "289")
		{
		}
		else if (areaCode == "343")
		{
		}
		else if (areaCode == "365")
		{
		}
		else if (areaCode == "416")
		{
		}
		else if (areaCode == "437")
		{
		}
		else if (areaCode == "519")
		{
			printf("correct area code");
		}
		else if (areaCode == "613")
		{
		}
		else if (areaCode == "647")
		{
		}
		else if (areaCode == "705")
		{
		}
		else if (areaCode == "807")
		{
		}
		else if (areaCode == "905")
		{
		}
		else
		{
			result = INVALID;
		}
		
	}
	else if (province == "QC")
	{

		if (areaCode == "418")
		{
		}
		else if (areaCode == "438")
		{
		}
		else if (areaCode == "450")
		{
		}
		else if (areaCode == "514")
		{
		}
		else if (areaCode == "579")
		{
		}
		else if (areaCode == "581")
		{
		}
		else if (areaCode == "819")
		{
		}
		else if (areaCode == "873")
		{
		}
		else
		{
			result = INVALID;
			
		}
	}
	else if (province == "BC")
	{

		if (areaCode == "236")
		{
		}
		else if (areaCode == "250")
		{
		}
		else if (areaCode == "604")
		{
		}
		else if (areaCode == "778")
		{
		}		
		else
		{
			result = INVALID;
		
		}
	}
	else if (province == "AB")
	{

		if (areaCode == "403")
		{
		}
		else if (areaCode == "587")
		{
		}
		else if (areaCode == "780")
		{
		}	
		else
		{
			result = INVALID;

		}
	}
	else if (province == "MB")
	{

		if (areaCode == "204")
		{
		}
		else if (areaCode == "431")
		{
		}
		else
		{
			result = INVALID;
		}
	}
	else if (province == "SK")
	{

		if (areaCode == "306")
		{
		}
		else if (areaCode == "639")
		{
		}
		else
		{
			result = INVALID;
		}
	}
	else if (province == "PE")
	{

		if (areaCode == "902")
		{
		}
		else if (areaCode == "782")
		{
		}
		else
		{
			result = INVALID;
		}
	}
	else if (province == "NB")
	{
		if (areaCode != "506")
		{
			result = INVALID;
		
		}
	}
	else if (province == "NL")
	{
		if (areaCode != "709")
		{
			result = INVALID;
		
		}
	}
	else if (province == "NS")
	{
		if (areaCode != "902")
		{
			result = INVALID;
			
		}
	}
	else if (province == "YT")
	{
		if (areaCode != "867")
		{
			result = INVALID;
			
		}
	}
	else if (province == "NU")
	{
		if (areaCode != "867")
		{
			result = INVALID;
			
		}
	}
	else if (province == "NT")
	{
		if (areaCode != "867")
		{
			result = INVALID;
			
		}
	}

		return result;
}

