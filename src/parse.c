#include "../lib/parser.h"

/*
	State Transition Table:
		+---+---+---+---+---+---+---+---+---+---+
		| <	| !	| -	| /	| > | A	| S	| E	| "	| x |
	+---+---+---+---+---+---+---+---+---+---+---+
	| 0	| 1   0   0   0   0   0   0   0   0   0	|
	+---+									 	+
	| 1	| 0   2   0   9   0   6   0   0   0	  0 |
	+---+										+
	| 2	| 0   0   3   0   0   0   0   0   0	  0 |
	+---+										+
	| 3	| 3   3   4   3   3   3   3   3   3	  3 |
	+---+										+
	| 4	| 3   3   5   3   3   3   3   3   3	  3 |
	+---+										+
	| 5	| 3   3   3   3   x   3   3   3   3	  3 |
	+---+										+
	| 6	| 6   6   6   8   x   6   7   7   0	  6 |
	+---+										+
	| 7	| 7   7   7   8   x   7   7   7   7	  7 |
	+---+										+
	| 8	| 7   7   7   7   x   7   7   7   7	  7 |
	+---+										+
	| 9	| 0   0   0   0   x   9   0   0   0	  0 |
	+---+---------------------------------------+

	<	for lesser than symbol
	!	for exclamation mark
	-	for hyphen
	/	for forward slash
	>	for greater than symbol
	A	for alphabet characters
	S	for space characters - space (' '), tab ('\t'), carriage return ('\r'), vertical tab ('\v') and formfeed ('\f')
	E	for enter character - newline ('\n')
	"	for quotation mark
	x	for anything else

	<!--XXX-->	=> Comment
	<XXX>		=> Container Tag Starts
	</XXX>		=> Container Tag Ends
	<XXX/>		=> Self-closing Tag
*/

const BYTE transition_table [10][10] = {
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	, {0, 2, 0, 9, 0, 6, 0, 0, 0, 0}
	, {0, 0, 3, 0, 0, 0, 0, 0, 0, 0}
	, {3, 3, 4, 3, 3, 3, 3, 3, 3, 3}
	, {3, 3, 5, 3, 3, 3, 3, 3, 3, 3}
	, {3, 3, 3, 3, 10, 3, 3, 3, 3, 3}
	, {6, 6, 6, 8, 10, 6, 7, 7, 0, 6}
	, {7, 7, 7, 8, 10, 7, 7, 7, 7, 7}
	, {7, 7, 7, 7, 10, 7, 7, 7, 7, 7}
	, {0, 0, 0, 0, 10, 9, 0, 0, 0, 0}
};

char tag_buffer [TAG_MAX];
int tag_length = 0;
char content_buffer [CONTENT_MAX];
int content_length = 0;
bool content_buffering = true;

