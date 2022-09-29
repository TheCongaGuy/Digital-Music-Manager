# Digital Music Manager
This program simulates a Digital Music Manager through a csv file containing data on various songs in a playlist. For this assignment I had to really get comfortable at managing and allocating memory in the heap with `malloc()`, a library method I had never used before. While it was a bit tricky to understand at first especially with `Node**` syntax, I found it fascinating with what you can do with a few pointers. This forced me to get quite comfortable with pointers and how they can be used.

---
## Loading List
This program works around a csv file working as our memory; everything changed in the playlist will be saved to this csv file, and everything loaded into the program will be from this csv file.

| Artist          | Album Title | Song Title    | Genre | Song Length | Times Played  | Rating  |
| :---:           | :---:       | :---:         | :---: | :---:       | :---:         | :---:   |
| "Swift, Taylor" | 1989        | Shake it Off  | Pop   | 3:35        | 12            | 3       |

Before we can modify our playlist we first need to load it into our program. Above is an example line of data that would come in through the csv file. How I went about parsing this data and inserting it into their respective fields was using a combination of `strtok()` and `strchr()` to find segments of data. `strtok()` would separate the strings into tokens to be used, but look at the song length column. There is no clean way to simply convert that into a set of integers.
```
// Impossible
musicData.length = atoi(strtok(NULL, ","));
```
Instead, we need to look for the separation of the two integers, the ":" in this case. We can't take that entire value out in one go, but we can separate it into two tokens and assign the values that way. A similar problem occurs with the Artist field. Using `strtok()` won't work here because we will either pick up on the quotation marks, or only get the first name. We can use `strchr()` to check for these characters and parse accordingly to be able to insert any field.

---
## Editing List
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

Next is searching the list. I can't do what I did with `printList()` by recursively going through the list, so I needed to adopt a different approach. I needed to search by the artist's name, but one big problem is when there are multiple entries by one artist. Drake is the artist behind *Own It* and *The Motto* but I can't return two addresses. I also can't assume that the user only wants the first or last occurrence of that artist. This might not be the most time efficient approach but my solution was to count how many songs were published by the target artist, ask the user for which song they wanted and go through the list again, counting the instances of that artist to finally arrive at the desired node.

```
searchList($100, "Drake"); --> 1) $513(Own It) | 2) $312(The Motto)
printf(both options);
scanf(for user input, either a 1 or a 2); --> User chooses 1
searchList($100, "Drake"); --> 1) $513(Own It) -/-
return $513;
```
We also needed to save any changes done to the list back to the file. Since we already had a print list method, we could use that to print to the csv file. However, printing in the same order we have been would actually reverse the playlist we have created. Since we don't want to reverse the playlist at the last second, I chose to simply print the list in reverse; starting at the end of the program and working my way to the front.

```
savePlayList($100); --> Loop through until end --> $312
printNode($312); --> Move backwards --> printNode($312->pPrev);
printNode($513); --> printNode($513->pPrev);
printNode($100); --> printNode($100->pPrev);
printNode(NULL); -/- Stop Printing
```
---

## Manipulating List

Deleting and Inserting nodes was fairly straightforward, especially with all of our previously defined methods. We would use `searchListTitle()` in delete to find our node, reassign their neighbors pointers to reference each other, and free the space on the heap. Insertion is just as simple. Create a new Record and populate it with data from the user, and use our `insertFront()` method to slap it into the list.

Where things get complicated are with the sort and shuffle commands. In both cases we need to traverse through the list and side step around to either print the list or re-arrange the list itself. To start, I focused on sort. I had to pick a sorting method for the linked list and while there are many to choose from, none of them I could implement were super efficient (with my skill level). I chose to go with insertion sort; finding the first discrepancy in order and moving the node backward in the list until the order is restored and continue to move forward from that point.

| 1     | 3     | 4     | 5     | 2     |
| :---: | :---: | :---: | :---: | :---: |

```
Move through the list until interruption
1->3->4->5->(2)-/
Swap backwards until order restored
5 !< 2    =>    1-3-4-(2)-5
4 !< 2    =>    1-3-(2)-4-5
3 !< 2    =>    1-(2)-3-4-5
Move through the list from 2 until interruption
2->3->4->5->(NULL)
List is now sorted
```
With a time complexity of O(n<sup>2</sup>) it isn't the best option out there but with my level of experience in C I feel that it suffices. I feel the only other way would be a recursive merge sort but that could get very ugly very quickly dealing with all those separate linked lists.

With shuffle on the other hand, I felt that the only way to dynamically shuffle the list (without making an array of indexes `int example[1000000000000]`) was to create a buffer list. This does temporarily take space in the heap, but nowhere near as much space as a 1000 item array. Additionally, this memory is dynamic and can grow to the size of the original list. Besides, once the shuffle option is done executing we free whatever space was taken by the buffer list. First we grab the length of the list by looping through each item in the list until we hit a `pNext == NULL`, meaning we have reached the end of our list. Each time we move onto a new item, we increment a counter.

Now that we have the size of our list, we generate random numbers up to that size, and clamped between 0 and the size. We also check for any repeating numbers and discard those. With our new list of indexes, all we have to do is shift down from the head of the list until we reach the index, add that node to the buffer list and repeat. When we're done, we can `play()` the buffer list and be done!

---

I feel that I learned so much more about pointers in this assignment alone than I ever had back in High School or Community College. Not only that, but I surprised myself at how quickly I picked up on C. Sure, C++ is similar in some aspects and if I really wanted to, I could compile C code in C++ but I thought it was going to be much harder. I am very happy with what I am learning at Wazzu so far and am hoping this trend continues for the next three years here!
