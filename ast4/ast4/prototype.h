#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#define NAME_MAX 30
#define VALID 0
#define INVALID  1
#define EMPTY 2
#define POSTAL_MAX 7
#define PHONE_MAX 15
#define CITY_MAX 60
#define PROVINCE_MAX 2
#define ESC 27

using namespace std;

int validateName(string name);
int validateStreet(string street);
int validateCity(string city);
int validateProvince(string province);
int validatePostal(string postal);
int validatePhone(string phone, string province);
