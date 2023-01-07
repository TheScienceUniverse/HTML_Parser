#include "../lib/stack.h"

Stack *create_stack () {
	return create_linked_list ();
}

void delete_stack (Stack **stack_address) {
	delete_linked_list (stack_address);
}

void display_stack (Stack *stack) {
	if (stack == NULL) {
		perror ("Stack does not exist to display!");
		return;
	}

	printf ("Stack (%d)", stack -> size);

	if (stack -> name != NULL) {
		printf (" <");
		display_string (stack -> name);
		printf (">");
	}

	printf (":=\n");

	if (stack -> size == 0) {
		perror ("Stack is Empty!");
		return;
	}

	Node *node = stack -> first_node;

	for (int i = 0; i < stack -> size; i++) {
		if (i < stack -> size) {
			printf ("\t|__*__| => ");
		}

		display_node (node);
		printf ("\n");
		node = *(node -> address_list -> item_addresses + 1);
	}

	printf ("\n");
}

void display_stack_details (Stack *stack) {
	if (stack == NULL) {
		perror ("Stack does not exist to display!");
		return;
	}

	printf ("Stack (%d)", stack -> size);

	if (stack -> name != NULL) {
		printf (" <");
		display_string (stack -> name);
		printf (">");
	}

	printf (":=\n");

	if (stack -> size == 0) {
		perror ("Stack is Empty!");
		return;
	}

	Node *node = stack -> first_node;

	for (int i = 0; i < stack -> size; i++) {
		if (i < stack -> size) {
			printf ("\t|__*__| => ");
		}

		display_node_details (node);
		node = *(node -> address_list -> item_addresses + 1);
	}

	printf ("\n");
}

void display_stack_data (Stack *stack) {
	if (stack == NULL) {
		perror ("Stack does not exist to display!");
		return;
	}

	printf ("Stack (%d)", stack -> size);

	if (stack -> name != NULL) {
		printf (" <");
		display_string (stack -> name);
		printf (">");
	}

	printf (":=\n");

	if (stack -> size == 0) {
		perror ("Stack is Empty!");
		return;
	}

	Node *node = stack -> first_node;

	for (int i = 0; i < stack -> size; i++) {
		if (i < stack -> size) {
			printf ("\t|__*__| => ");
		}

		display_data (node -> data);
		printf ("\n");
		node = *(node -> address_list -> item_addresses + 1);
	}

	printf ("\n");
}

void push (Stack *stack, Node *node) {
	attach_node_at_first (stack, node);
	stack -> first_node -> type = node -> type;
}

Node *pop (Stack *stack) {
	Node *x_node = stack -> first_node;
	Node *node = duplicate_node (stack -> first_node);

	forget_data (&(x_node -> data));
	detach_node_from_first (stack, true);

	return node;
}