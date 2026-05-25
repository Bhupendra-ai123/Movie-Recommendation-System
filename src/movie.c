
/*
 * ============================================================
 *   MOVIE RECOMMENDATION SYSTEM
 *   Language  : C (C99)
 *   Concepts  : Singly Linked List + Stack (Undo)
 *   Author    : Group Project
 * ============================================================
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* ============================================================
   SECTION 1 — DATA STRUCTURES
   ============================================================ */
 
/* ---------- Movie Node (Linked List) ---------- */
typedef struct Movie {
    int   id;
    char  title[100];
    char  genre[50];
    int   year;
    float rating;     /* 0.0 – 10.0 */
    int   watched;    /* 0 = No, 1 = Yes */
    struct Movie* next;
} Movie;
 
/* ---------- Action Types for Undo Stack ---------- */
typedef enum {
    ACTION_ADD,
    ACTION_DELETE,
    ACTION_RATE,
    ACTION_WATCH
} ActionType;
 
/* ---------- Stack Node ---------- */
typedef struct StackNode {
    ActionType type;
    int        id;
    char       title[100];
    char       genre[50];
    int        year;
    float      old_rating;
    int        old_watched;
    struct StackNode* next;
} StackNode;
 
/* ---------- Stack (top pointer) ---------- */
StackNode* stackTop = NULL;
 
/* ============================================================
   SECTION 2 — STACK OPERATIONS
   ============================================================ */
 
/* Push a new action onto the stack */
void push(ActionType type, int id, char* title, char* genre,
          int year, float old_rating, int old_watched) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    if (!node) { printf("Memory error!\n"); return; }
    node->type        = type;
    node->id          = id;
    node->year        = year;
    node->old_rating  = old_rating;
    node->old_watched = old_watched;
    strcpy(node->title, title ? title : "");
    strcpy(node->genre, genre ? genre : "");
    node->next = stackTop;
    stackTop   = node;
}
 
/* Pop the top action from the stack */
StackNode* pop() {
    if (!stackTop) return NULL;
    StackNode* top = stackTop;
    stackTop = stackTop->next;
    return top;
}
 
/* Check if stack is empty */
int isStackEmpty() { return stackTop == NULL; }
 
/* ============================================================
   SECTION 3 — LINKED LIST OPERATIONS
   ============================================================ */
 
/* --- Add movie at the front of the list --- */
Movie* addMovie(Movie* head, int id, char* title,
                char* genre, int year) {
    Movie* node = (Movie*)malloc(sizeof(Movie));
    if (!node) { printf("Memory allocation failed!\n"); return head; }
    node->id      = id;
    node->year    = year;
    node->rating  = 0.0f;
    node->watched = 0;
    strcpy(node->title, title);
    strcpy(node->genre, genre);
    node->next = head;
    /* Push to undo stack */
    push(ACTION_ADD, id, title, genre, year, 0.0f, 0);
    printf("\n  [OK] Movie \"%s\" added successfully! (ID: %d)\n", title, id);
    return node;
}
 
