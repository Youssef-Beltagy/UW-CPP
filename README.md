# UW CPP

This program tests these system calls which are used in CSS courses at UWB:

-  open
- close
- read
- write
- lseek
- remove
- fork
- wait
- execlp
- dup2
- pipe 



It finds the number of occurrences of a word in treasure_island.txt. treasure_island.txt is the full text of the *Treasure Island* novel by Robert Louis Stevenson. I got it from the [Gutenberg project](http://www.gutenberg.org/ebooks/120).



If you haven't installed the g++ compiler, then run this in the terminal:

```shell
sudo apt update;
sudo apt upgrade;
sudo apt install build-essential;

```

Build the program with:

```
g++ -o main.out main.cpp

```

Run the program:

```
./main.out

```

If you want to count "fifteen men" (for example) instead of "Jim", pass a program argument like this:

```
./main.out "fifteen men"

```

I got 98 counts of "Jim" and 6 counts of "fifteen men". The search is case-insensitive.