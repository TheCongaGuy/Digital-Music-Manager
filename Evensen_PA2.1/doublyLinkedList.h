#ifndef DOUBLY_LINKED_LIST_H // Guard Code Start
#define DOUBLY_LINKED_LIST_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> // puts(), printf(), fprintf(), fopen(), fclose(), fgets(), gets(), scanf()
#include <stdlib.h> // atoi(), malloc(), srand(), rand()
#include <string.h> // strcpy(), strcmp()
#include <time.h> // time()
#include <Windows.h> // Sleep()

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

	int timesPlayed;
	int rating;
} Record;

// Represents a node of data in the doubly linked list
typedef struct node
{
	Record songData;
	struct node* pPrev;
	struct node* pNext;
} Node;

// Takes input from the user and stores it into the given variable
// Takes a pointer to an int variable; changing the value upon sucessful conversion
void intInput(int* var);

// Print the contents of a Node
// Takes a Node; cannot be NULL
void printNode(Node* sListEntry);

// Print the contents of a list recursively
// Takes a Node to start from; cannot be NULL
void printList(Node* sListEntry);

// Print the filtered contents of a list recursively
// Takes a name to search for and a Node to start from; Neither can be NULL
void printFilteredList(char* target, Node* sListEntry);

// Inserts a song to the front of a doubly linked list of songs
// Takes a Node list (pointer to a pointer to a node) and a pointer to a Record
// Returns an int of success; 0 = failure, 1 = success
int insertFront(Node** songList, Record* pSong);

// Gets the current size of a list
// Takes a pointer to a pointer to a list
// Returns the number of items in the list
int lenList(Node* playList);

// Converts a string of data to a Record and adds it to the given list
// Takes a pointer to the play list and a char pointer to a formatted string
// Return an int of success; 0 = failure, 1 = success
int loadSong(Node** playList, char* dataLine);

// Save the entries in the list from back to front; preserving the order of the origonal file
// Takes a pointer to a list and a file to print to; Neither the list nor the file may be NULL
// Returns number of songs saved
int savePlayList(Node* playList, FILE* location);

// Grab the address of a node from the heap based on an artist
// Takes a pointer to a list and a search string; Neither the list nor the string may be NULL
// Returns the address of a node in the heap
Node* searchList(Node* playList, char* searchString);

// Grab the address of a node from the heap based on song title
// Takes a pointer to a list and a search string; Neither the list nor the string may be NULL; Assumes no duplicates
// Returns the address of a node in the heap
Node* searchListTitle(Node* playList, char* searchString);

// Delete a specific node from the list
// Takes a pointer to a pointer to a list, and a search string; Neither the list nor the string may be NULL
void deleteNode(Node** playList, char* searchString);

// "Plays" songs through a playlist at a given entry point
// Takes a pointer to a song
void play(Node* song);

// Sort a list A-Z by artist via insertion sort
// Takes a pointer to a pointer to a list; cannot be NULL
void artistInsertionSort(Node** playList);

// Sort a list A-Z by album title via insertion sort
// Takes a pointer to a pointer to a list; cannot be NULL
void albumInsertionSort(Node** playList);

// Sort a list lowest to highest by ratings via insertion sort
// Takes a pointer to a pointer to a list; cannot be NULL
void rateInsertionSort(Node** playList);

// Sort a list lowest to highest by times played via insertion sort
// Takes a pointer to a pointer to a list
void tPlayedInsertionSort(Node** playList);

// Play the playlist in a random order
// Takes a pointer to a list and the size of that list; neither may be NULL
int* shufflePlaylist(Node* playList, int length);

#endif // Guard Code end