void parse (FILE *fpi, FILE *fpo, long input_file_size) {
	long i;
	BYTE c;
	BYTE state = 0, previous_state;
	int sz;
	bool flag_copy = false;
	Tagging_Status tagging_status;
	Stack *stack = create_stack (0);
	Node *node, *current_node;
	String *string;
	Tree *tree = create_tree ();
	int depth_counter = 0;
	char *whitespace_characters;

	for (i = 0; i < input_file_size; i++) {
		sz = fread (&c, 1, 1, fpi);
		--sz;

		previous_state = state;
		state = get_next_state (state, c);
		tagging_status = process_state (tagging_status, previous_state, state, c);

		if (tagging_status == Container_Starts && is_self_closing_tag (tag_buffer)) {
			tagging_status = Self_Closing_Ends;
		}

		switch (tagging_status) {
			case Container_Starts:
				//whitespace_characters = get_N_characters ('\t', depth_counter);
				whitespace_characters = get_tabbed_N_characters (depth_counter);
				fprintf (fpo, "%s<%s>\n", whitespace_characters, tag_buffer);
				++ depth_counter;
				ERASE (&whitespace_characters);

				node = create_node (N_Stack);
				set_node_name (node, strlen (tag_buffer), tag_buffer);
				push (stack, node);
				delete_node (&node);

				node = create_node (N_Tree);
				set_node_name (node, strlen (tag_buffer), tag_buffer);

				if (tree -> node_count > 0) {
					append_child_node (tree, current_node, node);
					current_node = get_last_child_node (current_node);
				} else {
					set_root_node (tree, node);
					current_node = tree -> root_node;
				}

				delete_node (&node);
				break;
			case Container_Ends:
				-- depth_counter;
				//whitespace_characters = get_N_characters ('\t', depth_counter);
				whitespace_characters = get_tabbed_N_characters (depth_counter);
				fprintf (fpo, "%s</%s>\n", whitespace_characters, tag_buffer);
				ERASE (&whitespace_characters);

				string = create_string (strlen (tag_buffer), tag_buffer);

				if (are_strings_equal (string, stack -> first_node -> name)) {
					node = pop (stack);
					forget_list (&(node -> address_list));
					delete_node (&node);
				}

				current_node = get_parent_node (current_node);
				delete_string (&string);
				break;
			case Self_Closing_Ends:
				//whitespace_characters = get_N_characters ('\t', depth_counter);
				whitespace_characters = get_tabbed_N_characters (depth_counter);
				fprintf (fpo, "%s<%s/>\n", whitespace_characters, tag_buffer);
				ERASE (&whitespace_characters);

				node = create_node (N_Tree);
				set_node_name (node, strlen (tag_buffer), tag_buffer);

				if (tree -> node_count > 0) {
					append_child_node (tree, current_node, node);
				} else {
					set_root_node (tree, node);
					current_node = tree -> root_node;
				}

				delete_node (&node);
				break;
			default:
				break;
		}

		if (state == 10) {
			state = 0;
		}

		if (state == 8) {
			flag_copy = !flag_copy;
		}

		if (flag_copy) {
		//	fwrite (&c, 1, 1, fpo);
		}
	}

	delete_stack (&stack);

	//printf ("\n\n");
	//display_tree (tree);

	printf ("Displaying %d nodes in Tree\n", tree -> node_count);

	string = create_string (5, "aside");
	delete_all_nodes_by_name (tree, string);
	delete_string (&string);

	printf ("\n\n");
	printf ("Displaying %d nodes in Tree\n", tree -> node_count);
	display_tree (tree);

	delete_tree (&tree);
}

bool is_self_closing_tag (char *tag_name) {
	bool decision = false;
	int i, ti = 0, t, size = strlen (tag_name);
	// area, base, br, col, embed, hr, img, input, keygen, link, meta, param, source, track, and wbr
	const char *tags = "areabasebrcolembedhrimginputkeygenlinkmetaparamsourcetrackwbr";
	BYTE tag_lengths [15] = {4, 4, 2, 3, 5, 2, 3, 5, 6, 4, 4, 5, 6, 5, 3};

	for (i = 0; i < 15; i++) {
		if (size == tag_lengths [i]) {
			for (t = 0; t < size; t++) {
				if (*(tags + ti + t) != *(tag_name + t)) {
					break;
				}
			}
		} else {
			t = 0;
		}

		if (t < size) {
			ti += tag_lengths [i];
		} else {
			decision = true;
			break;
		}		
	}

	return decision;
}

BYTE get_next_state (BYTE current_state, BYTE symbol) {
	BYTE symbol_index = get_symbol_index (symbol);
	return (symbol_index == -1) ? current_state : transition_table [current_state][symbol_index];
}

BYTE get_symbol_index (BYTE symbol) {
	BYTE symbol_index = -1;

	switch (symbol) {
		case '<':
			symbol_index = 0;
			break;
		case '!':
			symbol_index = 1;
			break;
		case '-':
			symbol_index = 2;
			break;
		case '/':
			symbol_index = 3;
			break;
		case '>':
			symbol_index = 4;
			break;
		case 'a':
			symbol_index = 5;
			break;
		case ' ':
		case '\t':
		case '\r':
		case '\v':
		case '\f':
			symbol_index = 6;
			break;
		case '\n':
			symbol_index = 7;
			break;
		case '"':
			symbol_index = 8;
			break;
		default:
			symbol_index = 9;	// x = 10 (- 1)
			break;
	}

	if (isalnum (symbol)) {
		symbol_index = 5;
	}

	return symbol_index;
}

