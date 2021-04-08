// Copyright 2020 - 2021 - 311CA - Mihai Daniel Soare
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./CircularDoublyLinkedList.h"
#include "./utils.h"
#include "./galactic_war_utils.h"

#define MAX_STRING_SIZE 256
#define MIN_SHIELDS 4

void add_planet(doubly_linked_list_t *planets)
{
	char name[MAX_STRING_SIZE];
	uint idx_planet, nr_shields;
	planet_t new_planet;
	int one = 1;

	// reads  the details of a new planet
	fscanf(stdin, "%s", name);
	fscanf(stdin, "%d%d", &idx_planet, &nr_shields);

	if (idx_planet > planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	// creates a new temporary list of shields
	new_planet.shields = dll_create(sizeof(int));

	// adds enough shields in the list
	for (uint i = 0; i < nr_shields; i++)
		dll_add_nth_node(new_planet.shields, 0, &one);

	// initializes the name and the number of planets killed of a planet
	memcpy(new_planet.name, name, sizeof(name));
	new_planet.planets_killed = 0;

	// adds the planet in the galaxy and show a message if it succeed
	dll_add_nth_node(planets, idx_planet, &new_planet);

	fprintf(stdout, "The planet %s has joined the galaxy.\n", new_planet.name);
}

void black_hole(doubly_linked_list_t *planets)
{
	uint index;
	dll_node_t *removed;
	doubly_linked_list_t *shields;

	// reads the index of the planet wanted to be removed
	fscanf(stdin, "%d", &index);

	// checks if the planet can be removed
	if (index >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	// gets the planet wanted to be removed and show a message if it succeeded;
	removed = dll_remove_nth_node(planets, index);

	// frees the list of the shields;
	shields = ((planet_t *)removed->data)->shields;
	dll_free(&shields);

	fprintf(stdout, "The planet %s has been eaten by the vortex.\n",
			((planet_t *)removed->data)->name);

	// frees the data of the planet and itself
	free(removed->data);
	free(removed);
}

void show_planet(doubly_linked_list_t *planets)
{
	uint index;
	dll_node_t *curr;
	doubly_linked_list_t *curr_shields;

	scanf("%d", &index);

	// checks if the planet exists and the index isnt out of bounds
	if (!planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	if (index >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	// gets the planet at the given index and print the name,
	// the neighbour planets, the shields and the planets killed
	curr = dll_get_nth_node(planets, index);
	fprintf(stdout, "NAME: %s\n", ((planet_t *)curr->data)->name);

	if (planets->size == 1)
		fprintf(stdout, "CLOSEST: none\n");
	else if (planets->size == 2)
		fprintf(stdout, "CLOSEST: %s\n", ((planet_t *)curr->prev->data)->name);
	else
		fprintf(stdout, "CLOSEST: %s and %s\n",
				((planet_t *)curr->prev->data)->name,
				((planet_t *)curr->next->data)->name);

	fprintf(stdout, "SHIELDS: ");
	curr_shields = ((planet_t*)curr->data)->shields;

	dll_print_int_list(curr_shields);

	fprintf(stdout, "\nKILLED: %d\n", ((planet_t*)curr->data)->planets_killed);
}

void upgrade_shields_of_planet(doubly_linked_list_t *planets)
{
	uint idx_planet, idx_shield;
	int upgrade_value;
	dll_node_t *curr_planet, *curr_shield;

	fscanf(stdin, "%d%d%d", &idx_planet, &idx_shield, &upgrade_value);

	// checks if the wanted planet is out of bounds
	if (idx_planet >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	// gets the planet at the specified index
	curr_planet = dll_get_nth_node(planets, idx_planet);

	// checks if the wanted shield is out of bounds
	if (idx_shield >= ((planet_t *)curr_planet->data)->shields->size) {
		printf("Shield out of bounds!\n");
		return;
	}

	// gets the shield at the specified index
	curr_shield = dll_get_nth_node(((planet_t *)curr_planet->data)->shields,
									idx_shield);

	// increments the value of the shield with the given value
	*(int *)curr_shield->data += upgrade_value;
}

void exp_planet(doubly_linked_list_t *planets)
{
	uint idx_planet;
	int value_shield;
	dll_node_t *first_shield, *curr_planet, *new_shield;

	fscanf(stdin, "%d%d", &idx_planet, &value_shield);

	// checks if the index isnt out of bounds
	if (idx_planet >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	// gets the planet of the specified index
	curr_planet = dll_get_nth_node(planets, idx_planet);

	// gets the head of the list of shields
	first_shield = ((planet_t *)curr_planet->data)->shields->head;

	// creates a new shield and adds it in the last position
	new_shield = create_node(&value_shield, sizeof(int));

	// links the new shield to the head and the tail of the list
	new_shield->next = first_shield;
	new_shield->prev = first_shield->prev;

	// switches the links of the old prev and tail
	first_shield->prev->next = new_shield;
	first_shield->prev = new_shield;

	// increments the size of the list of shields
	((planet_t *)curr_planet->data)->shields->size++;
}

void remove_shield(doubly_linked_list_t *planets)
{
	uint idx_planet, idx_shield;
	dll_node_t *curr_planet, *curr_shield;

	fscanf(stdin, "%d%d", &idx_planet, &idx_shield);

	// checks if the index given is out of bounds
	if (idx_planet >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	// gets the wanted planet
	curr_planet = dll_get_nth_node(planets, idx_planet);

	// checks if the index_shield given is out of bounds
	if (idx_shield >= ((planet_t *)curr_planet->data)->shields->size) {
		fprintf(stdout, "Shield out of bounds!\n");
		return;
	}

	// gets the wanted shield
	curr_shield = dll_get_nth_node(((planet_t *) curr_planet->data)->shields,
									idx_shield);

	// checks if the shield wanted can be removed
	if (((planet_t *) curr_planet->data)->shields->size <= MIN_SHIELDS) {
		fprintf(stdout, "A planet cannot have less than 4 shields!\n");
		return;
	}

	// removes the shield at the given index and frees its data
	curr_shield = dll_remove_nth_node(((planet_t *)curr_planet->data)->shields,
									  idx_shield);
	free(curr_shield->data);
	free(curr_shield);
}

static void destroy_planet(doubly_linked_list_t *planets, uint idx_planet)
{
	// checks if the list is allocated
	if (!planets)
		return;

	// gets the planet at the specified index
	dll_node_t *removed = dll_remove_nth_node(planets, idx_planet);

	// removes the shields
	doubly_linked_list_t *shields = ((planet_t *)removed->data)->shields;
	dll_free(&shields);

	// frees the planet
	free(removed->data);
	free(removed);
}

void collide_planets(doubly_linked_list_t *planets)
{
	uint idx_first_planet, idx_second_planet;
	dll_node_t *first_planet, *second_planet;
	dll_node_t *first_shield, *second_shield;
	int one = 1;

	fscanf(stdin, "%d%d", &idx_first_planet, &idx_second_planet);

	// checks if the indexes of the two planets are eligible
	if (idx_first_planet >= planets->size || idx_second_planet >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	// gets the two planets
	first_planet = dll_get_nth_node(planets, idx_first_planet);
	second_planet = dll_get_nth_node(planets, idx_second_planet);

	// gets the shield at the position of size / 4 of the first planet and
	// the shield at the position of size / 4 * 3 of the second planet
	first_shield = dll_get_nth_node(((planet_t *)first_planet->data)->shields,
									((planet_t *)first_planet->data)->shields->size / 4);
	second_shield = dll_get_nth_node(((planet_t *)second_planet->data)->shields,
										((planet_t *)second_planet->data)->shields->size / 4 * 3);

	// checks if the shield value is zero or not and decrement it
	if (*(int *)first_shield->data == 0) {
		// removes the first planet from the galaxy
		fprintf(stdout, "The planet %s has imploded.\n",
				((planet_t *)first_planet->data)->name);

		destroy_planet(planets, idx_first_planet);

		// switches the index of the second and the first planet
		idx_second_planet = idx_first_planet;

		// increments the planets that the second planet killed
		((planet_t *)second_planet->data)->planets_killed++;

	} else {
		// decrements the shield's value with one
		*(int *)first_shield->data -= one;
	}

	if (*(int *)second_shield->data == 0) {
		// removes the second planet from the galaxy
		fprintf(stdout, "The planet %s has imploded.\n",
				((planet_t *)second_planet->data)->name);

		destroy_planet(planets, idx_second_planet);

		// checks if the first planet hasnt imploded and
		// increments its number of planets killed
		if (idx_second_planet != idx_first_planet)
			((planet_t *)first_planet->data)->planets_killed++;

	} else {
		// decrements the shield's value
		*(int *)second_shield->data -= one;
	}
}

void destroy_galaxy(doubly_linked_list_t **planets)
{
	dll_node_t *node = (*planets)->head;

	// checks if the galaxy isnt allocated
	if (!planets)
		return;

	// iterates through the list of planets and frees
	// every single one of them
	for (uint i = 0; i < (*planets)->size; i++) {
		doubly_linked_list_t *shields = ((planet_t *)node->data)->shields;
		dll_free(&shields);

		node = node->next;
	}

	// frees the galaxy
	dll_free(planets);
	*planets = NULL;
}

void rotate_planet(doubly_linked_list_t *planets)
{
	uint idx_planet, units;
	char direction;
	dll_node_t *curr_planet, *shield_head;

	fscanf(stdin, "%d %c%d", &idx_planet, &direction, &units);

	// checks if the given direction is permitted
	if (direction != 'c' && direction != 't') {
		fprintf(stdout, "Not a valid direction!\n");
		return;
	}

	// checks if the index is out of bounds
	if (idx_planet >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	// gets the planet wanted from the given index
	curr_planet = dll_get_nth_node(planets, idx_planet);

	// calculates the units so the shields wont repeat
	units = units % (((planet_t *)curr_planet->data)->shields->size);

	// gets the head of the list of shields
	shield_head = ((planet_t *)curr_planet->data)->shields->head;

	// iterates through the list of the shields and rotate the list
	// in the specified direction
	for (uint i = 0; i < units; i++) {
		if (direction == 't')
			shield_head = shield_head->next;
		else
			dll_move_first(&shield_head, shield_head->prev);
	}

	// initializes the new head of the list of shields
	((planet_t *)curr_planet->data)->shields->head = shield_head;
}
