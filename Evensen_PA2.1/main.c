#include"doublyLinkedList.h"

/*******************************************************************************
 * Programmer: Drew Evensen		                                               *
 * Class: CptS 122; Lab Section 7                                              *
 * Programming Assignment: 2	                                               *
 * Date: 9/9/22                                                                *
 *                                                                             *
 * Description: Simulates a Digital Music Manager where the user may insert,   *
 *				display, modify, rate, and play music						   *
 ******************************************************************************/

 // Topdown Plan:
 // Method for user input
 // List implementation
 // File Manager
 // Print List method
 // Search List method
 // Delete Node method
 // Sorting method
 // Random Number generator

int main(int argc, char argv[])
{
	// Linked list entry point
	Node* pHead = NULL;

	// Record the user's input
	int intSelect = -1;
	char strSelect[50] = "";

	// While the user has not chosen to exit:
	while (intSelect != 11)
	{
		// Clear the screen on successive loops
		system("cls");

		// Prompt the user for their input
		puts("Welcome, please make a selection:\n");
		puts("1)  load\n2)  store\n3)  display\n4)  insert\n5)  delete\n6)  edit\n7)  sort\n8)  rate\n9)  play\n10) shuffle (NOT AVAILABLE)\n11) exit");
		intInput(&intSelect);

		// Preform the chosen action by the user
		system("cls");
		switch (intSelect)
		{
			// Load songs (Complete)
			case 1:
			{
				// Catches lines in the file
				char line[100] = "";

				// Open the song file
				FILE* inFile = fopen("musicPlayList.csv", "r");

				// Check for success
				if (inFile == NULL)
				{
					puts("ERROR: Could not open music playlist. Please close the file.");
					break;
				}

				puts("Loading songs...");

				// Extract the songs from the csv file
				while (fgets(line, 99, inFile) != NULL)
					loadSong(&pHead, line);

				// Close the file
				fclose(inFile);

				puts("Songs loaded");

				break;
			}

			// Save songs (Complete)
			case 2:
			{
				// Check to see if there are songs to save
				if (pHead != NULL)
				{
					// Open the song file
					FILE* outFile = fopen("musicPlayList.csv", "w");

					// Check for success
					if (outFile == NULL)
					{
						puts("ERROR: Could not open music playlist. Please close the file.");
						break;
					}

					puts("Saving...");

					// Print contents of the list to the file
					savePlayList(pHead, outFile);

					// Close the file
					fclose(outFile);

					puts("Saved");
				}
				else
					puts("No Songs Loaded");

				break;
			}

			// Display songs (Complete)
			case 3:
			{
				// Check to see if the list is empty
				if (pHead != NULL)
				{
					puts("How would you like to print the list?\n1) Print All\n2) By Artist\n");
					intInput(&intSelect);

					// Print All
					if (intSelect == 1)
						printList(pHead);

					// Print by Artist
					else if (intSelect == 2)
					{
						puts("\nPlease enter the Artist's name (Last Name, First Name)");
						scanf(" %[^\n]s", &strSelect);
						printFilteredList(strSelect, pHead);
					}
					// Did not select 1 or 2
					else
						puts("Unknown Command");
				}
				else
					puts("No Songs Loaded");

				break;
			}

			// Insert Song (Complete)
			case 4:
			{
				// New song to add to the list
				Record newRecord = { "", "", "", "", {0, 0}, 0, 0 };

				// Populate the record with data
				printf("Name of Artist: ");
				scanf(" %[^\n]s", strSelect);
				strcpy(newRecord.artist, strSelect);

				printf("\nName of Song: ");
				scanf(" %[^\n]s", strSelect);
				strcpy(newRecord.sonTitle, strSelect);

				printf("\nName of Album: ");
				scanf(" %[^\n]s", strSelect);
				strcpy(newRecord.albTitle, strSelect);

				printf("\nGenre of Song: ");
				scanf(" %[^\n]s", strSelect);
				strcpy(newRecord.genre, strSelect);

				puts("Song Duration");
				printf("Minutes: ");
				intInput(&newRecord.length.minutes);

				printf("Seconds: ");
				intInput(&newRecord.length.seconds);

				printf("Song Rating /5: ");
				intInput(&intSelect);
				// Clamp values between 1 and 5 inclusively
				if (intSelect < 1)
					intSelect = 1;
				if (intSelect > 5)
					intSelect = 5;
				newRecord.rating = intSelect;

				insertFront(&pHead, &newRecord);

				break;
			}

			// Delete Song (Complete)
			case 5:
			{
				printList(pHead);

				printf("Name of Song: ");
				scanf(" %[^\n]s", strSelect);

				deleteNode(&pHead, strSelect);

				break;
			}

			// Edit list (Complete)
			case 6:
			{
				// Requested Node
				Node* reqNode = NULL;

				// Obtain the name of the artist
				printf("Name of the Artist (Last name, First name): ");
				scanf(" %[^\n]s", strSelect);

				// Grab the Node from the heap
				reqNode = searchList(pHead, strSelect);

				// Check to see if Node was obtained
				if (reqNode != NULL)
				{
					// Reset selection
					intSelect = 0;

					// Edit until user quits
					while (intSelect != 8)
					{
						// Refresh the screen after every edit
						system("cls");

						printNode(reqNode);
						puts("What would you like to change?");
						puts("1) Song Title\n2) Album Title\n3) Artist\n4) Genre\n5) Duration\n6) Rating\n7) Play Count\n8) Finish");

						// Get input from the user
						intInput(&intSelect);

						// Change the field chosen by the user
						switch (intSelect)
						{
							// Song Title
							case 1:
							{
								// Obtain the new title
								puts("New Song Title:");
								scanf(" %[^\n]s", strSelect);

								// Assign the new title
								strcpy(reqNode->songData.sonTitle, strSelect);
								break;
							}
							// Album Title
							case 2:
							{
								// Obtain the new title
								puts("New Album Title:");
								scanf(" %[^\n]s", strSelect);

								// Assign the new title
								strcpy(reqNode->songData.albTitle, strSelect);
								break;
							}
							// Artist
							case 3:
							{
								// Obtain the new artist
								puts("New Artist:");
								scanf(" %[^\n]s", strSelect);

								// Assign the new artist
								strcpy(reqNode->songData.artist, strSelect);
								break;
							}
							// Genre
							case 4:
							{
								// Obtain the new genre
								puts("New Genre:");
								scanf(" %[^\n]s", strSelect);

								// Assign the new genre
								strcpy(reqNode->songData.genre, strSelect);
								break;
							}
							// Duration
							case 5:
							{
								// Obtain and assign new minute and second values
								puts("Minute Value:");
								intInput(&intSelect);
								reqNode->songData.length.minutes = intSelect;

								puts("Second Value:");
								scanf(" %[^\n]s", strSelect);
								reqNode->songData.length.seconds = atoi(strSelect);
								break;
							}
							// Rating
							case 6:
							{
								// Obtain and assign new rating
								puts("New Rating /5:");
								intInput(&intSelect);

								// Clamp values between 1 and 5 inclusively
								if (intSelect < 1)
									intSelect = 1;
								if (intSelect > 5)
									intSelect = 5;

								reqNode->songData.rating = intSelect;
								break;
							}
							// Play Count
							case 7:
							{
								// Obtain and assign new play count value
								puts("Times Played:");
								intInput(&intSelect);
								reqNode->songData.timesPlayed = intSelect;
								break;
							}
						} // End of switch()
					} // End of while()
				}// End of if()
				else
					puts("Could Not Find Song");

				break;
			}

			// Sort (Complete)
			case 7:
			{
				// Prompt the user for a selection
				puts("How would you like to sort the playlist?\n1) Artist (A-Z)\n2) Album (A-Z)\n3) Rating (1-5)\n4) Times Played (low-high)");
				intInput(&intSelect);

				// Sort via Insertion Sort
				switch (intSelect)
				{
					// Sort by Artist
					case 1:
					{
						if (pHead != NULL)
						{
							puts("Sorting...");
							artistInsertionSort(&pHead);
							puts("Sorted");
						}
						else
							puts("No Songs Loaded");

						break;
					}
					// Sort by Album
					case 2:
					{
						if (pHead != NULL)
						{
							puts("Sorting...");
							albumInsertionSort(&pHead);
							puts("Sorted");
						}
						else
							puts("No Songs Loaded");

						break;
					}
					// Sort by Rating
					case 3:
					{
						if (pHead != NULL)
						{
							puts("Sorting...");
							rateInsertionSort(&pHead);
							puts("Sorted");
						}
						else
							puts("No Songs Loaded");

						break;
					}
					// Sort by Times Played
					case 4:
					{
						if (pHead != NULL)
						{
							puts("Sorting...");
							tPlayedInsertionSort(&pHead);
							puts("Sorted");
						}
						else
							puts("No Songs Loaded");

						break;
					}
				}

				break;
			}

			// Rate (Complete)
			case 8:
			{
				// Requested Node
				Node* reqNode = NULL;

				// Obtain the name of the artist
				printf("Name of the Artist (Last name, First name): ");
				scanf(" %[^\n]s", strSelect);

				// Grab the Node from the heap
				reqNode = searchList(pHead, strSelect);

				// Check to see if node was obtained
				if (reqNode != NULL)
				{
					// Print the Node
					printNode(reqNode);

					// Obtain new rating from the user
					puts("New Rating /5:");
					intInput(&intSelect);

					// Clamp values between 1 and 5 inclusively
					if (intSelect < 1)
						intSelect = 1;
					if (intSelect > 5)
						intSelect = 5;

					reqNode->songData.rating = intSelect;
				}
				else
					puts("Could Not Find Song");

				break;
			}

			// Play (Complete)
			case 9:
			{
				// Check to see if list is empty
				if (pHead != NULL)
				{
					// Node to be played
					Node* playing;

					// Display all songs
					printList(pHead);
					// Get the song the user would like to start at
					printf("What song would you like to play?: ");
					scanf(" %[^\n]s", strSelect);
					playing = searchListTitle(pHead, strSelect);

					// "Play" the selected song and continue through the list in order
					while (playing != NULL)
					{
						system("cls");
						printNode(playing);
						Sleep(5000);
						playing->songData.timesPlayed++; // Increment times played counter
						playing = playing->pNext;
					}
				}
				else
					puts("No Songs Loaded");

				break;
			}

			// Shufle
			case 10:
			{
				// Check to see if list is mepty
				if (pHead != NULL)
				{
					// Get the length of the list
					int len = lenList(pHead);

					shufflePlaylist(pHead, len);
				}

				break;
			}

			// Exit
			case 11:
			{
				// Save the list upon exit
				if (pHead != NULL)
				{
					FILE* outFile = fopen("musicPlayList.csv", "w");

					savePlayList(pHead, outFile);

					fclose(outFile);
				}
				return 0;
			}
		}

		// Pause on each loop
		system("pause");
	}
}