#ifndef NODE_H
#define NODE_H

// ---------- x ----------

#include "./data.h"
#include "./list.h"

// ---------- x ----------

typedef enum NODE_TYPE {
	N_Undefined
	, N_LinkedList
	, N_Stack
	, N_Queue
	, N_Tree
	, N_Graph
} Node_Type;

typedef struct NODE {
	Node_Type type;
	String* name;
	List* address_list;
	Data* data;
} Node;

// ---------- x ----------

Node* create_node (Node_Type type);
Node* duplicate_node (Node *node);
void delete_node (Node **node_address);
void set_node_name (Node *node, int name_length, char *name_address);
void display_node (Node *node);
void display_special_node (Node *node);
void display_node_details (Node *node);
void delete_temporary_node (Node **node_address);

#endif