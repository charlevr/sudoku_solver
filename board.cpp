#include <iostream>
#include "board.hpp"

Board::Board(char* fname)
{
	std::ifstream bfile(fname);
	std::string line;
	//Take each line and and turn it into a vector of ints. 
	if(bfile.is_open())
	{
		int v = 0;
		int vecsize = 9;
		while(getline(bfile, line))
		{
			board_vec.push_back(std::vector<int>());

			for(int i = 0 ; i < line.length(); i++)
			{
				board_vec[v].push_back((int)line[i] - 48);
			}
			v++;
		}
	}

	
}

void Board::print_board()
{
	for(int i = 0; i < board_vec.size(); i++)
	{
		for(int j = 0; j < board_vec[i].size(); j++)
		{
			std::cout << board_vec[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Board::insert_num(int x, int y, int num)
{
	/*
	if(board_vec[x][y] != 0)
	{ return; }
	*/
	board_vec[x][y] = num;
}

void Board::zero_num(int x, int y)
{
	board_vec[x][y] = 0;
}

bool Board::is_unique(const std::vector<int> &vec)
{
	for(int i = 0; i < vec.size(); i++)
	{
		if(vec[i] != 0)
		{
			int elem_count = std::count(vec.begin(), vec.end(), vec[i]);
			if (elem_count > 1){ return false; }
		}
	}
	return true;
}

bool Board::check_region(int x, int y)
{
	//Take an x, y < 3 and take its corresponding 3x3 square, turn it into a vector and check uniqueness.
	//For example, square (1, 1) is the middle 3x3 square.
	 
	std::vector<int> square_vec;
	for(int r = 3*x; r < (3*(x+1)); r++)
	{
		for(int c = 3*y; c < (3*(y+1)); c++)
		{
			square_vec.push_back(board_vec[r][c]);
		}
	}

	if(!Board::is_unique(square_vec))
	{
	//	std::cout << "Probem on region " << x << ", " << y << std::endl;
		return false;
	}
	return true;	
}

bool Board::check_validity()
{
	for(int r = 0; r < board_vec.size();r++)
	{
		if(!Board::is_unique(board_vec[r]))
		{
	//		std::cout << "Problem in row " << r << std::endl;
			return false; 
		
		}
	}

	for(int i = 0; i < board_vec.size(); i++)
	{
		std::vector<int> col_vec;
		for(int j = 0; j < board_vec[i].size(); j++)
		{
			col_vec.push_back(board_vec[j][i]);
		}
		
		if(!Board::is_unique(col_vec))
		{ 
	//		std::cout << "Problem on column " << i << std::endl;
			return false; 
		}
	}

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(!Board::check_region(i, j))
			{
				return false;
			}
		}
	}
	return true;
}

bool Board::check_solved()
{
	//If there are any zeros, then the board must not be solved. 
	for(int v = 0; v < board_vec.size(); v++)
	{
		int zero_count = std::count(board_vec[v].begin(), board_vec[v].end(), 0);
		if(zero_count > 0)
		{
	//		std::cout << "There is a zero on row "  << v << std::endl;
			return false;
		}
	}

	if(!check_validity())
	{
	//	std::cout << "Board is not valid." << std::endl;
		return false;
	}

	return true;
}
