#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

typedef std::string direction;

typedef struct command {
	direction dir;
	int value;
} command;

typedef struct coords {
	coords()
	{
		xcoord = 0;
		depth = 0;
	}

	int xcoord;
	int depth;
} coords;

auto get_commands_from_input_file(const std::string& input_file_path)
{
	auto input_commands = std::vector<command>();
	auto input_stream = std::ifstream(input_file_path);
	for (std::string line; std::getline(input_stream, line); )
	{
		command line_command;
		line_command.dir = line.substr(0, line.find(" "));
		line_command.value = std::stoi(line.substr(line.find(" ") + 1));
		input_commands.push_back(line_command);
	}

	return input_commands;
}

auto move_submarine_part1(const std::vector<command>& input_commands)
{
	auto submarine = coords();
	for(auto& command : input_commands)
	{
		if(command.dir == "down")
		{
			submarine.depth += command.value;
		}
		else if (command.dir == "up")
		{
			submarine.depth -= command.value;
		}
		else
		{
			submarine.xcoord += command.value;
		}
	}
	return submarine;
}

auto move_submarine_part2(const std::vector<command>& input_commands)
{
	auto submarine = coords();
	auto aim = 0;
	for(auto& command : input_commands)
	{
		if(command.dir == "down")
		{
			aim += command.value;
		}
		else if (command.dir == "up")
		{
			aim -= command.value;
		}
		else
		{
			submarine.xcoord += command.value;
			submarine.depth += command.value * aim;
		}
	}
	return submarine;
}

int main(int argc, char *argv[])
{
	if (argc != 2) { return EXIT_FAILURE; }
	else
	{
		// Getting the full path of the input file
		std::string current_path = std::filesystem::current_path().string();
		std::string input_file_path = current_path + "/" + argv[1];

		auto final_submarine_coords_part1 = move_submarine_part1(get_commands_from_input_file(input_file_path));
		auto final_submarine_coords_part2 = move_submarine_part2(get_commands_from_input_file(input_file_path));

		std::cout << final_submarine_coords_part1.xcoord * final_submarine_coords_part1.depth << '\n';
		std::cout << final_submarine_coords_part2.xcoord * final_submarine_coords_part2.depth << '\n';
	}
	return EXIT_SUCCESS;
}
