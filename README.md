# Lab4-Maze
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
Two SCUBA diving buddies have encountered a large, box-shaped storage facility inside the hull of the Heian Maru, a 512' submarine tender lying on the bottom of Truk Lagoon at 108'. The storage facility is composed of 10' x 10' x 10' cells, some of which can be entered and some which cannot. The only exterior walls that are missing are on the front of the storage facility in the upper left corner, and on the rear of the storage facility in the lower right corner. The divers wish to determine a path through the storage facility.

## Requirements
You will need the files in this github repository to complete your lab.

### File 1 - Import Maze (25 points)
* For this part, you will need to implement your importMaze() and toString() functions.  The importMaze function is described in the PathfinderInterface.h file, but here are some things to note:
* You will be given a filename for each maze (you must keep the Mazes folder in the working directory of your project).  Valid files will contain representations of mazes, with each cell represented by a 0 or a 1.
* You must check to make sure that the given file contains valid maze information.  Each maze should consist of exactly 125 1's or 0's.  Mazes may be solvable or unsolvable.

### File 2 - Invalid Import (10 points)
* This test will check your importMaze() function to make sure that it properly rejects invalid mazes and filenames.  A maze is invalid if it consists of anything other than exactly 125 cells, each represented by either a 0 or a 1.
* Your current maze should not change during an invalid import.
* Your maze should consist of all 1's if no maze has yet been imported.

### File 3 - Solvable Mazes (35 points)
* This will test your algorithm against several solvable mazes.  Each given maze should be properly imported and solved as described in the PathfinderInterface.h file.
* A valid path is one which starts at the entrance (0, 0, 0) and ends at the exit (4, 4, 4) and does not contain any cycles. When moving between cells, the divers can only move up, down, left, right, forward, and backwards one cell at a time. No diagonals are allowed.

### File 4 - Unsolvable Mazes (20 points)
* This will test your algorithm against several unsolvable mazes.  

### File 5 - Generate Random Mazes (10 points)
* This will test your createRandomMaze() function and your solveMaze() function.  
* You will be required to generate several random mazes.  Because the mazes will be randomly generated, there is no key_file5 to compare against.  Rather, you should make sure that each generated maze is a valid maze.  Mazes will be tested by calling solveMaze() on the generated mazes.  You must return either a valid path or no path for each maze, and there should be several solvable mazes and several unsolvable mazes in the output.  If you have either no solvable mazes or unsolvable mazes, run the program again until several of each are generated.
* The TA will have to check to make sure your Random Mazes are correct during the verification phase of the lab grading and it will not be checked by the autograder.


## Requirement Notes
* You are required to write a seperate '.h' and '.cpp' for every class you implement.
* Strictly follow the formats explained in the interface provided. If not, your generated mazes and paths will not work with the test program we will use and your program will not work with the mazes we will use for Part 3. If there are problems with your lab due to format, you will not be able to pass off until the problems are resolved.
* For the createRandomMaze() to correctly generate random numbers, #include <cstdlib> and use rand().  You should call srand() exactly once when the Pathfinder is generated.
* The format of the Maze Files are as follows: each row and column of the first 2D layer correspond to the x and y dimensions, respectively. The layers of 2D arrays correspond to the z dimension.
* Visually, this is what your code is creating:
  
![](https://mjcleme.github.io/3DMaze.JPG)

