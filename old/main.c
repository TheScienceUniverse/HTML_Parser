#include "helper.h"


/*
TAG MAKING
	<!###>
	<!--###-->
	<###>
	<###/>
	</###>

PROPERTY VALUES
	NAME="VALUE"
	NAME='VALUE'


<!-/>='"


1. read file char by char
2. send character to lexer/scanner --- DFA#1
3. get lexeme and send it to tokenizer
4. syntax analyzer --- DFA#2
5. create parse tree



buffer [1024]

DFA#1
-----------------------------------------
check if
	1. whitespace
		if buffer .last != whitespace
			create string from earlier buffer
			check type
			change state
			reset type
			reset buffer
		if buffer .last  == whitespace
			
			put character as it is
	2. alphabet
		if buffer .last != alphabet
			change state
			process the earlier buffer
			reset buffer
		add new chracter to buffer
	3. digits
		if buffer .last != digit
			change state
			process the earlier buffer
			reset buffer
		add new chracter to buffer
	5. special characters / break points
		=> character belongs to ['<', '!', '-', '/', '_', ''', '"', '>', '\']
		if buffer .last != special
			create string from earlier buffer
			check type
			change state
			reset type
			reset buffer
		if buffer .last  == whitespace

	


*/




int get_symbol_index_from_char (char);
int dfa (int, int);
Character_Type get_character_type (char);
char* get_code_from_type (Character_Type);
bool is_whitespace_character (char);
bool is_special_character (char);
void lex (FILE*);								// takes file pointer to scanner
String* evaluator (int, char*);						// takes position and buffer string -- returns number of character read






/*

void main (void)
	lexer ()		// scans the input file to buffer [1024]
	evaluator ()	// DFA returns the possible token
	parser ()		// takes file containing identified tokens as input

*/





int main (int argc, char *argv[]) {
	FILE *fpi = fopen ("ip.html", "rb+");

	if (fpi == NULL) {
		perror ("Can't open input file!");
		exit (1);
	}

	FILE *fpo = fopen ("op.txt", "wb+");

	if (fpo == NULL) {
		perror ("Can't open output file!");
		exit (1);
	}

	fseek (fpi, 1, SEEK_END);
	// unsigned long f_ic = 0;		// File Index Counter
	long f_sz = ftell (fpi);		// File SiZe
	//printf ("File Size: %ld bytes.\n", f_sz);
	rewind (fpi);

	lex (fpi);

	fclose (fpo);
	fclose (fpi);

	return 0;
}

Character_Type get_character_type (char character) {
	Character_Type c_type = C_UnRecognized;

	if (isalpha (character)) {
		c_type = C_Alpha;
	} else if (isdigit (character)) {
		c_type = C_Numeric;
	} else if (is_whitespace_character (character)) {
		c_type = C_WhiteSpace;
	} else if (is_special_character (character)) {
		c_type = C_Special;
	}

	return c_type;
}

char* get_code_from_type (Character_Type type) {
	if (type == C_UnRecognized) {
		return "UnRecognized";
	} else if (type == C_WhiteSpace) {
		return "Whitespace";
	} else if (type == C_Alpha) {
		return "Letter";
	} else if (type == C_Numeric) {
		return "Digit";
	} else if (type == C_Special) {
		return "Special";
	} else {
		return "";
	}
}

int get_symbol_index_from_char (char character) {
	int symbol_index = 0;
	return symbol_index;
}

bool is_whitespace_character (char character) {
	return (
		character == ' '
		|| character == '\t'
		|| character == '\r'
		|| character == '\n'
		|| character == '\v'
		|| character == '\f'
	);
}

bool is_special_character (char character) {
	return (
		character == '<'
		|| character == '!'
		|| character == '/'
		|| character == '-'
		|| character == '_'
		|| character == '\''
		|| character == '\"'
		|| character == '\\'
		|| character == ':'
		|| character == ';'
	);
}

int dfa (int state, int symbol) {
	int next_state = 0;
	return next_state;
}

void lex (FILE *fpi) {
	int i, sz;
	static char buffer [BUFFER_SIZE];
	// int buffer_index = 0;

	while ((sz = fread (buffer, 1, BUFFER_SIZE, fpi))!= 0) {
		display_raw_string (sz, buffer);
	}

	String *string = evaluator (BUFFER_SIZE, buffer);

}

String* evaluator (int buffer_size, char *buffer) {
	/*int i;
	String *string = NULL;

	for (int i = 0; i < buffer_size; i++) {
		printf ("%c", *(buffer + i));
	}*/

	return NULL;
}