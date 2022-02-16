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

## Tips
  These tips have been helpful to students in past semesters.
  
1. Differences in file 2 after trying to import invalid mazes

Make sure the maze is set to all 1’s by default (can do a triple for loop in the Pathfinder constructor)

If we realize part way through reading a file that the maze is invalid, the previous maze should remain intact. One way to do this is to read the file into a temporary maze array, and only once we make it past all our checks do we then copy the temporary maze into the real maze.

 

2. Maze has been altered

The test driver expects the maze array to not be permanently changed by the solveMaze function. However we do need to place markers during the recursive solve function to mark where we’ve been. You can either run the recursive function on a different array which is a copy of the real maze array, or just loop through the maze after you’re done with the recursive function and change any 2’s or other markers back to 1.

3. Invalid paths

The test driver expects this order: (column number, row number, layer number) in the coordinate strings, make sure these correspond when you build the coordinate strings to put in the solution.

 

If you solve the first maze but then the paths start to get suspiciously long and jump from (4, 4, 4) to (0, 0, 0) in the middle, most likely the solution vector is piling up all the old solutions from previous calls to solveMaze(). Try calling solutionVector.clear(); at the beginning of your solveMaze()

 

4. If you’re getting jumps in your coordinates:

Make sure that your recursive function ends up pushing the current coordinates for every return true, and does not include the coordinates from any return false branch.

 

If your recursive calls in different directions are in separate statements, for example:

bool left = findMazePath(x + 1, y, z);

bool right = findMazePath(x - 1, y, z);

bool up = findMazePath(x, y + 1, z);

//…

if (left || right || up /*… etc */ ) {

 

This can cause the function to take multiple valid paths if both directions in a fork can lead to the exit, but we only want one path in our solution. Try making the calls directly in one if statement, like this:

if (findMazePath(x + 1, y, z) || findMazePath(x - 1, y, z) || findMazePath(x, y + 1, z) /*… etc */ ) {

That way it will stop making further recursive calls from this spot as soon as one direction finds a path.

5. Solution vector matches the one in the key_file, but details.txt still says it's wrong

Make sure your solution vector has the correct syntax. It HAS to be (0, 0, 0). If it's (0,0,0) (basically without spaces after the commas) it will show up as incorrect.

6. Where do I start?

If you haven't done the Recursive Maze Exploration activity, PLEASE DO IT. It will help IMMENSELY on this lab. It works great as starter code.

7. There are so many files for this lab, which ones do I actually need?

You need ALL of the files downloaded from github. That includes check.sh, file.txt, key_file.txt, etc. ALL OF THEM. And they need to be in the SAME FOLDER as the rest of your code.

8. My file2.txt/Invalid3.txt isn't passing. Why?

Import the maze into a maze of your own creation in importMaze(). AFTER it passes all of the test cases, copy that maze over into your class maze (usually called maze_grid). This will require a triple nested for loop (like in your toString()). This will help you pass file2.txt, specifically Invalid3.txt.

9. I want to pass a copy of the maze into findPath(), but my findPath() function only takes in coordinates

If your findPath() doesn't already take a maze in as a parameter, then you can change it so it does. This is because findPath()/find_maze_path() is what we call a helper function: it's a private function that we created outside of the interface file to help a different function (solveMaze() in this case) complete the task. It should look something like this:

findPath(int mazeGrid[LEVEL_SIZE][ROW_SIZE][COL_SIZE], int level, int row, int col);

Make sure you change it both in your Pathfinder.h file and in your Pathfinder.cpp.

10. Gradescope said that my createRandomMaze() function created the same maze and to contact an instructor or TA. How do I fix that?

If you submit to Gradescope and it says createRandomMaze() created the same maze repeatedly (usually accompanied by the "contact your instructor or a TA" statement), make sure you called initialize_random_seed() in your constructor for Pathfinder.

11. I can't get my file2.txt/Invalid4.txt to pass

The reason Invalid4.txt often fails is because your program will look at "1a" and only take the "1" while ignoring the "a." This is because you told it to grab an integer, and since the compiler sees an int first, it takes only that.

There are a few ways to fix this:

You can check whether the individual value you're importing from the file is valid. A great way to do this is through stringstream's fail() function: https://www.cplusplus.com/reference/sstream/stringstream/

You can also import individual values as strings instead of ints. Then have a condition that compares the string you imported to "1" and "0".

12. I’m failing on file2.txt/Invalid5.txt, but I have a condition checking whether the values are 1’s or 0’s. Why would it be failing?

If your test case for whether all the values are 0's or 1's is failing (tested in file2.txt with Invalid5.txt), make sure your condition is NOT "if (value != 1 || value != 0). This is incorrect logic. The compiler will read this as (when value = 1): "1 != 0" and return false when you don't want it to. A && might help instead.

13. How do I test whether a maze is too big or small?

If you're struggling to test whether a maze is too small/big, understanding file's eof() feature might help: https://www.cplusplus.com/reference/ios/ios/eof/

There are so many files for this lab! What do they all mean?

This lab is set up such that:

file1.txt, file2.txt, etc. are the TEST FILES. The provided main.cpp will open those for you.

key_file1.txt, key_file2.txt, etc. are the KEY FILES. They show the output you should be getting.

out_file1.txt, out_file2.txt, etc. are CREATED BY YOUR MAIN. These are used to hold the output your program gives.

details.txt is created/updated by running bash check.sh. DETAILS.TXT WILL NOT UPDATE IF YOU DON'T COMPILE AND RUN YOUR PROGRAM THEN RUN THE BASH COMMAND.

14. Which functions does each file test?

Here's an overview of which functions the test files test:
- file1.txt tests your toString() and importMaze() functions. IT DOES NOT TEST SPECIAL CASES IN THE IMPORTMAZE FUNCTION. It only tests whether it can correctly open the file or return false when the file doesn't exist.
- file2.txt tests the special cases in your importMaze(): input is an int, input is 1 or 0, maze is too small, maze is too big, maze's exit/entrance points are 1
- file3.txt tests solveMaze() and findPath(): whether findPath() finds the correct path through a solvable maze
- file4.txt tests solveMaze() and findPath(): whether the maze is solvable
- file5.txt tests createRandomMaze()

15. How do I know which test cases I'm failing?

The "Mazes" folder contains the mazes your code is testing. Each file/out_file says which maze it is testing. If you're not sure why your code is failing that test case, look at the maze that it is failing on. That will help you understand which test case you need to work on.

The invalid mazes in Mazes folder test these special cases:
- Invalid1.txt: maze is too small
- Invalid2.txt: maze is too big
- Invalid3.txt: exit point is not 1
- Invalid4.txt: input is not an int (fail()ed)
- Invalid5.txt: input is not a 0 or 1

16. Why does my maze have an extra row of 0's where it shouldn't?

If the maze that you imported is printing a row of 0's where you shouldn't be, that's almost always a getline() issue. You need more than one getline() in importMaze(): one to retrieve each row of ints and one to retrieve the blank line in between each block of the maze.
