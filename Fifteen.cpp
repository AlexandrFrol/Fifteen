#include <iostream>
#include <ctime>
#include <conio.h>
#include <vector>
#include <Windows.h>

int c_menu_selection = -1, c_max_menu = 0, temp_max_menu = 0;

std::string ReturnKey()
{
	int key = _getch();

	std::string str_key = "";
	str_key += key;

	switch (key)
	{
	case 224:
	{
		int arrow_key = _getch();
		if (arrow_key == 72) { return "up"; }
		if (arrow_key == 75) { return "left"; }
		if (arrow_key == 80) { return "down"; }
		if (arrow_key == 77) { return "right"; }
	}
	case 13: return "enter";
	case 27: return "escape";
	default: return str_key;
	}
}

template<typename T>
void MenuDisplay(bool vertical, T t)
{
	if (c_menu_selection == temp_max_menu)
	{
		std::cout << '[' << t << ']';
		if (vertical == true)
			std::cout << std::endl;
		else
			std::cout << "   ";
	}
	else
	{
		std::cout << ' ' << t << ' ';
		if (vertical == true)
			std::cout << std::endl;
		else
			std::cout << "   ";
	}
	c_max_menu = temp_max_menu;
	temp_max_menu = 0;
}
template<typename T, typename ...Args> 
void MenuDisplay(bool vertical, T t, Args... arg)
{
	if (c_menu_selection == temp_max_menu)
	{
		std::cout << '[' << t << ']';
		if (vertical == true)
			std::cout << std::endl;
		else
			std::cout << "   ";
	}
	else
	{
		std::cout << ' ' << t << ' ';
		if (vertical == true)
			std::cout << std::endl;
		else
			std::cout << "   ";
	}
	temp_max_menu++;
	MenuDisplay(vertical, arg...);
}
template<typename T, typename ...Args>
void Menu(std::string title, std::string bottom, bool vertical, T t, Args... arg)
{
	std::string key;
	while (true)
	{
		system("cls");

		std::cout << title;
		MenuDisplay(vertical, t, arg...);
		std::cout << bottom;

		key = ReturnKey();

		if (vertical == true)
		{
			if (key == "up")
				c_menu_selection--;
			else if (key == "down")
				c_menu_selection++;
		}
		else
		{
			if (key == "left")
				c_menu_selection--;
			else if (key == "right")
				c_menu_selection++;
		}

		if (key == "enter")
		{
			return;
		}
		if (key == "escape")
		{
			c_menu_selection = c_max_menu;
			return;
		}

		if (c_menu_selection < 0)
			c_menu_selection = c_max_menu;
		else if (c_menu_selection > c_max_menu)
			c_menu_selection = 0;
	}
}

bool OFBCheck(int sz_y, int sz_x, int select_y, int select_x)
{
	if (select_y >= sz_y || select_y < 0 || select_x >= sz_x || select_x < 0)
		return true;
	else
		return false;
}

bool CheckWin(int** arr, int size)
{
	int max_value = size * size;
	for (int y = 0, counter = 1; y < size; y++)
	{
		for (int x = 0; x < size; x++, counter++)
		{
			if (counter == max_value && arr[y][x] == 0)
				return true;
			if (arr[y][x] != counter)
				return false;
		}
	}
}

std::vector<int> all_moves;

