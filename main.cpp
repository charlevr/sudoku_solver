#include "solver.hpp"
#include <iostream>
#include <cstdio>
#include <ctime>


int main(int argc, char* argv[])
{
	Board *board = new Board(argv[1]);
	board->print_board();

	std::clock_t start;
	double dur;
	start = std::clock();

	Solver *solver = new Solver(*board);
	
	dur = (std::clock() - start)/ (double)CLOCKS_PER_SEC;
	std::cout << "time taken: " << dur << std::endl;	
	board->print_board();
}
