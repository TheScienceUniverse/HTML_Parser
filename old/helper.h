#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#include "./lib/tree.h"

#define BYTE unsigned char
#define BUFFER_SIZE 32

typedef enum CHARACTER_TYPE {
	C_UnRecognized
	, C_WhiteSpace
	, C_Alpha
	, C_Numeric
	, C_Special
} Character_Type;

typedef enum TOKEN_TYPE {
	Tk_Identfier
	, Tk_Keyword
	, Tk_Separator
	, Tk_Operator
	, Tk_Literal
	, Tk_Comment
} Token_Type;

typedef struct TOKEN {
	String *string;
	Token_Type type;
} Token;

#endif