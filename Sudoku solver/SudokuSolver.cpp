#include <iostream>

enum { _ = -1 };

struct Puzzle
{
	int data[9][9];
} puzzle =
{
	{
		{ _, _, 8, _, _, _, _, _, _ },
		{ _, _, 6, 9, 2, _, _, _, 3 },
		{ 9, _, _, _, _, 6, _, _, _ },
		{ 2, 6, _, _, _, 7, _, _, _ },
		{ _, 1, _, 5, 9, 4, _, 6, _ },
		{ _, _, _, 6, _, _, _, 1, 9 },
		{ _, _, _, 3, _, _, _, _, 4 },
		{ 6, _, _, _, 1, 8, 5, _, _ },
		{ _, _, _, _, _, _, 2, _, _ },
	}
};

bool check(const Puzzle &puzzle)
{
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
			for (int k = j + 1; k < 9; ++k)
			{
				if (puzzle.data[i][j] != _ && puzzle.data[i][j] == puzzle.data[i][k])
					return false;
				if (puzzle.data[j][i] != _ && puzzle.data[j][i] == puzzle.data[k][i])
					return false;
				if (puzzle.data[j % 3 + (i % 3) * 3][j / 3 + (i / 3) * 3] != _ &&
					puzzle.data[j % 3 + (i % 3) * 3][j / 3 + (i / 3) * 3] ==
					puzzle.data[k % 3 + (i % 3) * 3][k / 3 + (i / 3) * 3])
					return false;
			}
	return true;
}

bool findSolution(Puzzle &puzzle)
{
	int x = -1;
	int y = -1;
	int min = 10;
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j)
		{
			if (puzzle.data[i][j] == _)
			{
				int c = 0;
				for (int k = 1; k <= 9; ++k)
				{
					puzzle.data[i][j] = k;
					if (check(puzzle))
						++c;
					puzzle.data[i][j] = _;
				}
				if (min > c)
				{
					min = c;
					x = i;
					y = j;
				}
			}
		}
	if (x == -1)
		return true;
	for (int k = 1; k <= 9; ++k)
	{
		puzzle.data[x][y] = k;
		if (check(puzzle))
			if (findSolution(puzzle))
				return true;
	}
	puzzle.data[x][y] = _;
	return false;
}

int main()
{
	if (findSolution(puzzle))
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
				std::cout << puzzle.data[i][j] << " ";
			std::cout << std::endl;
		}
	}
	else
		std::cout << "No solution\n";
	system("pause");
	return 0;
}