# tema1-SD
// Copyright 2020 - 2021 311CA Mihai Daniel Soare

WARNING: i hate to use uppercase letters

Data Structures

Homework #1 Galactic War

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*) first of all, i defined a struct in `galactic_war_utils.h` which containes
the name of a planet, a circular doubly linked list of shields and the number
of planets that the planet killed;

*) the program starts by allocating a new galaxy and reading a number of actions
from the keyboard which can be ADD, BLH, EXP, UPH, RMV, COL, ROT or SHW and by
default at the end of the program the memory allocated will be freed;

**) in the file `CircularDoublyLinkedList` file are operations on cdll that
are going to be needed in the use of the program;

**) in the `utils` file is defined a macro with which the program could verify
if the objects allocated were allocated well;

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

I)
	- if the action is ADD, it reads the details of a new planet and checks if
	if the new planet can be added on the given position;
	- uses a temporary variable to initialize a new planet and initializes its
	name, list of shields and planets killed;
	- uses the generic `dll_add_nth_node` to add the planet on the given
	position;
	- shows a message if the planet could be added in the galaxy;

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

II)
	- if the action is BLH, it reads the index of the planet which is wanted
	to be removed;
	- gets the node of the planet that is wanted to be removed
	- frees its details;
	- shows a message if the planet could be removed;

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

III)
	- if the action is SHW, it reads the index of the planet which is wanted
	to be seen;
	- verifies if the planet located at the index exists;
	- gets the planet at the given index;
	- shows its name, closest neighbours, the list of shields and the number
	of planets killed;

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

IV)
	- if the action is UPG, it reads the index of the planet, the index of the
	shield, and a new upgrade value that is gonna be added at the old value at
	the given position;
	- verifies if the planet exists and gets it;
	- verifies if the shield exists and gets it;
	- increments the value of the shield with the given value;

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

V)
	- if the action is EXP, it reads the index of the planet and the new value
	of the new shield that is gonna be added in the last position of the lists
	of shields;
	- gets the planet at the specified index;
	- gets the head of the list of shields;
	- creates a new shield with the specified value;
	- adds it on the last position of the list of shields;
	- increments the size of the list of shields;

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

VI)
	- if the actions is RMV, it reads the index of the planet and the index of
	the shield that is gonna be removed;
	- verifies if the planet exists and gets it;
	- verifies if the shield exists and gets it;
	- verifies if there are more than 4 actual shields and the shield could be
	removed;
	- removes the shield by using the operation of removing a node from a cdll;
	- frees the shield;

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

VII)
	- if the action is COL, it reads the index of two planets that are going to
	collide by a shield;
	- verifies if the planets at the specified indexes exist;
	- gets the shields from each planet that are going to collide
		*) first planet shield is located at size of first planet / 4;
		*) second planet shield is located at size of second planet / 4 * 3;
	- checks if the shield value from each planet is zero, if that happens, 
	the planet whose shield got zero value will be destroyed and the other
	planet will get a point in the planets killed section;

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

VIII)
	- if the action is ROT, it reads the index of the planet, the direction
	in which the shields gonna rotate and number of units;
	- verifies if the direction is permitted;
	- verifies if the planet exists;
	- gets the planet;
	- verifies if the shield list exist;
	- rotates the shield list by the units given;

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
