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

	fscanf(stdin, "%s", name);
	fscanf(stdin, "%d%d", &idx_planet, &nr_shields);

	if (idx_planet > planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	new_planet.shields = dll_create(sizeof(int));

	for (uint i = 0; i < nr_shields; i++)
		dll_add_nth_node(new_planet.shields, 0, &one);

	memcpy(new_planet.name, name, sizeof(name));
	new_planet.planets_killed = 0;

	dll_add_nth_node(planets, idx_planet, &new_planet);

	fprintf(stdout, "The planet %s has joined the galaxy.\n", new_planet.name);
}

void black_hole(doubly_linked_list_t *planets)
{
	uint index;
	dll_node_t *removed;
	doubly_linked_list_t *shields;

	fscanf(stdin, "%d", &index);
	if (index >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	removed = dll_remove_nth_node(planets, index);
	fprintf(stdout, "The planet %s has been eaten by the vortex.\n",
			((planet_t *)removed->data)->name);
	shields = ((planet_t *)removed->data)->shields;
	dll_free(&shields);
	free(removed->data);
	free(removed);
}

void show_planet(doubly_linked_list_t *planets)
{
	uint index;
	dll_node_t *curr, *curr_shields;
	scanf("%d", &index);

	if (!planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	if (index >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

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
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	curr_planet = dll_get_nth_node(planets, idx_planet);

	if (idx_shield >= ((planet_t *)curr_planet->data)->shields->size) {
		printf("Shield out of bounds!\n");
		return;
	}

	curr_shield = dll_get_nth_node(((planet_t *)curr_planet->data)->shields,
									idx_shield);

	*(int *)curr_shield->data += upgrade_value;
}

void exp_planet(doubly_linked_list_t *planets)
{
	uint idx_planet;
	int value_shield;
	dll_node_t *first_shield, *curr_planet, *new_shield;

	fscanf(stdin, "%d%d", &idx_planet, &value_shield);

	if (idx_planet >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
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

void remove_shield(doubly_linked_list_t *planets)
{
	uint idx_planet, idx_shield;
	dll_node_t *curr_planet, *curr_shield;

	fscanf(stdin, "%d%d", &idx_planet, &idx_shield);

	if (idx_planet >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	curr_planet = dll_get_nth_node(planets, idx_planet);

	if (idx_shield >= ((planet_t *)curr_planet->data)->shields->size) {
		fprintf(stdout, "Shield out of bounds!\n");
		return;
	}

	curr_shield = dll_get_nth_node(((planet_t *) curr_planet->data)->shields,
									idx_shield);

	if (idx_shield >= ((planet_t *) curr_planet->data)->shields->size) {
		fprintf(stdout, "Shield out of bounds!\n");
		return;
	}

	if (((planet_t *) curr_planet->data)->shields->size <= MIN_SHIELDS) {
		fprintf(stdout, "A planet cannot have less than 4 shields!\n");
		return;
	}

	curr_shield = dll_remove_nth_node(((planet_t *)curr_planet->data)->shields,
									  idx_shield);
	free(curr_shield->data);
	free(curr_shield);
}

static void destroy_planet(doubly_linked_list_t *planets, uint idx_planet)
{
	if (!planets)
		return;

	dll_node_t *removed = dll_remove_nth_node(planets, idx_planet);
	doubly_linked_list_t *shields = ((planet_t *)removed->data)->shields;
	dll_free(&shields);
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

	if (idx_first_planet >= planets->size || idx_second_planet >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	first_planet = dll_get_nth_node(planets, idx_first_planet);
	second_planet = dll_get_nth_node(planets, idx_second_planet);

	first_shield = dll_get_nth_node(((planet_t *)first_planet->data)->shields,
									((planet_t *)first_planet->data)->shields->size / 4);
	second_shield = dll_get_nth_node(((planet_t *)second_planet->data)->shields,
										((planet_t *)second_planet->data)->shields->size / 4 * 3);

	if (*(int *)first_shield->data == 0) {
		fprintf(stdout, "The planet %s has imploded.\n",
				((planet_t *)first_planet->data)->name);

		destroy_planet(planets, idx_first_planet);

		idx_second_planet = idx_first_planet;

		((planet_t *)second_planet->data)->planets_killed++;

	} else {
		*(int *)first_shield->data -= one;
	}

	if (*(int *)second_shield->data == 0) {
		fprintf(stdout, "The planet %s has imploded.\n",
				((planet_t *)second_planet->data)->name);

		destroy_planet(planets, idx_second_planet);

		if (idx_second_planet != idx_first_planet)
			((planet_t *)first_planet->data)->planets_killed++;

	} else {
		*(int *)second_shield->data -= one;
	}
}

void destroy_galaxy(doubly_linked_list_t **planets)
{
	dll_node_t *node = (*planets)->head;

	if (!planets)
		return;

	for (uint i = 0; i < (*planets)->size; i++) {
		doubly_linked_list_t *shields;
		shields = ((planet_t *)node->data)->shields;
		dll_free(&shields);
		node = node->next;
	}

	dll_free(planets);
	*planets = NULL;
}

void rotate_planet(doubly_linked_list_t *planets)
{
	uint idx_planet, units;
	char direction;
	dll_node_t *curr_planet, *shield_head;

	fscanf(stdin, "%d %c%d", &idx_planet, &direction, &units);

	if (direction != 'c' && direction != 't') {
		fprintf(stdout, "Not a valid direction!\n");
		return;
	}

	if (idx_planet >= planets->size) {
		fprintf(stdout, "Planet out of bounds!\n");
		return;
	}

	curr_planet = dll_get_nth_node(planets, idx_planet);
	units = units % (((planet_t *)curr_planet->data)->shields->size);
	shield_head = ((planet_t *)curr_planet->data)->shields->head;

	for (uint i = 0; i < units; i++) {
		if (direction == 't')
			shield_head = shield_head->next;
		else
			dll_move_first(&shield_head, shield_head->prev);
	}
	((planet_t *)curr_planet->data)->shields->head = shield_head;
}
