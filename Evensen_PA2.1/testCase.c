#include "testCase.h"

void testInsert()
{
	// Instantiate testing list
	Node* pHead = NULL;
	Record testPoint = { "Perry, Katy", "Witness", "Chained to the Rhythm", "Pop", {4, 36}, -1, 6 };
	insertFront(&pHead, &testPoint);

	// If the function fails to insert anything, it fails
	if (pHead == NULL)
		puts("Fail Test 0 - Did Not Insert");
	// If the function does not assign the correct Artist, it fails
	else if (strcmp(testPoint.artist, pHead->songData.artist) != 0)
		puts("Fail Test 1 - Artist");
	// If the funciton does not assign the correct Album, it fails
	else if (strcmp(testPoint.albTitle, pHead->songData.albTitle) != 0)
		puts("Fail Test 2 - Album");
	// If the function does not assign the correct Title, it fails
	else if (strcmp(testPoint.sonTitle, pHead->songData.sonTitle) != 0)
		puts("Fail Test 3 - Title");
	// If the function does not assign the correct Genre, it fails
	else if (strcmp(testPoint.genre, pHead->songData.genre) != 0)
		puts("Fail Test 4 - Genre");
	// If the function does not assign the correct duration, it fails
	else if (testPoint.length.minutes != pHead->songData.length.minutes || testPoint.length.seconds != pHead->songData.length.seconds)
		puts("Fail Test 5 - Duration");
	// If the number of times played is invalid after insertion, it fails
	else if (pHead->songData.timesPlayed < 0)
		puts("Fail Test 6 - Times Played");
	// If the rating is not between 1 and 5, it fails
	else if (5 < pHead->songData.rating || pHead->songData.rating < 1)
		puts("Fail Test 7 - Rating");

	else
		puts("insertFront() Pass");

	printNode(pHead);
}

void testDelete()
{
	// Instantiate testing list
	Node* pHead = NULL;
	Record testPoint = { "Perry, Katy", "Witness", "Chained to the Rhythm", "Pop", {4, 36}, 3, 5 };
	insertFront(&pHead, &testPoint);
	Node* pMem = pHead;
	deleteNode(&pHead, "Chained to the Rhythm");

	// If the head pointer is not NULL, it fails
	if (pHead != NULL)
		puts("Fail Test 0 - Did Not Remove");
	// If the memory address still exists, it fails
	else if (strcmp("Chained to the Rhythm", pMem->songData.sonTitle) == 0)
		puts("Fail Test 1 - Heap Exists");

	else
		puts("deleteNode() Pass");
}

void testShuffle()
{
	// Instantiate testing list
	Node* pHead = NULL;
	Record records[3] = { 
		{"Perry, Katy", "Witness", "Chained to the Rhythm", "Pop", {4, 36}, 3, 2},
		{ "Siames", "Bounce Into the Music", "The Wolf", "Alternative", {3, 36}, 19, 5 },
		{ "Platapus, Perry", "Grrrrr", "BobeBobeDoBop", "???", {9, 59}, 9999, 5 } 
	};
	insertFront(&pHead, &records[2]);
	insertFront(&pHead, &records[1]);
	insertFront(&pHead, &records[0]);
	int len = lenList(pHead);
	int* indexes = shufflePlaylist(pHead, len);

	// If the index's name is not equivalient to the list's position, it fails
	Node* pCur = pHead;
	for (int i = 0; i < indexes[0] - 1; i++)
		pCur = pCur->pNext;
	if (strcmp(pCur->songData.sonTitle, records[indexes[0] - 1].sonTitle) != 0)
		puts("Failed Test 1 - Incorrect First Shuffle");
	// Check 1 Passed; loop through the list again
	else
	{
		pCur = pHead;
		for (int i = 0; i < indexes[1] - 1; i++)
			pCur = pCur->pNext;
		if (strcmp(pCur->songData.sonTitle, records[indexes[1] - 1].sonTitle) != 0)
			puts("Failed Test 2 - Incorrect Second Shuffle");
		// Check 2 Passed; loop through the list again
		else
		{
			pCur = pHead;
			for (int i = 0; i < indexes[2] - 1; i++)
				pCur = pCur->pNext;
			if (strcmp(pCur->songData.sonTitle, records[indexes[2] - 1].sonTitle) != 0)
				puts("Failed Test 3 - Incorrect Third Shuffle");
			// Check 3 Passed; method has passed
			else
				puts("shufflePlaylist() Pass");
		}
	}
}