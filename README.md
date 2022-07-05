# Game of Life
Conway's Game of Life simulates the birth and death of cells through generations.

The universe of the Game of Life is an infinite, two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, live or dead (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

Any live cell with fewer than two live neighbours dies, as if by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
These rules, which compare the behavior of the automaton to real life, can be condensed into the following:

Any live cell with two or three live neighbours survives.
Any dead cell with three live neighbours becomes a live cell.
All other live cells die in the next generation. Similarly, all other dead cells stay dead.

### How to build and run
Download to your computer, go to the directory game_of_life/src, compile with -lncurses option and then run one of the patterns.
If you don't have ncurses library pre-installed go with "sudo apt-get install lib32ncurses-dev"
```
git clone https://github.com/sh-tanya/game_of_life.git
cd game_of_life/src
gcc -Wall -Werror -Wextra -lncurses game_of_life.c
./a.out > pattern1.txt
```
