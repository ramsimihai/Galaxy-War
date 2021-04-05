#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./CircularDoublyLinkedList.h"
#include "./utils.h"

typedef unsigned int uint;

/* create a node with a given data and its size */
dll_node_t *create_node(const void *new_data, uint data_size)
{
	dll_node_t *node;

	node = malloc(sizeof(*node));
	DIE(NULL == node, "malloc failed");

	node->data = malloc(data_size);
	DIE(NULL == node->data, "malloc failed");

	memcpy(node->data, new_data, data_size);

	return node;
}

/* create a list of a specified data_size */
doubly_linked_list_t*
dll_create(uint data_size)
{
	doubly_linked_list_t *list;

	list = malloc(sizeof(*list));
	DIE(NULL == list, "malloc failed");

	list->head = NULL;
	list->data_size = data_size;
	list->size = 0;

	return list;
}

/* get the node from a given position */
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, uint n)
{
	dll_node_t *node;
	uint i;

	if (!list || !list->size)
		return NULL;

	if (!list->size) {
		fprintf(stdout, "Cant get the nth node\n");
		return NULL;
	}

	node = list->head;

	n = n % list->size;

		for (i = 0; i < n; i++)
			node = node->next;

	return node;
}

/* add a node on the nth position of the list given as a parameter */
void
dll_add_nth_node(doubly_linked_list_t* list, uint n, const void* data)
{
	dll_node_t *new_node, *prev_node, *curr_node;

	if (!list) {
		fprintf(stderr, "Can't add the node\n");
		return;
	}

	if (n >= list-> size)
		n = list->size;

	new_node = create_node(data, list->data_size);

	if (!list->size) {
		new_node->next = new_node;
		new_node->prev = new_node;
		list->head = new_node;
	} else if (n == 0) {
		curr_node = list->head;

		new_node->next = curr_node;
		new_node->prev = curr_node->prev;

		curr_node->prev->next = new_node;
		curr_node->prev = new_node;

		list->head = new_node;
	} else {
		prev_node = dll_get_nth_node(list, n - 1);

		new_node->next = prev_node->next;
		prev_node->next->prev = new_node;

		prev_node->next = new_node;
		new_node->prev = prev_node;
	}

	list->size++;
}

/* delete a node from the nth position of the list given as a parameter */
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, uint n)
{
	dll_node_t *removed;

	if (!list || !list->size) {
		fprintf(stderr, "Can't remove the node\n");
		return NULL;
	}

	if (n < 0) {
		fprintf(stdout, "Can't remove the node\n");
		return NULL;
	}

	if (n >= list->size)
		n = list->size - 1;

	if (!n) {
		removed = list->head;
		list->head = removed->next;

	} else {
		removed = dll_get_nth_node(list, n);
	}

	removed->next->prev = removed->prev;
	removed->prev->next = removed->next;

	list->size--;

	if (!list->size)
		list->head = NULL;

	return removed;
}

/* get the size of a list */
uint
dll_get_size(doubly_linked_list_t* list)
{
	return list->size;
}

/* free the memory allocated from a list */
void
dll_free(doubly_linked_list_t** pp_list)
{
	dll_node_t *node;

	if (!pp_list || !*pp_list)
		return;

	while((*pp_list)->size) {
		node = dll_remove_nth_node(*pp_list, 0);

		free(node->data);
		free(node);
	}

	free(*pp_list);
	*pp_list = NULL;
}

/* print a list that contains int datas */
void
dll_print_int_list(doubly_linked_list_t* list)
{
	dll_node_t *curr;

	if (list == NULL)
		return;

	curr = list->head;

	for (uint i = 0; i < list->size; i++) {
		printf("%d ", *(int *)curr->data);
		curr = curr->next;
	}

	printf("\n");
}

/* print a list that contains string datas */
void
dll_print_string_list(doubly_linked_list_t* list)
{
	dll_node_t *curr;

	if (list == NULL)
		return;

	curr = list->head;

	for (uint i = 0; i < list->size; i++) {
		printf("%s ", (char *)curr->data);
		curr = curr->next;
	}

	printf("\n");
}

/* print a list in left direction */
void
dll_print_ints_left_circular(dll_node_t* start)
{
	dll_node_t *curr;

	curr = start;

	while (curr->prev != start) {
		printf("%d ", *(int *)curr->data);
		curr = curr->prev;
		if (curr->prev == start)
			printf("%d ", *(int *)start->next->data);
	}

	printf("\n");
}

/* print a list in right direction */
void
dll_print_ints_right_circular(dll_node_t* start)
{
	dll_node_t *curr;

	curr = start;

	while (curr->next != start) {
		printf("%d ", *(int *)curr->data);
		curr = curr->next;
		if (curr->next == start)
			printf("%d ", *(int *)start->prev->data);
	}

	printf("\n");
}

/* function to insert a node in the first position */
void
dll_move_first(dll_node_t **head, dll_node_t *new_node)
{
	dll_node_t *last;

	if (*head == NULL) {
		new_node->next = new_node->prev = new_node;
		*head = new_node;
		return;
	}

	new_node->next->prev = new_node->prev;
	new_node->prev->next = new_node->next;

	last = (*head)->prev;

	new_node->next = *head;
	new_node->prev = last;

	last->next = (*head)->prev = new_node;

	*head = new_node;
}
