#include "solver.hpp"

Solver::Solver(Board &board)
{
	//Get all valid values given the initial board so that time is not wasted on clearly valid values. 
	getVals(board);

	//Each cell that only has one value must only be that one value. Thus treat these cells as givens on the board.
	for(auto &entry: consMap)
	{
		int row = entry.first.first;
		int col = entry.first.second;

		int valSize = consMap[std::make_pair(row, col)].size();
		if(valSize == 1)
		{
			board.insert_num(row, col, consMap[std::make_pair(row, col)][0]);
			consMap.erase(std::make_pair(row, col));
		}
	}

	//Iterator to go through each coordinate in order that they were inserted into the map. 
	std::map<std::pair<int, int>, std::vector<int> >::iterator starting_coord = consMap.begin();

	if(check_board_valid(board))
	{

		//Solve and return once finished. 
		solving_algo(board, starting_coord);

		if(!board.check_solved())
		{
			std::cout << "This sudoku is not possible!" << std::endl;
		}
	}
	else
	{
		std::cout << "Make sure your board is the right format!" << std::endl;
	}


}

bool Solver::check_board_valid(Board &board)
{
	for(int r = 0; r < board.board_vec.size(); r++)
	{
		if(board.board_vec[r].size() != 9)
		{
			return false;
		}
	}
	return true;
}

void Solver::solving_algo(Board &board, std::map<std::pair<int, int>, std::vector<int> >::iterator &coord)
{
	//Check that if the board has been solved first before continuing.
	if(board.check_solved() || solved)
	{
		solved = true;
		return;
	}
	
	int row = coord->first.first;
	int col = coord->first.second;
	for(int i = 0; i < consMap[std::make_pair(row, col)].size(); i++)
	{
		//Test the number first.
		board.insert_num(row, col, consMap[std::make_pair(row, col)][i]);

		//If its valid, prepare the next coordinate in the iterator and recur with the new board and coordinates as arguments. 
		if(board.check_validity())
		{
			auto next_coord = next(coord, 1);
			solving_algo(board, next_coord);
		}
		
		//If the insertion solves it, mark the puzzle as solved and return. 
		if(board.check_solved())
		{
			solved = true;
			return;
		}

		//At this point, the number does not work, so make the space become zero again and use the next number.
		board.zero_num(row, col);
	}

	//At this point, none of the numbers work so go back to the previous coordinates and try another number. 
	return;
}

void Solver::printConsMap()
{
	for(auto &entry: consMap)
	{
		std::cout << entry.first.first << ", " << entry.first.second << ": ";
		int valSize = consMap[std::make_pair(entry.first.first, entry.first.second)].size();
		for(int i = 0; i < valSize; i++)
		{
			std::cout<<consMap[std::make_pair(entry.first.first, entry.first.second)][i]<< ",";
		}
		std::cout << std::endl;
	}
}

void Solver::getVals(Board &board)
{
	//Iterate through the whole board and get the coordinates of all cells where the cell is zero.
	for(int r = 0; r < board.board_vec.size(); r++)
	{
		for(int c = 0; c < board.board_vec[r].size(); c++)
		{
			if(board.board_vec[r][c] == 0)
			{
				//Add the coordinate to the map and test all possible numbers to see if they are valid. 
				consMap.insert(std::pair<std::pair<int, int>, std::vector<int> >(std::make_pair(r, c), std::vector<int>()));
				for(int i = 1; i < 10; i++)
				{
					board.insert_num(r, c, i);
					if(board.check_validity())
					{
						consMap[std::make_pair(r,c)].push_back(i);
					}
					board.zero_num(r, c);
				}	
			}
		}
	}
}
