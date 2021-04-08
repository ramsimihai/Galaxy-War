// Copyright 2020 - 2021 - 311CA - Mihai Daniel Soare
#ifndef  GALACTIC_WAR_UTILS_H_
#define  GALACTIC_WAR_UTILS_H_

#define MAX_NAME_SIZE 256

typedef unsigned int uint;

// the structure used to define a planet
typedef struct {
	char name[MAX_NAME_SIZE];
	doubly_linked_list_t *shields;
	int planets_killed;
} planet_t;

// create a new planet and add it in the galaxy
void add_planet(doubly_linked_list_t *planets);

// remove a planet from the galaxy
void black_hole(doubly_linked_list_t *planets);

// show a planet details, like the name, neighbours, shields
// and the planets killed by the planet
void show_planet(doubly_linked_list_t *planets);

// upgrades a given shield of a planet with a given value
void upgrade_shields_of_planet(doubly_linked_list_t *planets);

// add a new shield to a planet with a given value
void exp_planet(doubly_linked_list_t *planets);

// remove a shield from a planet
void remove_shield(doubly_linked_list_t *planets);

// collide two planets and decrement one shield of both of the planets
void collide_planets(doubly_linked_list_t *planets);

// rotate the shields of a planet in a specified direction
// by a number of shields
void rotate_planet(doubly_linked_list_t *planets);

// free the planets allocated and the galaxy
void destroy_galaxy(doubly_linked_list_t **planets);

#endif  // GALACTIC_WAR_UTILS_H_
