# Digital Music Manager
This program simulates a Digital Music Manager through a csv file containing data on various songs in a playlist. For this assignment I had to really get comfortable at managing and allocating memory in the heap with `malloc()`, a library method I had never used before. While it was a bit tricky to understand at first especially with `Node**` syntax, I found it facinating with what you can do with a few pointers. This forced me to get quite comfortable with pointers and how they can be used. This is only part one of this assignment and it will be finished later on. This is what is done so far

- [x] Load
- [x] Store
- [x] Display
- [ ] Insert
- [ ] Delete
- [x] Edit
- [ ] Sort
- [x] Rate
- [x] Play
- [ ] Shuffle

---

This program works around a csv file working as our memory; everything changed in the playlist will be saved to this csv file, and everything loaded into the program will be from this csv file. For this implementation of the music manager, we really only needed a method for user input, implementation for a doubly linked list, a file manager, and methods to search and display information from the linked list.

| Artist          | Album Title | Song Title    | Genre | Song Length | Times Played  | Rating  |
| :---:           | :---:       | :---:         | :---: | :---:       | :---:         | :---:   |
| "Swift, Taylor" | 1989        | Shake it Off  | Pop   | 3:35        | 12            | 3       |

Before we can modify our playlist we first need to load it into our program. Above is an example line of data that would come in through the csv file. How I went about parsing this data and inserting it into their respective fields was using a combination of `strtok()` and `strchr()` to find segments of data. `strtok()` would seperate the strings into tokens to be used, but look at the song length collumn. There is no clean way to simply convert that into a set of integers.
```
// Impossible
musicData.length = atoi(strtok(NULL, ","));
```
Instead, we need to look for the seperation of the two integers, the ":" in this case. We can't take that entire value out in one go, but we can seperate it into two tokens and assign the values that way. A similar problem occurs with the Artist field. Using `strtok()` won't work here because we will either pick up on the quotation marks, or only get the first name. We can use `strchr()` to check for these characters and parse accordingly to be able to insert any field.

---

Editing the list is what the majority of this assignment was about. There needed to be a way to travel not only forward in the list, but also backward; hence the doubly linked list. On top of that, there also had to be a method to search the entire list for a specific song and save the list back into the csv file.

| Address         | $100        | $513          | $312     |
|  ---:           | :---:       | :---:         | :---:    |
| Data            | Shake it Off| Own It        | The Motto|
| Next Pointer    | $513        | $312          | NULL     |
| Previous Pointer| NULL        | $100          | $513     |

Take this short doubly linked list for example. The first method that was needed was a way to print the list. That was pretty simple; print the contents of the node and if the next pointer is not NULL, continue on
```
printList($100); --> printList($100->pNext);
printList($513); --> printList($513->pNext);
printList($312); --> printList($312->pNext);
printList(NULL); -/- Stop Printing
```
Next is searching the list. I can't do what I did with `printList()` by recursively going through the list, so I needed to adobt a different approach. I needed to search by the artist's name, but one big problem is when there are multiple entries by one artist. Drake is the artist behind *Own It* and *The Motto* but I can't return two addresses. I also can't assume that the user only wants the first or last occurance of that artist. This might not be the most time efficient approach but my solution was to count how many songs were published by the target artist, ask the user for which song they wanted and go through the list again, counting the instances of that artist to finally arrive at the desired node.
```
searchList($100, "Drake"); --> 1) $513(Own It) | 2) $312(The Motto)
printf(both options);
scanf(for user input, either a 1 or a 2); --> User chooses 1
searchList($100, "Drake"); --> 1) $513(Own It) -/-
return $513;
```
Lastly, we needed to save any changes done to the list back to the file. Since we already had a print list method, we could use that to print to the csv file. However, printing in the same order we have been would actually reverse the playlist we have created. Since we don't want to reverse the playlist at the last second, I chose to simply print the list in reverse; starting at the end of the program and working my way to the front.
```
savePlayList($100); --> Loop through until end --> $312
printNode($312); --> Move backwards --> printNode($312->pPrev);
printNode($513); --> printNode($513->pPrev);
printNode($100); --> printNode($100->pPrev);
printNode(NULL); -/- Stop Printing
```

---

I feel that I learned so much more about pointers in this assignment alone than I ever had back in High School or Community College. Not only that, but I surprised myself at how quickly I picked up on C. Sure, C++ is similar in some aspects and if I really wanted to, I could compile C code in C++ but I thought it was going to be harder (not to brag or anything). I am very happy with what I am learning at Wazzu so far and am hoping this trend continues for the next three years here!
