#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CircularDoublyLinkedList.h"
#include "utils.h"
#include "galactic_war_utils.h"

#define MAX_STRING_SIZE 256
#define ONE 1

char *strdup(const char *src) {
    char *dst = malloc(strlen (src) + 1);  // Space for length plus nul
    if (dst == NULL) return NULL;          // No memory
    strcpy(dst, src);                      // Copy the characters
    return dst;                            // Return the new string
}

void add_planet(doubly_linked_list_t *planets)
{
	char name[MAX_STRING_SIZE];
	int idx_planet, nr_shields;
	planet_t new_planet;
	int one = 1;

	fscanf(stdin, "%s", name);
	fscanf(stdin, "%d%d", &idx_planet, &nr_shields);

	if (idx_planet > planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	new_planet.shields = dll_create(sizeof(int));

	for (uint i = 0; i < nr_shields; i++)
		dll_add_nth_node(new_planet.shields, 0, &one);


	strcpy(new_planet.name, name);
	new_planet.planets_killed = 0;

	dll_print_int_list(new_planet.shields);

	dll_add_nth_node(planets, idx_planet, &new_planet);

	fprintf(stdout, "The planet %s has joined the galaxy!\n", new_planet.name);
}

void black_hole(doubly_linked_list_t *planets) 
{
	uint index;
	dll_node_t *removed;

	if (index > planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	fscanf(stdin, "%d", &index);

	removed = dll_remove_nth_node(planets, index);
	fprintf(stdout, "The planet %s has been eaten by the vortex!\n", ((planet_t *)removed->data)->name);
	dll_free(&((planet_t *)removed->data)->shields);
	free(removed->data);
	free(removed);
}

void show_planet(doubly_linked_list_t *planets)
{
	uint index;
	dll_node_t *curr, *curr_shields;
	scanf("%d", &index);

	if (!planets) {
		fprintf(stdout, "There is no planet in galaxy.\n");
		return;
	}

	curr = dll_get_nth_node(planets, index);
	fprintf(stdout, "NAME: %s\n", ((planet_t *)curr->data)->name);
	
	if (planets->size == 1)
		fprintf(stdout, "CLOSEST: none\n");
	else
		fprintf(stdout, "CLOSEST: %s %s\n", ((planet_t *)curr->prev->data)->name, ((planet_t *)curr->next->data)->name);

	fprintf(stdout, "SHIELDS: ");
	curr_shields = ((planet_t*)curr->data)->shields->head;
	for (uint i = 0; i < ((planet_t*)curr->data)->shields->size; i++) {
		fprintf(stdout, "%d ", *(int *)curr_shields->data);
		curr_shields = curr_shields->next;
	}
	fprintf(stdout, "\n");

	fprintf(stdout, "KILLED: %d\n", ((planet_t*)curr->data)->planets_killed);
}

void upgrade_shields_of_planet(doubly_linked_list_t *planets)
{
	uint idx_planet, idx_shield;
	int upgrade_value;
	dll_node_t *curr_planet, *curr_shield;

	fscanf(stdin, "%d%d%d", &idx_planet, &idx_shield, &upgrade_value);

	if (idx_planet >= planets->size) {
		fprintf(stdout, "Planet out of bonds!\n");
		return;
	}

	curr_planet = dll_get_nth_node(planets, idx_planet);

	if (idx_shield >= ((planet_t *)curr_planet)->shields->size) {
		fprintf(stdout, "Planet out of bonds\n");
		return;
	}

	curr_shield = dll_get_nth_node(((planet_t *) curr_planet->data)->shields, idx_shield);

	*(int *)curr_shield->data += upgrade_value;
}

void exp_planet(doubly_linked_list_t *planets)
{
	uint idx_planet;
	int value_shield;
	dll_node_t *first_shield, *curr_planet, *new_shield;

	fscanf(stdin, "%d%d", &idx_planet, &value_shield);

	if (idx_planet >= planets->size) {
		fprintf(stdout, "Planet out of bonds!\n");
		return;
	}

	curr_planet = dll_get_nth_node(planets, idx_planet);

	first_shield = ((planet_t *)curr_planet->data)->shields->head;

	new_shield = create_node(&value_shield, sizeof(int));
	new_shield->next = first_shield;
	new_shield->prev = first_shield->prev;
	first_shield->prev->next = new_shield;
	first_shield->prev = new_shield;

	((planet_t *)curr_planet->data)->shields->size++;
}

void destroy_galaxy(doubly_linked_list_t **planets)
{
	dll_node_t *node = (*planets)->head;

	if (!planets)
		return;

	for (int i = 0; i < (*planets)->size; i++) {
		dll_free(&((planet_t *)node->data)->shields);
		node = node->next;
	}
	
	dll_free(planets);
	*planets = NULL;
}
