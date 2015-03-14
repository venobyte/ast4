#include "validation.h"

using namespace std;

/*
	Function: validateName
	Description: Function used to validate the name specified by the user.
	Parameters: name - input passed in from the user
	Returns: result - whether the string is empty, valid, or invalid.
*/
results validateName(string name)
{
	struct results result;
	result.result = VALID;
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
		result.result = EMPTY;
	}
	else if (name.length() > NAME_MAX)
	{
		result.result = INVALID;
		result.error = "Name is to long.\n";
	}
	//checks to see if the first letter is non-alphabetical
	else if (name[0] == '-' || name[0] == '\'' || name[0] == '.' || name[0] == ' ')
	{
		result.result = INVALID;
		result.error = "Name can't begin with non-alphabetic.\n";
	}
	//checks if there is any instance of an invalid character in the name string
	else if (name.find_first_not_of(validName) != string::npos)
	{
		result.result = INVALID;
		result.error = "Name has an invalid character, can only be letters, apostrophes, dashes, spaces, and periods.\n";
	}
	
	for (i = 0; i < NAME_MAX && result.result != INVALID && result.result != EMPTY; i++)
	{
		position = name.find_first_of("-'. ");
			
		if (position != string::npos)
		{
			if (name[position + 1] == '-' || name[position + 1] == '\'' || name[position + 1] == '.' || name[position + 1] == ' ')
			{
				result.result = INVALID;
				result.error = "Can't have more than one non-alphabetic character continuosly.\n";
			}
			else
			{
				name = name.substr(position + 1, name.length()-position);
			}
		}
		
	}
	return result;
}

/*
	Function: validateStreet
	Description: Function used to validate the street specified by the user.
	Parameters: street - input passed in from the user
	Returns: result - whether the string is empty, valid, or invalid.
*/
results validateStreet(string street)
{
	struct results result;
	result.result = VALID;
	char *kAllowedStreets[] = ALLOWED_STREETS;
	char kDirections[] = DIRECTIONS;
	string unit;
	int house = 0;

	if (street == "") {
		result.result = EMPTY;
	} else if (street.length() > STREET_MAX) {
		result.result = INVALID;
		result.error = "Street name is too long\n";
	} else {
		istringstream ss(street);
		// Separate the string by spaces and put into a vector
		vector<string> parts{istream_iterator<string>{ss}, istream_iterator<string>{}};
		size_t found = 0;

		if (street.at(0) == ' ' || parts.size() < 3 || parts.size() > 4) {
			result.result = INVALID;
			result.error = "Invalid street number\n";
		} else {
			// Parse the house unit and number
			ss.clear();
			ss.str(parts[0]);
			if ((found = parts[0].find('-')) != string::npos && found != 0) {\
				unit = parts[0].substr(0, found);
				ss.str(parts[0].substr(found + 1));
			}

			if (!(ss >> house) || house < 0) {
				result.result = INVALID;
			}

			// Make sure the street name only includes valid characters
			for (int i = 0; i < parts[1].length(); i++) {
				char c = parts[1].at(i);
				if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && c != '\'' && c != '-') {
					result.result = INVALID;
					result.error = "Invalid characters in street name.\n";
					break;
				}
			}

			bool valid_street = false;
			for (int i = 0; i < sizeof(kAllowedStreets)/sizeof(*kAllowedStreets); i++) {
				if (parts[2] == kAllowedStreets[i]) {
					valid_street = true;
					break;
				}
			}

			if (!valid_street) {
				result.result = INVALID;
				result.error = "Invalid street type.\n";
			}

			// If specified, check that the direction is valid
			if (parts.size() == 4) {
				bool valid_direction = false;

				// Must be a valid direction and can only be followed by a '.' or nothing
				if (parts[3].length() == 1 || (parts[3].length() == 2 && parts[3].at(1) == '.')) {
					for (int i = 0; i < sizeof(kDirections); i++) {
						if (parts[3].at(0) == kDirections[i]) {
							valid_direction = true;
							break;
						}
					}
				}

				if (!valid_direction) {
					result.result = INVALID;
					result.error = "Invalid street direction.\n";
				}
			}
		}
	}

	return result;
}

