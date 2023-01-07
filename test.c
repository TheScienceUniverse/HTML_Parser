#include "./lib/stack.h"
#include "./lib/queue.h"
#include "./lib/tree.h"


int main (int argc, char *argv[]) {
/*	String *string1 = create_string (5, "Hello");
	String *string2 = create_string (5, "World");
	display_string (string1);
	delete_string (&string1);
	printf ("%p\n", string1);
*/
/*	List *list = create_list (0);
	int x = 100;

	Data *data = create_data (DT_Integer, sizeof (int), &x);
	//display_data_properties (data);
	add_to_list (list, data, true);
//	display_list_addresses (list);
	delete_data (&data);

	data = create_data (DT_String, string1 -> length, string1 -> address);
	//display_data_properties (data);
	add_to_list (list, data, true);
//	display_list_addresses (list);
	delete_data (&data);

	data = create_data (DT_String, string2 -> length, string2 -> address);
	//display_data_properties (data);
	add_to_list (list, data, true);
//	display_list_addresses (list);
	delete_data (&data);

//	display_string (string1);
//	display_string (string2);
	//display_list (list);
	delete_list (&list);
*/
	//printf ("%d\n", are_strings_equal (string1, string2));
/*
	Linked_List *linked_list = create_linked_list ();
	display_linked_list (linked_list);
	Stack *stack = create_stack ();
	Queue *queue = create_queue ();

	Node *node = create_node (N_LinkedList);
	set_node_name (node, 5, "node1");
//	*(node -> address_list -> item_addresses + 1) = duplicate_string (string1);
//	display_node_details (node);

//	Node *node2 = duplicate_node (node);
//	display_node_details (node2);
	push (stack, node);
	enqueue (queue, node);
	attach_node_at_last (linked_list, node);
	delete_node (&node);
//	display_linked_list (linked_list);

	node = create_node (N_LinkedList);
	set_node_name (node, 5, "node2");
//	display_node_details (node);
	push (stack, node);
	enqueue (queue, node);
	attach_node_at_last (linked_list, node);
	delete_node (&node);
//	display_linked_list (linked_list);

	node = create_node (N_LinkedList);
	set_node_name (node, 5, "node3");
	//display_node (node);
	push (stack, node);
	enqueue (queue, node);
	attach_node_at_last (linked_list, node);
	delete_node (&node);
//	display_linked_list (linked_list);

	//display_linked_list (linked_list);

	//detach_node_from_last (linked_list, true);
	//display_linked_list (linked_list);
//	detach_node_from_first (linked_list, true);
//	display_linked_list (linked_list);
	//detach_node_from_first (linked_list, true);
	//detach_node_from_last (linked_list, true);
	//display_linked_list (linked_list);
	//detach_node_from_last (linked_list, true);
	//display_linked_list (linked_list);

	display_linked_list (linked_list);
	//delete_linked_list (&linked_list);
	delete_linked_list (&linked_list);
	display_linked_list (linked_list);
//	printf ("%p\n", linked_list);
//	printf ("%p\n", linked_list);

	display_stack (stack);
	Node *node1 = pop (stack);
	display_stack (stack);
	node1 = pop (stack);
	display_stack (stack);
	node1 = pop (stack);
	display_stack (stack);
	delete_stack (&stack);


	display_queue (queue);
	node1 = dequeue (queue);
	display_queue (queue);
	node1 = dequeue (queue);
	display_queue (queue);
	node1 = dequeue (queue);
	display_queue (queue);

	delete_queue (&queue);

	delete_node (&node1);
*/
	Node *node;
	Node *p_node, *root_node;
	//printf ("gotcha\n");
	Tree *tree = create_tree ();

	node = create_node (N_Tree);
	set_node_name (node, 4, "root");
	set_root_node (tree, node);
	delete_node (&node);

	root_node = get_root_node (tree);
	p_node = root_node;

	node = create_node (N_Tree);
	set_node_name (node, 1, "A");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	node = create_node (N_Tree);
	set_node_name (node, 5, "aside");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	node = create_node (N_Tree);
	set_node_name (node, 1, "B");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	p_node = get_Nth_child_node (p_node, 1);

	node = create_node (N_Tree);
	set_node_name (node, 1, "C");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	node = create_node (N_Tree);
	set_node_name (node, 1, "D");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	p_node = get_Nth_child_node (root_node, 2);

	node = create_node (N_Tree);
	set_node_name (node, 1, "E");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	node = create_node (N_Tree);
	set_node_name (node, 1, "F");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	p_node = get_Nth_child_node (p_node, 1);

	node = create_node (N_Tree);
	set_node_name (node, 1, "G");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	node = create_node (N_Tree);
	set_node_name (node, 1, "H");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	p_node = get_parent_node (p_node);
	p_node = get_parent_node (p_node);

	node = create_node (N_Tree);
	set_node_name (node, 5, "aside");
	append_child_node (tree, p_node, node);
	delete_node (&node);

	p_node = get_Nth_child_node (p_node, 4);

	node = create_node (N_Tree);
	set_node_name (node, 1, "Z");
	append_child_node (tree, p_node, node);
	delete_node (&node);


	display_tree (tree);

	String *name  = create_string (5, "aside");

	node = search_tree_by_node_name (tree, name);
	delete_node_from_tree (tree, node);
	display_node (node);

	node = search_tree_by_node_name (tree, name);
	delete_node_from_tree (tree, node);
	display_node (node);

	delete_string (&name);

	display_tree (tree);

	delete_tree (&tree);

	return 0;
}