// Copyright 2020 - 2021 - 311CA - Mihai Daniel Soare
#ifndef  GALACTIC_WAR_UTILS_H_
#define  GALACTIC_WAR_UTILS_H_

#define MAX_NAME_SIZE 256

typedef unsigned int uint;

typedef struct {
	char name[MAX_NAME_SIZE];
	doubly_linked_list_t *shields;
	int planets_killed;
} planet_t;

void add_planet(doubly_linked_list_t *planets);

void black_hole(doubly_linked_list_t *planets);

void show_planet(doubly_linked_list_t *planets);

void upgrade_shields_of_planet(doubly_linked_list_t *planets);

void exp_planet(doubly_linked_list_t *planets);

void remove_shield(doubly_linked_list_t *planets);

void collide_planets(doubly_linked_list_t *planets);

void rotate_planet(doubly_linked_list_t *planets);

void destroy_galaxy(doubly_linked_list_t **planets);

#endif  // GALACTIC_WAR_UTILS_H_
