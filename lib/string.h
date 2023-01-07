#ifndef STRING_H
#define STRING_H

#include "./basic.h"

// ---------- x ----------

typedef struct STRING {
	int length;
	char* address;
} String;

// ---------- x ----------

String* create_string (int length, char *address);			// creates string object // pass NULL as argument if empty string to be created
String* duplicate_string (String *string);
void delete_string (String **string_address);				// frees string object from memory
void display_string (String *string);						// prints only string part
void display_string_properties (String *string);			// prints whole description
void concatenate_strings (int input_count, ...);			// concatenates multiple string objects
bool are_strings_equal (String *string1, String *string2);	// checks if strings are same by value or not, does not check by address

#endif