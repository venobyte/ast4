#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>
#include <algorithm>

#define NAME_MAX 30
#define VALID 0
#define INVALID  1
#define EMPTY 2
#define POSTAL_MAX 7
#define PHONE_MAX 15
#define CITY_MAX 60
#define PROVINCE_MAX 2
#define STREET_MAX 60
#define ESC 27

// All allowed provinces, terminated with NULL
#define ALLOWED_PROVINCES {"ON", "BC", "QC", "AB", "MB", "NB", "NL", "NS", "NT", "NU", "PE", "SK", "YT", NULL}
// All allowed street types
#define ALLOWED_STREETS {"Road", "RD", "Rd.", "Street", "ST", "St.", "Avenue", "AV", "Ave.", "Circle", "CIR", "Circ.",\
						 "Boulevard", "BLVD", "Blvd.", "Lane", "Ln.", "Court", "CT", "Ct."}
// Valid directions
#define DIRECTIONS {'N', 'E', 'S', 'W'}

using namespace std;

struct results{
	int result = INVALID;
	string error;
};

results validateName(string name);
results validateStreet(string street);
results validateCity(string city);
results validateProvince(string province);
results validatePostal(string postal);
results validatePhone(string phone, string province);
