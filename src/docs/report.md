Project Report
Movie Recommendation System Using Linked List and Stack in C

Course: Data Structures and Algorithms
Language: C (C99)
Submitted by: [Your Group Name]
Members: Member 1 | Member 2 | Member 3 | Member 4
Date: 2025

1. Introduction
A Movie Recommendation System is a software tool that helps users manage a personal collection of movies. This project implements a console-based version of such a system using two fundamental data structures: a Singly Linked List and a Stack.
The linked list allows the program to store an unlimited number of movies in dynamic memory without wasting space. The stack records every user action, enabling an Undo feature that can reverse any mistake — similar to Ctrl+Z in text editors.
This project is written entirely in C language and runs in a terminal. It demonstrates core concepts of data structures including dynamic memory allocation, pointer manipulation, and LIFO (Last In First Out) logic.

2. Objective

Implement a real-world application using a Singly Linked List
Use a Stack to provide Undo functionality for all user actions
Practice dynamic memory allocation with malloc and free
Build a working, menu-driven console interface in C
Learn team-based software development using Git and GitHub


3. Problem Statement
Traditional arrays in C have a fixed size decided at compile time. If we store movies in an array:

We may waste memory (if array is too large)
Or run out of space (if array is too small)
Deleting a movie requires shifting all elements

A linked list solves all three problems. Each movie node is allocated exactly when needed and freed when deleted.
Additionally, users make mistakes. Without an Undo feature, a deleted movie is lost forever. A stack maintains a history of actions so any mistake can be reversed instantly.

4. Data Structures Used
4.1 Singly Linked List
A singly linked list is a chain of nodes where each node contains data and a pointer to the next node.
Structure of each Movie node:
┌─────────────────────────────────────────┐
│ id | title | genre | year | rating |    │──→ next node
│ watched | *next                         │
└─────────────────────────────────────────┘

List in memory:
HEAD → [Inception,2010] → [Dark Knight,2008] → [Interstellar,2014] → NULL
Operations on the Linked List:
OperationTime ComplexityDescriptionAdd (at head)O(1)New node becomes the new headDelete by IDO(n)Traverse until ID found, re-link pointersSearch by titleO(n)Compare each node's titleDisplay allO(n)Traverse from head to NULL
4.2 Stack (for Undo)
The stack is implemented as a linked list of StackNode elements. Each node records what action was performed and enough data to reverse it.
Stack (LIFO — Last In, First Out):
After 3 actions:
TOP → [ACTION_RATE, id=1] → [ACTION_ADD, id=5] → [ACTION_DELETE, id=2] → NULL

After Undo:
TOP → [ACTION_ADD, id=5] → [ACTION_DELETE, id=2] → NULL
(rating of movie 1 is restored to its previous value)
Undo Logic by Action Type:
Action PerformedUndo OperationAdd MovieDelete that movieDelete MovieRe-add the movie with all its dataRate MovieRestore old ratingMark WatchedRestore old watched status

5. Algorithm
Add Movie
1. Allocate new Movie node using malloc
2. Check if malloc returned NULL (error handling)
3. Copy title, genre, year into the node
4. Set rating = 0.0, watched = 0
5. Set node->next = current head
6. Update head = new node
7. Push ACTION_ADD onto the undo stack
Delete Movie
1. Start from head, set prev = NULL
2. While current node is not NULL:
   a. If current->id == target ID:
      - Save data to undo stack (ACTION_DELETE)
      - If prev is NULL: head = current->next
      - Else: prev->next = current->next
      - free(current)
      - Return updated head
   b. prev = current, current = current->next
3. If not found: print error message
Search Movie
1. Start from head
2. While current != NULL:
   a. Compare current->title with search string (case-insensitive)
   b. If match: return pointer to this node
   c. Move to next node
3. Return NULL if not found
Undo
1. If stack is empty: print "Nothing to undo"
2. Else: pop top action
3. Switch on action type:
   - ADD:    find the movie by id, delete it (without re-pushing to stack)
   - DELETE: allocate new node, copy saved data, insert at head
   - RATE:   find movie, restore old_rating
   - WATCH:  find movie, restore old_watched
