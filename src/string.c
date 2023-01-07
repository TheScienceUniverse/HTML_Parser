#include "../lib/string.h"

String* create_string (int length, char *str) {
	String *string = (String*) malloc (sizeof (String));

	if (string != NULL) {
		string -> length = 0;
		string -> address = NULL;
	}

	if (length > 0 && str != NULL) {
		string -> length = length;
		string -> address = malloc (length);

		if (string -> address != NULL) {
			string -> address = char_array_to_pointer (length, str);
		}
	}

	return string;
}

String* duplicate_string (String *old_string) {
	if (old_string == NULL) {
		return NULL;
	}

	String *new_string = (String*) malloc (sizeof (String));

	if (new_string != NULL) {
		new_string -> length = 0;
		new_string -> address = NULL;
	}

	if (old_string -> length > 0 && old_string -> address != NULL) {
		new_string -> length = old_string -> length;
		new_string -> address = malloc (old_string -> length);

		if (new_string -> address != NULL) {
			new_string -> address = memcpy (new_string -> address, old_string -> address, new_string -> length);
		}
	}

	return new_string;
}

void delete_string (String **string_address) {
	if (*string_address == NULL) {
		// perror ("String is empty to delete!");
		return;
	}

	String *string = *string_address;

	if (string -> address != NULL) {
		ERASE (&string -> address);
	}

	string = NULL;
	ERASE (string_address);
}

void display_string_properties (String *string) {
	printf ("String [%d]: ", string -> length);
	display_string (string);
	printf ("\n");
}

void display_string (String *string) {
	if (string == NULL) {
		// perror ("String does not exist to display!");
		return;
	}

	display_raw_string (string -> length, string -> address);
}

void concatenate_strings (int count, ...) {}

bool are_strings_equal (String *string1, String *string2)  {
	if (string1 == NULL || string2 == NULL) {
		perror ("One or Both given string does not exist");
		return false;
	}

	bool result = true;
	int i;

	if (string1 -> length != string2 -> length) {
		result = false;
	} else {
		for (i = 0; i < string1 -> length; i++) {
			if (*(string1 -> address + i) != *(string2 -> address + i)) {
				result = false;
				break;
			}
		}
	}

	return result;
}