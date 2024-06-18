# Bubble Trouble Clone

The project is my adaptation of the premise of a browser game from my childhood, "Bubble Trouble",
in which the player must destroy all the balls while avoiding them.
The game engine was created using the SDL2 library.

## Installation

So far, I've been using CLion's built-in compiler using CMake.
For this reason, at this time I am unable to provide CLI instructions .

## Controls

### First player

* Key Left - move left
* Key Right - move right
* Key Up - thrust

### Second Player

* Key A - move left
* Key D - move right
* Key W - thrust

## Rules

* The goal of the game is to destroy all the balls with the spear, when this is done a new level begins.
* During the game you have to avoid the balls, so they don't hit you, if they touch you, you lose one of your lives.
* You start the game with three lives, when the number of lives drops to zero you lose and have to start the game again.

## Tools used

* C++
* CMake
* SDL2