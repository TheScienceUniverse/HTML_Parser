#ifndef HELPER_H
#define HELPER_H

// ---------- x ----------

#include "tree.h"

// ---------- x ----------

typedef enum TAGGING_STATUS {
	None
	, Comment_Starts
	, Comment_Ends
	, Container_Name_Starts
	, Container_Starts
	, Container_Name_Ends
	, Container_Ends
	, Tag_Starts
	, Self_Closing_Starts
	, Self_Closing_Ends
	, Inside_Tag
	, Tag_Ends
	, Text
} Tagging_Status;

// ---------- x ----------

#define TAG_MAX 100
#define CONTENT_MAX 1000

extern const BYTE transition_table [10][10];
extern char tag_buffer [];
extern int tag_length;
extern char content_buffer [];
extern int content_length;
extern bool content_buffering;

// ---------- x ----------

void parse (FILE *input_file_pointer, FILE *output_file_pointer, long input_file_size);
bool is_self_closing_tag (char *tag_name);
BYTE get_next_state (BYTE current_state, BYTE symbol);
BYTE get_symbol_index (BYTE symbol);
Tagging_Status process_state (Tagging_Status old_status, int previous_state, int current_state, char symbol);
char* get_N_characters (char character, int character_count);
char* get_tabbed_N_characters (int character_count);
void process_content_buffer (void);

#endif