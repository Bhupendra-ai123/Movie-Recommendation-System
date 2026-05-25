🎬 Movie Recommendation System in C
Show Image
Show Image
Show Image
Show Image
A console-based Movie Recommendation System built in C using:

Singly Linked List — to store and manage movie records dynamically
Stack (Linked List-based) — to track every action and support unlimited Undo


📌 Features
FeatureDescription➕ Add MovieAdd title, genre, year dynamically using malloc🗑️ Delete MovieRemove a movie by ID; freed from memory🔍 Search MovieCase-insensitive title search📋 Display AllTabular view of all movies⭐ Rate MovieAssign a 0.0–10.0 rating👁️ Mark WatchedToggle watched status🏆 Top RatedShows top 5 highest-rated movies↩️ UndoReverses last Add / Delete / Rate / Watch action

🏗️ Project Structure
MovieRecommendationSystem/
├── src/
│   └── movie.c          ← All source code (single file)
├── docs/
│   ├── report.md        ← Full project report
│   └── github_guide_and_viva.md  ← GitHub steps + Viva Q&A
├── screenshots/         ← Add terminal output screenshots here
└── README.md

🚀 How to Compile and Run
On Linux / Mac
bashgcc src/movie.c -o movie
./movie
On Windows (MinGW)
bashgcc src/movie.c -o movie.exe
movie.exe
Using Makefile (optional)
bashmake
./movie

💡 Data Structures Used
Singly Linked List (for movies)
HEAD → [Movie1] → [Movie2] → [Movie3] → NULL
Each node stores: id, title, genre, year, rating, watched, *next
Stack (for undo — linked list based)
TOP → [Action3] → [Action2] → [Action1] → NULL
Push on every user action. Pop on Undo to reverse it.

📊 Sample Output
  ╔══════════════════════════════════════╗
  ║    MOVIE RECOMMENDATION SYSTEM       ║
  ╠══════════════════════════════════════╣
  ║  1. Add Movie                        ║
  ║  2. Delete Movie                     ║
  ║  3. Search Movie                     ║
  ║  4. Display All Movies               ║
  ║  5. Rate a Movie                     ║
  ║  6. Mark Movie as Watched            ║
  ║  7. Show Top Rated Movies            ║
  ║  8. Undo Last Action                 ║
  ║  0. Exit                             ║
  ╚══════════════════════════════════════╝
  Enter choice: 4

  ID    Title                      Genre          Year   Rating  Watched
  -------------------------------------------------------------------
  4     Parasite                   Thriller       2019   0.0     No
  3     Interstellar               Sci-Fi         2014   0.0     No
  2     The Dark Knight            Action         2008   0.0     No
  1     Inception                  Sci-Fi         2010   0.0     No

👥 Team Members & Contributions
MemberRoleFiles / CommitsMember 1Linked List ModuleaddMovie, deleteMovie, searchMovie, displayAllMember 2Stack Modulepush, pop, undoLastAction, freeAllMember 3UI & Testingmain(), menu, sample output, MakefileMember 4DocumentationREADME.md, report.md, GitHub management

🔧 Technologies Used

Language: C (C99 standard)
Compiler: GCC
IDE: VS Code / Code::Blocks / any text editor
Version Control: Git & GitHub


📚 Concepts Demonstrated

Dynamic memory allocation (malloc, free)
Singly Linked List (insert, delete, traverse, search)
Stack using linked list (push, pop, undo)
Enum for action types
Pointer manipulation in C
Error handling (NULL checks)


🔮 Future Scope

Save/load movies from a file (file I/O)
Genre-based filtering
Binary Search Tree for faster search
GUI using GTK or ncurses
Movie recommendation based on genre similarity


📄 License
This project is open source under the MIT License.
