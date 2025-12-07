# Multi-Sport Scoreboard

A console-based application written in C that functions as a digital scoreboard for multiple sports. This project allows users to track scores, manage game states, and determine winners for Badminton, Volleyball, Tennis, Basketball, and Cricket.

## Features

- **Multi-Sport Support**:
  - **Badminton**: Standard scoring with deuce logic (win by 2 points).
  - **Volleyball**: Standard scoring (first to 25, win by 2).
  - **Tennis**: Traditional scoring system (15, 30, 40) with deuce handling using array mapping.
  - **Basketball**: Manual score entry (1, 2, or 3 points) and game reset functionality.
  - **Cricket**: Detailed scorecard generation including runs, balls, wickets, and overs.
- **Interactive Menu**: Easy-to-use text-based menu to switch between sports.
- **Real-time Updates**: Displays current scores and server information after every point.

## Key C Features Used

This project demonstrates various fundamental concepts of the C programming language:

- **Modular Programming**: The project is split into multiple source files (`badminton.c`, `tennis.c`, etc.) and integrated into `main.c` to maintain code organization.
- **Control Flow**:
  - **Loops**: Extensive use of `while(1)` loops for continuous game states and menu navigation.
  - **Conditional Statements**: Complex `if-else` logic to handle scoring rules, deuce conditions, and winning criteria.
  - **Switch-Case**: Used for the main menu selection and specific game actions (like in Basketball).
  - **Jump Statements**: Usage of `break` to exit loops when a game ends and `continue` to handle invalid inputs.
- **Input/Output Handling**:
  - Standard I/O using `printf` and `scanf`.
  - **Buffer Management**: Custom `clearInputBuffer()` function to handle newline characters left in the input stream, preventing skipped inputs.
- **Data Structures**:
  - **Arrays**: Used for storing player names (strings) and mapping tennis scores (`0, 15, 30, 40`).
  - **Variables**: Integer tracking for scores and flags.
- **Operators**:
  - **Ternary Operator**: Used for concise conditional logic when displaying the current server (e.g., `(n == 1) ? np1 : np2`).
  - **Logical Operators**: Complex conditions (e.g., `&&`, `||`) to determine win states.

## Getting Started

### Prerequisites

- A C compiler (GCC recommended).

### Compilation

The project is structured such that the sport-specific modules are included directly into the main file. To build the project, compile `main.c`.

```bash
gcc main.c -o scoreboard