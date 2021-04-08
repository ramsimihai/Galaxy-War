// Galactic war - Homework
// Copyright - Mihai Daniel Soare - 311CA - 2020 - 2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./CircularDoublyLinkedList.h"
#include "./galactic_war_utils.h"

#define MAX_NAME_SIZE 256
#define MAX_COMMAND 4

int main(void)
{
	doubly_linked_list_t *planets;
	int number_commands;
	char command[MAX_COMMAND];

	// creates the galaxy
	planets = dll_create(sizeof(planet_t));

	fscanf(stdin, "%d", &number_commands);

	for (int i = 0; i < number_commands; i++) {
		fscanf(stdin, " %s", command);

		if (strcmp(command, "ADD") == 0) {
			add_planet(planets);

		} else if (strcmp(command, "BLH") == 0) {
			black_hole(planets);

		} else if (strcmp(command, "UPG") == 0) {
			upgrade_shields_of_planet(planets);

		} else if (strcmp(command, "EXP") == 0) {
			exp_planet(planets);

		} else if (strcmp(command, "RMV") == 0) {
			remove_shield(planets);

		} else if (strcmp(command, "COL") == 0) {
			collide_planets(planets);

		} else if (strcmp(command, "ROT") == 0) {
			rotate_planet(planets);

		} else if (strcmp(command, "SHW") == 0) {
			show_planet(planets);
		}
	}

	destroy_galaxy(&planets);

	return 0;
}
