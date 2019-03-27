# sudoku_solver
A basic sudoku solver in C++ which uses forward checking in addition to backtracking. 

To create a valid file, take the sudoku puzzle you want to solve and write all empty spaces a 0s and all given numbers as themselves. There should be 9 rows of zeros and numbers in your file. Reference the puzzle.txt and puzzle2.txt files for reference. 

Pass the .txt file as a command-line argument when executing a.out.

Puzzle.txt is an easier puzzle whereas puzzle2.txt is significantly harder. Both puzzles were taken from https://www.websudoku.com/.

To compile, for now, use g++ board.hpp bpard.cpp solver.hpp solver.cpp main.cpp as the command. The makefile is incoming. 
