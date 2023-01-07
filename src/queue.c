#include "../lib/queue.h"

Queue *create_queue () {
	return create_linked_list ();
}

void delete_queue (Queue **queue_address) {
	delete_linked_list (queue_address);
}

void display_queue (Queue *queue) {
	printf ("<Queue>(%d) :=\n", queue -> size);

	if (queue -> size == 0) {
		perror ("Queue is Empty!");
		return;
	}

	Node *node = queue -> first_node;

	for (int i = 0; i < queue -> size; i++) {
		if (i < queue -> size) {
			printf ("\t|  *  | => ");
		}

		display_node_details (node);
		node = *(node -> address_list -> item_addresses + 1);
	}

	printf ("\n");
}

void enqueue (Queue *queue, Node *node) {
	attach_node_at_last (queue, node);
	queue -> last_node -> type = N_Queue;
}

Node *dequeue (Queue *queue) {
	Node *x_node = queue -> first_node;
	Node *node = duplicate_node (queue -> first_node);

	forget_data (&(x_node -> data));
	detach_node_from_first (queue, true);

	return node;
}