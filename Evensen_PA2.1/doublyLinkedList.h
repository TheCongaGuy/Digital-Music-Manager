#ifndef DOUBLY_LINKED_LIST_H // Guard Code Start
#define DOUBLY_LINKED_LIST_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> // puts(), printf(), fprintf(), fopen(), fclose(), fgets(), gets()
#include <stdlib.h> // atoi(), malloc()
#include <string.h> // strcpy(), strcmp()

/*******************************************************************************
 * Programmer: Drew Evensen		                                               *
 * Class: CptS 122; Lab Section 7                                              *
 * Programming Assignment: 2	                                               *
 * Date: 9/9/22                                                                *
 *                                                                             *
 * Description: Simulates a Digital Music Manager where the user may insert,   *
 *				display, modify, rate, and play music						   *
 ******************************************************************************/

 // Holds a duration in time in minutes and seconds
typedef struct duration
{
	int minutes;
	int seconds;
} Duration;

// Holds data of a piece of music
typedef struct record
{
	char artist[50];
	char albTitle[25];
	char sonTitle[25];
	char genre[25];

	Duration length;

	unsigned int timesPlayed;
	unsigned int rating;
} Record;

// Represents a node of data in the doubly linked list
typedef struct node
{
	Record songData;
	struct Node* pPrev;
	struct Node* pNext;
} Node;

// Takes input from the user and stores it into the given variable
// Takes a pointer to an int variable; changing the value upon sucessful conversion
void intInput(int* var);

// Print the contents of a list recursively
// Takes a Node to start from
void printList(Node* sListEntry);

// Print the filtered contents of a list recursively
// Takes a name to search for and a Node to start from
void printFilteredList(char* target, Node* sListEntry);

// Converts a string of data to a Record and adds it to the given list
// Take a pointer to the play list and a char pointer to a formatted string
// Return an int of success; 0 = failure, 1 = success
int loadSong(Node** playList, char* dataLine);

// Save the entries in the list from back to front; preserving the order of the origonal file
// Takes a pointer to a list and a file to print to; Neither the list nor the file may be NULL
// Returns number of songs saved
int savePlayList(Node* playList, FILE* location);

#endif // Guard Code end