Tagging_Status process_state (Tagging_Status old_status, int previous_state, int current_state, char symbol) {
	Tagging_Status new_status = Text;
	bool content_was_buffering = content_buffering;
	content_buffering = true;

	if (previous_state == 1 && current_state == 3) { // comment tag starts
		content_buffering = true;
		new_status = Comment_Starts;
	}

	if (previous_state == 5 && current_state == 10) { // comment tag ends
		content_length = 0;
		content_buffer [0] = '\0';
		content_buffering = false;
		new_status = Comment_Ends;
	}

	if ((previous_state == 1 || previous_state == 6) && current_state == 6) { // container tag starts
		tag_buffer [tag_length ++] = symbol;
		content_buffering = false;
		new_status = Container_Name_Starts;
	}

	if ((previous_state == 6 || previous_state == 7) && current_state == 10) { // container tag ends
		tag_buffer [tag_length ++] = symbol;
		tag_buffer [tag_length - 1] = '\0';
		tag_length = 0;
		content_buffering = false;
		new_status = Container_Name_Starts;
	}

	if (previous_state == 9 && current_state == 9) {
		tag_buffer [tag_length ++] = symbol;
		content_buffering = false;
		new_status = Container_Name_Starts;
	}

	if (previous_state == 9 && current_state == 10) {
		tag_buffer [tag_length] = '\0';
		tag_length = 0;
		content_buffering = false;
		new_status = Container_Name_Ends;
	}

	if (previous_state == 8 && current_state == 10) {
		tag_buffer [tag_length] = '\0';
		tag_length = 0;
		content_buffering = false;
		new_status = Self_Closing_Starts;
	}

	if (current_state == 10) {
		tag_length = 0;
		content_length = 0;

		switch (new_status) {
			case Container_Name_Starts:
				new_status = Container_Starts;
				break;
			case Container_Name_Ends:
				new_status = Container_Ends;
				break;
			case Self_Closing_Starts:
				new_status = Self_Closing_Ends;
				break;
			default:
				break;
		}
	}

	if (content_was_buffering && !content_buffering) {
		process_content_buffer ();

		if (content_length > 0) {
			display_raw_string (content_length, content_buffer);
			printf ("\n");
		}
	}

	if ((content_buffering || new_status == Text) && content_length < CONTENT_MAX) {
		content_buffer [content_length ++] = symbol;
		content_buffer [content_length] = '\0';
	} else {
		content_length = 0;
		content_buffer [0] = '\0';
	}

	return new_status;
}

char* get_N_characters (char c, int n) {
	char *string = malloc (n + 1);
	char *p = string;
	int i;

	for (i = 0; i < n; i++) {
		*p = c;
		p = p + 1;
	}

	*p = '\0';
	p = NULL;

	return string;
}

char* get_tabbed_N_characters (int n) {
	char *string = malloc (2 * n + 1);
	char *p = string;
	int i;

	for (i = 0; i < n; i++) {
		*p = '|';
		p += 1;
		*p = '\t';
		p += 1;
	}

	*p = '\0';
	p = NULL;

	return string;
}

void process_content_buffer () {
	int i, shift = 0;

	if (content_length > 1 && content_buffer [content_length - 2] == '<' && content_buffer [content_length - 1] == '/') {
		content_buffer [content_length - 2] = '\0';
		content_length -= 2;
	}

	i = 0;

	while (i < content_length) {
		if (
			content_buffer [i] != ' '
			&& content_buffer [i] != '\n'
		) {
			break;
		}

		++i;
	}

	shift = i;
	content_length -= shift;

	for (i = 0; i <= content_length; i++) {
		content_buffer [i] = content_buffer [i + shift];
	}

	if (content_buffer [0] == '<') {
		shift = 1;
	}

	content_length -= shift;

	for (i = 0; i <= content_length; i++) {
		content_buffer [i] = content_buffer [i + shift];
	}
}