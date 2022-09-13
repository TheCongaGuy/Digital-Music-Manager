#include "doublyLinkedList.h"

/*******************************************************************************
 * Programmer: Drew Evensen		                                               *
 * Class: CptS 122; Lab Section 7                                              *
 * Programming Assignment: 2	                                               *
 * Date: 9/9/22                                                                *
 *                                                                             *
 * Description: Simulates a Digital Music Manager where the user may insert,   *
 *				display, modify, rate, and play music						   *
 ******************************************************************************/

 // Takes input from the user and attempts to convert it into an integer value.
 // Assigns the given variable the value upon sucessfull conversion
void intInput(int* pVar)
{
	char input[50] = "";
	if (scanf("%s", input) != EOF)
		*pVar = atoi(input);
}

// Allocates memory in the heap for a new node
// Takes a pointer to a Record
// Returns a pointer to the node in the heap
Node* makeNode(Record* pSong)
{
	// Allocate space for the new node
	Node* pMem = malloc(sizeof(Node));

	// Add data if space was allocated successfully
	if (pMem != NULL)
	{
		strcpy(pMem->songData.artist, pSong->artist);
		strcpy(pMem->songData.albTitle, pSong->albTitle);
		strcpy(pMem->songData.sonTitle, pSong->sonTitle);
		strcpy(pMem->songData.genre, pSong->genre);
		pMem->songData.length = pSong->length;
		pMem->songData.timesPlayed = pSong->timesPlayed;
		pMem->songData.rating = pSong->rating;

		pMem->pNext = NULL;
		pMem->pPrev = NULL;
	}

	return pMem;
}

// Inserts a song to the front of a doubly linked list of songs
// Takes a Node list (pointer to a pointer to a node) and a pointer to a Record
// Returns an int of success; 0 = failure, 1 = success
int insertFront(Node** songList, Record* pSong)
{
	// Track success of insertion
	int success = 0;

	// Pointer to new node in the heap
	Node* pMem = makeNode(pSong);
	// pPrev setter
	Node* pCur = *songList;

	// Insert the node if space has been allocated successfully
	if (pMem != NULL)
	{
		success = 1;

		// *songList ==> pHead of list
		pMem->pNext = *songList;
		*songList = pMem;

		// Assign the previous pointer if it exists
		if (pCur != NULL)
			pCur->pPrev = pMem;
	}

	return success;
}

// Print the contents of a Node
// Takes a Node; cannot be NULL
void printNode(Node* sListEntry)
{
	printf("Title:  %s\n", sListEntry->songData.sonTitle);
	printf("Album:  %s\n", sListEntry->songData.albTitle);
	printf("Artist: %s\n", sListEntry->songData.artist);
	printf("Genre:  %s\n", sListEntry->songData.genre);

	printf("%d:%d\n", sListEntry->songData.length.minutes, sListEntry->songData.length.seconds);
	printf("%d/5 Stars\n", sListEntry->songData.rating);
	printf("Played: %d\n", sListEntry->songData.timesPlayed);
	// Add a divider
	puts("--------------");
}

// Print the contents of a list recursively
// Takes a Node to start from; cannot be NULL
void printList(Node* sListEntry)
{
	printNode(sListEntry);

	// If we have not reached the end of the list, continue on
	if (sListEntry->pNext != NULL)
		printList(sListEntry->pNext);
}

// Print the filtered contents of a list recursively
// Takes a name to search for and a Node to start from
void printFilteredList(char* target, Node* sListEntry)
{
	if (strcmp(target, sListEntry->songData.artist) == 0)
	{
		printf("Title:  %s\n", sListEntry->songData.sonTitle);
		printf("Album:  %s\n", sListEntry->songData.albTitle);
		printf("Artist: %s\n", sListEntry->songData.artist);
		printf("Genre:  %s\n", sListEntry->songData.genre);

		printf("%d:%d\n", sListEntry->songData.length.minutes, sListEntry->songData.length.seconds);
		printf("%d/5 Stars\n", sListEntry->songData.rating);
		printf("Played: %d\n", sListEntry->songData.timesPlayed);
		// Add a divider
		puts("--------------");
	}

	// If we have not reached the end of the list, continue on
	if (sListEntry->pNext != NULL)
		printFilteredList(target, sListEntry->pNext);
}

