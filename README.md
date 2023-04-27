# Squirrel Game
A simple game written in C language where the player controls a squirrel dodging spikes and jumping over walls. The goal is to get as many points as possible before running out of lives. Curently is woring ony on **Windows**

# Getting Started
This game can be played in a terminal, by running the compiled executable file. The player controls the squirrel with the arrow keys or 'w' and 's'. Press 'q' to quit the game.

# Prerequisites
This game requires a C compiler to be installed on the system.

# How to Play
Move the squirrel up and down to dodge the spikes and jump over the walls.
Collect points by jumping over the walls.
If the squirrel collides with a spike, one life is lost.
The game ends when all lives are lost.
Press 'q' to quit the game at any time.
![](https://github.com/Gecazo/red-squirrel/blob/main/screenshot.png)

# The game uses the following C libraries:

* **stdio.h** : for standard input/output operations.
* **stdlib.h** : for memory allocation and other general-purpose functions.
* **windows.h** : for using HANDLE to hide the cursor and changing console text color.
* **conio.h** : for keyboard input.
* **string.h** : for string manipulation functions.
The game logic is based on a game loop, which is executed continuously until the game is over. The loop includes functions to update the game state, handle user input, and display the game screen.

The game state includes the squirrel's position, the walls and spikes position and speed, the current score and number of lives, and the game over state.
