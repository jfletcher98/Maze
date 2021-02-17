# Maze
A simple maze program

##Makefile
A way to quickly compile the cpp and h files. Just use command "make" in directory.

##Maze.cpp
This file holds the logic of constructing the board, getting allowedMoves, Moving the actual Player, Creating a new game,
Taking turns, status of game.

##Maze.h
Header file of maze that also includes the enum SquareType that holds the possible types a square can have. This is also where
the 2D array of type SquareType is defined.

##Player.cpp
This file holds the logic of moving the player, getting the players position, setting the position, and the relative position of
another coordiante.

##Player.h
This is where the struct Position is defined that holds both a row and column. I use this struct through out the program to
retrieve squareType values, set a new location for a player/enemy, and recieve information of other Squaretypes nearby.


