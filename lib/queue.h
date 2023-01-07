#ifndef QUEUE_H
#define QUEUE_H

// ---------- x ----------

#include "./linked_list.h"

// ---------- x ----------

typedef Linked_List Queue;

// ---------- x ----------

Queue* create_queue ();
void delete_queue (Queue **queue_address);
void display_queue (Queue *queue);
void enqueue (Queue *queue, Node *node);
Node* dequeue (Queue *queue);

#endif