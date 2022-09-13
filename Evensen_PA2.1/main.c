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
 // Edit method

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
				// Obtain the name of the artist
				printf("Name of the Artist (Last name, First name): ");
				scanf(" %[^\n]s", strSelect);

				// Grab the Node from the heap
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