Maze Running Game

A multi-player terminal-based strategy game where players navigate a 3D maze across three floors. Players must manage their Movement Points (MP), handle random environmental effects from the Bawana area, and use stairs and poles to reach the flag first.
### Game Features

    3D Environment: A maze spanning 3 floors with active and inactive cells.

    Dynamic Movement: Movement is governed by a 6-sided dice and a direction system (North, South, East, West).

    Dynamic Stairs: Staircases can change directions (unidirectional, one-way up, or one-way down) every 5 rounds.

    Bawana Area: A special zone where players can receive MP boosts or negative status effects:

        Food Poisoning: Skips the player's next 3 turns.

        Disoriented: Forces random direction changes for 5 turns.

        Triggered: Doubles movement speed due to "bad food quality."

        Happy: Grants a massive 200 MP boost.

    Capture Mechanic: Landing on the same cell as another player sends them back to their starting position.

    Resource Management: Every move costs MP. If MP hits zero, you are transported to Bawana for replenishment.

### File Structure
File	Description
game.c	The main entry point. Handles turn logic, dice rolls, and player initialization.
board.c	Core logic for board generation, movement validation, and special cell effects.
draw.c	Handles the visual rendering of the maze floors in the terminal using ANSI colors.
board.h	Header file containing the position struct and function prototypes.
stairs.txt	Configuration for stair locations.
walls.txt	Configuration for wall boundaries.
poles.txt	Configuration for sliding poles.
flag.txt	Contains the coordinates for the winning flag.
### Installation & Setup

    Ensure you have a C compiler (GCC) installed.

    Create the necessary data files: Ensure stairs.txt, walls.txt, poles.txt, and flag.txt are in the same directory as the source code.

    Compile the game:
    Bash

gcc game.c board.c draw.c -o maze_game

Run the game:
Bash

    ./maze_game

### How to Play
1. Starting the Game

    Enter unique names for all three players.

    Choose a player tag (A, B, or C).

    To enter the maze, a player must roll a 6 on the movement dice.

2. Movement & Turns

    Every 4th turn, the direction dice rolls automatically to change your heading.

    The board is rendered after every round.

    [ ] (Green): Open path.

    [x] (Red): Wall/Blocked.

    [A/B/C] (Yellow): Player positions.

3. Winning

The first player to reach the coordinates defined in flag.txt is declared the winner.
### Technical Notes

    Randomization: The game uses time(NULL) to seed random events, ensuring a different experience each time.

    Terminal Formatting: Uses ANSI escape codes for colors and screen clearing. This is best played in a Linux/Unix-based terminal.

    MP Limit: Movement Points are capped at a maximum of 500.