// Convert a string of data to Record
// Takes a pointer to the play list and a char pointer to a formatted string
// Return an int of success; 0 = failure, 1 = success
int loadSong(Node** playList, char* dataLine)
{
	// Create a new empty record
	Record newSong = { "", "", "", "", {-1, -1}, 0, 0 };

	// Extract the artist's name
	if (strchr(dataLine, '"') == NULL)
		strcpy(newSong.artist, strtok(dataLine, ",")); // Copy to newSong artist the value up to the first comma
	else
		strcpy(newSong.artist, strtok(strchr(dataLine, '"'), "\"")); // Copy to newSong artist the value between the first and second quotation mark

	// Extract the rest of the string values
	strcpy(newSong.albTitle, strtok(NULL, ","));
	strcpy(newSong.sonTitle, strtok(NULL, ","));
	strcpy(newSong.genre, strtok(NULL, ","));

	// Extract the int values
	newSong.length.minutes = atoi(strtok(NULL, ":"));
	newSong.length.seconds = atoi(strtok(NULL, ","));
	newSong.timesPlayed = atoi(strtok(NULL, ","));
	newSong.rating = atoi(strtok(NULL, "\n"));

	// Insert the new song to the front of the play list
	return insertFront(playList, &newSong);
}

// Save the entries in the list from back to front; preserving the order of the origonal file
// Takes a pointer to a list and a file to print to; Neither the list nor the file may be NULL
// Returns number of songs saved
int savePlayList(Node* playList, FILE* location)
{
	// Song count
	int count = 0;

	// Traversal pointers
	Node* pCur = playList;

	// Find the end of the list
	while (pCur->pNext != NULL)
		pCur = pCur->pNext;

	// Print the records from back to front
	while (pCur != NULL)
	{
		// Add "" if the artist has more than one name value
		if (strchr(pCur->songData.artist, ',') != NULL)
			fprintf(location, "\"%s\",", pCur->songData.artist);
		else
			fprintf(location, "%s,", pCur->songData.artist);

		// Print the rest of the string attributes
		fprintf(location, "%s,", pCur->songData.albTitle);
		fprintf(location, "%s,", pCur->songData.sonTitle);
		fprintf(location, "%s,", pCur->songData.genre);

		// Print the int attributes
		fprintf(location, "%d:%d,", pCur->songData.length.minutes, pCur->songData.length.seconds);
		fprintf(location, "%d,", pCur->songData.timesPlayed);
		fprintf(location, "%d\n", pCur->songData.rating);

		// Update the counter and continue through the list
		count++;
		pCur = pCur->pPrev;
	}

	return count;
}

// Grab the address of a node from the heap based on an artist
// Takes a pointer to a list and a search string; Neither the list nor the string may be NULL
// Returns the address of a node in the heap
Node* searchList(Node* playList, char* searchString)
{
	// Number of nodes found
	int nFound = 0;
	// User input
	int intSelect = 0;

	// Traversal pointer
	Node* pCur = playList;

	puts("Please Select Desired Song:");

	// Search through the list for matching nodes
	while (pCur != NULL)
	{
		if (strcmp(searchString, pCur->songData.artist) == 0)
		{
			nFound++;
			printf("%d) %s\n", nFound, pCur->songData.sonTitle);
		}

		// Traverse the list
		pCur = pCur->pNext;
	}

	// Obtain user input if matches found
	if (nFound > 0)
	{
		intInput(&intSelect);

		// Fetch requested node
		pCur = playList;
		for (int i = 0; i <= intSelect;)
		{
			// Check for invalid input
			if (pCur == NULL)
				return pCur;

			if (strcmp(searchString, pCur->songData.artist) == 0)
			{
				// Break the loop if we found our Node
				i++;
				if (i == intSelect)
					return pCur;
			}

			// Traverse the List
			pCur = pCur->pNext;
		}
	}

	// If a valid node was not found, return a NULL pointer
	return NULL;
}