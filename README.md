### How to build and run
Download to your computer, go to the directory game_of_life/src, compile with -lncurses option and then run one of the patterns.
If you don't have ncurses library pre-installed go with "sudo apt-get install lib32ncurses-dev"
```
git clone https://github.com/sh-tanya/game_of_life.git
cd game_of_life/src
gcc -Wall -Werror -Wextra -lncurses game_of_life.c
./a.out > pattern1.txt
```
