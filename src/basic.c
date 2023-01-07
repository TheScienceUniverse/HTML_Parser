#include "../lib/basic.h"

void display_raw_string (int length, char *address) {
	for (int i = 0; i < length; i++) {
		printf ("%c", *(address + i));
	}
}

char* char_array_to_pointer (int length, char *str) {
	char *string = (char*) malloc (length);
	string = memcpy (string, str, length);
	return string;
}