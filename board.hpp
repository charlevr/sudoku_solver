#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <utility>

class Board
{
public:
	Board();

	//Contructor which take a file and creates an interface that C++ can interact with. 
	Board(char* fname);

	//Prints the current sudoku board.
	void print_board();

	//Inserts a number at coordinates (x, y)
	void insert_num(int x, int y, int num);

	//Makes a space at coordinates (x, y) equal to zero.
	void zero_num(int x, int y);

	//Checks if all numbers in the vector are unique. 
	bool is_unique(const std::vector<int> &vec);

	//Checks if the board so far is valid i.e. there are no broken rules.
	bool check_validity();

	//Checks if a region is valid (the 3x3 square on the board).
	bool check_region(int x, int y);

	//Checks if the puzzle has been solved. 
	bool check_solved();
//private:
	//The sudoku puzzle represented as a 2d vector. 
	std::vector<std::vector<int> > board_vec;
};