/* --- Delete movie by ID --- */
Movie* deleteMovie(Movie* head, int id) {
    Movie *curr = head, *prev = NULL;
    while (curr) {
        if (curr->id == id) {
            /* Save info for undo before deleting */
            push(ACTION_DELETE, curr->id, curr->title,
                 curr->genre, curr->year, curr->rating, curr->watched);
            if (!prev) head = curr->next;
            else       prev->next = curr->next;
            printf("\n  [OK] Movie \"%s\" deleted.\n", curr->title);
            free(curr);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("\n  [!] Movie with ID %d not found.\n", id);
    return head;
}
 
/* --- Search movie by title (case-insensitive) --- */
Movie* searchMovie(Movie* head, char* title) {
    Movie* curr = head;
    while (curr) {
        if (strcasecmp(curr->title, title) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}
 
/* --- Display all movies --- */
void displayAll(Movie* head) {
    if (!head) { printf("\n  [!] No movies in the system.\n"); return; }
    printf("\n  %-5s %-26s %-14s %-6s %-7s %-8s\n",
           "ID", "Title", "Genre", "Year", "Rating", "Watched");
    printf("  -------------------------------------------------------------------\n");
    Movie* curr = head;
    while (curr) {
        printf("  %-5d %-26s %-14s %-6d %-7.1f %-8s\n",
               curr->id, curr->title, curr->genre,
               curr->year, curr->rating,
               curr->watched ? "Yes" : "No");
        curr = curr->next;
    }
}
 
/* --- Rate a movie --- */
Movie* rateMovie(Movie* head, int id, float rating) {
    Movie* curr = head;
    while (curr) {
        if (curr->id == id) {
            push(ACTION_RATE, id, curr->title, curr->genre,
                 curr->year, curr->rating, curr->watched);
            curr->rating = rating;
            printf("\n  [OK] Rated \"%s\" = %.1f\n", curr->title, rating);
            return head;
        }
        curr = curr->next;
    }
    printf("\n  [!] Movie ID %d not found.\n", id);
    return head;
}
 
/* --- Mark movie as watched --- */
Movie* markWatched(Movie* head, int id) {
    Movie* curr = head;
    while (curr) {
        if (curr->id == id) {
            push(ACTION_WATCH, id, curr->title, curr->genre,
                 curr->year, curr->rating, curr->watched);
            curr->watched = 1;
            printf("\n  [OK] \"%s\" marked as watched!\n", curr->title);
            return head;
        }
        curr = curr->next;
    }
    printf("\n  [!] Movie ID %d not found.\n", id);
    return head;
}
 
/* --- Display top-rated movies (simple selection sort display) --- */
void displayTopRated(Movie* head) {
    if (!head) { printf("\n  [!] No movies to show.\n"); return; }
 
    /* Count movies */
    int count = 0;
    Movie* curr = head;
    while (curr) { count++; curr = curr->next; }
 
    /* Copy pointers into array */
    Movie** arr = (Movie**)malloc(count * sizeof(Movie*));
    if (!arr) { printf("Memory error!\n"); return; }
    curr = head;
    for (int i = 0; i < count; i++) { arr[i] = curr; curr = curr->next; }
 
    /* Bubble sort by rating descending */
    for (int i = 0; i < count - 1; i++)
        for (int j = 0; j < count - i - 1; j++)
            if (arr[j]->rating < arr[j+1]->rating) {
                Movie* tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }
 
    printf("\n  === TOP RATED MOVIES ===\n");
    printf("  %-5s %-26s %-14s %-7s\n", "Rank", "Title", "Genre", "Rating");
    printf("  -----------------------------------------------\n");
    int limit = count < 5 ? count : 5;
    for (int i = 0; i < limit; i++)
        printf("  #%-4d %-26s %-14s %.1f\n",
               i+1, arr[i]->title, arr[i]->genre, arr[i]->rating);
    free(arr);
}
 
/* --- Undo last action --- */
Movie* undoLastAction(Movie* head) {
    if (isStackEmpty()) {
        printf("\n  [!] Nothing to undo.\n");
        return head;
    }
    StackNode* last = pop();
    switch (last->type) {
        case ACTION_ADD:
            /* Undo add = delete the movie (without pushing to stack again) */
            {
                Movie *curr = head, *prev = NULL;
                while (curr) {
                    if (curr->id == last->id) {
                        if (!prev) head = curr->next;
                        else       prev->next = curr->next;
                        printf("\n  [UNDO] Removed \"%s\"\n", curr->title);
                        free(curr);
                        break;
                    }
                    prev = curr; curr = curr->next;
                }
            }
            break;
        case ACTION_DELETE:
            /* Undo delete = re-add the movie */
            {
                Movie* node = (Movie*)malloc(sizeof(Movie));
                if (node) {
                    node->id      = last->id;
                    node->year    = last->year;
                    node->rating  = last->old_rating;
                    node->watched = last->old_watched;
                    strcpy(node->title, last->title);
                    strcpy(node->genre, last->genre);
                    node->next = head;
                    head = node;
                    printf("\n  [UNDO] Restored \"%s\"\n", last->title);
                }
            }
            break;
        case ACTION_RATE:
            /* Undo rate = restore old rating */
            {
                Movie* curr = head;
                while (curr) {
                    if (curr->id == last->id) {
                        curr->rating = last->old_rating;
                        printf("\n  [UNDO] Rating of \"%s\" restored to %.1f\n",
                               curr->title, curr->rating);
                        break;
                    }
                    curr = curr->next;
                }
            }
            break;
        case ACTION_WATCH:
            /* Undo watch = mark as unwatched */
            {
                Movie* curr = head;
                while (curr) {
                    if (curr->id == last->id) {
                        curr->watched = last->old_watched;
                        printf("\n  [UNDO] \"%s\" watch status restored.\n",
                               curr->title);
                        break;
                    }
                    curr = curr->next;
                }
            }
            break;
    }
    free(last);
    return head;
}
 
/* --- Free all memory on exit --- */
void freeAll(Movie* head) {
    while (head) {
        Movie* tmp = head;
        head = head->next;
        free(tmp);
    }
    while (!isStackEmpty()) {
        StackNode* tmp = pop();
        free(tmp);
    }
}
 
/* ============================================================
   SECTION 4 — MAIN MENU
   ============================================================ */
 
int main() {
    Movie* head  = NULL;
    int    nextId = 1;
    int    choice;
 
    char  title[100], genre[50];
    int   id, year;
    float rating;
 
    /* Preload some sample movies */
    head = addMovie(head, nextId++, "Inception",       "Sci-Fi",  2010);
    head = addMovie(head, nextId++, "The Dark Knight",  "Action",  2008);
    head = addMovie(head, nextId++, "Interstellar",     "Sci-Fi",  2014);
    head = addMovie(head, nextId++, "Parasite",         "Thriller",2019);
 
    do {
        printf("\n");
        printf("  ╔══════════════════════════════════════╗\n");
        printf("  ║    MOVIE RECOMMENDATION SYSTEM       ║\n");
        printf("  ╠══════════════════════════════════════╣\n");
        printf("  ║  1. Add Movie                        ║\n");
        printf("  ║  2. Delete Movie                     ║\n");
        printf("  ║  3. Search Movie                     ║\n");
        printf("  ║  4. Display All Movies               ║\n");
        printf("  ║  5. Rate a Movie                     ║\n");
        printf("  ║  6. Mark Movie as Watched            ║\n");
        printf("  ║  7. Show Top Rated Movies            ║\n");
        printf("  ║  8. Undo Last Action                 ║\n");
        printf("  ║  0. Exit                             ║\n");
        printf("  ╚══════════════════════════════════════╝\n");
        printf("  Enter choice: ");
        scanf("%d", &choice);
        getchar(); /* flush newline */
 
        switch (choice) {
 
            case 1:
                printf("  Movie Title : "); fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                printf("  Genre       : "); fgets(genre, 50, stdin);
                genre[strcspn(genre, "\n")] = 0;
                printf("  Release Year: "); scanf("%d", &year); getchar();
                head = addMovie(head, nextId++, title, genre, year);
                break;
 
            case 2:
                printf("  Enter Movie ID to delete: ");
                scanf("%d", &id); getchar();
                head = deleteMovie(head, id);
                break;
 
            case 3:
                printf("  Enter title to search: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = 0;
                {
                    Movie* found = searchMovie(head, title);
                    if (found)
                        printf("\n  [FOUND] ID:%d | %s (%d) | Genre:%s | Rating:%.1f | Watched:%s\n",
                               found->id, found->title, found->year,
                               found->genre, found->rating,
                               found->watched ? "Yes" : "No");
                    else
                        printf("\n  [!] Movie \"%s\" not found.\n", title);
                }
                break;
 
            case 4:
                displayAll(head);
                break;
 
            case 5:
                printf("  Enter Movie ID to rate: ");
                scanf("%d", &id); getchar();
                printf("  Enter Rating (0.0 - 10.0): ");
                scanf("%f", &rating); getchar();
                if (rating < 0.0f || rating > 10.0f)
                    printf("\n  [!] Rating must be between 0.0 and 10.0\n");
                else
                    head = rateMovie(head, id, rating);
                break;
 
            case 6:
                printf("  Enter Movie ID to mark watched: ");
                scanf("%d", &id); getchar();
                head = markWatched(head, id);
                break;
 
            case 7:
                displayTopRated(head);
                break;
 
            case 8:
                head = undoLastAction(head);
                break;
 
            case 0:
                printf("\n  Goodbye! Happy watching!\n\n");
                break;
 
            default:
                printf("\n  [!] Invalid choice. Try again.\n");
        }
 
    } while (choice != 0);
 
    freeAll(head);
    return 0;
}
