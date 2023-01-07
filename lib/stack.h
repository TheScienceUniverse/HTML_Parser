#ifndef STACK_H
#define STACK_H

// ---------- x ----------

#include "./linked_list.h"

// ---------- x ----------

typedef Linked_List Stack;

// ---------- x ----------

Stack* create_stack ();
void delete_stack (Stack **stack_address);
void display_stack (Stack *stack);
void display_stack_details (Stack *stack);
void display_stack_data (Stack *stack);
void push (Stack *stack, Node *node);
Node* pop (Stack *stack);

#endif