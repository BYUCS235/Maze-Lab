# Maze Lab
Exploring a 3D maze

## Purpose
This lab will help you gain experience with recursion so that you are more comfortable using this powerful tool.

## Video
This 
[video](https://youtu.be/IzNTe-8Vw14) 
should help you to understand the problem.
This
[video](https://youtu.be/T2o5vfLv9fA) 
should help you solve the problem by hand so you can get your code to do the same.


## Background
Two SCUBA diving buddies have encountered a large, box-shaped storage facility inside the hull of the Heian Maru, a 512' submarine tender lying on the bottom of Truk Lagoon at 108'. The storage facility is composed of large, cubic cells, some of which can be entered and some which cannot. The only exterior walls that are missing are on the front of the storage facility in the upper left corner, and on the rear of the storage facility in the lower right corner. The divers wish to determine a path through the storage facility.

Visually, this is what your code is creating:
  
![](https://mjcleme.github.io/3DMaze.JPG)

## Requirements

Write a command-line program that takes solves a 3D maze. The first argument is the maze file and the second argument is the file to which the solution will be written. For example, if you name your program executable `maze`, then the following command

```bash
./maze maze1.txt maze1-solution.txt
```

should read the file `maze1.txt` and write the solution to the maze in the file `maze1-solution.txt`.

### What do I turn in?

You must turn in a file named `maze.cpp` and any custom header files you `#include` in `maze.cpp`.

You should compile and run `validate.cpp` on each of your solutions before submitting to Gradescope.

### Maze format

The first line of the maze file indicates the dimensions of the maze: number of rows, number of columns, number of levels.

The layout of each level is presented. Each level starts with an empty line, then an n_rows by n_columns block of text. `1` indicates a passable space, while `0` indicates a blocked space. A solution to the maze can only go through passable spaces. 

The rows are numbered 0 to n_rows from top to bottom. The columns are numbered 0 to n_columns from left to right. The levels are numbered 0 to n_levels starting with the first level in the file to the last level in the file. 

The maze solution will always start at (0, 0, 0) and end at (n_rows-1, n_columns-1, n_levels-1) (i.e. the opposite corner of the maze). 

### Solution format

If the maze has no solution, print `NO SOLUTION` on the first line of the output file and exit.

If the maze has a solution, print `SOLUTION` on the first line of the output file. Then print the coordinates of the solution, one coordinate per line, starting with `0 0 0` (separate each coordinate by a space).

### Example

**Maze**

```
3 4 3

1 1 0 0
0 1 0 0
0 1 1 0

0 0 0 0
0 0 0 0
0 0 1 0

0 0 0 0
0 0 0 0
0 0 1 1
```

**Solution**

```
SOLUTION
0 0 0
0 1 0
1 1 0
2 1 0
2 2 0
2 2 1
2 2 2
2 3 2
```

### Testing your program

You are provided with the mazes that you will be graded on in the `mazes` folder.

You can compile `validate.cpp` and run it to test whether a given solution is valid.

```bash
./validate maze1.txt maze1-solution.txt
```

You will need the files in this github repository to complete your lab.

## Tips

You may find the following tips helpful.
  
### Recursion

If your recursive calls in different directions are in separate statements, for example:

```c++
bool left = findMazePath(x + 1, y, z);
bool right = findMazePath(x - 1, y, z);
bool up = findMazePath(x, y + 1, z);
//…
if (left || right || up /*… etc */ ) {
```

This can cause the function to take multiple valid paths if both directions in a fork can lead to the exit, but we only want one path in our solution. Try making the calls directly in one if statement, like this:

```c++
if (findMazePath(x + 1, y, z) || findMazePath(x - 1, y, z) || findMazePath(x, y + 1, z) /*… etc */ ) {
```

That way it will stop making further recursive calls from this spot as soon as one direction finds a path.

### Getting started

If you haven't done the Recursive Maze Exploration activity, PLEASE DO IT. It will help IMMENSELY on this lab. It works great as starter code.

### The brilliance of data structures

In this lab, you need to represent the data in memory. What strategy can you use?

#### 3D Array

One option could be to represent the maze as a 3D array (or nested vectors). 
Because the dimensions of a given maze are not known until runtime, you have to put this array on the heap (use `new`).
Loading the array would look something like:

```c++
int*** grid = new int**[NL];
for (int lev = 0; lev < NL; lev++) {
  grid[lev] = new int*[NR];
  for (int row = 0; row < NR; row++) {
    grid[lev][row] = new int[NC];
      for (int col = 0; col < NC; col++) {
        fin >> grid[lev][row][col];
      }
  }
}
```

and accessing a value now looks like:

```c++
if (grid[lev][row][col] == 1) { ... }
```

#### Map

Maybe you notice that once you have loaded the grid, all you actually do with it is get and set values based on a (r, c, l) triple.
Essentially, you want these two methods:

```c++
int get(int row, int col, int lev);
void set(int row, int col, int lev, int value);
```

So, you could create a class called `Grid` that delegates to a map:

```c++
class Grid {
  private:
  map<list<int>, int> _grid;
  public:
  int get(int row, int col, int lev) {
    return _grid[{row, col, lev}];
  }
  /* ... other methods for initializing the Grid from an istream, etc. */
}
```

And now when using the grid:
```c++
if (grid.get(row, col, lev) == 1) { ... }
```

#### Vector

Well, if all you need to do is implement a Grid class with `get` and `set` and `friend void operator >>(istream& ins, Grid& grid)`,
you could simply use a linear vector with a little indexing math:

$index = lev \cdot NR \cdot NC + row \cdot NC + col$

For example:

```
2 3 2

A B C
D E F

G H I
J K L
```

Is stored linearly as
```
A B C D E F G H I J  K  L
0 1 2 3 4 5 6 7 8 9 10 11
```

What value is at `(1, 1, 1)`?

$index = 1 \cdot 2 \cdot 3 + 1 \cdot 3 + 1 = 6 + 3 + 1 = 10$

`K` is at `(1, 1, 1)`.

So, the `Grid` class could instead be something like:

```c++
class Grid {
private:
    vector<int> _grid;
    int NR, NC, NL;
    int _index(int row, int col, int lev) {
        return lev * NR * NC + row * NC + col;
    }
public:
    int get(int row, int col, int lev) {
        return _grid[_index(row, col, lev)];
    }
    /* etc. */
    friend istream& operator >>(istream &ins, Grid& grid) {
        ins >> grid.NR >> grid.NC >> grid.NL;
        int value;
        for (int i = 0; i < grid.NR * grid.NC * grid.NL; i++) {
            ins >> value;
            grid._grid.push_back(value);
        }
        return ins;
    }
}
```

## Above and beyond

If you are looking for an additional challenge:

- Write a separate program that generates random mazes (taking the dimensions as arguments on the command line)
- Write a separate program that finds all possible paths
  - Just be careful that nothing (i.e. your computer) explodes when there are too many solutions!
  - It might be a good idea to take an upper-limit parameter on how many solutions you will allow the program to find
    - How many solutions are there in a 3 x 3 x 3 all-1 maze? How about a 4 x 4 x 4 all-1 maze? How about a 10 x 10 x 10 all-1 maze?
- Write a separate program that solves a maze and prints the solution using the input maze format but with `x` indicating the spaces in the path.
- How can you organize your code into various `.cpp` and `.h` files to support both the assignment solution as well as these additional programs?