4. Free the popped StackNode

6. Flowchart
START
  │
  ▼
Show Menu
  │
  ▼
Read Choice ──→ 0 (Exit) ──→ Free all memory ──→ END
  │
  ├──→ 1: Add     ──→ malloc node ──→ insert at head ──→ push stack
  ├──→ 2: Delete  ──→ traverse ──→ re-link ──→ free ──→ push stack
  ├──→ 3: Search  ──→ traverse ──→ compare title ──→ print result
  ├──→ 4: Display ──→ traverse ──→ print each node
  ├──→ 5: Rate    ──→ find by id ──→ update rating ──→ push stack
  ├──→ 6: Watch   ──→ find by id ──→ watched=1 ──→ push stack
  ├──→ 7: Top     ──→ copy to array ──→ sort ──→ print top 5
  └──→ 8: Undo    ──→ pop stack ──→ reverse action
  │
  ▼
Loop back to Show Menu

7. Source Code Structure
All code is in a single file src/movie.c with four clearly marked sections:
SectionContentsSection 1Struct definitions (Movie, StackNode, ActionType enum)Section 2Stack operations (push, pop, isStackEmpty)Section 3Linked List operations (add, delete, search, display, rate, watch, undo, free)Section 4main() with menu loop

8. Sample Output
  ╔══════════════════════════════════════╗
  ║    MOVIE RECOMMENDATION SYSTEM       ║
  ╠══════════════════════════════════════╣
  Enter choice: 1
  Movie Title : Dune Part Two
  Genre       : Sci-Fi
  Release Year: 2024
  [OK] Movie "Dune Part Two" added successfully! (ID: 5)

  Enter choice: 5
  Enter Movie ID to rate: 5
  Enter Rating (0.0 - 10.0): 8.7
  [OK] Rated "Dune Part Two" = 8.7

  Enter choice: 8
  [UNDO] Rating of "Dune Part Two" restored to 0.0

  Enter choice: 7
  === TOP RATED MOVIES ===
  Rank  Title                      Genre          Rating
  -----------------------------------------------
  #1    Inception                  Sci-Fi         9.3
  #2    The Dark Knight            Action         8.8
  #3    Interstellar               Sci-Fi         8.6

9. Advantages

Dynamic size — no fixed limit on number of movies
Undo feature — every action is reversible
No database required — runs entirely in memory
Fast insertion — O(1) at head of linked list
Memory efficient — each node freed when deleted
Simple interface — menu-driven, no GUI required


10. Disadvantages

Data is lost when the program exits (no file storage)
Search is O(n) — slow for very large collections
No sorting of the main list (only for top-rated display)
Text-based UI only; no graphical interface


11. Technologies Used
TechnologyPurposeC Language (C99)Core programming languageGCC CompilerCompiling the C source codeGitVersion controlGitHubRemote repository and collaborationVS Code / Code::BlocksIDE for writing code

12. Future Scope

File I/O — Save and load movies from a .txt or .csv file so data persists between runs
Binary Search Tree — Replace linked list with BST for O(log n) search
Genre filter — Display only movies of a selected genre
Watchlist export — Print watched movies to a file
GUI — Build a graphical interface using GTK or ncurses
Recommendation engine — Suggest movies based on genre of highest-rated movies


13. Conclusion
This project successfully demonstrates the practical use of two fundamental data structures — Singly Linked List and Stack — in a real-world application. The Movie Recommendation System shows how dynamic memory allocation eliminates the limitations of fixed-size arrays, and how a stack can implement a powerful Undo feature with minimal additional code.
Through this project, all team members gained hands-on experience with pointer manipulation, struct design, dynamic memory management, and collaborative development using Git and GitHub. The contribution graph on GitHub reflects the individual work of each member across separate branches and pull requests.

14. References

Kernighan, B. W., & Ritchie, D. M. — The C Programming Language (2nd Ed.)
Cormen, T. H. et al. — Introduction to Algorithms (3rd Ed.)
GeeksforGeeks — Linked List in C: https://www.geeksforgeeks.org/linked-list-set-1-introduction/
GitHub Docs — https://docs.github.com
cppreference.com — C standard library reference
