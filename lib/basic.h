#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

// ---------- x ----------

// updated version of free to avoid dangling pointer
#define ERASE(address) {\
	free (*address);\
	*address = NULL;\
}

// ---------- x ----------

void display_raw_string (int length, char *address);				// prints string // takes length and address pointer
char* char_array_to_pointer (int length, char *address);			// converts character array to string object

#endif