/*
	Function: validateCity
	Description: Function used to validate the city specified by the user.
	Parameters: city - input passed in from the user
	Returns: result - whether the string is empty, valid, or invalid.
*/
results validateCity(string city)
{
	struct results result;
	result.result = VALID;

	if (city == "")
	{
		// Field can be skipped if the first character is a character return.
		result.result = EMPTY;
	}
	else if (city.length() > CITY_MAX)
	{
		// Too long
		result.result = INVALID;
		result.error = "City name too long.\n";
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
					result.result = INVALID;
					result.error = "Can't start with a space.\n";
				}
				else if (city.at(i - 1) == ' ')
				{
					// CANNOT have two in a row
					result.result = INVALID;
					result.error = "Can't have two spaces in a row\n";
				}
			}
			else if (chr == '-')
			{
				// Dash
				if (i == 0)
				{
					// CANNOT start with this
					result.result = INVALID;
					result.error = "Can't start with a -\n";
				}
			}
			else if (chr == '.')
			{
				// Dot
				if (i == 0)
				{
					// CANNOT start with this
					result.result = INVALID;
					result.error = "Can't start with a period.\n";
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
				result.result = INVALID;
				result.error = "City must only consist of letters, spaces, dashes, and periods.\n";
			}
		}
	}

	return result;
}

/*
	Function: validateProvince
	Description: Function used to validate the province specified by the user.
	Parameters: province- input passed in from the user
	Returns: result - whether the string is empty, valid, or invalid.
*/
results validateProvince(string province)
{
	struct results result;
	result.result = INVALID;
	char *kAllowedProvinces[] = ALLOWED_PROVINCES;

	if (province == "")
	{
		// Field can be skipped if first character is a character return.
		result.result = EMPTY;
	}
	else if (province.length() > PROVINCE_MAX)
	{
		result.result = INVALID;
		result.error = "Province can only be 2 characters long.\n";
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
				result.result = VALID;
				break;
			}

			str = kAllowedProvinces[++i];
		}
	}
	result.error = "Province does not exist.\n";
	return result;
}