void FifteenGame()
{
	bool user_scramble = false;
	int field_size = 4, turns = 0;

	while (c_menu_selection != c_max_menu)
	{
		Menu("// Выбор размера поля\n", "", true, "3x3", "4x4", "Выход");
		switch (c_menu_selection)
		{
			case 0:
			{
				system("cls");
				field_size = 3;
				c_menu_selection = c_max_menu;
				break;
			}
			case 1:
			{
				system("cls");
				field_size = 4;
				c_menu_selection = c_max_menu;
				break;
			}
			default: break;
		}
	}

	c_menu_selection = 0;
	int current_y = field_size - 1, current_x = field_size - 1;
	int** field = new int* [field_size];

	for (int y = 0, count = 1; y < field_size; y++)
	{
		field[y] = new int[field_size];
		for (int x = 0; x < field_size; x++)
		{
			field[y][x] = count;
			count++;
		}
	}
	field[field_size - 1][field_size - 1] = 0;

	while (c_menu_selection != c_max_menu)
	{
		Menu("// Scramble mode\n", "", true, "User", "Computer", "Exit");
		switch (c_menu_selection)
		{
			case 0:
			{
				system("cls");
				user_scramble = true;
				c_menu_selection = c_max_menu;
				break;
			}
			case 1:
			{
				system("cls");
				user_scramble = false;
				c_menu_selection = c_max_menu;
				break;
			}
		default: break;
		}
	}

	c_menu_selection = 0;

	std::string pkey;

	if (user_scramble == false)
	{
		int random_moves_amount = rand() % 80 + 20;
		int random_move = 0;
		for (int i = 0; i < random_moves_amount; i++)
		{
			random_move = rand() % 4;
			switch (random_move)
			{
			case 0:
			{
				if (OFBCheck(field_size, field_size, current_y - 1, current_x) == false)
				{
					std::swap(field[current_y][current_x], field[current_y - 1][current_x]);
					current_y--;
					all_moves.push_back(0);
				}
				break;
			}
			case 1:
			{
				if (OFBCheck(field_size, field_size, current_y, current_x - 1) == false)
				{
					std::swap(field[current_y][current_x], field[current_y][current_x - 1]);
					current_x--;
					all_moves.push_back(1);
				}
				break;
			}
			case 2:
			{
				if (OFBCheck(field_size, field_size, current_y + 1, current_x) == false)
				{
					std::swap(field[current_y][current_x], field[current_y + 1][current_x]);
					current_y++;
					all_moves.push_back(2);
				}
				break;
			}
			case 3:
			{
				if (OFBCheck(field_size, field_size, current_y, current_x + 1) == false)
				{
					std::swap(field[current_y][current_x], field[current_y][current_x + 1]);
					current_x++;
					all_moves.push_back(3);
				}
				break;
			}
			}
		}
		while (current_y != field_size - 1)
		{
			std::swap(field[current_y][current_x], field[current_y + 1][current_x]);
			current_y++;
			all_moves.push_back(2);
		}
		while (current_x != field_size - 1)
		{
			std::swap(field[current_y][current_x], field[current_y][current_x + 1]);
			current_x++;
			all_moves.push_back(3);
		}
	}
	else
	{
		while (user_scramble == true)
		{
			if (_kbhit())
			{
				pkey = ReturnKey();
				if (pkey == "w")
				{
					if (OFBCheck(field_size, field_size, current_y - 1, current_x) == false)
					{
						std::swap(field[current_y][current_x], field[current_y - 1][current_x]);
						current_y--;
						all_moves.push_back(0);
					}
				}
				if (pkey == "a")
				{
					if (OFBCheck(field_size, field_size, current_y, current_x - 1) == false)
					{
						std::swap(field[current_y][current_x], field[current_y][current_x - 1]);
						current_x--;
						all_moves.push_back(1);
					}
				}
				if (pkey == "s")
				{
					if (OFBCheck(field_size, field_size, current_y + 1, current_x) == false)
					{
						std::swap(field[current_y][current_x], field[current_y + 1][current_x]);
						current_y++;
						all_moves.push_back(2);
					}
				}
				if (pkey == "d")
				{
					if (OFBCheck(field_size, field_size, current_y, current_x + 1) == false)
					{
						std::swap(field[current_y][current_x], field[current_y][current_x + 1]);
						current_x++;
						all_moves.push_back(3);
					}
				}
				if (pkey == "f")
				{
					user_scramble = false;
				}
			}

			printf("\x1b[H");


			for (int y = 0; y < field_size; y++)
			{
				for (int x = 0; x < field_size; x++)
				{
					if (field[y][x] != 0 && field[y][x] < 10) { std::cout << "  [" << field[y][x] << " ]  "; }
					else if (field[y][x] != 0 && field[y][x] > 9) { std::cout << "  [" << field[y][x] << "]  "; }
					else { std::cout << "  [  ]  "; }

				}
				if (y == 2) { std::cout << "  -- Закончить перемешку: f --"; }
				std::cout << '\n';
			}
			std::cout << "y " << current_y << "   x " << current_x;

			Sleep(100);
		}
		
	}
	
	system("cls");

	bool assembly = false;
	bool win = false;
	time_t msec_timer = clock();

	while (win == false)
	{
		if (clock() - msec_timer > 100)
		{
			if (_kbhit())
			{
				pkey = ReturnKey();
				if (pkey == "w")
				{
					if (OFBCheck(field_size, field_size, current_y - 1, current_x) == false)
					{
						std::swap(field[current_y][current_x], field[current_y - 1][current_x]);
						current_y--;
						turns++;
						all_moves.push_back(0);
					}
				}
				if (pkey == "a")
				{
					if (OFBCheck(field_size, field_size, current_y, current_x - 1) == false)
					{
						std::swap(field[current_y][current_x], field[current_y][current_x - 1]);
						current_x--;
						turns++;
						all_moves.push_back(1);
					}
				}
				if (pkey == "s")
				{
					if (OFBCheck(field_size, field_size, current_y + 1, current_x) == false)
					{
						std::swap(field[current_y][current_x], field[current_y + 1][current_x]);
						current_y++;
						turns++;
						all_moves.push_back(2);
					}
				}
				if (pkey == "d")
				{
					if (OFBCheck(field_size, field_size, current_y, current_x + 1) == false)
					{
						std::swap(field[current_y][current_x], field[current_y][current_x + 1]);
						current_x++;
						turns++;
						all_moves.push_back(3);
					}
				}
				if (pkey == "f")
				{
					assembly = true;
					break;
				}
			}

			printf("\x1b[H");


			for (int y = 0; y < field_size; y++)
			{
				for (int x = 0; x < field_size; x++)
				{
					if (field[y][x] != 0 && field[y][x] < 10) { std::cout << "  [" << field[y][x] << " ]  "; }
					else if (field[y][x] != 0 && field[y][x] > 9) { std::cout << "  [" << field[y][x] << "]  "; }
					else { std::cout << "  [  ]  "; }

				}
				if (y == 0) { std::cout << "  -- Time: " << msec_timer / 1000 << " --"; }
				if (y == 1) { std::cout << "  -- Turns: " << turns << " --"; }
				if (y == 2) { std::cout << "  -- F for auto assembly"; }
				std::cout << '\n';
			}
			std::cout << "y " << current_y << "   x " << current_x;

			win = CheckWin(field, field_size);

			msec_timer = clock();

		}		
	}


	int current_move = all_moves.size() - 1;
	while (assembly == true)
	{
		if (clock() - msec_timer > 100)
		{
			system("cls");
			switch (all_moves[current_move])
			{
			case 0: // w
			{
				std::swap(field[current_y][current_x], field[current_y + 1][current_x]);
				current_y++;
				break;
			}
			case 1: // a
			{
				std::swap(field[current_y][current_x], field[current_y][current_x + 1]);
				current_x++;
				break;
			}
			case 2: // s
			{
				std::swap(field[current_y][current_x], field[current_y - 1][current_x]);
				current_y--;
				break;
			}
			case 3: // d
			{
				std::swap(field[current_y][current_x], field[current_y][current_x - 1]);
				current_x--;
				break;
			}
			}
			current_move--;

			for (int y = 0; y < field_size; y++)
			{
				for (int x = 0; x < field_size; x++)
				{
					if (field[y][x] != 0 && field[y][x] < 10) { std::cout << "  [" << field[y][x] << " ]  "; }
					else if (field[y][x] != 0 && field[y][x] > 9) { std::cout << "  [" << field[y][x] << "]  "; }
					else { std::cout << "  [  ]  "; }

				}
				std::cout << '\n';
			}
			std::cout << "y " << current_y << "   x " << current_x;


			if (current_move == -1)
				break;

			msec_timer = clock();
		}
	}

	for (int y = 0; y < field_size; y++)
	{
		delete[] field[y];
	}
	delete[] field;
	field = nullptr;

	std::cout << "\nAssembled in " << msec_timer / 1000 << " seconds\nTurns: " << turns;
	if (assembly == true)
		std::cout << "  [Assembled by computer]";
	std::cout << "\n\n";

	system("pause");

}

int main()
{
	srand(time(0));
	system("cls");

	std::cout << " Controls \n\n Arrows: Element movement \n Enter: interact\n Esc: Return/Exit\n\n";
	Sleep(1000);
	system("pause");

	while (c_menu_selection != c_max_menu)
	{
		Menu("// Fifteen\n", "", true, "Play", "Exit");
		switch (c_menu_selection)
		{
			case 0:
			{
				system("cls");
				FifteenGame();
				break;
			}
			default:
			{
				break;
			}
		}
	}	

	return 0;
}