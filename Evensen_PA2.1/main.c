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
		puts("1)  load\n2)  store\n3)  display\n4)  insert (NOT AVAILABLE)\n5)  delete (NOT AVAILABLE\n6)  edit\n7)  sort (NOT AVAILABLE)\n8)  rate\n9)  play\n10) shuffle (NOT AVAILABLE)\n11) exit");
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
					puts("List is empty");

				break;
			}

			// Edit list
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
					puts("Could Not Find Node");

				break;
			}

			// Exit
			case 11:
			{
				return 0;
			}
		}

		system("pause");
	}
}