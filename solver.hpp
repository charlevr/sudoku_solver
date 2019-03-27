#include "board.hpp"
class Solver
{
public:
	Solver();

	//Constructor which solves the sudoku puzzle at time of contruction.
	Solver(Board &board);

	bool check_board_valid(Board &board);

	//Gets all valid values for each cell. Done so that automatically invalid values are discarded. 
	void getVals(Board &board);

	//Prints map of all values that satisfy each cell's constraints.
	void printConsMap();

	//Forward-checking and backtracking algorithm that solves the puzzle itself. 
	void solving_algo(Board &board, std::map<std::pair<int, int>, std::vector<int> >::iterator &coord);

//private:
	//A C++ map that stores the coordinates of a cell as keys with their valid values as values.
	//Maps a std::pair of ints to a std::vector of ints for ease of access.  
	std::map<std::pair<int, int>, std::vector<int> > consMap;

	//Flag to check whether or not puzzle has been solved. 
	bool solved = false;
};