/*
	Function: validatePostal
	Description: Function used to validate the postal code specified by the user.
	Parameters: postal - input passed in from the user
	Returns: result - whether the string is empty, valid, or invalid.
*/
results validatePostal(string postal)
{
	struct results result;
	result.result = VALID;
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
		result.result = EMPTY;
	}
	else if (postal.length() > POSTAL_MAX)
	{
		result.result = INVALID;
		result.error = "Postal code is too long.\n";
	}
	else
	{
		//check against the valid letters for a postal code.
		if (firstValidLetter.find(postal[0]) == string::npos)
		{
			result.result = INVALID;
			result.error = "First character must be a letter and not be D, F, I, O, Q, U, W, or Z\n";
		}
		else if (isdigit(postal[1]) == false)
		{
			result.result = INVALID;
			result.error = "Second character must be a number\n";
		}
		else if (validLetter.find(postal[2]) == string::npos)
		{
			result.result = INVALID;
			result.error = "Third character must be a letter and not be D, F, I, O, Q, or U\n";
		}

		if (postal.length() == POSTAL_MAX && result.result != INVALID)
		{
			if (postal[3] == ' ')
			{
				postal = postal.substr(4, 3);
			}
			else
			{
				result.result = INVALID;
				result.error = "There must be a space in the middle.\n";
			}
		}
		else if (postal.length() == (POSTAL_MAX - 1) && result.result != INVALID)
		{
			postal = postal.substr(3, 3);
		}

		if (result.result != INVALID && isdigit(postal[0]) == false)
		{
			result.result = INVALID;
			result.error = "The Fourth character must be a number\n";
		}
		else if (result.result != INVALID && validLetter.find(postal[1]) == string::npos)
		{
			result.result = INVALID;
			result.error = "The Fifth character must be a letter and not be D, F, I, O, Q, or U\n";
		}
		else if (result.result != INVALID && isdigit(postal[2]) == false)
		{
			result.result = INVALID;
			result.error = "The last character must be a number\n";
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
results validatePhone(string phone, string province)
{
	struct results result;
	result.result = VALID;
	int i = 0;
	string validPhone = "1234567890-. ()";
	string validPhoneChars = "-.";
	string areaCode = "   ";
	
	
	//is phone string empty
	if (phone == "")
	{
		//we can skip if phone number is empty
		result.result = EMPTY;
	}
	//is phone number too long
	else if (phone.length() > PHONE_MAX)
	{
		//too long has to invalid
		result.result = INVALID;
		result.error = "Phone number is too long\n";
	}
	//check to make sure everything is valid before we even break it down
	else if (phone.find_first_not_of(validPhone) != string::npos)
	{
		//if something not valid exists in number we dont need to continue
		result.result = INVALID;
		result.error = "There is an invalid character in the phone number\n";
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
				result.result = INVALID;
				result.error = "There area is not comprised of all numbers\n";
			}
			// make sure space is after area code
			else if (isspace(phone[5]) == false)
			{
				result.result = INVALID;
				result.error = "There is no space after the area code\n";
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
						result.result = INVALID;
						result.error = "The first three characters after the area code are not digits\n";
					}
				}
				//next digit can contain peroid dash or any number check for number first
				if (isdigit(phone[9]) == false)
				{
					//not a number so make sure its valid
					if (validPhoneChars.find(phone[9]) == string::npos)
					{
						//not valid
						result.result = INVALID;
						result.error = "The character after the first 3 digits after the area code is not valid\n";
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
								result.result = INVALID;
								result.error = "The last four characters are not digits\n";
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
							result.result = INVALID;
							result.error = "The last four characters are not digits\n";
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
				result.result = INVALID;
				result.error = "The character after the area code is not valid\n";
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
						result.result = INVALID;
						result.error = "The characters after the area code are not digits\n";
					}
				}
				//next digit must be a character to match format
				if (validPhoneChars.find(phone[7]) == string::npos)
				{
					//format is  not consistant we cant use this
					result.result = INVALID;
					result.error = "The next character is not a digit, format is not consistent\n";			
				}

			}
		}
		//is a digit
		else
		{

			//rest of numbers up to point must all be digits to follow format
			for (i = 0; i < 7; i++)
			{
				if (isdigit(phone[i + 2]) == false)
				{
					//rest are not digits invalid
					result.result = INVALID;
					result.error = "Phone number is not comprised of just digits.\n";
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
			result.result = INVALID;
			result.error = "Area code does not belong to ON.\n";
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
			result.result = INVALID;
			result.error = "Area code does not belong to QC.\n";
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
			result.result = INVALID;
			result.error = "Area code does not belong to BC.\n";
		
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
			result.result = INVALID;
			result.error = "Area code does not belong to AB.\n";

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
			result.result = INVALID;
			result.error = "Area code does not belong to MB\n";
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
			result.result = INVALID;
			result.error = "Area code does not belong to SK\n";
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
			result.result = INVALID;
			result.error = "Area code does not belong to PE\n";
		}
	}
	else if (province == "NB")
	{
		if (areaCode != "506")
		{
			result.result = INVALID;
			result.error = "Area code does not belong to NB\n";
		}
	}
	else if (province == "NL")
	{
		if (areaCode != "709")
		{
			result.result = INVALID;
			result.error = "Area code does not belong to NL\n";
		
		}
	}
	else if (province == "NS")
	{
		if (areaCode != "902")
		{
			result.result = INVALID;
			result.error = "Area code does not belong to NS\n";
			
		}
	}
	else if (province == "YT")
	{
		if (areaCode != "867")
		{
			result.result = INVALID;
			result.error = "Area code does not belong to YT\n";
			
		}
	}
	else if (province == "NU")
	{
		if (areaCode != "867")
		{
			result.result = INVALID;
			result.error = "Area code does not belong to NU\n";
			
		}
	}
	else if (province == "NT")
	{
		if (areaCode != "867")
		{
			result.result = INVALID;
			result.error = "Area code does not belong to NT\n";
			
		}
	}

		return result;
}

